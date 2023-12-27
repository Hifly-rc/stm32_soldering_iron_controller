                                                                                                                                                                                                                                                                                                                                                                                                                                                   /*
 * main_screen.c
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#include "main_screen.h"
#include "screen_common.h"

#define SCREENSAVER
#define PWR_BAR_WIDTH   52
#define SCALE_FACTOR    (int)((65536*PWR_BAR_WIDTH*1.005)/100)

//-------------------------------------------------------------------------------------------------------------------------------
// Main screen variables
//-------------------------------------------------------------------------------------------------------------------------------

static uint32_t barTime;
slide_t screenSaver = {
    .x = 34,
    .y = 0,
    .xAdd = 1,
    .yAdd = 1,
};

static char *tipNames[NUM_TIPS];
enum mode{  main_none=0, main_irontemp, main_error, main_setpoint, main_tipselect,  main_tipselect_auto, main_profileselect };
enum{ status_ok=0x20, status_error };
enum { temp_numeric, temp_graph };
xbm_t shakeXBM = {
  .width=9,
  .height=9,
  .xbm=(const uint8_t[]){
    0x70, 0x00, 0x80, 0x00, 0x30, 0x01, 0x40, 0x01, 0x45, 0x01, 0x05, 0x00,
    0x19, 0x00, 0x02, 0x00, 0x1C, 0x00,
  },
};
xbm_t tempXBM = {
  .width=5,
  .height=9,
  .xbm=(const uint8_t[]){
    0x04, 0x0A, 0x0A, 0x0A, 0x0A, 0x0E, 0x1F, 0x1F, 0x0E,
  },
};
#ifdef USE_VIN
xbm_t voltXBM = {
  .width=6,
  .height=9,
  .xbm=(const uint8_t[]){
    0x20, 0x18, 0x0C, 0x06, 0x3F, 0x18, 0x0C, 0x06, 0x01,
  },
};
#endif
xbm_t warningXBM = {
  .width=6,
  .height=9,
  .xbm=(uint8_t*)(const uint8_t[]){
    0x10, 0x00, 0x28, 0x00, 0x54, 0x00, 0x54, 0x00, 0x82, 0x00, 0x92, 0x00,
    0x01, 0x01, 0xFF, 0x01,
  },
};
#ifdef SCREENSAVER
xbm_t ScrSaverXBM = {
  .width=60,
  .height=49,
  .xbm=(const uint8_t[]){
    0x00, 0x00, 0x00, 0xC0, 0xE1, 0x3F, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF,
    0x1F, 0xFF, 0x00, 0x00, 0x00, 0x02, 0x7E, 0x00, 0x60, 0xFC, 0x01, 0x00,
    0x80, 0xFF, 0xFF, 0xFF, 0x1F, 0xFB, 0x03, 0x00, 0xE0, 0x1F, 0xFF, 0x1F,
    0xC0, 0xE4, 0x03, 0x00, 0xF0, 0xF3, 0xF1, 0xEF, 0x3F, 0xD9, 0x07, 0x00,
    0xF8, 0xF9, 0xFF, 0xEF, 0xFF, 0xF4, 0x0F, 0x00, 0xF8, 0xFD, 0xFB, 0xFF,
    0xFF, 0xEB, 0x0F, 0x00, 0xF8, 0xFF, 0xF7, 0xFF, 0x80, 0xFF, 0x1F, 0x00,
    0xF8, 0xFF, 0xFF, 0x3F, 0x00, 0xFE, 0x1F, 0x00, 0xFC, 0x03, 0xFC, 0x0F,
    0x03, 0xF8, 0x3F, 0x00, 0x7E, 0x01, 0xF8, 0xC7, 0x01, 0x98, 0x0F, 0x00,
    0x03, 0x01, 0xC0, 0x27, 0x00, 0x98, 0x0F, 0x00, 0xFC, 0x7F, 0xC0, 0x07,
    0xEE, 0x6F, 0xE0, 0x00, 0xF8, 0xFF, 0xE3, 0x8F, 0x8F, 0x1F, 0xC0, 0x01,
    0x05, 0xFE, 0xF3, 0xFF, 0x1F, 0x00, 0x8F, 0x05, 0x01, 0xE0, 0xF3, 0xFF,
    0x3F, 0xE0, 0x1C, 0x05, 0xFF, 0xE0, 0xF1, 0xFF, 0xFF, 0x7F, 0x3C, 0x0D,
    0xBF, 0xF9, 0xF8, 0x8F, 0xFE, 0x1F, 0x38, 0x0D, 0x9D, 0x7F, 0xFC, 0x0F,
    0xE0, 0x07, 0x21, 0x0D, 0x1F, 0x3F, 0xFC, 0x33, 0xFF, 0xC1, 0x21, 0x05,
    0x0C, 0x07, 0xFC, 0x20, 0x3F, 0xF0, 0x38, 0x05, 0x0B, 0xF6, 0xF8, 0x07,
    0x07, 0x78, 0xBC, 0x00, 0x0E, 0xFC, 0xC3, 0x7F, 0xC0, 0x19, 0x7C, 0x02,
    0x0E, 0xE0, 0xE7, 0x07, 0xF8, 0x00, 0xBE, 0x01, 0x0E, 0x00, 0x00, 0x00,
    0x7C, 0x00, 0x7F, 0x00, 0x0E, 0x06, 0x00, 0xF8, 0x1C, 0x10, 0x7F, 0x00,
    0x0E, 0xE4, 0x71, 0xFC, 0x00, 0x98, 0x3F, 0x00, 0x0E, 0xE4, 0x71, 0x3E,
    0x80, 0xC9, 0x3F, 0x00, 0x0E, 0x00, 0x00, 0x00, 0xE0, 0xE1, 0x1F, 0x00,
    0x0E, 0x00, 0x00, 0x00, 0xF8, 0xE3, 0x1F, 0x00, 0x0E, 0x00, 0x00, 0x80,
    0xF9, 0xF0, 0x0F, 0x00, 0x0E, 0x00, 0x00, 0xF0, 0x79, 0xFC, 0x07, 0x00,
    0x1E, 0x00, 0x80, 0xF9, 0x33, 0xFE, 0x03, 0x00, 0x1E, 0x92, 0xF3, 0xF9,
    0x03, 0xFF, 0x01, 0x00, 0x3E, 0x32, 0xF3, 0xF9, 0xC1, 0xBB, 0x00, 0x00,
    0x7E, 0x20, 0xE7, 0x19, 0xF0, 0x4C, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00,
    0x3E, 0x13, 0x00, 0x00, 0xFE, 0x0F, 0x00, 0xE0, 0xC7, 0x0C, 0x00, 0x00,
    0x7E, 0xFF, 0xFF, 0xFF, 0x39, 0x03, 0x00, 0x00, 0xFE, 0xFE, 0xFF, 0x3F,
    0xE6, 0x00, 0x00, 0x00, 0xEE, 0xF1, 0x7F, 0x40, 0x3C, 0x00, 0x00, 0x00,
    0xDE, 0x1F, 0xC0, 0x83, 0x07, 0x00, 0x00, 0x00, 0x3E, 0xFF, 0x0F, 0xFC,
    0x01, 0x00, 0x00, 0x00, 0xFC, 0x08, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00,
    0xFC, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x01,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 },
};
#endif
 xbm_t ironXBM_T12 = {
  .width=105,
  .height=7,
  .xbm=(const uint8_t[]){
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x07, 0x00, 0x01, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1C, 0x00, 0x01, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x01, 0x3E, 0xF8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x01, 0x01, 0x3E, 0xF8, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x01, 0x3E,
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x07, 0x00,
  },
};
 xbm_t ironXBM_JBC = {
  .width=105,
  .height=7,
  .xbm=(const uint8_t[]){
    0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0xF8, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF,
    0x0F, 0x80, 0x07, 0x00, 0x80, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x80, 0x01,
    0x00, 0x00, 0x08, 0x80, 0x3F, 0x00, 0xFF, 0x03, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x08, 0x80, 0xFF, 0x01, 0x80, 0xFF, 0x0F, 0x00,
    0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x08, 0x80, 0x3F, 0x00, 0x00, 0x00,
    0x1C, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x0F, 0x80, 0x07, 0x00,
    0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0xF8, 0xFF,
    0x00, 0x00,
  },
};
xbm_t x_markXBM = {
  .width=12,
  .height=15,
  .xbm=(const uint8_t[]){
    0x03, 0x0C, 0x07, 0x0E, 0x06, 0x06, 0x0C, 0x03, 0x9C, 0x03, 0xF8, 0x01,
    0xF0, 0x00, 0x60, 0x00, 0xF0, 0x00, 0xF8, 0x01, 0x9C, 0x03, 0x0C, 0x03,
    0x06, 0x06, 0x07, 0x0E, 0x03, 0x0C,
  },
};
//-------------------------------------------------------------------------------------------------------------------------------
// Main screen widgets
//-------------------------------------------------------------------------------------------------------------------------------
screen_t Screen_main;

#ifdef USE_NTC
static widget_t *Widget_AmbTemp;
#endif

#ifdef USE_VIN
static widget_t *Widget_Voltage;
#endif

static widget_t *Widget_IronTemp;
static widget_t *Widget_SetPoint;

static struct{
  uint8_t lastPwr;                        // Last stored power for widget
  uint8_t shakeActive;                    // Shake icon status: 0=disabled, 1=needs drawing, 2=drawign done, 3=needs clearing
  uint8_t ironStatus;                     // iron status: status_ok, status_error
  uint8_t lastError;                      // Last error, stored to detect error changes
  uint8_t setMode;                        // Main screen variable, set to switch between modes (iron_temp, setpoint, tip_select)
  uint8_t currentMode;                    // Current screen mode (iron_temp, setpoint, tip_select)
  uint8_t displayMode;                    // Iron temp display mode (temp_numeric, temp_graph)
  uint8_t updateReadings;                 // Flag to update power, tip, ambient, voltage widgets
  uint8_t boost_allow;                    // Flag used only for boost mode while in plot graph display
  int16_t lastTip;                        // Last stored tip temperature for widget
  #ifdef USE_NTC
  int16_t lastAmb;                        // Last stored ambient temperature for widget
  #endif
  #ifdef USE_VIN
  uint16_t lastVin;                       // Last stored voltage for widget
  #endif
  uint32_t modeTimer;                     // Timer to track current screen mode time
  uint32_t inputBlockTimer;               // Timer to block user input Load current time+blocking time in ms
  uint32_t lastErrorTimer;                // Timer to track last error time
}mainScr;

//-------------------------------------------------------------------------------------------------------------------------------
// Main screen widgets functions
//-------------------------------------------------------------------------------------------------------------------------------

void resetModeTimer(void){
  mainScr.modeTimer=current_time;
}

// Checks elapsed time since the current main screen mode was set
uint8_t checkMainScreenModeTimer(uint32_t time){
  if((current_time-mainScr.modeTimer)>time){
    return 1;
  }
  return 0;
}

// Checks elapsed time since the current iron mode was set
uint8_t checkIronModeTimer(uint32_t time){
  if((current_time-getIronCurrentModeTimer())>time){
    return 1;
  }
  return 0;
}

static void setTemp(uint16_t *val) {
  setUserTemperature(*val);
}

static void * getTemp() {
  temp = getUserTemperature();
  return &temp;
}

static void * main_screen_getIronTemp() {
  if(mainScr.updateReadings){
    mainScr.lastTip=readTipTemperatureCompensated(old_reading, read_average, getSystemTempUnit());
    if(getCurrentMode()>mode_sleep){
      uint16_t const targetTemp = getIronTargetTemperature();
      // Lock numeric display if within limits
      if(isIronTargetTempReached() && abs(mainScr.lastTip-targetTemp)<systemSettings.settings.guiTempDenoise){
        mainScr.lastTip = targetTemp;
      }
    }
  }
  temp=mainScr.lastTip;
  return &temp;
}

#ifdef USE_VIN
static void * main_screen_getVin() {
  if(mainScr.updateReadings){
    mainScr.lastVin = getSupplyVoltage_v_x10();
  }
  temp=mainScr.lastVin;
  return &temp;
}
#endif

#ifdef USE_NTC
static void * main_screen_getAmbTemp() {
  if(mainScr.updateReadings){
    if(getSystemTempUnit()==mode_Celsius){
      mainScr.lastAmb = last_NTC_C;
    }
    else{
      mainScr.lastAmb = last_NTC_F;
    }
  }
  temp=mainScr.lastAmb;
  return &temp;
}
#endif

void updateIronPower(void) {

  static uint32_t stored=0;
  static uint32_t updateTim;
  if((current_time-updateTim)>19){
    updateTim = current_time;
    int32_t tmpPwr = getCurrentPower();
    if(tmpPwr < 0){
      tmpPwr = 0 ;
    }
    tmpPwr = tmpPwr<<12;
    stored = ( ((stored<<3)-stored)+tmpPwr+(1<<11))>>3 ;
    tmpPwr = stored>>12;
    tmpPwr = (tmpPwr*SCALE_FACTOR)>>16;
    mainScr.lastPwr=tmpPwr;
  }
}

static void setMainWidget(widget_t* w){
  Screen_main.state=screen_Erase;
  Screen_main.current_widget=w;
  widgetEnable(w);
}

//-------------------------------------------------------------------------------------------------------------------------------
// Main screen functions
//-------------------------------------------------------------------------------------------------------------------------------
static void setMainScrTempUnit(void) {
  if(getSystemTempUnit()==mode_Farenheit){
    ((displayOnly_widget_t*)Widget_IronTemp->content)->endString="\260F";      // \260 = ASCII dec. 176(°) in octal representation
    #ifdef USE_NTC
    ((displayOnly_widget_t*)Widget_AmbTemp->content)->endString="\260F";
    #endif
    ((editable_widget_t*)Widget_SetPoint->content)->inputData.endString="\260F";
  }
  else{
    ((displayOnly_widget_t*)Widget_IronTemp->content)->endString="\260C";
    #ifdef USE_NTC
    ((displayOnly_widget_t*)Widget_AmbTemp->content)->endString="\260C";
    #endif
    ((editable_widget_t*)Widget_SetPoint->content)->inputData.endString="\260C";
  }
}

// Ignore future input for specified amount of time
void blockInput(uint16_t time){
  mainScr.inputBlockTimer = current_time+time;
}

void updateScreenSaver(void){
#ifdef SCREENSAVER
  if(!screenSaver.enabled || getCurrentMode() !=mode_sleep || (getIronErrorFlags().active)){
    return;
  }
  if(current_time-screenSaver.timer>50){
    screenSaver.timer=current_time;
    screenSaver.x+=screenSaver.xAdd;
    screenSaver.y+=screenSaver.yAdd;
    if(screenSaver.x<-(ScrSaverXBM.width+10) || screenSaver.x>(displayWidth+10)){
      screenSaver.xAdd = -screenSaver.xAdd;
    }
    if(screenSaver.y<-(ScrSaverXBM.height+10) || screenSaver.y>(displayHeight+10)){
      screenSaver.yAdd = -screenSaver.yAdd;
    }
    screenSaver.update=1;
  }
#endif
}

// Switch main screen modes
int8_t switchScreenMode(void){
  if(mainScr.setMode!=main_none){
    resetScreenTimer();
    resetModeTimer();
    plot.enabled = (mainScr.displayMode==temp_graph);
    Screen_main.state=screen_Erase;
    mainScr.updateReadings=1;
    switch(mainScr.setMode){

      case main_irontemp:
        widgetDisable(Widget_SetPoint);
        mainScr.boost_allow=0;
        if(mainScr.ironStatus!=status_error){
          if(!plot.enabled){
            setMainWidget(Widget_IronTemp);
          }
          break;
        }
        mainScr.setMode=main_error;
        // No break intentionally
      case main_error:
        plot.enabled = 0;
        widgetDisable(Widget_IronTemp);
        break;

      case main_setpoint:
        plot.enabled = 0;
        setMainWidget(Widget_SetPoint);
        break;

      case main_tipselect:
      case main_tipselect_auto:
        break;

      case main_profileselect:
        break;

      default:
        break;
    }
    mainScr.currentMode=mainScr.setMode;
    mainScr.setMode=main_none;
    return 1;                                                             // Changed mode
  }
  return 0;                                                               // No changes
}

int main_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
  uint8_t currentIronMode = getCurrentMode();

  mainScr.updateReadings=update_GUI_Timer();
  updateIronPower();
  updatePlot();
  updateScreenSaver();

  IronError_t ironErrorFlags = getIronErrorFlags();

  if(ironErrorFlags.active){
    if(mainScr.shakeActive){
      mainScr.shakeActive=3;
    }
    if(mainScr.ironStatus!=status_error || mainScr.lastError != ironErrorFlags.Flags){  // If error appeared or changed
      wakeOledDim();                                                      // Wake up screen
      mainScr.ironStatus = status_error;
      mainScr.lastError=ironErrorFlags.Flags;
      mainScr.lastErrorTimer = getIronLastErrorTime();
    }
  }
  else if(mainScr.ironStatus != status_ok){                               // If error is gone
    mainScr.ironStatus = status_ok;
    wakeOledDim();                                                        // Wake up screen
    if( (mainScr.lastError == (FLAG_ACTIVE | FLAG_NO_IRON)) && (current_time - mainScr.lastErrorTimer > 3000) ){    // If last error was no tip and >3 seconds passed, enable automatic tip selection
      mainScr.setMode = main_tipselect_auto;
      switchScreenMode();
      return -1;
    }
  }


  // Timer for ignoring user input
  if(current_time < mainScr.inputBlockTimer){
    input=Rotate_Nothing;
  }

  if(input!=Rotate_Nothing){
    resetScreenTimer();                                                   // Reset screen idle timer
    if(getDisplayPower()==disable){                                       // If oled off, block user action
      input=Rotate_Nothing;
    }
    wakeOledDim();                                                        // But  wake up screen
  }

  if(systemSettings.settings.dim_mode!=dim_always && currentIronMode>mode_standby){  // If dim not enabled in all modes
    wakeOledDim();                                                        // Refresh timeout if running
  }

  handleOledDim();

  // Handle shake wake icon drawing and timeout
  if( !mainScr.shakeActive && getIronShakeFlag()){
    clearIronShakeFlag();
    mainScr.shakeActive=1;
  }
  else if((mainScr.shakeActive == 2) && ((current_time- getIronLastShakeTime()) > 150)){
    mainScr.shakeActive=3; // Clear
  }

  // If at main temperature screen
  if(mainScr.currentMode == main_irontemp && (input == Rotate_Increment || input == Rotate_Decrement || input == Click)){  // Capture rotation and click events
    if(getIronWakeSource()==wakeSrc_Button && !checkIronModeTimer(200)){  // To avoid unwanted mode change, ignore action if iron mode was set <200ms ago
        input = Rotate_Nothing;
      }
      else if(currentIronMode==mode_boost){                               // Click / rotation events will exit boost mode, don't process the input afterwards
        setCurrentMode(mode_run);
        input = Rotate_Nothing;
      }
      else if(currentIronMode!=mode_run && input != Click){               // Ignore click in low power mode. Only rotation will resume run mode.
        IronWake(wakeSrc_Button);                                         // Send wake signal
        if(getCurrentMode()==mode_run){                                   // If mode actually changed
          input = Rotate_Nothing;                                         // Ignore rotation to prevent setpoint adjustment
          resetModeTimer();                                               // Reset mode timer
          if(mainScr.displayMode==temp_graph){                            // If in graph display mode
            mainScr.boost_allow=1;                                        // Allow boost triggering
          }
        }
      }
  }
  // Handle main screen
  switch(mainScr.currentMode){
    case main_irontemp:

      if(mainScr.ironStatus!=status_ok){                                  // When the screen goes to error state
        mainScr.setMode=main_error;                                       // Set error screen
        break;
      }

      switch((uint8_t)input){

        case LongClick:
          return screen_settings;

        case Rotate_Increment_while_click:
          mainScr.setMode=main_tipselect;
          break;

        case Click:                                                         // Received a Click, enter low power mode.
          if(mainScr.displayMode==temp_graph){                              // If in graph display
            if(checkMainScreenModeTimer(1000)){                             // If more than 1 second since last rotation, disable boost allow flag
              mainScr.boost_allow=0;
            }
            if(mainScr.boost_allow && currentIronMode==mode_run){           // If boost flag enabled and iron running
              mainScr.boost_allow=0;                                        // Clear flag
              setCurrentMode(mode_boost);                                   // Set boost mode
            }
          }
          if(checkMainScreenModeTimer(500)){                                // After other events, wait for more than 500ms before allowing click events from entering low power modes
            if(currentIronMode > mode_standby){                             // Otherwise the user might accidentally enter them
              setCurrentMode(mode_standby);
            }
            else{
              setCurrentMode(mode_sleep);
            }
          }
          break;

        case Rotate_Increment:
        case Rotate_Decrement:
          if(mainScr.displayMode==temp_graph){
            if(!checkMainScreenModeTimer(500)){                             // If last rotation step happened <500ms ago, disable boost allow flag and modify the setpoint.
              mainScr.boost_allow=0;                                        // Disable boost allow flag
              widgetEnable(Widget_SetPoint);                                // Enable the setpoint widget, but don't set it as current widget (Dirty hack), just to be able to process the input
              default_widgetProcessInput(Widget_SetPoint, input, state);    // If the widget is disabled, the widget process will skip it. It will be disabled before drawing in drawMisc function
            }
            else{                                                           // If last step was more than 500ms ago, enable boost flag
              mainScr.boost_allow=1;                                        // Set boost flag. Click within 1 second to enable boost mode
            }
            resetModeTimer();                                               // Reset mode timer
          }
          else{
            mainScr.setMode=main_setpoint;
          }
          return -1;
          break;

        case Rotate_Decrement_while_click:                                  // Switch between numeric and graph displays
          scr->state=screen_Erase;
          if(mainScr.displayMode==temp_numeric){
            mainScr.updateReadings=1;
            mainScr.displayMode=temp_graph;
            widgetDisable(Widget_IronTemp);
            plot.enabled=1;
            plot.update=1;
          }
          else{
            mainScr.displayMode=temp_numeric;
            mainScr.updateReadings=1;
            mainScr.boost_allow=0;                                        // Clear flag
            widgetEnable(Widget_IronTemp);
            plot.enabled=0;
          }

        default:
          break;
      }
      break;


    case main_error:

      switch((uint8_t)input){
        case LongClick:
          return screen_settings;

        case Rotate_Increment_while_click:
          mainScr.setMode=main_tipselect;
          break;

        case Rotate_Increment:
        case Rotate_Decrement:
            mainScr.setMode=main_setpoint;

        default:
          break;
      }
      if(mainScr.ironStatus==status_ok){
        mainScr.setMode=main_irontemp;
      }
      break;


    case main_tipselect_auto:
      if(input!=Rotate_Nothing){
        mainScr.currentMode = main_tipselect;                               // Set normal tipselect on user input to use small timeout.
      }
    case main_tipselect:
      {
        uint8_t tip = systemSettings.currentTip;

        if(mainScr.ironStatus==status_error){                                 // If error appears while in tip selection, it needs to update now to avoid overlapping problems
          plot.enabled = 0;
          widgetDisable(Widget_IronTemp);
        }
        else{
          if(mainScr.displayMode==temp_numeric){
            widgetEnable(Widget_IronTemp);
          }
          else{
            plot.enabled=1;
          }
        }

        switch((uint8_t)input){
          case LongClick:
            Selected_Tip = systemSettings.currentTip;
            return screen_tip_settings;

          case Click:
            mainScr.setMode=main_irontemp;
            break;

          case Rotate_Nothing:        // Return after 2 seconds of inactivity, or after 5 seconds or error appears when a new tip was placed
            if( (mainScr.currentMode == main_tipselect && checkScreenTimer(2000)) ||
                (mainScr.currentMode == main_tipselect_auto && (mainScr.ironStatus==status_error || checkScreenTimer(5000)) )){
              mainScr.setMode=main_irontemp;
            }
            break;

          case Rotate_Increment:
            if(++tip >= systemSettings.Profile.currentNumberOfTips){
              tip=0;
            }
            break;

          case Rotate_Decrement:
            if(--tip >= systemSettings.Profile.currentNumberOfTips){          // If underflowed
              tip = systemSettings.Profile.currentNumberOfTips-1;
            }
            break;

          case Rotate_Increment_while_click:
          case Rotate_Decrement_while_click:
            mainScr.setMode=main_profileselect;
            break;

          default:
            break;
        }
        if(tip!=systemSettings.currentTip){
          setCurrentTip(tip);
          Screen_main.state=screen_Erase;
        }
        break;
      }

    case  main_profileselect:
      {
        uint8_t profile = systemSettings.currentProfile;

        if(mainScr.ironStatus==status_error){                                 // If error appears while in tip selection, it needs to update now to avoid overlapping problems
          plot.enabled = 0;
          widgetDisable(Widget_IronTemp);
        }
        else{
          if(mainScr.displayMode==temp_numeric){
            widgetEnable(Widget_IronTemp);
          }
          else{
            plot.enabled=1;
          }
        }

        switch((uint8_t)input){
          case Rotate_Nothing:                                                // Return after 2 seconds of inactivity
            if(checkScreenTimer(2000)){
              mainScr.setMode=main_irontemp;
            }
          break;
          case Click:
            mainScr.setMode=main_irontemp;
            break;

          case Rotate_Increment:
            if(++profile > profile_C210){
              profile=profile_T12;
            }
            break;

          case Rotate_Decrement:
            if(--profile >= profile_C210){          // If underflowed
              profile = profile_C210;
            }
            break;

          default:
            break;
        }

        if(profile!=systemSettings.currentProfile){
          if(isCurrentProfileChanged()){         // If there's unsaved profile data
            saveSettingsFromMenu(save_Settings); // Save settings
            checkSettings();
          }
          loadProfile(profile);
          Screen_main.state=screen_Erase;
        }
      }
      break;

    case main_setpoint:

      switch((uint8_t)input){
        case LongClick:
        case Click:
          if(mainScr.ironStatus != status_error && currentIronMode==mode_run && !checkMainScreenModeTimer(1000)){
            setCurrentMode(mode_boost);
          }
          mainScr.setMode=main_irontemp;
          break;

        case Rotate_Nothing:
          if(checkScreenTimer(1000)){
            mainScr.setMode=main_irontemp;
          }
          break;

        case Rotate_Increment_while_click:
        case Rotate_Decrement_while_click:
          mainScr.setMode=main_irontemp;
          break;

        default:
          break;
      }
      if(input!=Rotate_Nothing){
        IronWake(wakeSrc_Button);
      }
    default:
      break;
  }

  if(switchScreenMode()){
    return -1;
  }

  return default_screenProcessInput(scr, input, state);
}

static uint8_t  drawIcons(uint8_t refresh){
  if(refresh){
    #ifdef USE_NTC
    u8g2_DrawXBMP(&u8g2, Widget_AmbTemp->posX-tempXBM.width -1, 0, tempXBM.width, tempXBM.height, tempXBM.xbm);
    #endif

    #ifdef USE_VIN
    u8g2_DrawXBMP(&u8g2, 0, 0, voltXBM.width, voltXBM.height, voltXBM.xbm);
    #endif
  }

  if(mainScr.shakeActive==1 || (mainScr.shakeActive==2 && refresh) ){ //1 = needs drawing, 2 = already drawn
    mainScr.shakeActive=2;
    u8g2_DrawXBMP(&u8g2, displayWidth-shakeXBM.width-PWR_BAR_WIDTH-8, displayHeight-shakeXBM.height, shakeXBM.width, shakeXBM.height, shakeXBM.xbm);
    return 1;
  }
  else if(mainScr.shakeActive==3){                                    // 3 = needs clearing
    mainScr.shakeActive=0;
    u8g2_SetDrawColor(&u8g2,BLACK);
    u8g2_DrawBox(&u8g2, displayWidth-shakeXBM.width-PWR_BAR_WIDTH-8, displayHeight-shakeXBM.height, shakeXBM.width, shakeXBM.height);
    u8g2_SetDrawColor(&u8g2,WHITE);
    return 1;
  }/*
  Fontname: -FreeType-AR PL New Sung-Medium-R-Normal--13-130-72-72-P-120-ISO10646-1
  Copyright: (c) Copyright 1994-1999, Arphic Technology Co., Ltd.
  Glyphs: 271/6865
  BBX Build Mode: 0
*/
const uint8_t u8g2_font_menu[5969] U8G2_FONT_SECTION("u8g2_font_menu") =
  "\17\0\3\2\4\4\4\5\5\14\14\377\377\11\377\12\377\1Z\2\312\4\34 \5\0\267/!\7\201\32"
  "/.\1#\21\206\30\257\222,I\206)\211\222hXjI\4$\20\245\11\257\262AI\224L\324\22"
  "%\31\264\10%\22\207\30oB%J\232\22%J\224(iJ\304\4&\20\207\30\357\322$LB\61"
  "\211\264D\214\206$(\11\264\372\356\242\266\216\15)\12\264\371.\302\266Nm\0*\11EY\257*\235"
  "\222\4+\12U\30\257\302h\220\302\10,\10B\372.\206D\1-\7\25I/\6\1.\7\42\31+"
  "\206\0/\14\244\11\357JY)\213\262\32\0\60\12\205\31o\226\314\267d\1\61\12\205\31o\244$\354"
  "i\20\62\13\205\31/\206\64\314:\16\2\63\15\205\31/\206\64L\326\60\34\24\0\64\16\205\31\357\62"
  ")\211\222R\62ha\2\65\14\204\31/\6-\33\263lH\0\66\14\205\31o\6\261b\322\264d\1"
  "\67\13\205\31/\6\61k\314\302\20\70\15\205\31o\226LK\226h\323\222\5\71\15\205\31o\226\314\244"
  "(a\70(\0:\10b\32/\206p\10;\12\202\372.\206pH\24\0<\12e\31/#ES\325"
  "\0=\10\66\70/\316\303\0>\12e\30/R\233\42\205\0\77\15\205\31/\206$\13\263b\16E\0"
  "@\21\207\30\257\266\244\213RJ*J\224(\71\60\1A\20\207\30\357\322$L\302$+\15R\226\244"
  "\1B\17\205\31/\206$\323\6%J\62mP\0C\12\205\31\257\226,lM\7D\13\205\31/\246"
  "J\346)\231\0E\13\205\31/\216\341\220\204\305AF\13\205\31/\216\341\220\204\215\0G\14\205\31\257"
  "\226,\254iI\24\15H\13\205\31/\62\333\60dn\1I\12\205\31/\6)\354i\20J\11\204\31"
  "o\266\336\206\4K\16\205\31/\62))iZ\22U\262\0L\11\205\31/\302>\16\2M\14\206\30"
  "/Bq\32\242\305\243\30N\15\205\31/\262iR\22%\221n\1O\14\205\31\257\262\244\346\226\324\42"
  "\0P\14\205\31/\206$\63%SX\4Q\14\225\11\257\262\244\346\226\324\324\0R\16\205\31/\206$"
  "\263\15J\224dZ\0S\13\205\31o\6\61U\213\203\2T\12\207\30/\16Y\334\67\0U\12\205\31"
  "/\62\277%\13\0V\21\207\30/\322$\213\262(\253\204I\230\244\31\0W\17\207\30/RS$U"
  "L\212\224EY\2X\16\205\31/\262\244\224da\226\324\264\0Y\14\205\31/\62-)%Y\330\4"
  "Z\13\205\31/\6\61+f\305A[\11\263\372.\206\250\77\15\134\13\246\10/\322\270\32\247q\65]"
  "\11\263\372.\246\376\64\4^\13e\71\257\302,\211\222\232\26_\7\27\10/\16\1`\7\42\212/\242"
  "\0a\15f\31/\206\70\32\222,\211L\1b\14\225\31/\302\26\223\246M\212\2c\11e\31o\6"
  "\261u\10d\13\225\31/[L\233IQ\2e\13e\31o\226l\30\302t\10f\14\226\31\357\246\64"
  "\33\246\264\33\0g\14\205\371nL\233IQ\302A\1h\12\225\31/\302\26\223\346\26i\10\203\32\257"
  "\262\251\7j\13\244\371\356\302!\353mH\0k\15\225\31/\302\246\244\244%Q%\13l\10\223\31/"
  "\246\376\0m\16g\30/\22eHL\221\24I\221Tn\11e\31/\22\223\346\26o\12e\31o\226"
  "\314-Y\0p\15\205\371.\22\223\246M\212\22\206\0q\13\205\371nL\233IQ\302\2r\12e\31"
  "/\222A\22\33\1s\12e\31o\6UM\7\5t\12u\31o\262A\11[\7u\11e\31/\62"
  "O\212\22v\15e\31/\62-)%Q\222E\0w\16g\30/R)R\226\304\224EY\2x\13"
  "e\31/\262\244\26fI-y\15\205\371.\62-)%YX\322\0z\11e\31/\6\255\343 {"
  "\13\264\371\256\224\254)\314\32\5|\7\241\13/\36\2}\14\264\372.\304\254\61\312Z$\0~\12\66"
  "\211o\302$\312\24\0\260\12Dik\224HJ\24\0\0\0\0\4\377\377%\24\12gL\71\342\316\303"
  "\20c\11\31\273\367\270\302\64\31^\243,\226Re\30\224(+\25\263\261\222\334\2\215%\36\273\367\70"
  "\6)+eIeX\232\222\312\224tJ:%MZ\222iQ\22%a\1O\335\37\273\367\270\222a"
  "K\302\250\30E\303\42U\242\64L\206A\11\305,\321\242J\224dQ\0P\15\34\273\367\270\262x\270"
  "DYS\244%a\62\14J\216E\303T\214\212Q\64,\0YT\30\273\367x\323\341\240U\243\222\62"
  "(j\216\264\15\7\255\32fj\6k\324\25\272\370\70\302\336\304(\31\222)\354MJ\262!\312\304A"
  "\225\355\30\272\370x\242a\212\305L\314\206\213fJ\62%\312\266L\332\344\1\177\26\37\273\367\270\302\64"
  "\31\206$J\245\341\240\344@\64\14\312R\231\206!JZ\26\245)\11\5l\342\34\273\367x\322b\16"
  "\34\224RE\211\322d\230*QKI\311\302$J\62E\23ke\31\273\367xs \32\264(\7\242"
  "t\70\250\71R+\325\322\34Q\207\30\220\350\42\273\367\370r\340A\311\222\250\22%\311\60(\71R\32"
  "\224(\311\222(\311\22%\31\224R\226d\0\203\334\33\273\367\370\242p\70hQ:\234\262(\214\252I"
  "m\70hI\65*i\231\0S\302\32\273\367\70\243\70\314\206k<\34\244J\30eQ\42E\242\224#"
  "\342\240\2mK \273\367\70\242!KJY)I\244D\351\242tQ\272(\311\222(mQRJ\262"
  "dK\4\225\177\31\273\367\270\322\260\232\305Q\16$\361p\220\352@\26\207i\42\205\252\0S\202\30\273"
  "\367x\206C\222c\71\226c\71\226c\71\226c\71\224c\71\6\215\205\36\273\367\270\262A\12\243aj"
  "\213\206%\7\262aY\62%\313\224l\30t$\32\6\1y\360\34\273\367\370\224p\213\243\341\220\204Q"
  "\22\205RRZzJ\42\245\324\22\265i\0b\20\35\273\367\270\223\34\211\242\341\220\204i\30EC\22"
  "\265\324\242\242\22UJI\42f\2c\1\34\273\367\270\302\64\31\16Z\32\246\311\60Db\264\14C\224"
  "daTL\243m\2Q\372\26\271\370\70k\231\226i\331p\10k\231\226i\231\226\15\207\0\226d\34"
  "\273\367\70\206\254T\211\222(KZ\225hP\242\254\64\274\25\223\266(\222\42)k!\31\273\367\70\322"
  "b\34\15k\30%\245\254\32\206\306,\312\242\60J\342\0[X\31\273\367\70\343\341 \346\320\60di"
  "XT\206A\11\323\60\15\323h\3\225\31!\273\367x\302$\13\223L\31\6\65\211\226aHrhH"
  "\6)+%\311 IY\224\15\12\0bS\30\273\367\270r,\32\16Z\230\206i\270Ek\230\206i"
  "\230F\333\4_\205\32\273\367\270\262\70\31\246\260TN\206!Q\243d\70\65fI\230\206\331\4SU"
  "\33\273\367\370\352@\22\17\203\26e\331\60hQ\226\15\203\234\16\7\65\307R\0_S\26\272\367xk"
  "\245\346$\32\16\71\224C\311p\207rh\70\10{I\33\273\367\270\302pH\6\245\251\62\14r:\34"
  "t$\33\16Y\30g\71\62\1ON\35\273\367\270R-\31\302\250\30\325\244J\24\15C\22\25\243b"
  "\224t\322\224(\221\2^\225\35\273\367x\343\341\220\344X\62\14Q\22\245I\324\62\14J-L\232l"
  "\211\224H\2u\65\30\272\370\70s(K\206\203V\31.Y%\253\14\227,\207\302t\20\214\3\37\273"
  "\367x\242a\210\222\250\230,a\24\35\206$J\223(Y*J\213\222,\245\64\13\7[\232\30\273\367"
  "x\343\341\35\311\321\341\234\3Q\16D\203\246\304\221\232\16\2R\250\34\273\367\370\201l\220r,\207\206"
  "\203\22\25\243\244\26iQ\64,\231\230\245\321\2^\246\33\273\367\270\323\341\220DY\66\34\222(+\15"
  "Z\216%\303V\311\302-\331\6w\355!\273\367xr \212\206!\331\201$\32\264(K\206\255\64h"
  "Q\26%Q\222EI)\33\206\0[\371\35\273\367\370\241d\20\323\60\212\206!J\302R\61K\262$"
  "J\242b\222\205\71\262\0S\321\33\273\367\70\243\60\312J\361p\320rlX\223(\214\222\64K#E"
  "JT\1\226\0\36\272\370x\222a\210b)\221\224(I\224h\70hJd\211\222DY,a\242\3"
  "\2\177\373\37\273\367\370\344i\30\222R\64\14I\224L\312R\212\206EY\22\313\60EJ)\32\26\3"
  "\217\324\35\273\367x\322-\231\223\34\33\226%\314\222\306$J\245$\214\262(\311\201l\30\2e>\34"
  "\273\367\270\302\70\313\206eH\302(\32\222\250K\324\22\325J\221\224,Q\22\26\207\2\35\273\367\270\262"
  "\70\33\262(\251\14J)I\224^\16S\232\15\331\224-\303 g\0Y\15\33\273\367\370\322l\270\250"
  "Q\62\14a\32\16C\232c\303\246D\71\42\16\322\20\215\37\31\272\367\70sd\20\263p\30\224j\26"
  "\325\242ZT\213t R\206\64\232\330\32\273\367x\323\341\240\23\256a\66\34\222\34\251\14RR\213\222"
  "d\220\222xR\237\33\273\367\370\201l\220\322\60\215\206)\214\212Q\61\212\226l\314\322\60\223\26\0Q"
  "s\30\273\367\370\302\70\12\207s\216\345X:\34\304$\7\262\264\244\3\2\217\307\34\273\367\70r \213"
  "\263d\30t$Z\262\60*F\305\64\314\266$\7\262a\10T\16\33\273\367\70\207M\207rl\70\345"
  "X\216%\303\226\204Q\61\212\206%\13\23\0b\244\32\273\367\270\302\264\64$\303T\214\212\221\62\234r"
  " \312\201$G\312C\16U$\33\273\367\270\303i\210\222Z\224\14\203\322\224tJ:%\311\360\252#"
  "Q*\12fC\34\273\367\270\206!L\303a\10\323p\30\302\250\232\324\206\203\230\344@\224\15\331 `"
  "b\34\273\367x\262\70\31\16Y:%\231\226DIT\211*[\222\205\225\254)Q\3V\336\32\272\370"
  "\70\36tDG\224AR\262H\311\42e\220\224,\322\221\341\35\11m;\34\273\367x\322-\31\322\60"
  "\213\303d\30\244\60M\206\251\230Ha\24\15S\61\1g:\35\273\367\270\322\60\32\224a\12\243bT"
  "[\242L\221*QKT\211\222,\211\304\1\217\221\37\273\367\270\242A\213\262dH\6)\207\222d\70"
  "(Y)\331\224%\231\62)\31\266\70\1~\247\37\273\367\270\342,\31\206$\214\222\250\22m\211\24F"
  "I\324\62%\305$\212\226(\11\23-\213\241\30\273\367x\322b\216\345X&\15C\222\206i\230\206I"
  "\26\212\325\14\213\260\35\273\367xr \213\206)\316\261d\312J\203\26\345@\224\3\211\30)a\24\15"
  "\3R\240\35\273\367\270r,G\206e\210*QK\324\22\265D-Q\222%Q\222%\203$\25\225\364"
  "\34\272\367x\242a\212uD\32\24)K\244A\221\262D\312\22iPtD\7\4h\300\35\273\367\270"
  "\262\70\323\206$\12\223\60\222\206$\331\201\244))%\265(\251\245\341p\217\333\36\273\367x\262(\214"
  "\252\303\240F\221\26e\311\60(Y\224\225\262(\213\22\61\212\206A_\0\30\273\367\370\241h\70d\345"
  ",\316\262\341\240\225\263\70K\303L\315\0\200\3\33\273\367\70\263l\30\344(\33\16j\16\15\233\222J"
  "\303\216\345P\16\14\21\0QK\31\273\367x\323\341\240\346\300!L\303\64\34\206\70\311\221Z)\33\262"
  "A_\353\34\273\367x\302\64L\243a\331\242D\211\32\243\312\60(a\232%a\224e\253\0n\203\37"
  "\273\367x\302\70\31\266\244\224D\303\240\344`\62L\225\250%J\244D\211\262(\33B\1b\311\34\273"
  "\367\270\262\70\314\206d\230r,\312\62%K\266(\253\204Y\22\326\226a\10p\331\36\273\367\270\262\70"
  "\33\62%KzJ\302,\311\222\60\321\244h\220\222Z\224U\302A\1|{\31\273\367\270Z\223\332p"
  "\320\222jT\322\1\65\35\16b\222\3Y\266\16O\213\35\273\367\270r \32\246$\312\222\322\222LI"
  "OIE\351-JJY\322\234\250\3N\256\30\273\367x\323\341\240\303\303\20\246\321\360\16e\203\234E"
  "\305h\35\2\226\206\37\273\367\70\206$j\31\224\236\222lJ\22mJjQ\62\134\242,J\6%\316"
  "\242a\20s\207\31\273\367x\323\341\240d-\255I\65iR\6%N\207\203\232c)\0n\344#\273"
  "\367\70\322!\12\343d\30\264$K\224!\311\222d\210\352@\224(\211\222hI\242D\221\66$\0x"
  "\1\36\273\367\70\206d\220r \12\243b\24M\25%\31\226r\222\14K\62'\345\34X\0w \36"
  "\273\367\70\207e\11\223\306\344\260\64eI\62\34\222(KJYRK\206\244$\212\1\236#\37\273\367"
  "\270\303!\31\224(\311\222(\351\224$K\224\244C\62\14Q\234\15K\216\345\300\2T\15\30\272\367\70"
  "sh\330\302L+%\71\222#\303\244.i\226f\303\20j!!\273\367\270\222a\210\262$\32\222A"
  "\213\262H\32\244%KJ\203RL\223a\210\262$L\64\1^U\33\273\367\70\36\304(\35\206\60\15"
  "\207!L\243\341 \65\15\7\251\61J$\0\200\375!\273\367\270\262\64J\242dP\226\70K\206dP"
  "\242\34\30\222\250e\33\222,\211\222,I\224A\220\6\35\273\367\70\302,\12\223,\31\6\35\310\244J"
  "\324\22E\303\24\246Y\232\224\243a\20\224\256\36\273\367x\262A\32\222\250\30%i\224\14Q\333\240\14"
  "JT\214*QI\213J\303\20PO\37\273\367\270\302\64\31\206$J\223h\70\345@\64\14I\224t"
  "\32\206$QZ\224\236B\1\230\221\35\273\367\370\222a)f\211\62(\245l\30\224R\226T\224\26\245"
  "\267JV\233\304\0\134O\34\273\367x\206S\16D\303)\11\263\250\230\14C\324\70\34\222\250\26e\225"
  "\60\3Qv\31\273\367\370j\303A+\17r\26\17r\26g\331p\220\322H\7\22\0T/\31\272\367"
  "x\343a\220\342(\216\206A\312\241a\220\324\244\232T\245a\10Vh!\273\367x\206d\210*QK"
  "\24\15\311\20G\321p\320\302hP\6%J\242\226(\32\222!\1RM\36\273\367\370\352@\22%\303"
  "AG\207(\211Z\242!J\242\226h\210\222\250\30%\322\2S\326\36\273\367\70\316Q\62D\225(\32"
  "\222\250%\212\206$j\251%K\266Dr\22\245b\0Qh\31\273\367xs(\311\201,-)\203\242"
  "\346X\16\34r \307\322\341 xn\36\273\367\270\303A\31\262\250\26\15C\262\224\226dX:%\225"
  "aYJI\247\60J\4Qe\30\273\367\370t\60\307r,\207\222\34\251\3Y\234\245\265\34Hr("
  "R \32\273\367xNI\247\244S\322)\351\64\34\222\236\222NI\247\244\223\262\30N\12\27\273\367x"
  "s,\307r,\307\6\71\307r,\307r,\35\16\2\213\276\34\273\367x\262!\214\352@\224\3\321\260"
  "\344\210\62hQ\326\22ji\226\244\233\0u\37\32\273\367xs \312\201(\213\206C\222\245a\16\34"
  "\344\34\313\261t\70\10Y\61\31\273\367xs \312\201\203\26\305Y:\34\324\34Jr KK: "
  "e\366\35\273\367\370\221h\10\243h\70\205Q%\212\206(\211Z\242b\64\204Q\61G&\0Y\313\36"
  "\273\367\270\302\64\314\6%\252\24\223\312\260\324\221\322\60$Q\26IY\22%\303\232\5_\17\33\273\367"
  "\270\223\34\211\222\341 \347X\70\14\71\20\345@\26gQ\66%C,y:\27\273\367\370\221l\270\63"
  "\15\7\65GJa\224EY(\326V\0\213\325\35\273\367\70r@\212\223\312\60\350H$g\321\240\225"
  "\262R\226$C\222\330\224\34\11bK\27\273\367\270\207d\330\261x\70\347X:\34\324\34\313\261\34Y"
  "\1\231\226\34\273\367\370\352@\22%\303A\314\221a\10\323p\30\302\64\34\206\60\15\207!\2ep "
  "\273\367\70\242\244\230H\331\260\14\221\324\242DI\224\264\205I\62LY\224\205S\222hZ\0\230z\33"
  "\273\367x*\303R\13\223dX\32\223NI\247\244S\322)\251I]\62\61\220\37\36\273\367\70\322\312"
  "\60(a\216\14\213\224D\245a\12\305L\311\22%Jja\64\14\2\177)\35\273\367\270\302\322\60H"
  "\352\20\15S[\224\14\207$\13\223AJjS\222\205\311 b@\36\273\367\370DE\333\302tH\322"
  "(\31\224(\211\242!\211j\245\254\222\205I\224&\0[\203\31\273\367x\343\341\220\344\210\216\204\71\26"
  "\255;\222ci\230\206\303\220\0c\320 \273\367\270\242A\213\262dH\6-\312\62e\220t\244\62\14"
  "Q%\215\222-I\264!\33\2\224\301\35\273\367x\322\60K\302eP\302$\33\244\60\32\16Z\230\206"
  "I\224dR\26U\3~\337\35\273\367\270\302\64\32\226Z\66Dq\224E\331p\210\222\34)JI\262"
  "EI\246\15Y\64\31\273\367\270c)G\252Z\16D\71\26%\303A\315\241D\16\225\35\10\220\0\35"
  "\273\367\70\262a*F\321\260\206\211\64Lu J\224\250V\232\222D\7\262a\10OM\33\273\367\270"
  "\352@\226&\303\240\344\220\224\225\262\246\254\22fI\230\206\311\60\10n)\35\273\367\70\262a*\246\303"
  "\222\205Q\64L\71\226\14C\22%\235\222NI\227\341\0e\207\30\273\367\70s\60K\206\203V\316\342"
  ",\7\222\34\251C\71b[\7e\340\32\273\367x\206s\216\345X:\34\304$G\352@\224\3Q\26"
  "e\331\70\10\213\357\36\273\367x\262A\213\262R\26\17\212\216E\303\220\244a\62\14J)\311\244,J"
  "\324\0|\373\31\273\367\270\207h\320\241,\34v$\207\262p\30\304\244\32\325Z\242\61N\13\30\273\367"
  "\370\241d\70\250\71\226c;\22\345@\26\347X\216\345X\12f>\34\273\367\270\206!L\303a\10\323"
  "p\30rB\224DYR\312\222\346D\33\16\2\226P!\273\367\70\206dP\242$K\242dPJY"
  "R\312\222(\31\224()\15J\307\250\230\64j\1\230y\33\273\367\70\207\203\226F\203\26e\245\244\26"
  "%\265(\251)-\252\216D\251\30m\210\35\272\367x\302\64)\205I\227aQ\302(\31\226(L\242"
  "a\220\302$\12\223(\32\134\17\30\273\367xs,\307r\244\71\211\302(\213\262P\254\346X\216\254\0"
  "h!\35\273\367\270\262\70\314\206d\230\262$T\262H\311\22%*fIX\315\222p\310\4\202\257\30"
  "\273\367\370j\303A\253Ss$J\223\250%N\212\211\24\246\303\4W\213\36\273\367x\6\255\22%Y"
  "\22%\311\60(Y\22%Y\22F\65%\214\207s:\34\4\210L\33\273\367\270\222a\313\241\34\212\206"
  "AJ\63\65J\322\60\15\323\60\15\243!\2\221\222 \273\367\70\6ePJ\331\260\14K\233R\31\206"
  "D)e\311p\220j\311p\310\242l\30\2O\21\30\273\367\270\262\70\213\207S\226ja\22\255I\243"
  "Tk\312\342,\4O\356\37\273\367\270\262\70\33\242$Q\262D\312\224(\311\222%QJI\226\64&"
  "Q\253\26\215\0~\355\34\273\367\270\302\64\31\246\64\213\206\227RM\314\222l\31\206\34\310\206(\211\265"
  "\4e\313\34\273\367x\302\70\33.q\64\14\311\26%=%\215IeH\272%\312V\32\2\220\11\37"
  "\273\367\70\322R\222F\303\30\205\312\60(Y\22fI\230%Q\22E\203\242\3\321\60\10S\213\32\273"
  "\367x\206C\222c\345,\316\342d\30\242,\11\263(k\11\323d\70^\366\33\273\367\370\241a\31\302"
  "\326pI\206,)&\215Ik\64,u \33\206\0\212\0\31\273\367x\323\341\240\303\303\220S\206!"
  "\247\14C\230\206i\70\14\21\0h\67\32\273\367\270j-\321p\220\302\64\32\244\255\22\246\311\60Da"
  "\32\246a\6y\373\34\273\367\370\244\354 \325\222A)\26\27%S\242A\311\62%Qj\241\230\214\0"
  "u(\30\272\367x\206KV\311*\303%\253d\225\341\222U\262L\314\304dg\11\31\273\367x\323\341"
  " \346\320\60\212Y\22F\321\260\206\351\260\206i&\1S\363\33\273\367xs,\35\16b\16\345\330\60"
  "dj\224\244I\224\206\303\20\246\11\0\213\355 \273\367\70\242aP\302\34\31t \212\264(K\206A"
  "\311\261h\230\22\61R\302(\32\26\0\230\204\35\273\367\70\206d\330\212\332 e\331\260\64%\235\262\244"
  "\224%\245P\314\242d\21\3\217\320\32\273\367x\242a\313Y\206C\230\206i\26e\321\60\25\223:\22"
  "\15\203\0\217}\37\273\367\370\242$\33\246\60\12\207\203\224\205\303\20U\242$\33\224\70\213\206A\251%"
  "\231\0Q\215\33\273\367\70\36\324\34\70hQV\312\262a\320\242,\31\16R\234\305Y\270\0W(\27"
  "\273\367\70\343\341 \346P\71\213\263T\31\226Z\234\305Y<\34b\351\35\273\367\270\222a\213\262dP"
  "\212\231\232H\223\226-\303\26\246\311\60Da\66f\0X\236\35\273\367x\262R\230d\321\360T\211\222"
  "\245\324\22\15C\262d\211\66\310Y<(\0et\37\273\367\370j\303\62$\225%\32\224\232\22eI"
  "\226T\206!Is \32\264(\35\16\2kc\34\273\367\370\241d\70\250\71\226\3Q\16D\203\26\345"
  "@\224\3Q\16D\351p\20P<\34\273\367\270\262x\70ei\64L\305D\12\243h\230\212Q\64L"
  "\305(\31\6\1\177n\32\273\367x\206S%\212\206s:\34\244\64\34\206\60\15\207!L\243\341 R"
  "\66\35\273\367\370\342\244\61\31\226D\12\223aPja\222\14K\247\244S\226T\264\342\0fz\35\273"
  "\367\270rlH\206\244\26\15C\22U\242!\311\322hX\303tX\303t\230\0N-\27\271\370\70s"
  "$\34\16Y\246eZ\66\34\302\34\311\221\34\11\1\221\315\30\273\367x\206s:\34\324\34\70\204Qq"
  "\30\302\250\66\234\323\341 OO\30\273\367\270\352@\26\17\27-L\262\70\213\223a+gq\26\17\7"
  "\217l\33\273\367\270\302l\220\302lX\304,\211\206\203\22gC\66&k\230\251%\0Q\306\37\273\367"
  "x\223,\211\222P\31\206(\211\302d\30\224\250&\25\243aH\242bT\7\16\1\226;$\273\367\70"
  "\206dP\242$KJYR\32\224R\226DI\226D\311\240\14I\226\204Y\22fI\64\14\2g\0"
  "\34\273\367\270\206!L\303a\10\323h\70Hu\340\240EYe\211\206$\321\1I]\346\30\273\367\70"
  "s,L\206\203\230C\71\66\14Y\71K\303j:\34\2^\247\35\273\367\270\323\341\220\344X\22%Y"
  "\22%Yb\211lI\62\14QX\15\223\341\0\0";
