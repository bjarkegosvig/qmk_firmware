#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the KCmap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2
#define _GAME 3
#define _SYMB 4
// Some basic macros
#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

// see https://docs.qmk.fm/#/keycodes for keycodes
#define KC_STAR  LSFT(KC_8)
#define KC_DOLLR LSFT(KC_4)
#define KC_CARET LSFT(KC_6)
#define KC_PRCNT LSFT(KC_5)
#define KC_EXCLM LSFT(KC_1)
#define KC_HASH  LSFT(KC_3)
#define KC_AND   LSFT(KC_7)
#define KC_LCB   LSFT(KC_LBRACKET)
#define KC_RCB   LSFT(KC_RBRACKET)
#define KC_AWDW  LALT(LSFT(KC_H))
#define KC_AWIW  LALT(LSFT(KC_L))
#define KC_AWMM  LCTRL(LGUI(KC_ENTER))
#define KC_MCHAT  LCTRL(LSFT(KC_M))
#define KC_MMON  LGUI(LSFT(KC_LEFT))
#define KC_MXL   LGUI(KC_LEFT)
#define KC_MXR   LGUI(KC_RIGHT)
#define KC_MAX   LGUI(KC_UP)
#define KC_MIN   LGUI(KC_DOWN)
#define KC_MDT   LGUI(LCTRL(KC_D))
#define KC_DTL   LGUI(LCTRL(KC_LEFT))
#define KC_DTR   LGUI(LCTRL(KC_RIGHT))



enum bgk_keycodes {
  KCAE = SAFE_RANGE,
  KCOE,
  KCAA,
};



enum tapdances{
  TD_RBP = 0,
  TD_LBP,
  TD_CLN,
  TD_RST
  // TD_MNUB,
};
// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RBP]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC,KC_RPRN),
  [TD_LBP] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LPRN),
  [TD_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_COLON, KC_SCOLON),
  [TD_RST] = ACTION_TAP_DANCE_DOUBLE(KC_NO, RESET)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_5x7(

/* KCmap 0: Basic layer
 *
 * ,--------------------------------------------------.                    ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  |      |                    | Esc  |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|                    |------+------+------+------+------+------+--------|
 * |Tab/ARRW|   Q  |   W  |   E  |   R  |   T  |{/(/[ |                    |]/)/} |   Y  |   U  |   I  |   O  |   P  |   +=   |
 * |--------+------+------+------+------+------|------|                    |------|------+------+------+------+------+--------|
 * | LCTL   |   A  |   S  |   D  |   F  |   G  | :/;  |                    |      |   H  |   J  |   K  |   L  | ;    |   '"   |
 * |--------+------+------+------+------+------|------'                    '------|------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |                                  |   N  |   M  |   ,  |   .  |   /  |  _-    |
 * `--------+------+------+------+------+------'                                  `-------------+------+------+------+--------'
 *   |      |CTL+X |CTL+C |CTL+V |                                                              |      |      |CTL+S |CTL+Z |
 *   `---------------------------'                            									'----------------------------'
 *						    ,---------------.                                         ,---------------.
 '						    |  Space | Ent  |  ,---------------.   ,---------------.  |  Shft  |BckSP |
 *                          `--------|------'  | LCTL   |Enter |   | LALT |  GUI   |  `--------|------'
 *                                             |--------|------|   |------+--------+
 *                                             | TT SB  | TT FN|   |TT FN | TT SB  |
 *                                             `---------------'   `---------------'
 */
  // left hand
   KC_ESC,    		KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_NO,
   KC_TAB,    		KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   TD(TD_LBP),
   KC_LCTL,   		KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   TD(TD_CLN),
   OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
   KC_NO,   		LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_V),
                               KC_SPC, KC_ENT,
									KC_LCTL, KC_HOME,
									TT(_SYMB), TT(_FN),
        // right hand
                     KC_ESC,       KC_6,    KC_7,    KC_8,     KC_9,     KC_0,         KC_GRV,
                     TD(TD_RBP),   KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,         KC_EQUAL,
                     TT(_SYMB),    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,      KC_QUOTE,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,      KC_MINUS,
                                                     KC_NO,    KC_NO,    LCTL(KC_S),   LCTL(KC_Z),
			KC_LSFT, KC_BSPC,
        KC_LALT, KC_LGUI,
        TT(_FN), TT(_SYMB)),

[_GAME] = LAYOUT_5x7(

/* KCmap 0: Basic layer
 *
 * ,--------------------------------------------------.                    ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  |      |                    | Esc  |   6  |   7  |   8  |   9  |   0  |   rofi |
 * |--------+------+------+------+------+-------------|                    |------+------+------+------+------+------+--------|
 * |Tab/ARRW|   Q  |   W  |   E  |   R  |   T  |{/(/[ |                    |]/)/} |   Y  |   U  |   I  |   O  |   P  |   +=   |
 * |--------+------+------+------+------+------|------|                    |------|------+------+------+------+------+--------|
 * | LCTL   |   A  |   S  |   D  |   F  |   G  | :/;  |                    | SB   |   H  |   J  |   K  |   L  |; / LM|   '"   |
 * |--------+------+------+------+------+------|------'                    '------|------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |                                  |   N  |   M  |   ,  |   .  |   /  |  _-    |
 * `--------+------+------+------+------+------'                                  `-------------+------+------+------+--------'
 *   |      |      |      |      |                                                              |      |      |      |       |
 *   `---------------------------'                            									'----------------------------'
 *						    ,---------------.                                         ,---------------.
 '						    |  Space | Ent  |  ,---------------.   ,---------------.  |  Shft  |BckSP |
 *                          `--------|------'  |  CTRL  |      |   |      |        |  `--------|------'
 *                                             |--------|------|   |------+--------+
 *                                             |   $B   |      |   |      |        |
 *                                             `---------------'   `---------------'
 */
  // left hand
   KC_ESC,    		KC_1,        KC_2,        KC_3,    KC_4,   KC_5,   KC_NO,
   KC_TAB,    		KC_Q,        KC_W,        KC_E,    KC_R,   KC_T,   TD(TD_LBP),
   KC_LCTL,   		KC_A,        KC_S,        KC_D,    KC_F,   KC_G,   TAB_RO,
   OSM(MOD_LSFT),   KC_Z,        KC_X,        KC_C,    KC_V,   KC_B,
   _______,   		LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_V),
                               KC_SPC, KC_ENT,
									KC_LCTL,     _______,
									 TG(_SYMB),  _______,
        // right hand
                     KC_ESC,     KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_GRV,
                     TD(TD_RBP), KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_EQUAL,
                     TG(_SYMB),  KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOTE,
                                 KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_MINUS,
                                       KC_LEFT, KC_UP,    KC_DOWN,  KC_RGHT,
			KC_LSFT, KC_BSPC,
        KC_PGUP, KC_PGDN,
        TG(_SYMB), KC_LALT),

