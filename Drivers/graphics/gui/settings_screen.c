/*
 * debug_screen.c
 *
 *  Created on: Aug 2, 2017
 *      Author: jose
 */

#include "settings_screen.h"
#include "oled.h"

//-------------------------------------------------------------------------------------------------------------------------------
// Settings screen variables
//-------------------------------------------------------------------------------------------------------------------------------
static char t[sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0])][sizeof(systemSettings.ironTips[0].name)];
static uint16_t temp;
char str[5];
static char *oledFixstr[] = {" No", "Yes" };
static char *tempstr[] = {"*C", "*F" };
bool TempUnit;

//-------------------------------------------------------------------------------------------------------------------------------
// Settings screen widgets
//-------------------------------------------------------------------------------------------------------------------------------
static widget_t Widget_IronTips_Name_back;
static widget_t Widget_IronTips_Name_save;
static widget_t Widget_IronTips_Name_delete;
static widget_t Widget_IronTips_Name_edit;
static widget_t Widget_Misc_OK;
static widget_t Widget_TempUnit_edit;
static widget_t Widget_Gui_Upd_edit;
static widget_t Widget_Save_Delay_edit;
static widget_t Widget_Detection_OK;
static widget_t Widget_NoIron_Delay_edit;
static widget_t Widget_ADC_Limit_edit;
static widget_t Widget_PWM_OK;
static widget_t Widget_ADC_Delay_edit;
static widget_t Widget_PWM_Period_edit;
static widget_t Widget_Boost_OK;
static widget_t Widget_Boost_Temp_edit;
static widget_t Widget_Boost_Time_edit;
static widget_t Widget_Sleep_OK;
static widget_t Widget_Stby_Time_edit;
static widget_t Widget_Sleep_Temp_edit;
static widget_t Widget_Sleep_Time_edit;
static widget_t Widget_Power_edit;
static widget_t Widget_Contrast_edit;
static widget_t Widget_OledFix_edit;
static widget_t Widget_Screen_OK;
static widget_t Widget_PID_OK;
static widget_t Widget_PID_Kd_edit;
static widget_t Widget_PID_Ki_edit;
static widget_t Widget_PID_Kp_edit;

static widget_t Widget_Settings_combo;
static comboBox_item_t Settings_Combo_PID;
static comboBox_item_t Settings_Combo_SCREEN;
static comboBox_item_t Settings_Combo_SLEEP;
static comboBox_item_t Settings_Combo_BOOST;
static comboBox_item_t Settings_Combo_PWM;
static comboBox_item_t Settings_Combo_DETECTION;
static comboBox_item_t Settings_Combo_MISC;
static comboBox_item_t Settings_Combo_TIPTYPE;
static comboBox_item_t Settings_Combo_TIPS;
static comboBox_item_t Settings_Combo_CALIBRATION;
static comboBox_item_t Settings_Combo_TESTOPTS;
static comboBox_item_t Settings_Combo_EXIT;

static widget_t Widget_Settings_opts_combo;
static comboBox_item_t Widget_Settings_opts_combo_opt1;
static comboBox_item_t Widget_Settings_opts_combo_opt2;
static comboBox_item_t Widget_Settings_opts_combo_opt3;
static comboBox_item_t Widget_Settings_opts_combo_opt4;
static comboBox_item_t Widget_Settings_opts_combo_opt5;
static comboBox_item_t Widget_Settings_opts_combo_exit;
static widget_t Widget_testopts_num;
static widget_t Widget_testopts_multimode;

static widget_t Widget_IronTips_Combo;
static comboBox_item_t IronTips[ sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0]) ];
static comboBox_item_t IronTips_addNewTip;
static comboBox_item_t IronTips_Exit;