/*
  Fontname: -FreeType-AR PL New Sung-Medium-R-Normal--13-130-72-72-P-120-ISO10646-1
  Copyright: (c) Copyright 1994-1999, Arphic Technology Co., Ltd.
  Glyphs: 118/6865
  BBX Build Mode: 0
*/
const uint8_t u8g2_font_small[1739] U8G2_FONT_SECTION("u8g2_font_small") =
  "v\0\3\2\4\4\3\5\5\13\14\377\377\11\377\12\377\1X\2\305\4\25 \5\0\333\27!\7\201\216"
  "\27\227\0#\21\206\214WI\226$\303\224DI\64,\265$\2$\20\245\205W\331\240$J&j\211"
  "\222\14Z\4%\22\207\214\67\241\22%M\211\22%J\224\64%b\2&\20\207\214wi\22&\241\230"
  "DZ\42FC\22(\11\264~wQ[\307\6)\12\264}\27a[\247\66\0*\11E\255W\225N"
  "I\2+\12U\214Wa\64Ha\4,\10B~\27C\242\0-\7\25\245\27\203\0.\7\42\215\25"
  "C\0/\13\244\205w\245\254\224EY\15\60\12\205\215\67K\346[\262\0\61\12\205\215\67R\22\366\64"
  "\10\62\13\205\215\27C\32f\35\7\1\63\15\205\215\27C\32&k\30\16\12\0\64\16\205\215w\231\224"
  "DI)\31\264\60\1\65\14\204\215\27\203\226\215Y\66$\0\66\14\205\215\67\203X\61iZ\262\0\67"
  "\13\205\215\27\203\230\65fa\10\70\15\205\215\67K\246%K\264i\311\2\71\15\205\215\67KfR\224"
  "\60\34\24\0:\10b\216\27C\70\4;\12\202~\27C\70$\12\0<\12e\215\227\221\242\251j\0"
  "=\7\66\234\27\347a>\12e\214\27\251M\221B\0\77\15\205\215\27C\222\205Y\61\207\42\0@\21"
  "\207\214W[\322E)%\25%J\224\34\230\0A\20\207\214wi\22&a\222\225\6)K\322\0B"
  "\17\205\215\27C\222i\203\22%\231\66(\0C\12\205\215WK\26\266\246\3D\13\205\215\27S%\363"
  "\224L\0E\13\205\215\27\307pH\302\342 F\13\205\215\27\307pH\302F\0G\14\205\215WK\26"
  "\326\264$\212\6H\13\205\215\27\231m\30\62\267\0I\12\205\215\27\203\24\366\64\10J\11\204\215\67["
  "oC\2K\16\205\215\27\231\224\224\64-\211*Y\0L\11\205\215\27a\37\7\1M\14\206\214\27\241"
  "\70\15\321\342Q\14N\15\205\215\27\331\64)\211\222H\267\0O\14\205\215WYRsKj\21\0P"
  "\14\205\215\27C\222\231\222),\2Q\14\225\205WYRsKjj\0R\15\205\215\27C\222\331\6"
  "%J\62-S\13\205\215\67\203\230\252\305A\1T\12\207\214\27\207,\356\33\0U\11\205\215\27\231\337"
  "\222\5V\20\207\214\27i\222EY\224U\302$L\322\14W\17\207\214\27\251)\222*&E\312\242,"
  "\1X\16\205\215\27YRJ\262\60KjZ\0Y\14\205\215\27\231\226\224\222,l\2Z\13\205\215\27"
  "\203\230\25\263\342 [\11\263~\27C\324\237\6\134\13\246\204\27i\134\215\323\270\32]\11\263~\27S"
  "\177\32\2^\13e\235Wa\226DIM\13_\7\27\204\27\207\0`\7\42\306\27Q\0a\15f\215"
  "\27C\34\15I\226D\246\0b\14\225\215\27a\213I\323&E\1c\11e\215\67\203\330:\4d\13"
  "\225\215\227-\246\315\244(\1e\13e\215\67K\66\14a:\4f\13\226\215wS\232\15S\332\15g"
  "\14\205}\67\246\315\244(\341\240\0h\12\225\215\27a\213Is\13i\10\203\216W\331\324\3j\13\244"
  "}w\341\220\365\66$\0k\15\225\215\27aSR\322\222\250\222\5l\7\223\215\27S\177m\16g\214"
  "\27\211\62$\246H\212\244H*n\11e\215\27\211Is\13o\12e\215\67K\346\226,\0p\15\205"
  "}\27\211I\323&E\11C\0q\13\205}\67\246\315\244(a\1r\12e\215\27\311 \211\215\0s"
  "\12e\215\67\203\252\246\203\2t\12u\215\67\331\240\204\255\3u\11e\215\27\231'E\11v\15e\215"
  "\27\231\226\224\222(\311\42\0w\16g\214\27\251\24)Kb\312\242,\1x\13e\215\27YR\13\263"
  "\244\26y\15\205}\27\231\226\224\222,,i\0z\11e\215\27\203\326q\20{\13\264}WJ\326\24"
  "f\215\2|\7\241\207\27\17\1}\14\264~\27b\326\30e-\22\0~\12\66\305\67a\22e\12\0"
  "\260\12D\265\65J$%\12\0\0\0\0\4\377\377[\211\30\273{\274\361pHrD\13\323x\70h"
  "e)Gt\304\64\244\2N\15\31\273{\34\17r\16\345X\16)q\22\205Q\226ha\232c\71\226"
  "\2mK \273{\34\321\220%\245\254\224$R\242tQ\272(]\224dI\224\266()%Y\262%"
  "\2\215\205\36\273{\134\331 \205\321\60\265E\303\222\3\331\260,\231\222eJ\66\14:\22\15\203\0_"
  "\205\32\273{\134Y\234\14SX*'\303\220\250Q\62\234\32\263$L\303l\2R\60\34\273{\34\207"
  "\254\34%Q%K\242\341\224\225\262\322\60$QV\312\206lH\7ON\35\273{\134\251\226\14aT"
  "\214jR%\212\206!\211\212Q\61J:iJ\224H\1u\65\30\272|\234\71\224%\303A\253\14\227"
  "\254\222U\206K\226Ca:\10\213\373\36\273{\34ii\330\201\34x\310\222(\211\22\61K\302d\30"
  "\224\64\324\222,\322\22\0\232\330\32\273{\274\351p\320\11\327\60\33\16I\216T\6)\251EI\62H"
  "I<\217\307\34\273{\34\71\220\305Y\62\14:\22-Y\30\25\243b\32f[\222\3\331\60\4g:"
  "\35\273{\134i\30\15\312\60\205Q\61\252-Q\246H\225\250%\252DI\226D\342\0h\300\35\273{"
  "\134Y\234iC\22\205I\30IC\222\354@\322\224\224\222Z\224\324\322p\70p\331\36\273{\134Y\234"
  "\15\231\222%=%a\226dI\230hR\64HI-\312*\341\240\0w \36\273{\234\303\262\204I"
  "crX\232\262$\31\16I\224%\245,\251%CR\22\305\0j!!\273{\134\311\60DY\22\15"
  "\311\240EY$\15\322\222%\245A)\246\311\60DY\22&\232\0Qh\31\273{\274\71\224\344@\226"
  "\226\224AQs,\7\16\71\220c\351p\20_\17\33\273{\334I\216D\311p\220s,\34\206\34\210"
  "r \213\263(\233\222!\26\224\301\35\273{<i\230%\341\62(a\222\15R\30\15\7-L\303$"
  "J\62)\213\252\1Y\64\31\273{\334\261\224#U-\7\242\34\213\222\341\240\346P\42\207\312\16\4n"
  ")\34\273{\34\331\60\25\323a\311\302(\32\246\34K\206!\211\222NI\247\244\313pO\21\30\273{"
  "\134Y\234\305\303)K\265\60\211\326\244Q\252\65eq\26\2S\213\32\273{<\303!\311\261r\26g"
  "q\62\14Q\226\204Y\224\265\204i\62\34P<\34\273{\134Y<\234\262\64\32\246b\42\205Q\64L"
  "\305(\32\246b\224\14\203\0\0";

  return 0;
}