[_FN] = LAYOUT_5x7(
  // left hand
   _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    _______,
   _______,   _______,   _______,    _______,  _______,   _______,  _______,
   _______,   _______,   _______,    _______,  _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,
   KC_MSTP,   KC_MPLY,   KC_MPRV,   KC_MNXT,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
                     _______,   _______,   _______,   _______,   _______,   _______,   KC_F12,
                     _______,   _______,   KCAE,      KCOE,      KCAA,      _______,   _______,
                                _______,   _______,   _______,   _______,   _______,   _______,
                                                      _______,   _______,   _______,   _______,
        _______, _______,
        _______, _______,
        _______, _______),

[_NUMPAD] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,
   _______,   _______,   _______,   _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                                _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                                      KC_P0,     KC_PDOT,   _______,   _______,
        _______, KC_PENT,
        _______, _______,
        _______, _______),

/* KCmap 0: Symbol
 *
 * ,--------------------------------------------------.                    ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |                    |RESET |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|                    |------+------+------+------+------+------+--------|
 * |        |   &  |   @  |   {  |   }  |   |  |      |                    |      |      | Home |  Up  | End  |      |        |
 * |--------+------+------+------+------+------|------|                    |------|------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   *  |      |                    |      |      | Left | Down |Right |      |        |
 * |--------+------+------+------+------+------|------'                    '------|------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |                                  |      |  <   |  >   |      |      |        |
 * `--------+------+------+------+------+------'                                  `-------------+------+------+------+--------'
 *   |      |      |      |      |                                                              |      |      |      |       |
 *   `---------------------------'                            									'----------------------------'
 *						    ,---------------.                                         ,---------------.
 '						    |        |      |  ,---------------.   ,---------------.  |        |Delete|
 *                          `--------|------'  |        |      |   |      |        |  `--------|------'
 *                                             |--------|------|   |------+--------+
 *                                             |        |      |   |      |        |
 *                                             `---------------'   `---------------'
 */
 [_SYMB] = LAYOUT_5x7(
  // left hand
   RESET,    		_______,    _______,    _______,   _______,   _______,  _______,
   _______,    		KC_AMPR,    KC_AT,      KC_LCBR,   KC_RCBR,   KC_PIPE,  _______,
   _______,   		KC_HASH,    KC_DLR,     KC_LPRN,   KC_RPRN,   KC_ASTR,  _______,
   _______,         KC_PERC,    KC_CIRC,    KC_LBRC,   KC_RBRC,   KC_TILD,
   _______,   		_______,   _______,   _______,
                               _______, _______,
									_______, _______,
									_______, _______,
        // right hand
                     _______,    _______,       _______,    _______,     _______,  _______,    _______,
                     _______,    _______,       KC_HOME,    KC_UP,       KC_END,   _______,    _______,
                     _______,    _______,       KC_LEFT,    KC_DOWN,     KC_RGHT,  _______,    _______,
                                 _______,       KC_LT,      KC_GT,       _______,  _______,    _______,
                                       _______, _______,    _______,  _______,
			_______, KC_DEL,
        _______, _______,
        _______, _______
		),
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case _QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case _GAME:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_GAME);
          }
          return false;
          break;
        case KCOE:
          if( record->event.pressed)
          {
              if(keyboard_report->mods & (MOD_BIT(KC_LSFT)))
              {
                  /* clear_mods(); */
                  unregister_code(KC_LSFT);
                  SEND_STRING(SS_RALT("/O"));
                  register_code(KC_LSFT);
              }
              else
                    SEND_STRING(SS_RALT("/o"));
          };
          break;
        case KCAE:
          if( record->event.pressed)
          {
              if(keyboard_report->mods & (MOD_BIT(KC_LSFT)))
              {
                  /* clear_mods(); */
                  unregister_code(KC_LSFT);
                  SEND_STRING(SS_RALT("AE"));
                  register_code(KC_LSFT);
              }
              else
                    SEND_STRING(SS_RALT("ae"));
          };
          break;
	  case KCAA:
		if( record->event.pressed)
          {
              if(keyboard_report->mods & (MOD_BIT(KC_LSFT)))
              {
                  /* clear_mods(); */
                  unregister_code(KC_LSFT);
                  SEND_STRING(SS_RALT("oA"));
                  register_code(KC_LSFT);
              }
              else
                    SEND_STRING(SS_RALT("oa"));
          };
        break;
      }
   return true;
};
