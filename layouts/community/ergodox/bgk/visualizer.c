/*
Copyright 2017 Fred Sundvik

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "config.h"
#include "simple_visualizer.h"


// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 128;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    }
    
     if (state->status.layer & 0x200) {
        state->target_lcd_color = LCD_COLOR(255, saturation, 0xFF);
        state->layer_text = "FLASH";
    }
    else if (state->status.layer & 0x100) {
        state->target_lcd_color = LCD_COLOR(80, saturation, 0x85);
        state->layer_text = "GAME 2";
    }
    else if (state->status.layer & 0x80) {
        state->target_lcd_color = LCD_COLOR(15, saturation, 0xFF);
        state->layer_text = "Gaming";
    }
    else if (state->status.layer & 0x40) {
        state->target_lcd_color = LCD_COLOR(170, saturation, 0xFF);
        state->layer_text = "Arrow";
    }
    else if (state->status.layer & 0x20) {
        state->target_lcd_color = LCD_COLOR(113, saturation, 0xFF);
        state->layer_text = "KBD functions";
    }
    else if (state->status.layer & 0x10) {
        state->target_lcd_color = LCD_COLOR(39, saturation, 0xFF);
        state->layer_text = "Num Pad";
    }
    else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(213, saturation, 0xFF);
        state->layer_text = "Symbols";
    }
    else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(125, saturation, 0xFF);
        state->layer_text = "Function keys";
    }
//    else if (state->status.layer & 0x2) {
//    state->target_lcd_color = LCD_COLOR(181, saturation, 0xFF);
//    state->layer_text = "Dvorak";
//    }
    else {
 //       state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
 //       state->layer_text = "Default";
 //       if (is_dvrk == 1)
 //       {
  //          state->target_lcd_color = LCD_COLOR(181, saturation, 0xFF);
  //          state->layer_text = "Dvorak";
  //      }
   //     else {
            state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
            state->layer_text = "Default";
     //   }
    } 
}