static uint8_t  drawScreenSaver(uint8_t refresh){
#ifdef SCREENSAVER
  if(!refresh || !screenSaver.enabled || getCurrentMode()!=mode_sleep || mainScr.currentMode!=main_irontemp){
    return 0;
  }
  screenSaver.update=0;
  if(screenSaver.x>(-ScrSaverXBM.width) ||screenSaver.x<displayWidth || screenSaver.y>(-ScrSaverXBM.height) || screenSaver.y<displayHeight ){
    u8g2_SetDrawColor(&u8g2, WHITE);
    u8g2_DrawXBMP(&u8g2, screenSaver.x, screenSaver.y, ScrSaverXBM.width, ScrSaverXBM.height, ScrSaverXBM.xbm);
    return 1;
  }
#endif
  return 0;
}

static void  drawMode(uint8_t refresh){
  if(!refresh) return;

  u8g2_SetFont(&u8g2, u8g2_font_small);

  switch(getCurrentMode()){

    case mode_run:
    {
      char SetTemp[8];
      char c;
      if(getSystemTempUnit()==mode_Celsius){
        c='C';
      }
      else{
        c='F';
      }
      sprintf(SetTemp,"%u\260%c", getIronTargetTemperature(),c);
      u8g2_DrawUTF8(&u8g2, 46, 0, SetTemp);
      break;
    }

    case mode_sleep:
      u8g2_DrawUTF8(&u8g2,  strings[lang].main_mode_Sleep_xpos, 0, strings[lang].main_mode_Sleep);
      break;

    case mode_standby:
      u8g2_DrawUTF8(&u8g2, strings[lang].main_mode_Standby_xpos, 0, strings[lang].main_mode_Standby);
      break;

    case mode_boost:
      u8g2_DrawUTF8(&u8g2, strings[lang].main_mode_Boost_xpos, 0, strings[lang].main_mode_Boost);

    default:
      break;
  }
}

