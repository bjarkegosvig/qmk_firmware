#include <stdarg.h>
#include QMK_KEYBOARD_H
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "timer.h"
#include "keymap_plover.h"
#include "eeconfig.h"
#include "wait.h"
#include "version.h"


#define BASE 0 // default layer
#define DVRK 1 // Dvorak
#define FKEY 2 // F keys
#define SYMB 3 // symbols
#define NUM  4 // numpad
#define MDIA 5 // media keys
#define ARRW 6 // Arrows
#define GAME 7 // gaming keys
#define GAME2 8 // gaming keys
#define REST 9 // flash mode
#define LAYER_MODOLUS 10 // highest layer + 1


static uint16_t key_timer;


uint8_t next_layer = 0;
//Tap Dance Declarations
enum {
  TD_LBP = 0,
  TD_RBP,
  TD_DOT,
  TD_COL,
  CT_TA,
  CT_LK,
  CT_AW,
  CT_LC,
  CT_AFW,
  CT_LU,
  CT_DN,
};

// macro deceletations
enum {
  MC_CP = 0 // copy on hold, paste on tap
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |  F5  |           | Esc  |   6  |   7  |   8  |   9  |   0  |   rofi |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Tab/ARRW|   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|   /  |           | SF11 |------+------+------+------+------+--------|
 * | LCTL   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / LM|   '"   |
 * |--------+------+------+------+------+------|   .  |           |OS Sb |------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |   ,  |           |      |   N  |   M  |   ,  |   .  |   /  | RCtrl  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LD   |   \  |   ~  | Alt  | ;/:  |                                       |   -  |OS Sb |OS FL | NumPL|  LU   |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                      ,---------------.       ,---------------.
 *                                      |  Esc   |   <  |       |   >  |  Lead  |  
 *                               ,------|--------|------|       |------+--------+------.
 *                               |      |        | Home |       |Del   |        |      |
 *                               | Space| Enter  |------|       |------| LSFT   |Bcksp |
 *                               |      | ~WIN   | End  |       |Win/lk|        |      |
 *                               `----------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
    // left hand
    KC_EQL,          KC_1,         KC_2,          KC_3,    KC_4,    KC_5,   KC_F5,
    LT(ARRW,KC_TAB), KC_Q,         KC_W,          KC_E,    KC_R,    KC_T,   KC_SLASH,
    KC_LCTL,         KC_A,         KC_S,          KC_D,    KC_F,    KC_G,
    KC_LSFT,         KC_Z,         KC_X,          KC_C,    KC_V,    KC_B,   TD(TD_DOT),
    TD(CT_LU),          KC_BSLS,      KC_TILD,       KC_LALT,   TD(TD_COL),
                                                                KC_ESC, LSFT(KC_COMMA), 
                                                                               KC_HOME,
                                                     KC_SPACE, GUI_T(KC_ENTER), KC_END,
    // right hand
    KC_ESC,       KC_6,    KC_7,      KC_8,      KC_9,      KC_0,              TD(CT_TA), 
    LSFT(KC_F11), KC_Y,    KC_U,      KC_I,      KC_O,      KC_P,              KC_BSLS,
                  KC_H,    KC_J,      KC_K,      KC_L,      TD(CT_AFW),        KC_QUOT,
    OSL(SYMB),    KC_N,    KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,           OSM(MOD_RCTL),
                           KC_MINS,   OSL(SYMB), TG(FKEY),  TG(NUM),          TD(CT_DN),
    LSFT(KC_DOT), KC_LEAD,
    KC_DEL,
    TD(CT_LK),      KC_LSFT,  KC_BSPACE
),
/* Keymap Dvorak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |  F5  |           | Esc  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab/L5 |   '" |   ,  |   .  |   P  |   Y  |      |           | cbld |   F  |   G  |   C  |   R  |   L  |   \    |
 * |--------+------+------+------+------+------|   /  |           |      |------+------+------+------+------+--------|
 * | LShift |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |S / LM|   '"   |
 * |--------+------+------+------+------+------|   .  |           |   ;  |------+------+------+------+------+--------|
 * |  LCtrl |   :  |   Q  |   J  |   K  |   X  |   ,  |           |   :  |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LD   |   \  |   ~  | Alt  |OS L2 |                                       | OS L1|  FnL |SymbL | NumPL|  LU  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,---------------.       ,---------------.
 *                                      |   Alt  |   <  |       |   >  |  Lead  |  
 *                               ,------|--------|------|       |------+--------+------.
 *                               |      |        | Home |       |   `  |        |      |
 *                               | Space| Enter  |------|       |------| Enter  |Bcksp |
 *                               |      | ~WIN   | End  |       | Win  | ~LSFT  |      |
 *                               `----------------------'       `----------------------'
 */

[DVRK] = KEYMAP(          // left hand
        KC_EQL,         KC_1,           KC_2,    KC_3,   KC_4,   KC_5,   KC_F5,
        LT(ARRW,KC_TAB),KC_QUOT,        KC_COMM, KC_DOT, KC_P,   KC_Y,   KC_SLASH,
        KC_LCTRL,       KC_A,           KC_O,    KC_E,   KC_U,   KC_I,
        OSM(MOD_LSFT),  KC_SCLN,        KC_Q,    KC_J,   KC_K,   KC_X,   TD(TD_DOT),
        TD(CT_LU),         KC_BSLS,        KC_TILD, KC_LALT,        OSL(SYMB),
                                                 ALT_T(KC_ESC),             LSFT(KC_COMMA), 
                                                                          KC_HOME,
                                                 KC_SPACE, GUI_T(KC_ENTER), KC_END,
        // right hand
             KC_ESC,      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_DELETE,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,             KC_BSLS,
                          KC_D,   KC_H,   KC_T,   KC_N,   LT(MDIA, KC_S),   KC_QUOT,
             TD(TD_COL),  KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,             KC_RCTRL,
                                  OSL(FKEY), TG(FKEY), TG(SYMB), TG(NUM),   TD(CT_DN),
             LSFT(KC_DOT), KC_LEAD,
             KC_GRV,
             KC_RGUI, SFT_T(KC_ENTER), KC_BSPACE
),




/* Keymap : FKEY
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F8  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[FKEY] = KEYMAP(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),


/* Keymap : Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | PrScr  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Insert |   &  |   @  |   {  |   }  |   |  |      |           |      |      | Home |  Up  | End  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Pause  |   #  |   $  |   (  |   )  |   *  |------|           |------|      | Left | Down |Right |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |      |  <   |  >   |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, LSFT(KC_7), KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,  KC_TRNS,
       KC_TRNS, KC_HASH,    KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR,
       KC_TRNS,  KC_PERC,   KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,  KC_TRNS,
       KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                                                         KC_TRNS, KC_TRNS,
                                                                  KC_TRNS,
                                                KC_TRNS, KC_TRNS, KC_TRNS,

        // right hand
        KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_HOME,        KC_UP,        KC_END,  KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_LEFT,        KC_DOWN,      KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, LSFT(KC_COMMA), LSFT(KC_DOT), KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS,        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS    ,KC_TRNS
),

/* Keymap : Numeric Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   Up |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Down |   1  |   2  |   3  |   /  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   &  |      |    . |   0  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[NUM] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9,    KC_ASTR,  KC_TRNS,
       KC_TRNS, KC_UP,   KC_4,    KC_5,    KC_6,    KC_PLUS,  KC_TRNS,
                KC_DOWN, KC_1,    KC_2,    KC_3,    KC_SLASH, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_TRNS, KC_DOT,  KC_0,    KC_TRNS,  KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),


/* Keymap : Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap : Arrow layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      | Home |  Up  |  End |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      | Left | Down | Rght |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

[ARRW] = KEYMAP(
      // left hand
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                  KC_TRNS,  KC_TRNS,
                                                            KC_TRNS,
                                          KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_TRNS,
               KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   
      KC_TRNS, KC_TRNS,
      KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap : gaming
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |   \  |Alt   | Left | Space|                                       |Volup |Voldn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,---------------.       ,---------------.
 *                                      |        |Al/Esc|       |      |        |r 
 *                               ,------|--------|------|       |------+--------+------.
 *                               |      |        | Home |       |      |        |      |
 *                               |Space |   R    |------|       |------|        |      |
 *                               |      |        | End  |       |      |        |      |
 *                               `----------------------'       `----------------------'
 */

[GAME] = KEYMAP(  // layer 0 : default
    // left hand
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4, KC_5, KC_TRNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R, KC_T, KC_TRNS,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F, KC_G,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V, KC_B, KC_TRNS,
    KC_TRNS,  KC_BSLS, KC_LALT, KC_F, KC_G,
                                   KC_TRNS,         KC_TRNS,
                                                    KC_TRNS,
                                   KC_SPC, KC_R,    KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap : gaming2
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |  Up  |   E  |   R  |   T  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  | Left | Down | Rght |   F  |   G  |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |   \  |Alt   | Left | Space|                                       |Volup |Voldn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,---------------.       ,---------------.
 *                                      |        |Al/Esc|       |      |        |r 
 *                               ,------|--------|------|       |------+--------+------.
 *                               |      |        | Home |       |      |        |      |
 *                               |Space |   R    |------|       |------|        |      |
 *                               |      |        | End  |       |      |        |      |
 *                               `----------------------'       `----------------------'
 */

[GAME2] = KEYMAP(  // layer 0 : default
    // left hand
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4, KC_5, KC_TRNS,
    KC_TAB,  KC_Q,    KC_UP,   KC_E,    KC_R, KC_T, KC_TRNS,
    KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_F, KC_G,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V, KC_B, KC_TRNS,
    KC_TRNS,  KC_BSLS, KC_LALT, KC_F, KC_G,
                                   KC_TRNS,         KC_TRNS,
                                                    KC_TRNS,
                                   KC_SPC, KC_R,    KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),




/* Keymap : reset layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      | Home |  Up  |  End |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      | Left | Down | Rght |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      | Flash|           |Flash |      |      |
 *                                  `--------------------'           `--------------------'
 */

[REST] = KEYMAP(
    // left hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                KC_TRNS,  KC_TRNS,
                                                          KC_TRNS,
                                          KC_TRNS, KC_TRNS, RESET,

    // right hand
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                       KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    RESET, KC_TRNS, KC_TRNS
),

};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_SET(FKEY, ON_PRESS),     // FN0 move to Fn'd             when press
    [1] = ACTION_LAYER_SET(SYMB, ON_PRESS),     // FN1 move to Fn'd arrow       when press
    [2] = ACTION_LAYER_SET(NUM, ON_PRESS),     // FN2 move to Fn'd Esc         when press
    [3] = ACTION_LAYER_SET(MDIA, ON_PRESS),     // FN2 move to Fn'd Esc         when press
    [4] = ACTION_LAYER_SET(ARRW, ON_PRESS), // FN3 move to Fn'd arrow + Esc when press
    [5] = ACTION_LAYER_SET(GAME, ON_PRESS), // FN3 move to Fn'd arrow + Esc when press
    [6] = ACTION_LAYER_SET(REST, ON_PRESS), // FN3 move to Fn'd arrow + Esc when press
    [7] = ACTION_LAYER_SET(BASE, ON_PRESS), // FN3 move to Fn'd arrow + Esc when press

};




