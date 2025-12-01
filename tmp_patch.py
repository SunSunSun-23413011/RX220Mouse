from pathlib import Path
import re
path = Path(r'd:\RX220Mouse2\RX220Mouse2.c')
text = path.read_text(encoding='cp932')
text = re.sub(r'(com_turn\( 2 \);\s*// .+?\n\s*com_stop\(\);\s*// .+?\n)(\s*)head_change = 2;', r'\1\2melody_stop();               // stop melody before finish\n\2head_change = 2;', text, count=1)
text = re.sub(r'(default : com_stop\(\);\s*// .+?\n)(\s*)head_change = 0;', r'\1\2melody_stop();               // stop melody before exit\n\2head_change = 0;', text, count=1)
path.write_text(text, encoding='cp932')
print('inserted melody_stop in mouse_search')