static uint8_t  drawPowerBar(uint8_t refresh){
  static uint8_t previousPower=0;
  uint8_t update=refresh;
  if((current_time-barTime)>9){
    barTime = current_time;
    if(previousPower!=mainScr.lastPwr){
      previousPower = mainScr.lastPwr;
      update=1;
    }
  }
  if(update){                          // Update every 10mS or if screen was erased
    if(!refresh){                           // If screen not erased
      u8g2_SetDrawColor(&u8g2,BLACK);                               // Draw a black square to wipe old widget data
      u8g2_DrawBox(&u8g2, displayWidth-PWR_BAR_WIDTH-2 , displayHeight-7, PWR_BAR_WIDTH, 5);
      u8g2_SetDrawColor(&u8g2,WHITE);
    }
    else{
      u8g2_DrawRFrame(&u8g2, displayWidth-PWR_BAR_WIDTH-4, displayHeight-9, PWR_BAR_WIDTH+4, 9, 2);
    }
    u8g2_DrawBox(&u8g2, displayWidth-PWR_BAR_WIDTH-2, displayHeight-7, mainScr.lastPwr, 5);
    return 1;
  }
  return 0;
}

static uint8_t  drawPlot(uint8_t refresh){
#define PLOT_X  7
#define PLOT_Y  12

  plot.enabled &= !(getIronErrorFlags().active);

  if(!plot.enabled){ return 0; }
  if(refresh || plot.update){
    int16_t ref;
    if(getCurrentMode() != mode_sleep){
      ref=getIronTargetTemperature();
      if(getSystemTempUnit()==mode_Farenheit){
        ref = TempConversion(ref, mode_Celsius, 0);
      }
    }
    else{
      ref = (last_NTC_C+5)/10;                                          // Use ambient temperature as reference when sleeping
    }

    plot.update=0;
    // plot is 16-56 V, 14-113 H ?
    u8g2_DrawVLine(&u8g2, PLOT_X+3, PLOT_Y, 41);                                // left scale
    for(uint8_t t=0;t<5;t++){
      u8g2_DrawHLine(&u8g2, PLOT_X, PLOT_Y+(10*t), 3);                                     // left ticks
    }
    /*
    12-13-14-15-16-17-18-19-20-21
    22-
    32------
    42-
    52-
    */
    for(uint8_t x=0; x<100; x++){
      uint8_t pos=plot.index+x;
      if(pos>99){ pos-=100; }                                             // Reset index if > 99

      int16_t plotV = (plot.d[pos]-ref)+20;                               // relative to t, +-20C

      if (plotV < 1) plotV = 0;
      else if (plotV > 40) plotV = 40;

      u8g2_DrawVLine(&u8g2, x+PLOT_X+7, (PLOT_Y+40)-plotV, plotV+1);              // data points
    }
    #define set (PLOT_Y+20)
    u8g2_DrawTriangle(&u8g2, PLOT_X+116, set-3, PLOT_X+116, set+3, PLOT_X+110, set);           // Setpoint marker
    return 1;
  }
  return 0;
}