//-------------------------------------------------------------------------------------------------------------------------------
// Settings screen widgets functions
//-------------------------------------------------------------------------------------------------------------------------------
static void edit_iron_tip_screen_init(screen_t *scr) {
	if(strcmp(Widget_IronTips_Combo.comboBoxWidget.currentItem->text, "ADD NEW") == 0) {
		strcpy(str, "    ");
		Widget_IronTips_Name_delete.enabled = 0;
	}
	else {
		strcpy(str, Widget_IronTips_Combo.comboBoxWidget.currentItem->text);
		if(systemSettings.currentNumberOfTips>1){
			Widget_IronTips_Name_delete.enabled = 1;
		}
		else{
			Widget_IronTips_Name_delete.enabled = 0;
		}
	}
	default_init(scr);
}
static void edit_iron_screen_init(screen_t *scr) {
	comboBox_item_t *i =Widget_IronTips_Combo.comboBoxWidget.items;
	for(int x = 0; x < sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0]); ++x) {
		if(x < systemSettings.currentNumberOfTips) {
			strcpy(i->text, systemSettings.ironTips[x].name);
			i->enabled = 1;
		}
		else
			i->enabled = 0;
		i = i->next_item;
	}
	Widget_IronTips_Combo.comboBoxWidget.currentItem = Widget_IronTips_Combo.comboBoxWidget.items;
	Widget_IronTips_Combo.comboBoxWidget.currentScroll = 0;
	if(systemSettings.currentNumberOfTips >= sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0])) {
		IronTips_addNewTip.enabled = 0;
	}

	else{
		IronTips_addNewTip.enabled = 1;
	}
}
static void *getTipStr() {
	return str;
}

static void setTipStr(char *s) {
	strcpy(str, s);
}
static int saveTip(widget_t *w) {
	if(strcmp(Widget_IronTips_Combo.comboBoxWidget.currentItem->text, "ADD NEW") == 0) {
		strcpy(systemSettings.ironTips[systemSettings.currentNumberOfTips].name, str);
		++systemSettings.currentNumberOfTips;
	}
	else {
		for(int x = 0; x < sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0]); ++ x) {
			if(strcmp(Widget_IronTips_Combo.comboBoxWidget.currentItem->text, systemSettings.ironTips[x].name) == 0) {
				strcpy(systemSettings.ironTips[x].name, str);
				break;
			}
		}
	}
	return screen_edit_iron_tips;
}
static int cancelTip(widget_t *w) {
	return screen_edit_iron_tips;
}
static int delTip(widget_t *w) {
	uint8_t itemIndex = 0;
	for(int x = 0; x < sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0]); ++ x) {
		if(strcmp(Widget_IronTips_Combo.comboBoxWidget.currentItem->text, systemSettings.ironTips[x].name) == 0) {
			itemIndex = x;
			break;
		}
	}
	for(int x = itemIndex; x < sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0]) - 1; ++ x) {
		systemSettings.ironTips[x] = systemSettings.ironTips[x + 1];
	}
	--systemSettings.currentNumberOfTips;
	return screen_edit_iron_tips;
}

static void * getMaxPower() {
	temp = currentPID.max * 100;
	return &temp;
}
static void setMaxPower(uint16_t *val) {
	currentPID.max = (double)*val / 100.0;
	systemSettings.ironTips[systemSettings.currentTip].PID.max=currentPID.max;
	setupPIDFromStruct();
}

static void * getContrast_() {
	temp = systemSettings.contrast;
	return &temp;
}
static void setContrast_(uint16_t *val) {
	systemSettings.contrast=*val;
	setContrast(*val);
}

static void * getBoostTime() {
	temp = systemSettings.boost.Time;
	return &temp;
}
static void setBoostTime(uint16_t *val) {
	systemSettings.boost.Time = *val;
}
static void * getBoostTemp() {
	temp = systemSettings.boost.Temperature;
	return &temp;

}
static void setBoostTemp(uint16_t *val) {
	systemSettings.boost.Temperature = *val;
}
static int returnSettingsScreen(widget_t *w) {
	return screen_settings;
}

static void setSleepTime(uint16_t *val) {
	systemSettings.sleep.Time = *val;
}

