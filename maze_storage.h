#ifndef MAZE_STORAGE_H
#define MAZE_STORAGE_H

#include <stdbool.h>
#include <stdint.h>

#define MAZE_STORAGE_WIDTH   16U
#define MAZE_STORAGE_HEIGHT  16U

typedef struct
{
    uint8_t pos_x;
    uint8_t pos_y;
    uint8_t head;
    uint8_t reserved;
    uint8_t map[MAZE_STORAGE_WIDTH][MAZE_STORAGE_HEIGHT];
} maze_storage_snapshot_t;

bool maze_storage_load(maze_storage_snapshot_t *snapshot);
bool maze_storage_save(const maze_storage_snapshot_t *snapshot);
void maze_storage_clear(void);

#endif /* MAZE_STORAGE_H */