static uint8_t  drawError(uint8_t refresh){
  static uint32_t last_time;
  static uint8_t x_mark_state;
  if(mainScr.ironStatus!=status_error || mainScr.currentMode==main_setpoint ){
    x_mark_state=0;
    last_time = current_time;
    return 0;
  }

  IronError_t const ironErrorFlags = getIronErrorFlags();

  if(ironErrorFlags.Flags == (FLAG_ACTIVE | FLAG_NO_IRON)){                               // Only "No iron detected". Don't show error screen just for it

    uint8_t xp, update = 0;

    if(systemSettings.currentProfile == profile_T12)
      xp = (displayWidth-ironXBM_T12.width-x_markXBM.width-5)/2;
    else
      xp = (displayWidth-ironXBM_JBC.width-x_markXBM.width-5)/2;

    if(refresh){
      if(systemSettings.currentProfile == profile_T12)
        u8g2_DrawXBM(&u8g2, xp, (displayHeight-ironXBM_T12.height)/2, ironXBM_T12.width, ironXBM_T12.height, ironXBM_T12.xbm);
      else
        u8g2_DrawXBM(&u8g2, xp, (displayHeight-ironXBM_JBC.height)/2, ironXBM_JBC.width, ironXBM_JBC.height, ironXBM_JBC.xbm);
      update = 1;
    }

    if(current_time-last_time>500){
      last_time=current_time;
      x_mark_state ^=1;
      update=1;
    }

    if(update){
      if(x_mark_state){
        u8g2_SetDrawColor(&u8g2, BLACK);
        if(systemSettings.currentProfile == profile_T12)
          u8g2_DrawBox(&u8g2, xp+ironXBM_T12.width+5, (displayHeight-x_markXBM.height)/2, x_markXBM.width, x_markXBM.height);
        else
          u8g2_DrawBox(&u8g2, xp+ironXBM_JBC.width+5, (displayHeight-x_markXBM.height)/2, x_markXBM.width, x_markXBM.height);
        u8g2_SetDrawColor(&u8g2, WHITE);
      }
      else{
        if(systemSettings.currentProfile == profile_T12)
          u8g2_DrawXBM(&u8g2, xp+ironXBM_T12.width+5, (displayHeight-x_markXBM.height)/2, x_markXBM.width, x_markXBM.height, x_markXBM.xbm);
        else
          u8g2_DrawXBM(&u8g2, xp+ironXBM_JBC.width+5, (displayHeight-x_markXBM.height)/2, x_markXBM.width, x_markXBM.height, x_markXBM.xbm);
      }
    }
    return update;
  }
  else if(refresh){
    uint8_t Err_ypos;

    uint8_t err = (uint8_t)ironErrorFlags.V_low +
                  (uint8_t)ironErrorFlags.safeMode +
                  (uint8_t)(ironErrorFlags.NTC_low | ironErrorFlags.NTC_high) +
                  ironErrorFlags.noIron;
    if(err<4){
      Err_ypos= 12+ ((40-(err*12))/2);
    }
    else{
      Err_ypos=12;
    }
    u8g2_SetFont(&u8g2, u8g2_font_small);
    if(ironErrorFlags.V_low){
      putStrAligned(strings[lang].main_error_VoltageLow, Err_ypos, align_center);
      Err_ypos+=12;
    }
    if(ironErrorFlags.safeMode){
      putStrAligned(strings[lang].main_error_failsafe, Err_ypos, align_center);
      Err_ypos+=12;
    }
    if(ironErrorFlags.NTC_high){
      putStrAligned(strings[lang].main_error_NTC_high, Err_ypos, align_center);
      Err_ypos+=12;
    }
    else if(ironErrorFlags.NTC_low){
      putStrAligned(strings[lang].main_error_NTC_low, Err_ypos, align_center);
      Err_ypos+=12;
    }
    if(ironErrorFlags.noIron){
      putStrAligned(strings[lang].main_error_noIron_Detected, Err_ypos, align_center);
      Err_ypos+=12;
    }
    return 1;
  }
  return 0;
}

