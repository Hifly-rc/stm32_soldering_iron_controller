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

      .main_error_noIron = "NO IRON",
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

      .IRON_Max_Temp = "Max temp",
      .IRON_Min_Temp = "Min temp",
      .IRON_User_Temp = "User temp",
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
      .SYSTEM_Contrast = "Contrast",
      .SYSTEM_Oled_Dim = "Dimmer",
      .SYSTEM_Oled_Dim_SleepPower = " In sleep",
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
      .TIP_SETTINGS_PID_kp = "PID Kp",
      .TIP_SETTINGS_PID_ki = "PID Ki",
      .TIP_SETTINGS_PID_kd = "PID Kd",
      .TIP_SETTINGS_PID_Imax = "PID Imax",
      .TIP_SETTINGS_PID_Imin = "PID Imin",
      .TIP_SETTINGS_COPY = "COPY",
      .TIP_SETTINGS_DELETE = "DELETE",

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
      .encMode =     { "REVERSE", "NORMAL" },
      .InitMode =    { "SLP", "STBY", "RUN" },
      .dimMode =     { "OFF", "SLP", "ALL" },
    },

    [lang_russian] = {
      .boot_firstBoot = "Выберите",
      .boot_Profile = "Тип",

      .main_error_noIron = "ОТКЛЮЧЕН",
      .main_error_noIron_Detected = "ОТСОЕДИНЕН",
      .main_error_failsafe = "РЕЖИМ ЗАЩИТЫ",
      .main_error_NTC_high = "NTC ЗНАЧ ВЫС",
      .main_error_NTC_low = "NTC ЗНАЧ НИЗ",
      .main_error_VoltageLow = "НАПР.ЗАНИЖЕНО",
      .main_mode_Sleep = "ВЫКЛ",
      .main_mode_Sleep_xpos = 46,
      .main_mode_Standby = "СОН",
      .main_mode_Standby_xpos = 49,
      .main_mode_Boost = "БУСТ",
      .main_mode_Boost_xpos = 48,

      .settings_IRON = "ПАЯЛЬНИК",
      .settings_SYSTEM = "СТАНЦИЯ",
      .settings_DEBUG = "ОТЛАДКА",
      .settings_EDIT_TIPS = "КАРТРИДЖ",
      .settings_CALIBRATION = "КАЛИБРОВКА",
      .settings_EXIT = "ВЫХОД",

      .IRON_Max_Temp = "Максимум",
      .IRON_Min_Temp = "Минимум",
      .IRON_User_Temp = "Стартовая",
      .IRON_Standby = "СОН",
      .IRON_Sleep = "ВЫКЛ",
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
      .FILTER_Reset_limit = "ПорогСброса",

      .SYSTEM_Profile = "Тип",
      .SYSTEM_Contrast = "Яркость",
      .SYSTEM_Oled_Dim = "Dimming",
      .SYSTEM_Oled_Dim_SleepPower = " Slp pwr",
      .SYSTEM_Offset = "Сдвиг",
      .SYSTEM_Wake_Mode = "ДатчикСна",
      .SYSTEM_Stand_Mode = "Подставка",
      .SYSTEM_Boot = "Старт с",
      .SYSTEM_Button_Wake = "Кнопка раб.",
      .SYSTEM_Shake_Wake = "Датчик раб.",
      .SYSTEM_Encoder = "Вращение",
      .SYSTEM_Buzzer = "Зуммер",
      .SYSTEM_Temperature = "Шкала темп.",
      .SYSTEM__Step = " Шаг",
      .SYSTEM__Big_Step = " Шаг быстр.",
      .SYSTEM_Active_Detection = "Проверка",
      .SYSTEM_LVP = "ПорогНапр.",
      .SYSTEM_Gui_Time = "Отрисовка",
      .SYSTEM_DEBUG = "Отладка",
      .SYSTEM_NTC_MENU = "NTC ПАР-РЫ",
      .SYSTEM_RESET_MENU = "МЕНЮ СБРОСА",

      .NTC_Enable_NTC = "Внешний NTC",
      .NTC_Pull = "Подтяжка",
      .NTC__Res = " Сопр-ие",
      .NTC__Beta = "  Кривая",
      .NTC_NTC_Detect = "Автоопр.",
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
      .TIP_SETTINGS_PID_kp = "ПИД кП",
      .TIP_SETTINGS_PID_ki = "ПИД кИ",
      .TIP_SETTINGS_PID_kd = "ПИД кД",
      .TIP_SETTINGS_PID_Imax = "ПИД Имакс",
      .TIP_SETTINGS_PID_Imin = "ПИД Имин",
      .TIP_SETTINGS_COPY = "ДУБЛИРОВАТЬ",
      .TIP_SETTINGS_DELETE = "УДАЛИТЬ",

      .CAL_Step = "ШАГ:",
      .CAL_Wait = "ЖДИТЕ...",
      .CAL_Measured = "ЗАМЕР:",
      .CAL_Success = "УСПЕШНО!",
      .CAL_Failed = "НЕУДАЧА!",
      .CAL_DELTA_HIGH_1 = "РАЗНИЦА ВЕЛИКА",
      .CAL_DELTA_HIGH_2 = "задайте вручную",
      .CAL_DELTA_HIGH_3 = "и повторите",
      .CAL_Error = "ОШИБКА!",
      .CAL_Aborting = "выход...",

      ._Language = "Язык",
      .__Temp = " Нагрев",
      .__Delay = " Задержка",
      ._Cal_250 = "АЦП 250\260C",
      ._Cal_400 = "АЦП 400\260C",
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
      .ERROR_UNKNOWN = "НЕИЗВ.ОШИБКА",
      .ERROR_SYSTEM_HALTED = "БЫЛИННЫЙ ОТКАЗ",
      .ERROR_BTN_RESET = "наж.для рестарта",

      .OffOn =       { "ВЫКЛ", "ВКЛ" },
      .DownUp =      { "ВНИЗ", "ВВЕРХ" },
      .WakeModes =   { "откл", "СОН", "ВЫКЛ", "все" },
      .wakeMode =    { "РУЧКА", "СТОЙКА" },
      .encMode =     { "ОБРАТНО", "ПРЯМО" },
      .InitMode =    { "ВЫКЛ", "СОН", "ПУСК" },
      .dimMode =     { "откл", "ВЫКЛ", "все" },

    },

    [lang_swedish] = {
      .boot_firstBoot = "Första Start!",
      .boot_Profile = "Profil",

      .main_error_noIron = "KOLV UR",
      .main_error_noIron_Detected = "KOLV EJ UPPTÄCKT",
      .main_error_failsafe = "FELSÄKERT LÄGE",
      .main_error_NTC_high = "NTC-VÄRDE HÖGT",
      .main_error_NTC_low = "NTC-VÄRDE LÅGT",
      .main_error_VoltageLow = "SPÄNNING LÅG",
      .main_mode_Sleep = "SOVER",
      .main_mode_Sleep_xpos = 40,
      .main_mode_Standby = "STBY",
      .main_mode_Standby_xpos = 46,
      .main_mode_Boost = "BOOST",
      .main_mode_Boost_xpos = 41,

      .settings_IRON = "LÖDKOLV",
      .settings_SYSTEM = "SYSTEM",
      .settings_DEBUG = "DEBUG",
      .settings_EDIT_TIPS = "SPETSAR",
      .settings_CALIBRATION = "KALIBRERING",
      .settings_EXIT = "AVSLUTA",

      .IRON_Max_Temp = "Max temp",
      .IRON_Min_Temp = "Min temp",
      .IRON_User_Temp = "Starttemp",
      .IRON_Standby = "Standby",
      .IRON_Sleep = "Sovläge",
      .IRON_Boost = "Boost",
      .IRON_Boost_Add = " Tillägg",
      .IRON_Power = "Effekt",
      .IRON_Heater = "Element",
      .IRON_ADC_Time = "ADO Tid",
      .IRON_PWM_mul = "PWM mul.",
      .IRON_No_Iron = "Kolv ur",
      .IRON_Filter_Settings = "FILTER INST.",

      .FILTER_Filter = "Filter",
      .FILTER__Threshold = " Tröskel",
      .FILTER__Count_limit = " Antalsgräns",
      .FILTER__Step_down = " Avbackning",
      .FILTER__Min = " Min",
      .FILTER_Reset_limit = "Resetgräns",

      .SYSTEM_Profile = "Profil",
      .SYSTEM_Contrast = "Kontrast",
      .SYSTEM_Oled_Dim = "Dimmer",
      .SYSTEM_Oled_Dim_SleepPower = " SOV-OLED",
      .SYSTEM_Offset = "Offset",
      .SYSTEM_Wake_Mode = "Väckmetod",
      .SYSTEM_Stand_Mode = "Ställ-läge",
      .SYSTEM_Boot = "Startläge",
      .SYSTEM_Button_Wake = "Knappväck",
      .SYSTEM_Shake_Wake = "Skakväck",
      .SYSTEM_Encoder = "Encoder",
      .SYSTEM_Buzzer = "Summer",
      .SYSTEM_Temperature = "Temperatur",
      .SYSTEM__Step = " Steg",
      .SYSTEM__Big_Step = " Storsteg",
      .SYSTEM_Active_Detection = "Aktiv avk.",
      .SYSTEM_LVP = "LSS",
      .SYSTEM_Gui_Time = "Gui-tid",
      .SYSTEM_DEBUG = "DEBUG",
      .SYSTEM_NTC_MENU = "NTC MENY",
      .SYSTEM_RESET_MENU = "ÅTERST. MENY",

      .NTC_Enable_NTC = "Aktivera NTC",
      .NTC_Pull = "Pull",
      .NTC__Res = " Res",
      .NTC__Beta = " Beta",
      .NTC_NTC_Detect = "NTC Auto-avk.",
      .NTC__High = " Hög",
      .NTC__Low = " Låg",

      .RESET_Reset_Settings = "Återst. Inst.",
      .RESET_Reset_Profile = "Återst. Profil",
      .RESET_Reset_Profiles = "Återst. Profiler",
      .RESET_Reset_All = "Återst. Allt",
      .RESET_Reset_msg_settings_1 = "ÅTERST. SYSTEM-",
      .RESET_Reset_msg_settings_2 = "INSTÄLLNINGAR?",
      .RESET_Reset_msg_profile_1 = "ÅTERST. AKTUELL",
      .RESET_Reset_msg_profile_2 = "PROFIL?",
      .RESET_Reset_msg_profiles_1 = "ÅTERST. ALLA",
      .RESET_Reset_msg_profiles_2 = "PROFILER?",
      .RESET_Reset_msg_all_1 = "UTFÖR TOTAL",
      .RESET_Reset_msg_all_2 = "SYSTEMÅTERST.?",

      .TIP_SETTINGS_Name = "Namn",
      .TIP_SETTINGS_PID_kd = "PID Kp",
      .TIP_SETTINGS_PID_ki = "PID Ki",
      .TIP_SETTINGS_PID_kp = "PID Kd",
      .TIP_SETTINGS_PID_Imax = "PID Imax",
      .TIP_SETTINGS_PID_Imin = "PID Imin",
      .TIP_SETTINGS_COPY = "KOPIERA",
      .TIP_SETTINGS_DELETE = "RADERA",

      .CAL_Step = "KAL STEG:",
      .CAL_Wait = "VÄNTA...",
      .CAL_Measured = "UPPMÄTT:",
      .CAL_Success = "KAL.OK!",
      .CAL_Failed = "KAL.FEL!",
      .CAL_DELTA_HIGH_1 = "DELTA FÖR HÖGT!",
      .CAL_DELTA_HIGH_2 = "Justera manuellt",
      .CAL_DELTA_HIGH_3 = "och försök igen",
      .CAL_Error = "FEL UPPTÄCKT!",
      .CAL_Aborting = "Avbryter...",

      ._Language = "Språk",
      .__Temp = " Temp",
      .__Delay = " Fördr.",
      ._Cal_250 = "Kal 250\260C",
      ._Cal_400 = "Kal 400\260C",
      ._BACK = "TILLBAKA",
      ._SAVE = "SPARA",
      ._CANCEL = "AVBRYT",
      ._STOP = "STOPP",
      ._RESET = "ÅTERST.",
      ._START = "START",
      ._SETTINGS = "INSTÄLLNINGAR",
      ._ADD_NEW = "LÄGG TILL",

      .ERROR_RUNAWAY = "TEMP AVVIKELSE",
      .ERROR_EXCEEDED = "ÖVERSKRIDET",
      .ERROR_UNKNOWN = "OKÄNT FEL",
      .ERROR_SYSTEM_HALTED = "SYSTEM STOPPAT",
      .ERROR_BTN_RESET = "Anv knapp för återst.",

      .OffOn =       { "AV", "PÅ" },
      .DownUp =      { "NER", "UPP" },
      .WakeModes =   { "AV", "STBY", "SOV", "ALLA" },
      .wakeMode =    { "SKAKA", "STÄLL" },
      .encMode =     { "OMVÄND", "NORMAL" },
      .InitMode =    { "SOV", "STBY", "KÖR" },
      .dimMode =     { "AV", "SOV", "ALLA" },
    },
};


char * tempUnit[2] =    { "\260C", "\260F" };
char * profileStr[ProfileSize] = { "T12", "C245", "C210" };
char * Langs[LANGUAGE_COUNT] = {
                                   [lang_english] = "EN",
                                   [lang_russian] = "RU",
                                   [lang_swedish] = "SE",
                               };