void td_left_brackets(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_LBRC);
    unregister_code (KC_LBRC);
    break;
  case 2:
    register_code (KC_LSFT);
    register_code (KC_9);
    unregister_code (KC_9);
    unregister_code (KC_LSFT);
    break;
  }
};

void td_right_brackets(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_RBRC);
    unregister_code (KC_RBRC);
    break;
  case 2:
    register_code (KC_LSFT);
    register_code (KC_0);
    unregister_code (KC_0);
    unregister_code (KC_LSFT);
    break;
   }
};
void td_dot_comma(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_DOT);
    unregister_code (KC_DOT);
    break;
  case 2:
    register_code (KC_COMM);
    unregister_code (KC_COMM);
    break;
   }
};

void td_semicol_col(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_SCOLON);
    unregister_code (KC_SCOLON);
    break;
  case 2:
    register_code (KC_LSFT);
    register_code (KC_SCOLON);
    unregister_code (KC_SCOLON);
    unregister_code (KC_LSFT);
    break;
   }
};

void td_lsft_aswm(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_LALT);
    register_code (KC_LSFT);
    register_code (KC_SPC);
    unregister_code (KC_LALT);
    unregister_code (KC_LSFT);
    unregister_code (KC_SPC);
    break;
   case 2:
    register_code (KC_LALT);
    register_code (KC_LCTRL);
    register_code (KC_ENTER);
    unregister_code (KC_LALT);
    unregister_code (KC_LCTRL);
    unregister_code (KC_ENTER);
    break;
  case 3:
    register_code (KC_LALT);
    register_code (KC_LSFT);
    register_code (KC_C);
    unregister_code (KC_LALT);
    unregister_code (KC_LSFT);
    unregister_code (KC_C);
    break;
  case 4: 
    register_code (KC_LALT);
    register_code (KC_LSFT);
    register_code (KC_D);
    unregister_code (KC_LALT);
    unregister_code (KC_LSFT);
    unregister_code (KC_D);
    break;
   }
};