static void  drawMisc(uint8_t refresh){
  if(!refresh) return;
  uint8_t len = 0;
  char *s = NULL;

  Widget_SetPoint->enabled &= (mainScr.currentMode==main_setpoint);                            // Disable setpoint widget if not in setpoint screen

  u8g2_SetFont(&u8g2, u8g2_font_small);
  if(mainScr.currentMode==main_tipselect || mainScr.currentMode==main_tipselect_auto){

  }
  if(mainScr.currentMode==main_profileselect){
    len = u8g2_GetUTF8Width(&u8g2, profileStr[systemSettings.currentProfile])+4;              // Profile string len
    s = profileStr[systemSettings.currentProfile];                                            // Profile name
  }
  else{
    len = u8g2_GetUTF8Width(&u8g2, tipNames[systemSettings.currentTip])+4;                    // Tip string len
    s = tipNames[systemSettings.currentTip];                                                  // Tip name
  }
  if(mainScr.currentMode==main_tipselect || mainScr.currentMode==main_tipselect_auto || mainScr.currentMode==main_profileselect){     // Tip / profile selection active
    u8g2_DrawRBox(&u8g2, 0, 54, len, 10, 2);                                                  // Draw edit frame
    u8g2_SetDrawColor(&u8g2, BLACK);
  }
  u8g2_DrawUTF8(&u8g2, 2, 54, s);                                                             // Draw tip/profile name
  u8g2_SetDrawColor(&u8g2, WHITE);
  return;
}

