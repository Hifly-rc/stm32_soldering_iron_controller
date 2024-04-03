import re,os

regex_string = r'(\b[a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*(.*)'
gui_strings_path = "..\\..\\..\\..\\gui\\screens\\gui_strings.c"
   
def make_menu_file(infile, outfile):
    with open(infile, 'r', encoding='utf-8') as file:
        code = file.read()
    matches = re.findall(regex_string, code)
    chars = ""
    filtered_assignments = [(var, val) for var, val in matches if 'main_mode_' not in var and 'main_error_' not in var]
    for var, value in filtered_assignments:
        chars += value
    chars = set(filter(lambda c: ord(c) >= 19968, chars))
    with open(outfile, "w", encoding="utf-8") as file:
        file.write("".join(chars))
        file.write("└") #Add filtered symbols from here

def make_small_file(infile, outfile):
    with open(infile, 'r', encoding='utf-8') as file:
        code = file.read()
    matches = re.findall(regex_string, code)
    chars = ""
    filtered_assignments = [(var, val) for var, val in matches if 'main_mode' in var or 'main_error' in var]
    for var, value in filtered_assignments:
        chars += value
    chars = set(filter(lambda c: ord(c) >= 19968, chars))    
    with open(outfile, "w", encoding="utf-8") as file:
        file.write("".join(chars))

def make_map_file(file_path, outfile):
    with open(file_path, "r", encoding="utf-8") as file:
        data = file.read()
    unicode_text = [hex(ord(c)).upper() + "\t" + hex(ord(c)).upper() for c in data]
    unicode_text.sort()
    map_file_data = "\n".join(unicode_text)
    with open(outfile, "w", encoding="utf-8") as file:
        file.write(map_file_data)

def mux_map_file(eng, ch, out):
    eng_data = open(eng).read()
    start = eng_data.find("CHARS ") + 6
    end = eng_data.find("STARTCHAR")
    eng_chars = int(eng_data[start:end])
    ch_data = open(ch).read()
    start = ch_data.find("CHARS ") + 6
    end = ch_data.find("STARTCHAR")
    ch_chars = int(ch_data[start:end])
    index = eng_data.find("ENDFONT")
    start = ch_data.find("STARTCHAR")
    end = ch_data.find("ENDFONT")
    out_comt = "COMMENT Traditional Chinese Fonts start from here!!!\n"
    #out_comt = out_comt + "COMMENT Please add fonts above for better maintenance\n"
    out_data = eng_data[:index] + out_comt + ch_data[start:end] + eng_data[index:]
    out_data = out_data.replace(f"CHARS {eng_chars}", f"CHARS {eng_chars + ch_chars}")
    open(out, "w").write(out_data)
        
if __name__ == '__main__':
    make_menu_file(gui_strings_path, "font_menu_ch.txt")
    make_small_file(gui_strings_path, "font_small_ch.txt")
    make_map_file("font_menu_ch.txt", "font_menu_ch.map")
    make_map_file("font_small_ch.txt", "font_small_ch.map")
    os.system("..\\otf2bdf\\otf2bdf.exe -m font_menu_ch.map -p 9 fireflysung.ttf -o font_menu_ch.bdf")
    os.system("..\\otf2bdf\\otf2bdf.exe -m font_small_ch.map -p 8 fireflysung.ttf -o font_small_ch.bdf")
    mux_map_file("../bdf/font_menu.bdf", "font_menu_ch.bdf", "font_menu_all.bdf")
    mux_map_file("../bdf/font_small.bdf", "font_small_ch.bdf", "font_small_all.bdf")
    os.system("..\\bdfconv\\bdfconv.exe -v -b 0 -f 1 -m \"32-126,160-255,268-271,282-283,286,287,304,305,327,328,344,345,350-353,356,357,366,367,381,382,937,1040-1103,5000-65535\" -o font_menu.c -n u8g2_font_menu font_menu_all.bdf")
    os.system("..\\bdfconv\\bdfconv.exe -v -b 0 -f 1 -m \"32-126,160-255,268-271,282-283,286,287,304,305,327,328,344,345,350-353,356,357,366,367,381,382,937,1040-1103,5000-65535\" -o font_small.c -n u8g2_font_small font_small_all.bdf")
    os.system("..\\bdfconv\\bdfconv.exe -v -b 0 -f 1 -m \"45,48-57,67,70,176\" \"../bdf/ITC Avant Garde Gothic Medium_31.bdf\" -o font_iron_temp.c  -n u8g2_font_iron_temp")
    os.system("copy /b font_iron_temp.c + font_menu.c + font_small.c u8g2_aio.c")
    os.system("del *ch.map && del *ch.bdf && del *all.bdf && del font_*.c")

    print("Make Complete")
