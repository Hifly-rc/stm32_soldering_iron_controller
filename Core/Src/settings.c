/*
 * settings.c
 *
 *  Created on: Sep 13, 2017
 *      Author: jose
 */

#include "settings.h"
#include <string.h>


systemSettings_t systemSettings = {0};
systemSettings_t* flashSettings = (systemSettings_t*)FLASH_ADDR;

void Checksum_error(void);
void Flash_error(void);
void Button_reset(void);
void Diag_init(void);
void ErrCountDown(uint8_t Start,uint8_t xpos, uint8_t ypos);

void saveSettings() {
	uint32_t error=0;

	// Calculate new checksum
	systemSettings.checksum=ChecksumSettings(&systemSettings);

	HAL_FLASH_Unlock(); //unlock flash writing
	FLASH_EraseInitTypeDef erase;
	erase.NbPages = 1;
	erase.PageAddress = FLASH_ADDR;
	erase.TypeErase = FLASH_TYPEERASE_PAGES;

	//Erase flash page
	if(HAL_FLASHEx_Erase(&erase, &error)!=HAL_OK){
		Flash_error();
	}
	if(error!=0xFFFFFFFF){
		Flash_error();
		HAL_FLASH_Lock();
		return;
	}
	// Ensure that the flash was erased
	for (uint16_t i = 0; i < sizeof(systemSettings)/2; i++) {
			if( *(uint16_t*)(FLASH_ADDR+(i*2)) != 0xFFFF){
				Flash_error();
			}
		}

	//Store settings
	HAL_IWDG_Refresh(&hiwdg);
	for (uint16_t i = 0; i < sizeof(systemSettings) / 2; i++) {
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (((uint32_t)flashSettings)+(i*2)), *(((uint16_t*)&systemSettings)+i) ) != HAL_OK){
			Flash_error();
		}
	}
	HAL_FLASH_Lock();

	//Ensure flash data has the same CRC as systemSettings
	if(ChecksumSettings(flashSettings)!=systemSettings.checksum){
		Flash_error();
	}
}

void restoreSettings() {
#ifdef NOSAVESETTINGS				// Stop erasing the flash every time while in debug mode
	resetSettings();
	currentPID = systemSettings.ironTips[systemSettings.currentTip].PID;
	setupPIDFromStruct();
	return;
#endif
	Button_reset();
	systemSettings = *flashSettings;
	// Compare loaded checksum with calculated checksum
	if( (systemSettings.version != SETTINGSVERSION) || (ChecksumSettings(&systemSettings)!=systemSettings.checksum) ){
		Checksum_error();
	}
	currentPID = systemSettings.ironTips[systemSettings.currentTip].PID;
	setupPIDFromStruct();
	setContrast(systemSettings.contrast);
}

uint32_t ChecksumSettings(systemSettings_t* Settings){
	uint32_t checksum;
	checksum = HAL_CRC_Calculate(&hcrc, ((uint32_t*)&Settings->version), (sizeof(*Settings)-sizeof(Settings->checksum))/sizeof(uint32_t) );
	return checksum;
}

void resetSettings() {
	systemSettings.version = SETTINGSVERSION;
	systemSettings.contrast = 0xFF;
	systemSettings.OledFix = 1;
	systemSettings.boost.Time = 30;
	systemSettings.boost.Temperature = 400;
	systemSettings.sleep.Time = 120;
	systemSettings.sleep.Temperature = 150;
	systemSettings.standby.Time = 300;
	systemSettings.UserSetTemperature = 320;
	systemSettings.pwmPeriod=19999;
	systemSettings.pwmDelay=99;
	systemSettings.noIronDelay=500;
	systemSettings.guiUpdateDelay=200;
	systemSettings.tempUnit=Unit_Celsius;
	systemSettings.saveSettingsDelay=10;
	systemSettings.TipType=Tip_None;
	systemSettings.bootMode=mode_normal;
	systemSettings.buzzDisable=0;
	resetTips();
}


