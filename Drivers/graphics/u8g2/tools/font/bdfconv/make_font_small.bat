echo.
md out>nul
bdfconv.exe -v -b0 -f1 -m "32-126,176,196,197,214,220,228,229,246,252,937,1040-1103" ../bdf/font_small.bdf -o ./out/font_small.c  -n u8g2_font_small