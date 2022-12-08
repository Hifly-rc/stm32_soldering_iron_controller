/*
 * debug_screen.h
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#ifndef _GUI_DISPLAY_SCREEN_H_
#define _GUI_DISPLAY_SCREEN_H_

#include "screen.h"


extern screen_t Screen_display;
void display_screen_setup(screen_t *scr);

#ifndef ST7565
extern screen_t Screen_display_adv;
void display_screen_adv_setup(screen_t *scr);
#endif

#endif /* SETTINGS_GUI_DEBUG_SCREEN_H_ */
