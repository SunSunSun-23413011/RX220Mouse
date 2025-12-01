from pathlib import Path
import re
path = Path(r'd:\RX220Mouse2\RX220Mouse2.c')
text = path.read_text(encoding='cp932')
text = text.replace('  if( midi <= 0 ) return 0;\n  double freq = 440.0 * pow( 2.0, ((double)midi - 69.0) / 12.0 );\n  double cnt  = (312500.0 / ( 2.0 * freq )) - 1.0;','  double freq;\n  double cnt;\n\n  if( midi <= 0 ) return 0;\n  freq = 440.0 * pow( 2.0, ((double)midi - 69.0) / 12.0 );\n  cnt  = (312500.0 / ( 2.0 * freq )) - 1.0;')
path.write_text(text, encoding='cp932')
print('declarations moved')