void td_win_lock(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_LGUI);
    unregister_code (KC_LGUI);
    break;
  case 2:
    register_code (KC_LGUI);
    register_code (KC_L);
    unregister_code (KC_L);
    unregister_code (KC_LGUI);
    break;
  case 3:
    register_code (KC_LCTRL);
    register_code (KC_LALT);
    register_code (KC_DEL);
    unregister_code (KC_LCTRL);
    unregister_code (KC_LALT);
    unregister_code (KC_DEL);
    break;
   }
};

void td_launcher(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_LALT);
    register_code (KC_P);
    unregister_code (KC_LALT);
    unregister_code (KC_P);
    break;
  case 2:
    register_code (KC_ESC);
    unregister_code (KC_ESC);
    break;
   }
};

typedef struct {
  bool layer_toggle;
  bool sticky;
} td_ta_state_t;

static void ang_tap_dance_ta_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (td_ta->sticky) {
    td_ta->sticky = false;
    td_ta->layer_toggle = false;
    layer_off (NUM);
    return;
  }

  if (state->count == 1 && !state->pressed) {
    register_code (KC_LALT);
    register_code (KC_P);
    td_ta->sticky = false;
    td_ta->layer_toggle = false;
  } else {
    td_ta->layer_toggle = true;
    layer_on (NUM);
    td_ta->sticky = (state->count == 2);
  }
}