static void * getSleepTime() {
	temp = systemSettings.sleep.Time;
	return &temp;
}
static void setStandByTime(uint16_t *val) {
	systemSettings.standby.Time  = *val;
}
static void * getStandByTime() {
	temp = systemSettings.standby.Time;
	return &temp;
}
static void setSleepTemp(uint16_t *val) {
	systemSettings.sleep.Temperature = *val;
}
static void * getSleepTemp() {
	temp = systemSettings.sleep.Temperature;
	return &temp;
}

static void * getKp() {
	temp = currentPID.Kp * 1000000;
	return &temp;
}
static void setKp(uint16_t *val) {
	currentPID.Kp = (double)*val / 1000000;
	systemSettings.ironTips[systemSettings.currentTip].PID.Kp=currentPID.Kp ;
	setupPIDFromStruct();
}
static void * getKi() {
	temp = currentPID.Ki * 1000000;
	return &temp;
}
static void setKi(uint16_t *val) {
	currentPID.Ki = (double)*val / 1000000;
	systemSettings.ironTips[systemSettings.currentTip].PID.Ki=currentPID.Ki;
	setupPIDFromStruct();
}
static void * getKd() {
	temp = currentPID.Kd * 1000000;
	return &temp;
}
static void setKd(uint16_t *val) {
	currentPID.Kd = (double)*val / 1000000;
	systemSettings.ironTips[systemSettings.currentTip].PID.Kd=currentPID.Kd;
	setupPIDFromStruct();
}

static void * getPwmPeriod() {
	temp=(systemSettings.pwmPeriod+1)/100;
	if(temp<501){
		Widget_ADC_Delay_edit.editable.max_value = temp-1;
	}
	else{
		Widget_ADC_Delay_edit.editable.max_value = 500;
	}
	return &temp;
}
static void setPwmPeriod(uint16_t *val) {
	systemSettings.pwmPeriod = (*val*100)-1;
	ApplyPwmSettings();
}
static void * getPwmDelay() {
	temp=(systemSettings.pwmDelay+1)/100;


	return &temp;
}
static void setPwmDelay(uint16_t *val) {
	systemSettings.pwmDelay=(*val*100)-1;
	ApplyPwmSettings();
}

static void * getTmpUnit() {
	temp = systemSettings.tempUnit;
	return &temp;
}
static void setTmpUnit(uint16_t *val) {
	setTempUnit(*val);
}
static void * getOledFix() {
	temp = systemSettings.OledFix;
	return &temp;
}
static void setOledFix(uint16_t *val) {
	systemSettings.OledFix= * val;
}

static void * getGuiUpd_ms() {
	temp = systemSettings.guiUpdateDelay;
	return &temp;
}
static void setGuiUpd_ms(uint16_t *val) {
	systemSettings.guiUpdateDelay = *val;

}

static void * getSavDelay() {
	temp =systemSettings.saveSettingsDelay;
	return &temp;
}
static void setSavDelay(uint16_t *val) {
	systemSettings.saveSettingsDelay = *val;
}

static void * getNoIronDelay() {
	temp = systemSettings.noIronDelay;
	return &temp;
}
static void setNoIronDelay(uint16_t *val) {
	systemSettings.noIronDelay = *val;
}