static uint8_t main_screen_draw(screen_t *scr){
  static uint32_t lastState = 0;

  uint8_t refresh= 0u;
  uint8_t ret    = 0u;

  IronError_t const ironErrorFlags = getIronErrorFlags();

  uint32_t currentState = (uint32_t)ironErrorFlags.Flags<<24 | (uint32_t)getCurrentMode()<<16 | mainScr.currentMode;    // Simple method to detect changes

  if( lastState!=currentState || Widget_SetPoint->refresh || Widget_IronTemp->refresh || plot.update || screenSaver.update || scr->state==screen_Erase
      #ifdef USE_NTC
      || Widget_AmbTemp->refresh
      #endif
      #ifdef USE_VIN
      || Widget_Voltage->refresh
      #endif
                              ){

    lastState=currentState;
    refresh=1;
  }
  if(refresh){
    scr->state=screen_Erased;
    fillBuffer(BLACK, fill_dma);
  }

  u8g2_SetDrawColor(&u8g2, WHITE);

  if(mainScr.ironStatus != status_error){
    ret |= drawScreenSaver(refresh);
  }
  ret |= drawPowerBar(refresh);
  ret |= drawIcons(refresh);
  drawMode(refresh);
  drawMisc(refresh);
  ret |= drawPlot(refresh);
  ret |= drawError(refresh);
  ret |= default_screenDraw(scr);
  if(ironErrorFlags.active && mainScr.ironStatus!=status_error){
    return 0u;                                                                                // If a new error appeared during the screen draw, skip oled update to avoid random artifacts
  }
  return (ret);
}

