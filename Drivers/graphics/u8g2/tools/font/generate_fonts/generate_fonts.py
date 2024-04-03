import re
import subprocess

# 通用的文件读取函数
def read_file(file_path):
    print(file_path)
    with open(file_path, 'r', encoding='utf-8') as file:
        return file.read()

# 通用的文件写入函数
def write_file(file_path, content):
    with open(file_path, "w", encoding="utf-8") as file:
        file.write(content)

# 提取特定字符的函数
def extract_chars(code, filter_condition):
    regex_string = r'(\b[a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*(.*)'
    matches = re.findall(regex_string, code)
    filtered_assignments = [(var, val) for var, val in matches if filter_condition(var)]
    chars = "".join(value for var, value in filtered_assignments)
    filtered_chars = set(filter(lambda c: ord(c) >= 19968, chars))
    return filtered_chars

# 菜单文件生成函数
def make_menu_file(infile, outfile):
    filtered_chars = extract_chars(read_file(infile), lambda var: 'main_mode_' not in var and 'main_error_' not in var)
    write_file(outfile, "".join(filtered_chars) + "└")

# 主界面小字体生成函数
def make_small_file(infile, outfile):
    filtered_chars = extract_chars(read_file(infile), lambda var: 'main_mode' in var or 'main_error' in var)
    write_file(outfile, "".join(filtered_chars))

# 映射文件生成函数
def make_map_file(infile, outfile):
    data = read_file(infile)
    unicode_text = [hex(ord(c)).upper() + "\t" + hex(ord(c)).upper() for c in data]
    unicode_text.sort()
    map_file_data = "\n".join(unicode_text)
    write_file(outfile, map_file_data)

# 合并映射文件函数
def mux_map_file(eng, ch, out):
    eng_data = read_file(eng)
    start = eng_data.find("CHARS ") + 6
    end = eng_data.find("STARTCHAR")
    eng_chars = int(eng_data[start:end])
    ch_data = read_file(ch)
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
    write_file(out, out_data)

# 替代 os.system 的函数
def run_command(command):
    subprocess.run(command, shell=True)

# 主函数
def main():
    gui_strings_path = "..\\..\\..\\..\\gui\\screens\\gui_strings.c"
    # 生成菜单文件和映射文件
    make_menu_file(gui_strings_path, "output\\font_menu_ch.txt")
    make_map_file("output\\font_menu_ch.txt", "output\\font_menu_ch.map")
    # 生成小文件和映射文件
    make_small_file(gui_strings_path, "output\\font_small_ch.txt")
    make_map_file("output\\font_small_ch.txt", "output\\font_small_ch.map")
    # 调用外部程序生成BDF文件
    run_command(f"..\otf2bdf\otf2bdf.exe -m output/font_menu_ch.map -p 9 fireflysung.ttf -o output/font_menu_ch.bdf")
    run_command(f"..\otf2bdf\otf2bdf.exe -m output/font_small_ch.map -p 8 fireflysung.ttf -o output/font_small_ch.bdf")
    # 合并映射文件
    mux_map_file("../bdf/font_menu.bdf", "output/font_menu_ch.bdf", "output/font_menu_all.bdf")
    mux_map_file("../bdf/font_small.bdf", "output/font_small_ch.bdf", "output/font_small_all.bdf")
    # 调用外部程序生成C文件
    run_command(f"..\\bdfconv\\bdfconv.exe -v -b 0 -f 1 -m \"32-126,160-255,268-271,282-283,286,287,304,305,327,328,344,345,350-353,356,357,366,367,381,382,937,1040-1103,5000-65535\" -o output/font_menu.c -n u8g2_font_menu output/font_menu_all.bdf")
    run_command(f"..\\bdfconv\\bdfconv.exe -v -b 0 -f 1 -m \"32-126,160-255,268-271,282-283,286,287,304,305,327,328,344,345,350-353,356,357,366,367,381,382,937,1040-1103,5000-65535\" -o output/font_small.c -n u8g2_font_small output/font_small_all.bdf")
    run_command(f"..\\bdfconv\\bdfconv.exe -v -b 0 -f 1 -m \"45,48-57,67,70,176\" \"../bdf/ITC Avant Garde Gothic Medium_31.bdf\" -o output/font_iron_temp.c  -n u8g2_font_iron_temp")
    run_command(f"copy /b output\\font_iron_temp.c + output\\font_menu.c + output\\font_small.c u8g2_aio.c")
    #run_command("del *ch.map && del *ch.bdf && del *all.bdf && del font_*.c")
    print('# DONE #')

if __name__ == '__main__':
    main()