static void * getNoIronADC() {
	temp = systemSettings.noIronValue;
	return &temp;
}
static void setNoIronADC(uint16_t *val) {
	systemSettings.noIronValue = *val;

}
static void tempUnitChanged(void) {
	TempUnit = systemSettings.tempUnit;
	if(TempUnit==Unit_Farenheit){
		Widget_Boost_Temp_edit.endString="*F";
		Widget_Sleep_Temp_edit.endString="*F";
		Widget_Boost_Temp_edit.editable.max_value=900;
		Widget_Boost_Temp_edit.editable.min_value=400;
		Widget_Boost_Temp_edit.editable.big_step = 50;
		Widget_Boost_Temp_edit.editable.step = 10;
		Widget_Sleep_Temp_edit.editable.max_value=750;
		Widget_Sleep_Temp_edit.editable.min_value=300;
		Widget_Sleep_Temp_edit.editable.big_step = 50;
		Widget_Sleep_Temp_edit.editable.step = 10;
	}
	else{
		Widget_Boost_Temp_edit.endString="*C";
		Widget_Sleep_Temp_edit.endString="*C";
		Widget_Boost_Temp_edit.editable.max_value=480;
		Widget_Boost_Temp_edit.editable.min_value=200;
		Widget_Boost_Temp_edit.editable.big_step = 50;
		Widget_Boost_Temp_edit.editable.step = 10;
		Widget_Sleep_Temp_edit.editable.max_value=400;
		Widget_Sleep_Temp_edit.editable.min_value=150;
		Widget_Sleep_Temp_edit.editable.big_step = 50;
		Widget_Sleep_Temp_edit.editable.step = 10;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------
// Settings screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void settings_screenUpdate(screen_t *scr) {
	if(TempUnit != systemSettings.tempUnit){
		tempUnitChanged();
	}
	default_screenUpdate(scr);
}

static void settings_screen_init(screen_t *scr) {
	UG_FontSetHSpace(0);
	UG_FontSetVSpace(0);
	default_init(scr);
	tempUnitChanged();
	scr->current_widget = &Widget_Settings_combo;
	scr->current_widget->comboBoxWidget.selectable.state = widget_selected;
}
int settings_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
	if(input==LongClick){
		return screen_debug;
	}
	return (default_screenProcessInput(scr, input, state));
}
static void settings_screen_exit(screen_t *scr) {
	//comboResetIndex(&Widget_Settings_combo);
}
//-------------------------------------------------------------------------------------------------------------------------------
// TEST screen functions
//-------------------------------------------------------------------------------------------------------------------------------