static void ang_tap_dance_ta_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle) {
    unregister_code (KC_LALT);
    unregister_code (KC_P);
  }
  if (!td_ta->sticky) {
    layer_off (NUM);
  }
}

static void td_layer_up(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_LEFT);
    unregister_code (KC_LEFT);
    break;
  case 2:
    layer_off(next_layer);
    next_layer = (((next_layer+1) % 10) + 10) % 10;
    layer_on(next_layer);
    break;
   }
};

static void td_layer_down(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_RGHT);
    unregister_code (KC_RGHT);
    break;
  case 2:
    layer_off(next_layer);
    next_layer = (((next_layer-1) % 10) + 10) % 10;
    layer_on(next_layer);
    break;
   }
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RBP]  = ACTION_TAP_DANCE_FN (td_right_brackets)
 ,[TD_LBP] = ACTION_TAP_DANCE_FN (td_left_brackets)
 ,[TD_DOT] = ACTION_TAP_DANCE_FN (td_dot_comma)
 ,[TD_COL] = ACTION_TAP_DANCE_FN (td_semicol_col)
 ,[CT_TA]  = { // two taps switched to the Numpad layer permenent stolen from algernon
     .fn = { NULL, ang_tap_dance_ta_finished, ang_tap_dance_ta_reset },
     .user_data = (void *)&((td_ta_state_t) { false, false })
            }
 ,[CT_LK] = ACTION_TAP_DANCE_FN(td_win_lock)
 ,[CT_AW] = ACTION_TAP_DANCE_FN(td_lsft_aswm)
 ,[CT_LC] = ACTION_TAP_DANCE_FN(td_launcher)
 ,[CT_AFW] = ACTION_TAP_DANCE_DUAL_ROLE(KC_SCLN, ARRW)
 ,[CT_LU] = ACTION_TAP_DANCE_FN(td_layer_up) 
 ,[CT_DN] = ACTION_TAP_DANCE_FN(td_layer_down) 
};