static void main_screen_init(screen_t *scr) {
  editable_widget_t *edit;
  default_init(scr);
  clearIronShakeFlag();
  mainScr.shakeActive = 0;
  plot.timeStep = (systemSettings.Profile.readPeriod+1)/200;                                                         // Update at the same rate as the system pwm

  mainScr.setMode = main_irontemp;
  switchScreenMode();

  edit = extractEditablePartFromWidget(Widget_SetPoint);
  edit->step = systemSettings.settings.tempStep;
  edit->big_step = systemSettings.settings.tempBigStep;
  edit->max_value = systemSettings.Profile.MaxSetTemperature;
  edit->min_value = systemSettings.Profile.MinSetTemperature;
  setMainScrTempUnit();
}

static void main_screen_create(screen_t *scr){
  widget_t *w;
  displayOnly_widget_t* dis;
  editable_widget_t* edit;

  //  [ Iron Temp Widget ]
  //
  newWidget(&w,widget_display,scr,NULL);
  Widget_IronTemp = w;
  dis=extractDisplayPartFromWidget(w);
  edit=extractEditablePartFromWidget(w);
  dis->reservedChars=5;
  dis->dispAlign=align_center;
  dis->textAlign=align_center;
  dis->font=u8g2_font_iron_temp;
  w->posY = 16;
  dis->getData = &main_screen_getIronTemp;
  w->enabled=0;
  //  [ Iron Setpoint Widget ]
  //
  newWidget(&w,widget_editable,scr,NULL);
  Widget_SetPoint=w;
  dis=extractDisplayPartFromWidget(w);
  edit=extractEditablePartFromWidget(w);
  dis->reservedChars=5;
  w->posY = Widget_IronTemp->posY-2;
  dis->getData = &getTemp;
  dis->dispAlign=align_center;
  dis->textAlign=align_center;
  dis->font=((displayOnly_widget_t*)Widget_IronTemp->content)->font;
  edit->selectable.tab = 1;
  edit->setData = (void (*)(void *))&setTemp;
  w->frameType=frame_solid;
  edit->selectable.state=widget_edit;
  w->radius=0;	//hifly
  w->enabled=0;
  w->width=128;

  #ifdef USE_VIN
  //  [ V. Supply Widget ]
  //
  newWidget(&w,widget_display,scr,NULL);
  Widget_Voltage=w;
  dis=extractDisplayPartFromWidget(w);
  dis->getData = &main_screen_getVin;
  dis->endString="V";
  dis->reservedChars=5;
  dis->textAlign=align_center;
  dis->number_of_dec=1;
  dis->font=u8g2_font_small;
  w->posY= 0;
  w->posX = voltXBM.width+2;
  edit=extractEditablePartFromWidget(w);
  //w->width = 40;
  #endif

  #ifdef USE_NTC
  //  [ Ambient Temp Widget ]
  //
  newWidget(&w,widget_display,scr,NULL);
  Widget_AmbTemp=w;
  dis=extractDisplayPartFromWidget(w);
  dis->reservedChars=7;
  dis->dispAlign=align_right;
  dis->textAlign=align_right;
  dis->number_of_dec=1;
  dis->font=u8g2_font_small;
  dis->getData = &main_screen_getAmbTemp;
  w->posY = 0;
  w->posX = 90;
  w->width = 38;
  #endif
}


void main_screen_setup(screen_t *scr) {
  scr->draw = &main_screen_draw;
  scr->init = &main_screen_init;
  scr->processInput = &main_screenProcessInput;
  scr->create = &main_screen_create;

  for(int x = 0; x < NUM_TIPS; x++) {
    tipNames[x] = systemSettings.Profile.tip[x].name;
  }
}