static void settings_screen_test_exit(screen_t *scr) {
	comboResetIndex(&Widget_Settings_opts_combo);
}
//-------------------------------------------------------------------------------------------------------------------------------
// PID screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void pid_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(15,1,"Kp:");//12
	UG_PutString(15,17,"Ki:");//12
	UG_PutString(15,33,"Kd:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Screen screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void screen_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(0,17,"Brightness:");//12
	UG_PutString(0,33,"Oled fix:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Sleep screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void sleep_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(0,1,"Sleep Time:");//12
	UG_PutString(0,17,"Sleep Temp:");//12
	UG_PutString(0,33,"StdBy Time:");//12
	default_screenDraw(scr);

}

//-------------------------------------------------------------------------------------------------------------------------------
// Boost screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void boost_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(0,17,"Boost Time:");//12
	UG_PutString(0,33,"Boost Temp:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// PWM screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void pwm_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(0,1,"Max power");//12
	UG_PutString(0,17,"PWM Period:");//12
	UG_PutString(0,33,"ADC Delay:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Detection screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void detection_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(0,17,"ADC limit:");//12
	UG_PutString(0,33,"Delay:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Misc screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void misc_screenDraw(screen_t *scr){
	UG_FontSelect(&FONT_8X14_reduced);
	UG_PutString(0,1,"Save Delay:");//12
	UG_PutString(0,17,"GuiUpdate:");//12
	UG_PutString(0,33,"Temp Unit:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Edit Tip screen functions
//-------------------------------------------------------------------------------------------------------------------------------
void edittipname_screenDraw(screen_t *scr){
	static bool prevState;
	if(strcmp(str, "    ") == 0) {
		if(!prevState){
			prevState=1;
			Widget_IronTips_Name_save.enabled=0;
			FillBuffer(C_BLACK,fill_dma);
		}
	}
	else{
		if(prevState){
			prevState=0;
			Widget_IronTips_Name_save.enabled=1;
			FillBuffer(C_BLACK,fill_dma);
		}
	}
	UG_FontSelect(&FONT_10X16_reduced);
	UG_PutString(0,17,"NAME:");//12
	default_screenDraw(scr);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Settings screen setup
//-------------------------------------------------------------------------------------------------------------------------------
void settings_screen_setup(screen_t *scr) {
	screen_t* sc;
	widget_t* w;

	///settings combobox
	scr->draw = &default_screenDraw;
	scr->processInput = &settings_screenProcessInput;
	scr->init = &settings_screen_init;
	scr->update = &settings_screenUpdate;
	scr->onExit = &settings_screen_exit;

	//###############################
	// Settings screen comboBox
	//###############################
	w = &Widget_Settings_combo;
	screen_addWidget(w, scr);
	widgetDefaultsInit(w, widget_combo);
	w->posY = 0;
	w->posX = 0;
	w->font_size = &FONT_8X14_reduced;
	comboAddScreen(&Settings_Combo_PID, w, "PID", screen_edit_pid);
	comboAddScreen(&Settings_Combo_SCREEN, w, "SCREEN", screen_edit_screen);
	comboAddScreen(&Settings_Combo_SLEEP, w, "SLEEP", screen_edit_sleep);
	comboAddScreen(&Settings_Combo_BOOST, w, "BOOST", screen_edit_boost);
	comboAddScreen(&Settings_Combo_PWM, w, "PWM", screen_edit_pwm);
	comboAddScreen(&Settings_Combo_DETECTION, w, "DETECTION", screen_edit_detection);
	comboAddScreen(&Settings_Combo_MISC, w, "MISC", screen_edit_misc);
	comboAddScreen(&Settings_Combo_TIPTYPE, w, "TIP TYPE", screen_tiptype);
	comboAddScreen(&Settings_Combo_TIPS, w, "TIPS", screen_edit_iron_tips);
	comboAddScreen(&Settings_Combo_CALIBRATION, w, "CALIBRATION", screen_edit_calibration_wait);
	comboAddScreen(&Settings_Combo_TESTOPTS, w, "TEST OPTS", screen_edit_test_opts);
	comboAddScreen(&Settings_Combo_EXIT, w, "EXIT", screen_main);

	//###############################
	// PID Control screen
	//###############################
	sc=&Screen_edit_pid;
	oled_addScreen(sc,screen_edit_pid);
	sc->draw = &pid_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// Kp edit
	w = &Widget_PID_Kp_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 78;
	w->posY = 1;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getKp;
	w->editable.inputData.number_of_dec = 2;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 200;
	w->editable.step = 100;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setKp;
	w->reservedChars = 6;
	w->displayWidget.justify = justify_right;

	// Ki edit
	w = &Widget_PID_Ki_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 78;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getKi;
	w->editable.inputData.number_of_dec = 2;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 200;
	w->editable.step = 100;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setKi;
	w->reservedChars = 6;
	w->displayWidget.justify = justify_right;

	// Kd edit
	w = &Widget_PID_Kd_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 78;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getKd;
	w->editable.inputData.number_of_dec = 2;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 200;
	w->editable.step = 100;
	w->editable.selectable.tab = 2;
	w->editable.setData = (void (*)(void *))&setKd;
	w->reservedChars = 6;
	w->displayWidget.justify = justify_right;

	// OK Button
	w = &Widget_PID_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 3;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// Edit Screen screen
	//###############################
	sc=&Screen_edit_contrast;
	oled_addScreen(sc,screen_edit_screen);
	sc->draw = &screen_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// Brightness edit
	w = &Widget_Contrast_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 102;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getContrast_;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 5;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setContrast_;
	w->editable.max_value = 255;
	w->editable.min_value = 0;
	w->displayWidget.hasEndStr = 0;
	w->reservedChars = 3;

	// Oled Fix edit
	w = &Widget_OledFix_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_multi_option);
	w->posX = 102;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getOledFix;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 1;
	w->editable.step = 1;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setOledFix;
	w->displayWidget.hasEndStr = 0;
	w->reservedChars = 3;
	w->multiOptionWidget.options = oledFixstr;
	w->multiOptionWidget.numberOfOptions = 2;
	w->editable.max_value = 1;
	w->editable.min_value = 0;

	// OK Button
	w = &Widget_Screen_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 2;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// Edit sleep screen
	//###############################
	sc=&Screen_edit_sleep;
	oled_addScreen(sc,screen_edit_sleep);
	sc->draw = &sleep_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// Sleep time
	w = &Widget_Sleep_Time_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 1;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getSleepTime;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 10;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setSleepTime;
	w->editable.max_value = 600;
	w->editable.min_value = 0;
	w->displayWidget.hasEndStr = 1;
	w->endString="s";
	w->reservedChars = 4;
	w->displayWidget.justify =justify_right;

	// Sleep temp
	w = &Widget_Sleep_Temp_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getSleepTemp;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 10;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setSleepTemp;
	w->reservedChars = 4;
	w->displayWidget.hasEndStr = 1;
	w->displayWidget.justify =justify_right;

	// StandBy time
	w = &Widget_Stby_Time_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getStandByTime;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 10;
	w->editable.selectable.tab = 2;
	w->editable.setData = (void (*)(void *))&setStandByTime;
	w->reservedChars = 4;
	w->editable.max_value = 600;
	w->editable.min_value = 0;
	w->displayWidget.hasEndStr = 1;
	w->endString="s";
	w->displayWidget.justify =justify_right;

	// OK Button
	w = &Widget_Sleep_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 3;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// Edit boost screen
	//###############################
	sc=&Screen_edit_boost;
	oled_addScreen(sc,screen_edit_boost);
	sc->draw = &boost_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// Boost time
	w = &Widget_Boost_Time_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getBoostTime;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 5;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setBoostTime;
	w->editable.max_value = 600;
	w->editable.min_value = 5;
	w->displayWidget.hasEndStr = 1;
	w->endString="s";
	w->reservedChars = 4;
	w->displayWidget.justify =justify_right;

	// Boost temp
	w = &Widget_Boost_Temp_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getBoostTemp;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 10;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setBoostTemp;
	w->reservedChars = 4;
	w->displayWidget.hasEndStr = 1;
	w->displayWidget.justify =justify_right;

	w = &Widget_Boost_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 2;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// PWM screen
	//###############################
	sc=&Screen_edit_pwm;
	oled_addScreen(sc, screen_edit_pwm);
	sc->draw = &pwm_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// Max Power
	w = &Widget_Power_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 1;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getMaxPower;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 5;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setMaxPower;
	w->editable.max_value = 100;
	w->editable.min_value = 5;
	w->displayWidget.hasEndStr = 1;
	w->endString="%";
	w->reservedChars = 4;
	w->displayWidget.justify =justify_right;

	// PWM Period
	w = &Widget_PWM_Period_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 86;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getPwmPeriod;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 5;
	w->editable.step = 1;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setPwmPeriod;
	w->editable.max_value = 650;
	w->editable.min_value = 20;
	w->displayWidget.hasEndStr = 1;
	w->endString="mS";
	w->reservedChars = 5;
	w->displayWidget.justify =justify_right;

	// ADC Delay
	w = &Widget_ADC_Delay_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 86;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getPwmDelay;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 5;
	w->editable.step = 1;
	w->editable.selectable.tab = 2;
	w->editable.setData = (void (*)(void *))&setPwmDelay;
	w->reservedChars = 5;
	w->editable.max_value = 500;
	w->editable.min_value = 1;
	w->displayWidget.hasEndStr = 1;
	w->endString="mS";
	w->displayWidget.justify =justify_right;

	// OK Button
	w = &Widget_PWM_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 3;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// Iron detection Screen
	//###############################
	sc=&Screen_edit_detection;
	oled_addScreen(sc, screen_edit_detection);
	sc->draw = &detection_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// ADC Limit
	w = &Widget_ADC_Limit_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 94;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getNoIronADC;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 200;
	w->editable.step = 10;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setNoIronADC;
	w->editable.max_value = 4100;
	w->editable.min_value = 200;
	w->displayWidget.hasEndStr = 0;
	w->reservedChars = 4;
	w->displayWidget.justify =justify_right;

	// No Iron delay
	w = &Widget_NoIron_Delay_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 86;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getNoIronDelay;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 100;
	w->editable.step = 50;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setNoIronDelay;
	w->reservedChars = 5;
	w->editable.max_value = 1000;
	w->editable.min_value = 100;
	w->displayWidget.hasEndStr = 1;
	w->endString="mS";
	w->displayWidget.justify =justify_right;

	// OK Button
	w = &Widget_Detection_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 2;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// MISC Screen
	//###############################
	sc=&Screen_edit_misc;
	oled_addScreen(sc,screen_edit_misc);
	sc->draw = &misc_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;

	// Save Delay
	w = &Widget_Save_Delay_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 102;//102
	w->posY = 1;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getSavDelay;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 1;
	w->editable.step = 1;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setSavDelay;
	w->editable.max_value = 60;
	w->editable.min_value = 1;
	w->displayWidget.hasEndStr = 1;
	w->endString="s";
	w->reservedChars = 3;
	w->displayWidget.justify =justify_right;

	// Gui Update mS
	w = &Widget_Gui_Upd_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 86;
	w->posY = 17;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getGuiUpd_ms;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 100;
	w->editable.step = 10;
	w->editable.selectable.tab = 1;
	w->editable.setData = (void (*)(void *))&setGuiUpd_ms;
	w->editable.max_value = 500;
	w->editable.min_value = 0;
	w->displayWidget.hasEndStr = 1;
	w->endString="mS";
	w->reservedChars = 5;
	w->displayWidget.justify =justify_right;

	// Temp unit
	w = &Widget_TempUnit_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_multi_option);
	w->posX = 110;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getTmpUnit;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 1;
	w->editable.step = 1;
	w->editable.selectable.tab = 2;
	w->editable.setData = (void (*)(void *))&setTmpUnit;
	w->reservedChars = 2;
	w->editable.max_value = Unit_Farenheit;
	w->editable.min_value = Unit_Celsius;
	w->multiOptionWidget.options = tempstr;
	w->multiOptionWidget.numberOfOptions = 2;

	// OK Button
	w = &Widget_Misc_OK;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 110;
	w->posY = 50;
	strcpy(w->displayString, "OK");
	w->reservedChars = 2;
	w->buttonWidget.selectable.tab = 3;
	w->buttonWidget.action = &returnSettingsScreen;

	//###############################
	// Edit iron tips screen
	//###############################
	sc=&Screen_edit_iron_tips;
	oled_addScreen(sc, screen_edit_iron_tips);
	sc->draw = &default_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &edit_iron_screen_init;
	sc->update = &default_screenUpdate;

	// Iron Tips ComboBox
	w = &Widget_IronTips_Combo;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_combo);
	w->posY = 5;
	w->posX = 0;
	w->font_size = &FONT_10X16_reduced;

	for(int x = 0; x < sizeof(systemSettings.ironTips) / sizeof(systemSettings.ironTips[0]); ++x) {
		t[x][0] = '\0';
		comboAddScreen(&IronTips[x],w, &t[x][0], screen_edit_tip_name);
	}
	comboAddScreen(&IronTips_addNewTip, w, "ADD NEW", screen_edit_tip_name);
	comboAddScreen(&IronTips_Exit, w, "EXIT", screen_settings);
	sc->current_widget = w;

	//###############################
	//Screen edit iron tip
	//###############################
	sc=&Screen_edit_tip_name;
	oled_addScreen(sc, screen_edit_tip_name);
	sc->draw = &edittipname_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &edit_iron_tip_screen_init;
	sc->update = &default_screenUpdate;

	// Name Edit
	w = &Widget_IronTips_Name_edit;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_editable);
	w->posX = 50;
	w->posY = 17;
	w->font_size = &FONT_10X16_reduced;
	w->editable.inputData.getData = &getTipStr;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_string;
	w->editable.big_step = 10;
	w->editable.step = 1;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setTipStr;
	w->editable.max_value = 9999;
	w->reservedChars = 4;

	// Name Save
	w = &Widget_IronTips_Name_save;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 2;
	w->posY = 50;
	strcpy(w->displayString, "SAVE");
	w->reservedChars = 4;
	w->buttonWidget.selectable.tab = 3;
	w->buttonWidget.action = &saveTip;

	// Name Back
	w = &Widget_IronTips_Name_back;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 94;
	w->posY = 50;
	strcpy(w->displayString, "BACK");
	w->reservedChars = 4;
	w->buttonWidget.selectable.tab = 1;
	w->buttonWidget.action = &cancelTip;

	// Name Delete
	w = &Widget_IronTips_Name_delete;
	screen_addWidget(w,sc);
	widgetDefaultsInit(w, widget_button);
	w->font_size = &FONT_8X14_reduced;
	w->posX = 48;
	w->posY = 50;
	strcpy(w->displayString, "DEL.");
	w->reservedChars = 4;
	w->buttonWidget.selectable.tab = 2;
	w->buttonWidget.action = &delTip;
	w->buttonWidget.action = &delTip;

	//###############################
	// TEST screen
	//###############################
	sc=&Screen_edit_test_opts;
	oled_addScreen(sc,screen_edit_test_opts);
	sc->draw = &default_screenDraw;
	sc->processInput = &default_screenProcessInput;
	sc->init = &default_init;
	sc->update = &default_screenUpdate;
	sc->onExit = &settings_screen_test_exit;

	w = &Widget_testopts_num;
	widgetDefaultsInit(w, widget_editable);
	w->posX = 102;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getContrast_;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 20;
	w->editable.step = 5;
	w->editable.selectable.tab = 0;
	w->editable.setData = (void (*)(void *))&setContrast_;
	w->editable.max_value = 255;
	w->editable.min_value = 0;
	w->displayWidget.hasEndStr = 0;
	strcpy(w->displayString,"255");
	w->reservedChars = 3;
	w = &Widget_testopts_multimode;
	widgetDefaultsInit(w, widget_multi_option);
	w->posX = 110;
	w->posY = 33;
	w->font_size = &FONT_8X14_reduced;
	w->editable.inputData.getData = &getTmpUnit;
	w->editable.inputData.number_of_dec = 0;
	w->editable.inputData.type = field_uinteger16;
	w->editable.big_step = 1;
	w->editable.step = 1;
	w->editable.selectable.tab = 2;
	w->editable.setData = (void (*)(void *))&setTmpUnit;
	w->reservedChars = 2;
	w->editable.max_value = Unit_Farenheit;
	w->editable.min_value = Unit_Celsius;
	w->multiOptionWidget.options = tempstr;
	w->multiOptionWidget.numberOfOptions = 2;

	w = &Widget_Settings_opts_combo;
	screen_addWidget(w, sc);
	widgetDefaultsInit(w, widget_combo);
	w->posY = 0;
	w->posX = 0;
	w->font_size = &FONT_8X14_reduced;
	comboAddScreen(&Widget_Settings_opts_combo_opt1, w, "OPT1", screen_settings);
	comboAddScreen(&Widget_Settings_opts_combo_opt2, w, "OPT2", screen_settings);
	comboAddOption(&Widget_Settings_opts_combo_opt3, w, "NUM:", &Widget_testopts_num);
	comboAddOption(&Widget_Settings_opts_combo_opt4, w, "M.MODE:", &Widget_testopts_multimode);
	comboAddScreen(&Widget_Settings_opts_combo_opt5, w, "OPT5", screen_settings);
	comboAddScreen(&Widget_Settings_opts_combo_exit, w, "EXIT", screen_settings);
}