//macro
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case MC_CP: { // copy on held past on tap
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO(D(LALT), D(LCTL), T(C), U(LALT), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LALT), D(LCTL), T(V), U(LALT), U(LCTL), END  );
                }
            }
            break;
        }
      }
    return MACRO_NONE;
};


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  uint8_t dl;
  next_layer = 0;
  // is_dvrk = 0; 
  if (!eeconfig_is_enabled())
    eeconfig_init();
  dl = eeconfig_read_default_layer ();
 // if (dl == (1UL << DVRK)) {
    //is_dvrk = 1;
  //}
  next_layer = dl;
};


LEADER_EXTERNS();
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

 //   uint8_t layer = biton32(layer_state);

    // ergodox_board_led_off();
    // ergodox_right_led_1_off();
    // ergodox_right_led_2_off();
    // ergodox_right_led_3_off();
    // switch (layer) {
    //   // TODO: Make this relevant to the ErgoDox EZ.
    //     case 1:
    //         ergodox_right_led_1_on();
    //         break;
    //     case 2:
    //         ergodox_right_led_2_on();
    //         break;
    //     default:
    //         // none
    //         break;
    // }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // do a vim yank line
    SEQ_ONE_KEY(KC_Y) {
      register_code(KC_HOME);   
      unregister_code(KC_HOME);
      register_code(KC_RSFT);
      register_code(KC_END);
      unregister_code(KC_END);
      unregister_code(KC_RSFT); 
      register_code(KC_LCTL);
      register_code(KC_C);
      unregister_code(KC_C);
      unregister_code(KC_LCTL);
      register_code(KC_END);
      unregister_code(KC_END);
    }
    // do a vim cut line
    SEQ_ONE_KEY(KC_D) {
      register_code(KC_HOME);   
      unregister_code(KC_HOME);
      register_code(KC_RSFT);
      register_code(KC_END);
      unregister_code(KC_END);
      unregister_code(KC_RSFT); 
      register_code(KC_LCTL);
      register_code(KC_X);
      unregister_code(KC_X);
      unregister_code(KC_LCTL);
      register_code(KC_END);
      unregister_code(KC_END);
    }
    // do a vim paste line
    SEQ_ONE_KEY(KC_P) {
      register_code(KC_END);    
      unregister_code(KC_END);
      register_code(KC_ENT);
      unregister_code(KC_ENT);
      register_code(KC_LCTL);
      register_code(KC_V);
      unregister_code(KC_V); 
      unregister_code(KC_LCTL);
    }

        // ctrl-x
    SEQ_ONE_KEY(KC_COMMA) {
      register_code(KC_LCTL);
      register_code(KC_X);
      unregister_code(KC_X);
      unregister_code(KC_LCTL);
    }
        // ctrl-c
    SEQ_ONE_KEY(KC_N) {
      register_code(KC_LCTL);
      register_code(KC_C);
      unregister_code(KC_C);
      unregister_code(KC_LCTL);
    }
        // ctrl-v
    SEQ_ONE_KEY(KC_DOT) {
      register_code(KC_LCTL);
      register_code(KC_V);
      unregister_code(KC_V);
      unregister_code(KC_LCTL);
    }
    
        SEQ_ONE_KEY (KC_A) {
//      if (is_dvrk == 0) {
 //       default_layer_and (0);
 //       default_layer_or ((1UL << DVRK));
 //       eeconfig_update_default_layer ((1UL << DVRK));
  //      is_dvrk = 1;

    //  } else {
//        is_dvrk = 0;
        default_layer_and (0);
        default_layer_or (1UL << BASE);
        eeconfig_update_default_layer ((1UL << BASE));

      //}
    }
    
    SEQ_TWO_KEYS(KC_C, KC_S) {
    SEND_STRING("static_cast<>");

}

   
  }



};