void resetTips(void){

	if(systemSettings.TipType==Tip_T12){

		systemSettings.noIronValue=4000;
		strcpy(systemSettings.ironTips[0].name, "DFLT");
		for(uint8_t x = 0; x < ( sizeof(systemSettings.ironTips)/sizeof(systemSettings.ironTips[0])); ++x) {
			systemSettings.ironTips[x].calADC_At_200 = 1300;
			systemSettings.ironTips[x].calADC_At_300 = 2000;
			systemSettings.ironTips[x].calADC_At_400 = 3000;
			systemSettings.ironTips[x].PID.Kp = 0.0003;
			systemSettings.ironTips[x].PID.Kd = 0;
			systemSettings.ironTips[x].PID.Ki = 0.0025;
			systemSettings.ironTips[x].PID.min = 0;
			systemSettings.ironTips[x].PID.max = 1;
			systemSettings.ironTips[x].PID.maxI = 200;
			systemSettings.ironTips[x].PID.minI = -50;
		}
		systemSettings.currentNumberOfTips = 4;
		systemSettings.currentTip = 0;

		strcpy(systemSettings.ironTips[1].name, "B  ");
		systemSettings.ironTips[1].calADC_At_200 = 1221;
		systemSettings.ironTips[1].calADC_At_300 = 1904;
		systemSettings.ironTips[1].calADC_At_400 = 2586;
		systemSettings.ironTips[1].PID.Kp = 0.0040069999999999999;
		systemSettings.ironTips[1].PID.Ki = 0.003106000000000002;
		systemSettings.ironTips[1].PID.Kd = 0.00007;

		strcpy(systemSettings.ironTips[2].name, "BC2");
		systemSettings.ironTips[2].calADC_At_200 = 1463;
		systemSettings.ironTips[2].calADC_At_300 = 2313;
		systemSettings.ironTips[2].calADC_At_400 = 3162;
		systemSettings.ironTips[2].PID.Kp = 0.003056;
		systemSettings.ironTips[2].PID.Ki = 0.0025000000000000001;
		systemSettings.ironTips[2].PID.Kd = 0;

		strcpy(systemSettings.ironTips[3].name, "D24");
		systemSettings.ironTips[3].calADC_At_200 = 900;
		systemSettings.ironTips[3].calADC_At_300 = 1932;
		systemSettings.ironTips[3].calADC_At_400 = 3598;
		systemSettings.ironTips[3].PID.Kp = 0.002;
		systemSettings.ironTips[3].PID.Ki = 0.0025000000000000001;
		systemSettings.ironTips[3].PID.Kd = 0;
	}
	else {
		systemSettings.noIronValue=1200;
		for(uint8_t x = 0; x < ( sizeof(systemSettings.ironTips)/sizeof(systemSettings.ironTips[0])); ++x) {
			systemSettings.ironTips[x].calADC_At_200 = 390;
			systemSettings.ironTips[x].calADC_At_300 = 625;
			systemSettings.ironTips[x].calADC_At_400 = 883;
			systemSettings.ironTips[x].PID.Kp = 0.0028;
			systemSettings.ironTips[x].PID.Ki = 0.0018;
			systemSettings.ironTips[x].PID.Kd = 0.00007;
			systemSettings.ironTips[x].PID.min = 0;
			systemSettings.ironTips[x].PID.max = 1;
			systemSettings.ironTips[x].PID.maxI = 200;
			systemSettings.ironTips[x].PID.minI = -50;
		}
		systemSettings.currentNumberOfTips = 1;
		systemSettings.currentTip = 0;
		// By default take JBC values
		// T12 won't burn if using JBC settings. But JBC will do if using T12 settings!
		if(systemSettings.TipType!=Tip_JBC){
			strcpy(systemSettings.ironTips[0].name, "NONE");
		}
		else{
			strcpy(systemSettings.ironTips[0].name, "010");
		}
	}
}

void Diag_init(void){
	systemSettings.OledFix = 1;
	setContrast(255);
	FillBuffer(C_BLACK,fill_soft);
	UG_FontSelect(&FONT_10X16_reduced);
	UG_SetForecolor(C_WHITE);
	UG_SetBackcolor(C_BLACK);
}

void Flash_error(void){
	Diag_init();
	UG_PutString(2,0,"ERROR WHILE");//11
	UG_PutString(12,16,"WRITING TO");//10
	UG_PutString(32,32,"FLASH!");//6
	update_display();
	while(1){
		HAL_IWDG_Refresh(&hiwdg);
	}
}


void Checksum_error(void){
	Diag_init();
	UG_PutString(2,0,"CHECKSUM ERR");//12
	UG_PutString(17,16,"RESTORING");//9
	UG_PutString(12,32,"DEFAULTS...");//10
	update_display();
	ErrCountDown(5,117,50);
	resetSettings();
	saveSettings();
}

void Button_reset(void){
	uint16_t ResetTimer= HAL_GetTick();
	if(!BUTTON_input){
		Diag_init();
		UG_PutString(7,10,"HOLD BUTTON");//11
		UG_PutString(12,26,"TO RESTORE");//10
		UG_PutString(22,42,"DEFAULTS");//8
		update_display();
		while(!BUTTON_input){
			HAL_IWDG_Refresh(&hiwdg);
			if((HAL_GetTick()-ResetTimer)>5000){
				FillBuffer(C_BLACK,fill_dma);
				UG_PutString(27,15,"RELEASE");//7
				UG_PutString(12,31,"BUTTON NOW");// 10
				update_display();
				while(!BUTTON_input){
					HAL_IWDG_Refresh(&hiwdg);
				}
				resetSettings();
				saveSettings();
			}
		}
	}
}
//Max 99 seconds countdown.
void ErrCountDown(uint8_t Start,uint8_t  xpos, uint8_t ypos){
	uint32_t timErr = 0;
	char str[3];
	char cleanStr[3]= {' ', ' ', 0};
	uint8_t length;
	if(Start>99){Start=99;}
	if(Start>9){
		length=2;
	}
	else{
		length=1;
		cleanStr[1]=0;
	}

	HAL_Delay(20);				// Dirty fix to ensure Oled DMA transfer has ended before writing to the buffer
	while(Start){
		timErr=HAL_GetTick();
		UG_PutString(xpos,ypos,&cleanStr[0]);
		sprintf(&str[0],"%*d",length-1,Start--);
		UG_PutString(xpos,ypos,&str[0]);
		update_display();
		while( (HAL_GetTick()-timErr)<999 ){
			HAL_IWDG_Refresh(&hiwdg);			// Clear watchdog
		}
	}
}
