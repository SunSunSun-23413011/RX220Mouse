
import pathlib
path = pathlib.Path('RX220Mouse2.c')
text = path.read_text(encoding='cp932')
marker = '//  RX220初期化'
idx = text.find(marker)
if idx == -1:
    raise SystemExit('marker not found')
