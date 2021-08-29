/*
 * gui_strings.c
 *
 *  Created on: 27 ene. 2021
 *      Author: David
 */
#include "gui_strings.h"

// See settings.h for language index

const strings_t strings[LANGUAGE_COUNT] = {

    {                                                             // 0 = English
     .boot_firstBoot = "First Boot!",
     .boot_Profile = "Profile",

     .main_error_noIron = "NO IRON",
     .main_error_noIron_Detected = "NO IRON DETECTED",
     .main_error_failsafe = "FAILSAFE MODE",
     .main_error_NTC_high = "NTC READ HIGH",
     .main_error_NTC_low = "NTC READ LOW",
     .main_error_VoltageLow = "VOLTAGE LOW",
     .main_mode_Sleep = "SLEEP",
     .main_mode_Standby = "STBY",
     .main_mode_Boost = "BOOST",

     .settings_IRON = "IRON",
     .settings_SYSTEM = "SYSTEM",
     .settings_DEBUG = "DEBUG",
     .settings_EDIT_TIPS = "EDIT TIPS",
     .settings_CALIBRATION = "CALIBRATION",
     .settings_EXIT = "EXIT",

     .IRON_Max_Temp = "Max temp",
     .IRON_Min_Temp = "Min temp",
     .IRON_Standby = "Standby",
     .IRON_Sleep = "Sleep",
     .IRON_Boost = "Boost",
     .IRON_Boost_Add = " Add",
     .IRON_Power = "Power",
     .IRON_Heater = "Heater",
     .IRON_ADC_Time = "ADC Time",
     .IRON_PWM_mul = "PWM mul.",
     .IRON_No_Iron = "No iron",
     .IRON_Filter_Settings = "FILTER SETTINGS",

     .FILTER_Filter = "Filter",
     .FILTER__Threshold = " Threshold",
     .FILTER__Count_limit = " Count limit",
     .FILTER__Step_down = " Step down",
     .FILTER__Min = " Min",
     .FILTER_Reset_limit = "Reset limit",

     .SYSTEM_Profile = "Profile",
     ._Language = "Language",
     .SYSTEM_Contrast = "Contrast",
     .SYSTEM_Auto_Dim = "Auto dim",
     .SYSTEM_Offset = "Offset",
     .SYSTEM_Wake_Mode = "Wake mode",
     .SYSTEM_Stand_Mode = "Stand mode",
     .SYSTEM_Boot = "Boot",
     .SYSTEM_Button_Wake = "Btn wake",
     .SYSTEM_Shake_Wake = "Shake wake",
     .SYSTEM_Encoder = "Encoder",
     .SYSTEM_Buzzer = "Buzzer",
     .SYSTEM_Temperature = "Temperature",
     .SYSTEM__Step = " Step",
     .SYSTEM__Big_Step = " Big step",
     .SYSTEM_Active_Detection = "Active det.",
     .SYSTEM_LVP = "LVP",
     .SYSTEM_Gui_Time = "Gui time",
     .SYSTEM_DEBUG = "DEBUG",
     .SYSTEM_NTC_MENU = "NTC MENU",
     .SYSTEM_RESET_MENU = "RESET MENU",

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
     .TIP_SETTINGS_PID_kd = "PID Kp",
     .TIP_SETTINGS_PID_ki = "PID Ki",
     .TIP_SETTINGS_PID_kp = "PID Kd",
     .TIP_SETTINGS_PID_Imax = "PID Imax",
     .TIP_SETTINGS_PID_Imin = "PID Imin",
     .TIP_SETTINGS_COPY = "COPY",
     .TIP_SETTINGS_DELETE = "DELETE",

     .CAL_Step = "CAL STEP:",
     .CAL_Wait = "WAIT...",
     .CAL_Measured = "MEASURED:",
     .CAL_Succeed = "SUCCEED!",
     .CAL_Failed = "FAILED!",
     .CAL_DELTA_HIGH_1 = "DELTA TOO HIGH!",
     .CAL_DELTA_HIGH_2 = "Adjust manually",
     .CAL_DELTA_HIGH_3 = "and try again",
     .CAL_Error = "ERROR DETECTED!",
     .CAL_Aborting = "Aborting...",

     .__Temp = " Temp",
     .__Delay = " Delay",
     ._Cal_250 = "Cal 250\260C",
     ._Cal_350 = "Cal 350\260C",
     ._Cal_450 = "Cal 450\260C",
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
    },

    {                                                             // 1 = Russian
      .boot_firstBoot = "Выберите",
      .boot_Profile = "Тип",

      .main_error_noIron = "ОТКЛЮЧЕН",
      .main_error_noIron_Detected = "ОТСОЕДИНЕН",
      .main_error_failsafe = "РЕЖИМ ЗАЩИТЫ",
      .main_error_NTC_high = "NTC ЗНАЧ ВЫС",
      .main_error_NTC_low = "NTC ЗНАЧ НИЗ",
      .main_error_VoltageLow = "НАПР.ЗАНИЖЕНО",
      .main_mode_Sleep = "ВЫКЛ",
      .main_mode_Standby = "СОН",
      .main_mode_Boost = "БУСТ",

      .settings_IRON = "ПАЯЛЬНИК",
      .settings_SYSTEM = "СТАНЦИЯ",
      .settings_DEBUG = "ОТЛАДКА",
      .settings_EDIT_TIPS = "КАРТРИДЖ",
      .settings_CALIBRATION = "КАЛИБРОВКА",
      .settings_EXIT = "ВЫХОД",

      .IRON_Max_Temp = "Максимум",
      .IRON_Min_Temp = "Минимум",
      .IRON_Standby = "Сон",
      .IRON_Sleep = "Откл",
      .IRON_Boost = "Буст",
      .IRON_Boost_Add = " Догрев",
      .IRON_Power = "Мощность",
      .IRON_Heater = "Ом жала",
      .IRON_ADC_Time = "АЦП Замер",
      .IRON_PWM_mul = "ШИМ множ.",
      .IRON_No_Iron = "ПорогОткл",
      .IRON_Filter_Settings = "ПАРАМ. ФИЛЬТРА",

      .FILTER_Filter = "Фильтр",
      .FILTER__Threshold = " Порог",
      .FILTER__Count_limit = " Отсчетов",
      .FILTER__Step_down = " Шаг вниз",
      .FILTER__Min = " Минимум",
      .FILTER_Reset_limit = "Порог сброса",

      ._Language = "Язык",
      .SYSTEM_Profile = "Тип",
      .SYSTEM_Contrast = "Яркость",
      .SYSTEM_Auto_Dim = "Затемнять",
      .SYSTEM_Offset = "Сдвиг",
      .SYSTEM_Wake_Mode = "Датчик сна",
      .SYSTEM_Stand_Mode = "Подставка",
      .SYSTEM_Boot = "Старт с",
      .SYSTEM_Button_Wake = "Энкодер раб.",
      .SYSTEM_Shake_Wake = "Датчик раб.",
      .SYSTEM_Encoder = "Вращение",
      .SYSTEM_Buzzer = "Бипка",
      .SYSTEM_Temperature = "Шкала темп.",
      .SYSTEM__Step = " Шаг",
      .SYSTEM__Big_Step = " Шаг быстр.",
      .SYSTEM_Active_Detection = "Пост.Проверка",
      .SYSTEM_LVP = "Порог Напр.",
      .SYSTEM_Gui_Time = "Экр.Частота",
      .SYSTEM_DEBUG = "Отладка",
      .SYSTEM_NTC_MENU = "NTC ПАР-РЫ",
      .SYSTEM_RESET_MENU = "МЕНЮ СБРОСА",

      .NTC_Enable_NTC = "Внешний NTC",
      .NTC_Pull = "Подтяжка",
      .NTC__Res = " Сопр-ие",
      .NTC__Beta = "  Кривая",
      .NTC_NTC_Detect = "Автообнаруж.",
      .NTC__High = " Макс.",
      .NTC__Low = " Мин.",

      .RESET_Reset_Settings = "Сброс Настроек",
      .RESET_Reset_Profile = "Сброс Профиля",
      .RESET_Reset_Profiles = "Сброс Профилей",
      .RESET_Reset_All = "Общий сброс",
      .RESET_Reset_msg_settings_1 = "СБРОСИТЬ",
      .RESET_Reset_msg_settings_2 = "НАСТРОЙКИ?",
      .RESET_Reset_msg_profile_1 = "СБРОСИТЬ",
      .RESET_Reset_msg_profile_2 = "ТЕКУЩИЙ?",
      .RESET_Reset_msg_profiles_1 = "СБРОСИТЬ",
      .RESET_Reset_msg_profiles_2 = "ВСЕ?",
      .RESET_Reset_msg_all_1 = "ВЕРНУТЬ К",
      .RESET_Reset_msg_all_2 = "ЗАВОДСКИМ?",

      .TIP_SETTINGS_Name = "Название",
      .TIP_SETTINGS_PID_kd = "ПИД кП",
      .TIP_SETTINGS_PID_ki = "ПИД кИ",
      .TIP_SETTINGS_PID_kp = "ПИД кД",
      .TIP_SETTINGS_PID_Imax = "ПИД Имакс",
      .TIP_SETTINGS_PID_Imin = "ПИД Имин",
      .TIP_SETTINGS_COPY = "ДУБЛИРОВАТЬ",
      .TIP_SETTINGS_DELETE = "УДАЛИТЬ",

      .CAL_Step = "ШАГ:",
      .CAL_Wait = "ЖДИТЕ...",
      .CAL_Measured = "ЗАМЕРЕНО:",
      .CAL_Succeed = "УСПЕШНО!",
      .CAL_Failed = "НЕУДАЧА!",
      .CAL_DELTA_HIGH_1 = "РАЗНИЦА ВЕЛИКА",
      .CAL_DELTA_HIGH_2 = "задайте вручную",
      .CAL_DELTA_HIGH_3 = "и повторите",
      .CAL_Error = "ERROR DETECTED!",
      .CAL_Aborting = "Aborting...",

      .__Temp = " Нагрев",
      .__Delay = " Задержка",
      ._Cal_250 = "АЦП 250\260C",
      ._Cal_350 = "АЦП 350\260C",
      ._Cal_450 = "АЦП 450\260C",
      ._BACK = "НАЗАД",
      ._SAVE = "ЗАПИСЬ",
      ._CANCEL = "ОТМЕНА",
      ._STOP = "СТОП",
      ._RESET = "СБРОС",
      ._START = "НАЧАТЬ",
      ._SETTINGS = "ПАРАМЕТРЫ",
      ._ADD_NEW = "ДОБАВИТЬ",

      .ERROR_RUNAWAY = "УШЕЛ В РАЗНОС",
      .ERROR_EXCEEDED = "ПРЕВЫШЕНИЕ",
      .ERROR_UNKNOWN = "ОШИБКА 404",
      .ERROR_SYSTEM_HALTED = "БЫЛИННЫЙ ОТКАЗ",
      .ERROR_BTN_RESET = "наж.для рестарта",
     },
};








char *profileStr[] =  { "T12", "C245", "C210" };
char *OffOn[] =       { "OFF", "ON" };
char *DownUp[] =      { "DOWN", "UP" };
char *WakeModes[] =   { "OFF", "STBY", "SLP", "ALL" };
char *tempUnit[] =    { "\260C", "\260F" };
char *wakeMode[] =    { "SHAKE", "STAND" };
char *encMode[] =     { "REVERSE", "NORMAL" };
char *InitMode[] =    { "SLP", "STBY", "RUN"};
char *Langs[] =       { "EN", "RU" };
//char *filterMode[] =  { "AVG", "EMA"};
