/*
 * gui_strings.c
 *
 *  Created on: 27 ene. 2021
 *      Author: David
 */
#include "gui_strings.h"

// language indexes and LANGUAGE_COUNT defined in settings.h

const strings_t strings[LANGUAGE_COUNT] = {
		  [lang_english] = {
		      .boot_firstBoot = "First Boot!",
		      .boot_Profile = "Profile",

		      .main_error_noIron_Detected = "NO IRON DETECTED",
		      .main_error_failsafe = "FAILSAFE MODE",
		      .main_error_NTC_high = "NTC READ HIGH",
		      .main_error_NTC_low = "NTC READ LOW",
		      .main_error_VoltageLow = "VOLTAGE LOW",
		      .main_mode_Sleep = "SLEEP",
		      .main_mode_Sleep_xpos = 42,
		      .main_mode_Standby = "STBY",
		      .main_mode_Standby_xpos = 46,
		      .main_mode_Boost = "BOOST",
		      .main_mode_Boost_xpos = 41,

		      .settings_IRON = "IRON",
		      .settings_SYSTEM = "SYSTEM",
		      .settings_DEBUG = "DEBUG",
		      .settings_EDIT_TIPS = "EDIT TIPS",
		      .settings_CALIBRATION = "CALIBRATION",
		      .settings_EXIT = "EXIT",
		#ifdef ENABLE_ADDONS
		      .settings_ADDONS = "ADDONS/EXTRAS",
		#endif

		#ifdef ENABLE_ADDON_FUME_EXTRACTOR
		      .FUME_EXTRACTOR_Title         = "FUME EXT. CTL.",
		      .FUME_EXTRACTOR_Mode          = "Mode",
		      .FUME_EXTRACTOR_Modes         = { "DISABLED", "AUTO", "ALW. ON" },
		      .FUME_EXTRACTOR_AfterRun      = "After Run",
		      .FUME_EXTRACTOR_AfterRunUnit  = "s",
		#endif

		#ifdef ENABLE_ADDON_SWITCH_OFF_REMINDER
		      .SWITCH_OFF_REMINDER_Title               = "SW OFF REMINDER",
		      .SWITCH_OFF_REMINDER_EnableDisableOption = "Reminder",
		      .SWITCH_OFF_REMINDER_InactivityDelay     = "Delay",
		      .SWITCH_OFF_REMINDER_ReminderPeriod     = "Period",
		      .SWITCH_OFF_REMINDER_TimeUnit            = "m",
		      .SWITCH_OFF_REMINDER_BeepType            = "Beep len.",
		      .SWITCH_OFF_REMINDER_BeepTypes           = {"SHORT" ,"MED." ,"LONG"},
		#endif

		      .IRON_Max_Temp = "Max temp",
		      .IRON_Min_Temp = "Min temp",
		      .IRON_Default_Temp = "Def temp",
		      .IRON_Standby = "Standby",
		      .IRON_Sleep = "Sleep",
		      .IRON_Boost = "Boost",
		      .IRON_Boost_Add = " Increase",
		      .IRON_Wake_Mode = "Wake mode",
		      .IRON_Shake_Filtering = " Filter",
		      .IRON_Stand_Mode = " In stand",
		      .IRON_smartActiveEnable = "SMART",
		      .IRON_smartActiveLoad = " LOAD",
		      .IRON_Power = "Power",
		      .IRON_Heater = "Heater",
		      .IRON_ADC_Time = "ADC Time",
		      .IRON_PWM_mul = "PWM mul.",
		      .IRON_No_Iron = "No iron",
		      .IRON_Error_Timeout = "Err time",
		      .IRON_Error_Resume_Mode = " Resume",
		      .IRON_FILTER_MENU = "FILTER MENU",
		      .IRON_NTC_MENU = "NTC MENU",

		      .FILTER_Filter = "Filter",
		      .FILTER__Threshold = " Threshold",
		      .FILTER__Count_limit = " Count limit",
		      .FILTER__Step_down = " Step down",
		      .FILTER__Min = " Min",
		      .FILTER_Reset_limit = "Reset limit",

		      .SYSTEM_Boot = "Boot",
		      .SYSTEM_Button_Wake = "Btn wake",
		      .SYSTEM_Shake_Wake = "Shake wake",
		      .SYSTEM_Encoder = "Encoder",
		      .SYSTEM_Buzzer = "Buzzer",
		      .SYSTEM_Temperature = "Temperature",
		      .SYSTEM__Step = " Step",
		      .SYSTEM__Big_Step = " Big step",
		      .SYSTEM_Active_Detection = "Active det.",
		      .SYSTEM_Cold_Boost = "Cold Boost",
		      .SYSTEM_LVP = "LVP",
		      .SYSTEM_Gui_Time = "Gui time",
		      .SYSTEM_Battery = "Battery",
		      .SYSTEM_DEBUG = "DEBUG",
		      .SYSTEM_CLONE_FIX = "Clone fix",
		      .SYSTEM_RESET_MENU = "RESET MENU",

		      .SYSTEM_DISPLAY_MENU = "DISPLAY",
		#ifndef ST756
		      .DISPLAY_ContrastOrBrightness = "Brightness",
		#else
		      .DISPLAY_ContrastOrBrightness = "Contrast",
		#endif
		      .DISPLAY_StartColumn = "X",
		      .DISPLAY_StartLine = "Y",
		      .DISPLAY_Xflip = "X flip",
		      .DISPLAY_Yflip = "Y flip",
		      .DISPLAY_Ratio = "Ratio",
		      .DISPLAY_Dim = "Dimmer",
		      .DISPLAY_Dim_inSleep = " In sleep",
		      .DISPLAY_Advanced = "ADVANCED",

		      .NTC_Enable_NTC = "Enable NTC",
		      .NTC_Pull = "Pull",
		      .NTC__Res = " Res",
		      .NTC__Beta = " Beta",
		      .NTC_NTC_Detect = "NTC Detect",
		      .NTC__High = " High",
		      .NTC__Low = " Low",

		      .RESET_Reset_Settings = "Reset Settings",
		      .RESET_Reset_Profile = "Reset Profile",
		      .RESET_Reset_Profiles = "Reset Profiles",
		      .RESET_Reset_All = "Reset All",
		      .RESET_Reset_msg_settings_1 = "RESET SYSTEM",
		      .RESET_Reset_msg_settings_2 = "SETTINGS?",
		      .RESET_Reset_msg_profile_1 = "RESET CURRENT",
		      .RESET_Reset_msg_profile_2 = "PROFILE?",
		      .RESET_Reset_msg_profiles_1 = "RESET ALL",
		      .RESET_Reset_msg_profiles_2 = "PROFILES?",
		      .RESET_Reset_msg_all_1 = "PERFORM FULL",
		      .RESET_Reset_msg_all_2 = "SYSTEM RESET?",

		      .TIP_SETTINGS_Name = "Name",
		      .TIP_SETTINGS_PID_kp = "PID Kp",
		      .TIP_SETTINGS_PID_ki = "PID Ki",
		      .TIP_SETTINGS_PID_kd = "PID Kd",
		      .TIP_SETTINGS_PID_Imax = "PID Imax",
		      .TIP_SETTINGS_PID_Imin = "PID Imin",
		      .TIP_SETTINGS_COPY = "COPY",
		      .TIP_SETTINGS_DELETE = "DELETE",

		      .CAL_ZeroSet = "Zero set   ",       // Must be 11 chars long
		      .CAL_Sampling = "Sampling   ",      // Must be 11 chars long
		      .CAL_Captured = "Captured   ",      // Must be 11 chars long
		      .CAL_Step = "CAL STEP:",
		      .CAL_Wait = "WAIT...",
		      .CAL_Measured = "MEASURED:",
		      .CAL_Success = "SUCCESS!",
		      .CAL_Failed = "FAILED!",
		      .CAL_DELTA_HIGH_1 = "DELTA TOO HIGH!",
		      .CAL_DELTA_HIGH_2 = "Adjust manually",
		      .CAL_DELTA_HIGH_3 = "and try again",
		      .CAL_Error = "ERROR DETECTED!",
		      .CAL_Aborting = "Aborting...",

		      ._Language = "Language",
		      .__Temp = " Temp",
		      .__Delay = " Delay",
		      ._Cal_250 = "Cal 250\260C",
		      ._Cal_400 = "Cal 400\260C",
		      ._BACK = "BACK",
		      ._SAVE = "SAVE",
		      ._CANCEL = "CANCEL",
		      ._STOP = "STOP",
		      ._RESET = "RESET",
		      ._START = "START",
		      ._SETTINGS = "SETTINGS",
		      ._ADD_NEW = "ADD NEW",

		      .ERROR_RUNAWAY = "TEMP RUNAWAY",
		      .ERROR_EXCEEDED = "EXCEEDED",
		      .ERROR_UNKNOWN = "UNKNOWN ERROR",
		      .ERROR_SYSTEM_HALTED = "SYSTEM HALTED",
		      .ERROR_BTN_RESET = "Use btn to reset",

		      .OffOn =       { "OFF", "ON" },
		      .DownUp =      { "DOWN", "UP" },
		      .WakeModes =   { "OFF", "STBY", "SLP", "ALL" },
		      .wakeMode =    { "SHAKE", "STAND" },
		      .encMode =     { "REV", "FWD" },
		      .InitMode =    { "SLP", "STBY", "RUN" },
		      .dimMode =     { "OFF", "SLP", "ALL" },
		      .errMode =     { "SLP", "RUN", "LAST" },
		    },
 [lang_chinese] = {
        .boot_firstBoot = "首次开机！",
        .boot_Profile = "烙铁类型",

        .main_error_noIron_Detected = "检测不到烙铁头",
        .main_error_failsafe = "安全模式",
        .main_error_NTC_high = "NTC 读值过高",
        .main_error_NTC_low = "NTC 读值过低",
        .main_error_VoltageLow = "电压过低",
        .main_mode_Sleep = "休眠",
        .main_mode_Sleep_xpos = 53,
        .main_mode_Standby = "待机",
        .main_mode_Standby_xpos = 53,
        .main_mode_Boost = "超温",
        .main_mode_Boost_xpos = 53,

        .settings_IRON = "烙铁设定",
        .settings_SYSTEM = "系统设定",
        .settings_DEBUG = "工厂调试",
        .settings_EDIT_TIPS = "烙芯参数",
        .settings_CALIBRATION = "温度校准",
        .settings_EXIT = "退出",
#ifdef ENABLE_ADDONS
        .settings_ADDONS = "其它设置",
#endif

#ifdef ENABLE_ADDON_FUME_EXTRACTOR
        .FUME_EXTRACTOR_Title = "排烟控制",
        .FUME_EXTRACTOR_Mode = "模式",
        .FUME_EXTRACTOR_Modes = {"关闭", "自动", "打开"},
        .FUME_EXTRACTOR_AfterRun = "持续运行",
        .FUME_EXTRACTOR_AfterRunUnit = "s",
#endif

#ifdef ENABLE_ADDON_SWITCH_OFF_REMINDER
        .SWITCH_OFF_REMINDER_Title = "开机提醒",
        .SWITCH_OFF_REMINDER_EnableDisableOption = "定时提醒",
        .SWITCH_OFF_REMINDER_InactivityDelay = "等待延时",
        .SWITCH_OFF_REMINDER_ReminderPeriod = "蜂鸣间隔",
        .SWITCH_OFF_REMINDER_TimeUnit = "m",
        .SWITCH_OFF_REMINDER_BeepType = "蜂鸣时间",
        .SWITCH_OFF_REMINDER_BeepTypes = {"短", "中", "长"},
#endif

        .IRON_Max_Temp = "最高温度",
        .IRON_Min_Temp = "最低温度",
        .IRON_Default_Temp = "预设温度",
        .IRON_Standby = "待机时间",
        .IRON_Sleep = "休眠时间",
        .IRON_Boost = "超温时间",
        .IRON_Boost_Add = "└ 提高",
        .IRON_Wake_Mode = "唤醒模式",
        .IRON_Shake_Filtering = "└ 滤波器",
        .IRON_Stand_Mode = "└ 放入底座",
        .IRON_smartActiveEnable = "智能检测",
        .IRON_smartActiveLoad = "└ 灵敏度",
        .IRON_Power = "功率限制",
        .IRON_Heater = "烙铁电阻",
        .IRON_ADC_Time = "ADC 频率",
        .IRON_PWM_mul = "PWM 频率",
        .IRON_No_Iron = "无烙铁阀值",
        .IRON_Error_Timeout = "错误等待",
        .IRON_Error_Resume_Mode = "└ 还原状态",
        .IRON_FILTER_MENU = "滤波器设置",
        .IRON_NTC_MENU = "NTC 设置",

        .FILTER_Filter = "过滤值",
        .FILTER__Threshold = "└ 阀值",
        .FILTER__Count_limit = "└ 计数限制",
        .FILTER__Step_down = "└ 缩小值",
        .FILTER__Min = "└ 最小值",
        .FILTER_Reset_limit = "重设限制",

        .SYSTEM_Boot = "开机进入",
        .SYSTEM_Button_Wake = "按钮唤醒",
        .SYSTEM_Shake_Wake = "晃动唤醒",
        .SYSTEM_Encoder = "编码器",
        .SYSTEM_Buzzer = "蜂鸣器",
        .SYSTEM_Temperature = "温度单位",
        .SYSTEM__Step = "└ 旋钮步进",
        .SYSTEM__Big_Step = "└ 快速步进",
        .SYSTEM_Active_Detection = "活动检测",
        .SYSTEM_LVP = "低压保护",
        .SYSTEM_Gui_Time = "显示频率",
		.SYSTEM_Battery = "系统电池",
        .SYSTEM_DEBUG = "调试菜单",
        .SYSTEM_CLONE_FIX = "克隆修正",
        .SYSTEM_RESET_MENU = "重置菜单",

        .SYSTEM_DISPLAY_MENU = "屏幕设置",
#ifndef ST7565
        .DISPLAY_ContrastOrBrightness = "亮度",
#else
        .DISPLAY_ContrastOrBrightness = "对比度",
#endif
	    .DISPLAY_StartColumn = "X 偏移",
	    .DISPLAY_StartLine = "Y 偏移",
        .DISPLAY_Xflip = "上下翻转",
        .DISPLAY_Yflip = "左右翻转",
        .DISPLAY_Ratio = "亮度比例",
        .DISPLAY_Dim = "屏幕保护",
        .DISPLAY_Dim_inSleep = "└ 持续显示",
        .DISPLAY_Advanced = "高级设置",

        .NTC_Enable_NTC = "启用 NTC",
        .NTC_Pull = "模式",
        .NTC__Res = "└ 阻值",
        .NTC__Beta = "└ Beta 值",
        .NTC_NTC_Detect = "NTC 检测",
        .NTC__High = "└ 高阻值",
        .NTC__Low = "└ 低阻值",

        .RESET_Reset_Settings = "重置系统参数",
        .RESET_Reset_Profile = "重置当前烙铁参数",
        .RESET_Reset_Profiles = "重置所有烙铁参数",
        .RESET_Reset_All = "恢复出厂设置",
        .RESET_Reset_msg_settings_1 = "确定重置",
        .RESET_Reset_msg_settings_2 = "系统参数?",
        .RESET_Reset_msg_profile_1 = "确定重置",
        .RESET_Reset_msg_profile_2 = "当前烙铁参数?",
        .RESET_Reset_msg_profiles_1 = "确定重置",
        .RESET_Reset_msg_profiles_2 = "所有烙铁参数?",
        .RESET_Reset_msg_all_1 = "确定恢复",
        .RESET_Reset_msg_all_2 = "出厂设置?",

        .TIP_SETTINGS_Name = "名称",
        .TIP_SETTINGS_PID_kp = "PID Kp",
        .TIP_SETTINGS_PID_ki = "PID Ki",
        .TIP_SETTINGS_PID_kd = "PID Kd",
        .TIP_SETTINGS_PID_Imax = "PID Imax",
        .TIP_SETTINGS_PID_Imin = "PID Imin",
        .TIP_SETTINGS_COPY = "复制",
        .TIP_SETTINGS_DELETE = "刪除",

        .CAL_ZeroSet = "参考值     ",  // Must be 11 chars long
        .CAL_Sampling = "取样值     ", // Must be 11 chars long
        .CAL_Captured = "设定值     ", // Must be 11 chars long
        .CAL_Step = "设定温度:",
        .CAL_Wait = "等待中...",
        .CAL_Measured = "测量温度:",
        .CAL_Success = "成功!",
        .CAL_Failed = "失败!",
        .CAL_DELTA_HIGH_1 = "差值过大!",
        .CAL_DELTA_HIGH_2 = "手动调整后",
        .CAL_DELTA_HIGH_3 = "再次校准",
        .CAL_Error = "发生错误!",
        .CAL_Aborting = "正在退出...",

        ._Language = "系统语言",
        .__Temp = "└ 温度",
        .__Delay = "└ 延时",
        ._Cal_250 = "校值 250\260C",
        ._Cal_400 = "校值 400\260C",
        ._BACK = "返回",
        ._SAVE = "保存",
        ._CANCEL = "取消",
        ._STOP = "停止",
        ._RESET = "重置",
        ._START = "开始",
        ._SETTINGS = "设定",
        ._ADD_NEW = "添加",

        .ERROR_RUNAWAY = "温度过高",
        .ERROR_EXCEEDED = "数值超出",
        .ERROR_UNKNOWN = "未知错误",
        .ERROR_SYSTEM_HALTED = "系统奔溃",
        .ERROR_BTN_RESET = "使用按钮重设",

        .OffOn = {"关闭", "打开"},
        .DownUp = {"下拉", "上拉"},
        .WakeModes = {"关闭", "待机", "休眠", "全部"},
        .wakeMode = {"晃动", "底座"},
        .encMode = {"逆时", "顺时"},
        .InitMode = {"休眠", "待机", "运行"},
        .dimMode = {"关闭", "休眠", "全部"},
        .errMode = {"休眠", "运行", "持续"},
    }

};

char *const tempUnit[2] = {"\260C", "\260F"};
char *const profileStr[NUM_PROFILES] = {"T12", "C245", "C210"};
char *const Langs[LANGUAGE_COUNT] = {
    [lang_english] = "EN",
    [lang_chinese] = "中文"};
