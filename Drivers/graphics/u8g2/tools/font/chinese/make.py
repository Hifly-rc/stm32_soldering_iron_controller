import os
font_path = "font/fireflysung.ttf"
font_menu_chn = "└试准中文菜单最高温度最低预设待机时间休眠超用提唤醒模式过滤器放入底座智能启动负载功率限制烙铁电阻频率倍最无阀值错误等出厂设置选器计数缩小重设类型开进按钮晃动编码蜂鸣单位旋钮步进快速活择检测压保护显示频错误项克隆修正记住后屏幕亮对比偏移上下翻转左右比例保护持续级定加名称复制删除参考取样等待成功失败手调整再次始发生在退系统语言返回延校存增奔溃顺逆拉闭全部关头辑首休其它长短打运行消确恢芯刪波所有当前"
font_small_chn = "不低值检全到压安式待模机测温烙眠休读超过铁电头高"
def MakeMapFile(data, outfile):
        ret = "32-128"
        file = open(outfile, "w")
        for i in data:
                ret = ret + hex(ord(i)).upper().replace('0X', ', $')
        file.write(ret)
        file.close()
if __name__ == "__main__":
	#MakeMapFile(font_menu_chn, "font_menu_chn.map")
	#MakeMapFile(font_small_chn, "font_small_chn.map")
	#otf2bdfCMD = "otf2bdf.exe -v -r {3} -p {0} -o {1} {2}".format(13, "font_menu_chn.bdf", font_path, 72)
	#os.system(otf2bdfCMD)
	#otf2bdfCMD = "otf2bdf.exe -v -r {3} -p {0} -o {1} {2}".format(11, "font_small_chn.bdf", font_path, 72)
	#os.system(otf2bdfCMD)
	bdfconvCMD = "bdfconv.exe -v -b 0 -f 1 {0} -M {1} -n {2} -o {3} -p {4} -d {0}".format("font12.bdf", "font_menu_chn.map", "u8g2_font_menu", "u8g2_font_menu.c", 0)
	os.system(bdfconvCMD)
	bdfconvCMD = "bdfconv.exe -v -b 0 -f 1 {0} -M {1} -n {2} -o {3} -p {4} -d {0}".format("font12.bdf", "font_small_chn.map", "u8g2_font_small", "u8g2_font_small.c", 0)
	os.system(bdfconvCMD)
	aioCMD = "copy /b u8g2_font_menu.c + u8g2_font_small.c u8g2_fonts_aio.h"
	os.system(aioCMD)
	#os.system("del *font*.map")
	#os.system("del *font*.bdf")
	os.system("del *font*.c")
