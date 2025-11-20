#include "maze_storage.h"

#include <string.h>

#include "iodefine.h"

#define DATA_FLASH_BASE_ADDRESS      (0x00100000u)
#define DATA_FLASH_BLOCK_SIZE        (1024u)
#define MAZE_STORAGE_BLOCK_INDEX     (0u)
#define MAZE_STORAGE_BLOCK_ADDRESS   (DATA_FLASH_BASE_ADDRESS + (MAZE_STORAGE_BLOCK_INDEX * DATA_FLASH_BLOCK_SIZE))
#define FCU_COMMAND_AREA             ((volatile uint8_t *)0x007F0000u)
#define DATA_FLASH_WRITE_UNIT        (4u)
#define DATA_FLASH_WAIT_TIMEOUT      (600000u)
#define MAZE_STORAGE_MAGIC           (0x4D415A45u) /* 'MAZE' */

typedef struct
{
    uint32_t magic;
    uint16_t crc;
    uint16_t length;
    maze_storage_snapshot_t payload;
} maze_storage_image_t;

static volatile const maze_storage_image_t * const g_flash_image =
    (volatile const maze_storage_image_t *)MAZE_STORAGE_BLOCK_ADDRESS;

static uint16_t maze_storage_crc16(const uint8_t *data, uint32_t length);
static void data_flash_enter_pe_mode(void);
static void data_flash_exit_pe_mode(void);
static void data_flash_enable_block_access(void);
static void data_flash_disable_block_access(void);
static void data_flash_reset(void);
static bool data_flash_wait_ready(void);
static bool data_flash_erase_block(uint32_t address);
static bool data_flash_program_bytes(uint32_t address, const uint8_t *data, uint32_t length);
static bool maze_flash_matches(const maze_storage_image_t *image);

bool maze_storage_load(maze_storage_snapshot_t *snapshot)
{
    if (snapshot == NULL)
    {
        return false;
    }

    const maze_storage_image_t *image = (const maze_storage_image_t *)g_flash_image;

    if (image->magic != MAZE_STORAGE_MAGIC)
    {
        return false;
    }

    if (image->length != (uint16_t)sizeof(image->payload))
    {
        return false;
    }

    if (maze_storage_crc16((const uint8_t *)&image->payload, sizeof(image->payload)) != image->crc)
    {
        return false;
    }

    memcpy(snapshot, &image->payload, sizeof(*snapshot));
    return true;
}

bool maze_storage_save(const maze_storage_snapshot_t *snapshot)
{
    if (snapshot == NULL)
    {
        return false;
    }

    maze_storage_image_t image;
    image.magic = MAZE_STORAGE_MAGIC;
    image.length = (uint16_t)sizeof(image.payload);
    memcpy(&image.payload, snapshot, sizeof(image.payload));
    image.crc = maze_storage_crc16((const uint8_t *)&image.payload, sizeof(image.payload));

    if (maze_flash_matches(&image))
    {
        return true;
    }

    if (!data_flash_erase_block(MAZE_STORAGE_BLOCK_ADDRESS))
    {
        return false;
    }

    if (!data_flash_program_bytes(MAZE_STORAGE_BLOCK_ADDRESS, (const uint8_t *)&image, sizeof(image)))
    {
        return false;
    }

    return true;
}

void maze_storage_clear(void)
{
    data_flash_erase_block(MAZE_STORAGE_BLOCK_ADDRESS);
}

static uint16_t maze_storage_crc16(const uint8_t *data, uint32_t length)
{
    uint16_t crc = 0xFFFF;

    while (length-- != 0u)
    {
        crc ^= (uint16_t)(*data++ << 8);
        for (uint8_t i = 0; i < 8u; i++)
        {
            if ((crc & 0x8000u) != 0u)
            {
                crc = (uint16_t)((crc << 1) ^ 0x1021u);
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

static void data_flash_enter_pe_mode(void)
{
    FLASH.FWEPROR.BIT.FLWE = 0x01;
    FLASH.FENTRYR.WORD = 0xAA80;
}

static void data_flash_exit_pe_mode(void)
{
    FLASH.FENTRYR.WORD = 0x0000;
    FLASH.FWEPROR.BIT.FLWE = 0x02;
}

static void data_flash_enable_block_access(void)
{
    FLASH.DFLWE0.WORD = (uint16_t)(0xA500u | (1u << MAZE_STORAGE_BLOCK_INDEX));
}

static void data_flash_disable_block_access(void)
{
    FLASH.DFLWE0.WORD = 0xA500u;
}

static void data_flash_reset(void)
{
    FLASH.FRESETR.WORD = 0xA507u;
}

static bool data_flash_wait_ready(void)
{
    uint32_t timeout = DATA_FLASH_WAIT_TIMEOUT;

    while ((FLASH.FSTATR0.BIT.FRDY == 0u) && (timeout-- > 0u))
    {
        /* busy wait */
    }

    if (FLASH.FSTATR0.BIT.FRDY == 0u)
    {
        data_flash_reset();
        return false;
    }

    if ((FLASH.FSTATR0.BIT.ILGLERR != 0u) ||
        (FLASH.FSTATR0.BIT.ERSERR != 0u) ||
        (FLASH.FSTATR0.BIT.PRGERR != 0u))
    {
        data_flash_reset();
        return false;
    }

    return true;
}

static bool data_flash_erase_block(uint32_t address)
{
    bool result;

    data_flash_enter_pe_mode();
    data_flash_enable_block_access();

    FCU_COMMAND_AREA[0] = 0x20u;
    *((volatile uint8_t *)address) = 0xD0u;

    result = data_flash_wait_ready();

    data_flash_disable_block_access();
    data_flash_exit_pe_mode();

    return result;
}

static bool data_flash_program_bytes(uint32_t address, const uint8_t *data, uint32_t length)
{
    bool result = true;
    uint8_t buffer[DATA_FLASH_WRITE_UNIT];

    data_flash_enter_pe_mode();
    data_flash_enable_block_access();

    while (length > 0u)
    {
        uint32_t copy = (length >= DATA_FLASH_WRITE_UNIT) ? DATA_FLASH_WRITE_UNIT : length;

        memcpy(buffer, data, copy);
        if (copy < DATA_FLASH_WRITE_UNIT)
        {
            memset(&buffer[copy], 0xFF, DATA_FLASH_WRITE_UNIT - copy);
        }

        FCU_COMMAND_AREA[0] = 0xE8u;
        FCU_COMMAND_AREA[0] = DATA_FLASH_WRITE_UNIT;

        for (uint32_t i = 0; i < DATA_FLASH_WRITE_UNIT; i++)
        {
            *((volatile uint8_t *)(address + i)) = buffer[i];
        }

        FCU_COMMAND_AREA[0] = 0xD0u;

        if (!data_flash_wait_ready())
        {
            result = false;
            break;
        }

        address += DATA_FLASH_WRITE_UNIT;
        data += copy;
        length -= copy;
    }

    data_flash_disable_block_access();
    data_flash_exit_pe_mode();

    return result;
}

static bool maze_flash_matches(const maze_storage_image_t *image)
{
    const maze_storage_image_t *flash = (const maze_storage_image_t *)g_flash_image;

    if (flash->magic != image->magic)
    {
        return false;
    }

    if (flash->length != image->length)
    {
        return false;
    }

    if (flash->crc != image->crc)
    {
        return false;
    }

    if (memcmp(&flash->payload, &image->payload, sizeof(image->payload)) != 0)
    {
        return false;
    }

    return true;
}
