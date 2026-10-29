/* Copyright 2026 Bjarke Knudsen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#if __has_include("secrets.h")
#    include "secrets.h"
#endif

/* QMK gives higher layers priority, whereas Kaleidoscope uses activation
 * order. NUMPAD sits below the momentary layers and LAYSEL on top, so the
 * overlays behave as they did in Kaleidoscope. */
enum layers {
    QWERTY,
    COLEMAK,
    GAME,
    NUMPAD,
    GAMEFCN,
    FUNCTION,
    ARROW,
    LAYSEL,
};

enum custom_keycodes {
    VIM_PA = SAFE_RANGE, // vim: paste register a
    VIM_PB,              // vim: paste register b
    BASE_QW,             // switch base layer to QWERTY
    BASE_CM,             // switch base layer to Colemak
    BASE_GM,             // switch base layer to gaming
    DK_AE,               // æ/Æ via compose (Right Alt)
    DK_OE,               // ø/Ø via compose
    DK_AA,               // å/Å via compose
    PW_WIN,              // types SECRET_PW_WIN from secrets.h
    PW_LNX,              // types SECRET_PW_LINUX from secrets.h
};

enum tap_dances {
    CT_CLN, // : / ;
    CT_MNS, // - / _
    CT_CP,  // Windows console copy / paste
    CT_WEZ, // wezterm
    CT_LCK, // lock PC / ctrl+alt+del
};

tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
    [CT_MNS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
    [CT_CP]  = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_INS), LSFT(KC_INS)),
    [CT_WEZ] = ACTION_TAP_DANCE_DOUBLE(LALT(KC_L), LCTL(LSFT(KC_P))),
    [CT_LCK] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_L), LCTL(LALT(KC_DEL))),
};

#define LAUNCH   LGUI(LALT(KC_SPC))

#define WIN_WL   LGUI(LCTL(KC_LEFT))
#define WIN_WR   LGUI(LCTL(KC_RGHT))
#define WIN_XL   LGUI(LSFT(KC_LEFT))
#define WIN_XR   LGUI(LSFT(KC_RGHT))
#define WIN_WSL  LGUI(LCTL(LSFT(KC_LEFT)))
#define WIN_WSR  LGUI(LCTL(LSFT(KC_RGHT)))
#define WIN_MAX  LGUI(KC_LEFT)
#define WIN_MIN  LGUI(KC_RGHT)
#define WIN_MAXI LGUI(KC_UP)
#define WIN_MINI LGUI(KC_DOWN)
#define WIN_GMX  LGUI(LSFT(KC_GRV))

#define WEZ_SV   LCTL(LSFT(KC_ENT))  // split pane vertical
#define WEZ_SH   LCTL(LSFT(KC_EQL))  // split pane horizontal
#define WEZ_RP   LALT(LCTL(KC_F))    // rotate/promote pane
#define WEZ_NP   LSFT(LCTL(KC_LBRC)) // next pane
#define WEZ_PP   LSFT(LCTL(KC_RBRC)) // previous pane
#define WEZ_IF   LCTL(KC_EQL)        // increase font size
#define WEZ_DF   LCTL(KC_MINS)       // decrease font size
#define WEZ_RF   LCTL(KC_0)          // reset font size

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = LAYOUT(
  KC_ESC       , KC_1         , KC_2         , KC_3         , KC_4         , KC_5         ,                KC_6         , KC_7         , KC_8         , KC_9         , KC_0         , TG(NUMPAD),
  KC_TAB       , KC_Q         , KC_W         , KC_E         , KC_R         , KC_T         , LAUNCH       , TD(CT_WEZ)   , KC_Y         , KC_U         , KC_I         , KC_O         , KC_P         , KC_EQL,
  OSM(MOD_LCTL), KC_A         , KC_S         , KC_D         , KC_F         , KC_G         , KC_TAB       , VIM_PA       , KC_H         , KC_J         , KC_K         , KC_L         , KC_SCLN      , KC_QUOT,
  OSM(MOD_LSFT), KC_Z         , KC_X         , KC_C         , KC_V         , KC_B         , TD(CT_CLN)   , VIM_PB       , KC_N         , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH      , KC_MINS,
                                            OSM(MOD_LCTL),                                                                                            OSM(MOD_LALT),
                                               KC_SPC,                                                                                             KC_BSPC,
                                                  KC_ENT,                                                                                       OSM(MOD_LSFT),
                                                     KC_ESC,                                                                                 KC_LGUI,
                                    MO(FUNCTION),                                                                                                                         MO(ARROW)
),
[COLEMAK] = LAYOUT(
  KC_ESC       , KC_1         , KC_2         , KC_3         , KC_4         , KC_5         ,                KC_6         , KC_7         , KC_8         , KC_9         , KC_0         , OSL(LAYSEL),
  KC_TAB       , KC_Q         , KC_W         , KC_F         , KC_P         , KC_B         , LALT(KC_P)   , TD(CT_CP)    , KC_J         , KC_L         , KC_U         , KC_Y         , KC_SCLN      , KC_EQL,
  OSM(MOD_LCTL), KC_A         , KC_R         , KC_S         , KC_T         , KC_G         , TD(CT_CLN)   , TD(CT_MNS)   , KC_M         , KC_N         , KC_E         , KC_I         , KC_O         , KC_QUOT,
  OSM(MOD_LSFT), KC_Z         , KC_X         , KC_C         , KC_D         , KC_V         , KC_ESC       , KC_DEL       , KC_K         , KC_H         , KC_COMM      , KC_DOT       , KC_SLSH      , KC_MINS,
                                            OSM(MOD_LCTL),                                                                                            OSM(MOD_RCTL),
                                               KC_SPC,                                                                                             KC_BSPC,
                                                  KC_ENT,                                                                                       OSM(MOD_LSFT),
                                                     OSM(MOD_LSFT),                                                                          OSM(MOD_LALT),
                                    MO(FUNCTION),                                                                                                                         MO(ARROW)
),
[GAME] = LAYOUT(
  KC_ESC       , KC_1         , KC_2         , KC_3         , KC_4         , KC_5         ,                KC_6         , KC_7         , KC_8         , KC_9         , KC_0         , OSL(LAYSEL),
  KC_TAB       , KC_Q         , KC_W         , KC_E         , KC_R         , KC_T         , KC_N         , _______      , _______      , KC_HOME      , KC_UP        , KC_END       , KC_INS       , KC_PLUS,
  KC_LCTL      , KC_A         , KC_S         , KC_D         , KC_F         , KC_G         , KC_M         , KC_GT        , _______      , KC_LEFT      , KC_DOWN      , KC_RGHT      , _______      , _______,
  KC_LSFT      , KC_Z         , KC_X         , KC_C         , KC_V         , KC_B         , KC_ENT       , KC_PGDN      , _______      , _______      , _______      , _______      , KC_BSLS      , KC_PIPE,
                                            KC_LCTL,                                                                                                  _______,
                                               KC_SPC,                                                                                             _______,
                                                  KC_LSFT,                                                                                      _______,
                                                     KC_LALT,                                                                                _______,
                                    MO(GAMEFCN),                                                                                                                          MO(GAMEFCN)
),
[NUMPAD] = LAYOUT(
  _______      , _______      , _______      , _______      , _______      , _______      ,                _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , KC_MINS      , TG(NUMPAD),
  _______      , _______      , _______      , _______      , _______      , _______      , _______      , OSL(LAYSEL)  , KC_DOT       , KC_7         , KC_8         , KC_9         , KC_PLUS      , KC_LPRN,
  _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , KC_0         , KC_4         , KC_5         , KC_6         , KC_EQL       , KC_QUOT,
  _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , KC_COMM      , KC_1         , KC_2         , KC_3         , KC_SLSH      , TG(NUMPAD),
                                            _______,                                                                                                  _______,
                                               _______,                                                                                            _______,
                                                  _______,                                                                                      _______,
                                                     _______,                                                                                _______,
                                    _______,                                                                                                                              _______
),
[GAMEFCN] = LAYOUT(
  KC_NUM       , KC_F1        , KC_F2        , KC_F3        , KC_F4        , XXXXXXX      ,                KC_F6        , KC_F7        , KC_F8        , KC_F9        , KC_F10       , OSL(LAYSEL),
  KC_CAPS      , KC_P7        , KC_P8        , KC_P9        , KC_R         , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX,
  KC_PGUP      , KC_P4        , KC_P5        , KC_P6        , KC_P0        , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX,
  KC_PGDN      , KC_P1        , KC_P2        , KC_P3        , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX,
                                            KC_LCTL,                                                                                                  OSM(MOD_LALT),
                                               KC_SPC,                                                                                             KC_BSPC,
                                                  KC_LSFT,                                                                                      OSM(MOD_LSFT),
                                                     KC_LALT,                                                                                KC_DEL,
                                    MO(FUNCTION),                                                                                                                         MO(ARROW)
),
[FUNCTION] = LAYOUT(
  KC_GRV       , KC_F1        , KC_F2        , KC_F3        , KC_F4        , KC_F5        ,                KC_F6        , KC_F7        , KC_F8        , KC_F9        , KC_F10       , KC_F11,
  KC_PLUS      , KC_PIPE      , KC_LCBR      , KC_PERC      , KC_RCBR      , KC_AMPR      , _______      , _______      , KC_MUTE      , KC_HOME      , KC_UP        , KC_END       , KC_INS       , KC_PLUS,
  _______      , KC_HASH      , KC_LPRN      , KC_DLR       , KC_RPRN      , KC_ASTR      , KC_LT        , KC_GT        , KC_MPLY      , KC_LEFT      , KC_DOWN      , KC_RGHT      , _______      , TD(CT_LCK),
  _______      , KC_AT        , KC_LBRC      , KC_CIRC      , KC_RBRC      , KC_TILD      , KC_PGUP      , KC_PGDN      , KC_VOLD      , KC_VOLU      , KC_MPRV      , KC_MNXT      , KC_BSLS      , KC_PIPE,
                                            OSM(MOD_LCTL),                                                                                            _______,
                                               _______,                                                                                            KC_DEL,
                                                  _______,                                                                                      _______,
                                                     _______,                                                                                _______,
                                    _______,                                                                                                                              MO(LAYSEL)
),
[ARROW] = LAYOUT(
  _______      , _______      , _______      , _______      , _______      , _______      ,                _______      , _______      , _______      , _______      , _______      , PW_WIN,
  WEZ_SH       , WEZ_SV       , WEZ_NP       , WEZ_PP       , WEZ_RP       , WEZ_RF       , WEZ_IF       , RCTL(KC_F)   , _______      , KC_HOME      , KC_UP        , KC_END       , _______      , PW_LNX,
  _______      , WIN_XL       , WIN_XR       , WIN_MAX      , WIN_MIN      , WIN_MAXI     , WEZ_DF       , _______      , RCTL(KC_RBRC), KC_LEFT      , KC_DOWN      , KC_RGHT      , _______      , _______,
  _______      , WIN_WSL      , WIN_WSR      , WIN_WL       , WIN_WR       , WIN_MINI     , WIN_GMX      , KC_GRV       , _______      , _______      , _______      , _______      , _______      , _______,
                                            _______,                                                                                                  _______,
                                               _______,                                                                                            KC_DEL,
                                                  _______,                                                                                      _______,
                                                     _______,                                                                                _______,
                                    MO(LAYSEL),                                                                                                                           _______
),
[LAYSEL] = LAYOUT(
  _______      , _______      , _______      , _______      , _______      , _______      ,                _______      , _______      , _______      , _______      , _______      , _______,
  _______      , BASE_QW      , BASE_CM      , BASE_GM      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______,
  _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , DK_AE        , DK_OE        , DK_AA        , _______      , _______,
  _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______,
                                            _______,                                                                                                  _______,
                                               _______,                                                                                            _______,
                                                  _______,                                                                                      _______,
                                                     _______,                                                                                _______,
                                    _______,                                                                                                                              _______
)
};
// clang-format on

/* Port of the Kaleidoscope colormap (tools/colormap/colormap.txt with the bgk
 * palette): one palette index per LED, per layer. */
// clang-format off
/* Palette and colormaps from Model01-Firmware tools/colormap (bgk palette). */
static const rgb_t colormap_palette[] PROGMEM = {
    [ 0] = {.r =   0, .g =   0, .b =   0}, // Black
    [ 1] = {.r = 128, .g = 150, .b = 255}, // Blue
    [ 2] = {.r = 190, .g = 255, .b =  60}, // Green
    [ 3] = {.r = 100, .g = 245, .b = 200}, // Cyan
    [ 4] = {.r = 255, .g =  70, .b =  70}, // Red
    [ 5] = {.r = 230, .g = 128, .b = 255}, // Magenta
    [ 6] = {.r = 255, .g = 170, .b = 200}, // Pink
    [ 7] = {.r = 243, .g = 255, .b = 132}, // Yellow
    [ 8] = {.r = 255, .g = 216, .b = 128}, // Peach
    [ 9] = {.r = 255, .g = 255, .b = 255}, // white
    [10] = {.r =  30, .g = 187, .b = 215}, // bluish
    [11] = {.r =  30, .g = 215, .b = 151}, // greensih
    [12] = {.r = 255, .g =   0, .b = 128}, // pink
};

/* One palette index per LED, in LED index order (same as Kaleidoscope). */
static const uint8_t PROGMEM colormaps[][RGB_MATRIX_LED_COUNT] = {
    [QWERTY] = {
         0,  0,  0,  1,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
    },
    [COLEMAK] = {
         0,  0,  0,  2,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         8,  8,  5,  0,  0,  0,  0,  0,
    },
    [GAME] = {
         0,  0,  0,  3,  0,  0,  8,  0,
         0,  8,  8,  0,  0,  0,  8,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         5,  0,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  0,  0,  8,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
    },
    [GAMEFCN] = {
         8,  8, 11,  5,  1,  5,  5,  5,
         5,  5,  5,  1,  1,  5,  5,  5,
         0,  5,  0,  1,  1,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  1,  1,  0,  0,  0,
         0,  0,  0,  1,  1,  0,  0,  0,
         0,  0,  0,  1,  0,  0,  0,  0,
    },
    [FUNCTION] = {
         0,  0,  5,  0,  7,  5,  5,  5,
         3,  3,  3,  7,  7,  5,  5,  5,
         3,  3,  3,  7,  7,  5,  5,  5,
        10,  9,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  4,  0,  0,  9, 10,
         2,  2,  2,  7,  7,  6,  1,  2,
         2,  1,  1,  7,  7,  6,  1,  2,
         5,  0,  6,  7,  7,  5, 12,  5,
    },
    [ARROW] = {
         0,  0,  2,  0,  0,  2,  8,  0,
         0,  8,  1,  0,  0,  1,  8,  5,
         5,  8, 10,  0,  0,  3,  0,  0,
         2,  3,  3,  0,  0,  0,  0,  0,

         0,  0,  0,  4,  0,  0,  0,  0,
         0, 11,  0,  0,  0,  6,  1,  0,
         0,  1,  1,  0,  0,  6,  1,  0,
         0,  0,  0,  0, 12, 12,  0,  0,
    },
    [LAYSEL] = {
         0,  0,  0,  0,  0,  1,  0,  0,
         0,  0,  2,  0,  0,  3,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  1,  0,
         0,  1,  0,  0,  0,  0,  1,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
    },
    [NUMPAD] = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,

         0,  0,  0,  0,  0,  7,  0,  0,
         2, 10,  2,  0,  0, 10, 10, 10,
        10, 10, 10,  0,  0, 10, 10, 10,
         2,  2,  2,  2, 12,  2,  2, 12,
    },
};
// clang-format on

void keyboard_post_init_user(void) {
    /* The colormap is drawn as an indicator over the (otherwise unused)
     * base effect, so RGB Matrix must be on whatever EEPROM holds. */
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

static void set_base_layer(uint8_t layer) {
    layer_clear();
    default_layer_set((layer_state_t)1 << layer);
}

/* Types a Danish letter as a compose sequence. The host needs a compose key
 * on Right Alt (e.g. WinCompose on Windows). */
static void send_danish(uint16_t keycode) {
    const uint8_t mods    = get_mods();
    const bool    shifted = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;

    clear_oneshot_mods();
    del_mods(MOD_MASK_SHIFT);
    tap_code(KC_RALT);
    switch (keycode) {
        case DK_AE: // compose a e / a E
            tap_code(KC_A);
            tap_code16(shifted ? S(KC_E) : KC_E);
            break;
        case DK_OE: // compose o / / O /
            tap_code16(shifted ? S(KC_O) : KC_O);
            tap_code(KC_SLSH);
            break;
        case DK_AA: // compose o a / o A
            tap_code(KC_O);
            tap_code16(shifted ? S(KC_A) : KC_A);
            break;
    }
    set_mods(mods);
    send_keyboard_report();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case KC_ESC:
            /* Escape cancels pending one-shot modifiers and layers. */
            if (get_oneshot_mods() || is_oneshot_layer_active()) {
                clear_oneshot_mods();
                if (is_oneshot_layer_active()) {
                    layer_off(get_oneshot_layer());
                    reset_oneshot_layer();
                }
                return false;
            }
            return true;
        case VIM_PA:
            SEND_STRING("\"ap");
            break;
        case VIM_PB:
            SEND_STRING("\"bp");
            break;
        case BASE_QW:
            set_base_layer(QWERTY);
            break;
        case BASE_CM:
            set_base_layer(COLEMAK);
            break;
        case BASE_GM:
            set_base_layer(GAME);
            break;
        case DK_AE:
        case DK_OE:
        case DK_AA:
            send_danish(keycode);
            break;
#ifdef SECRET_PW_WIN
        case PW_WIN:
            SEND_STRING(SECRET_PW_WIN "\n");
            break;
#endif
#ifdef SECRET_PW_LINUX
        case PW_LNX:
            SEND_STRING(SECRET_PW_LINUX "\n");
            break;
#endif
    }

    /* Custom keycodes continue as KC_NO, so a pending one-shot layer
     * (e.g. LAYSEL) is released like after any other key. */
    return true;
}

static uint8_t osm_to_mod_mask(uint16_t keycode) {
    const uint8_t mods = QK_ONE_SHOT_MOD_GET_MODS(keycode);
    return (mods & 0x10) ? (mods & 0xF) << 4 : mods;
}

/* Draws the colormap of the highest active layer (like Kaleidoscope's
 * Colormap effect, palette colours as-is), then approximates Kaleidoscope's
 * ActiveModColor and the caps/num lock highlights from the sketch. */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    if (layer >= ARRAY_SIZE(colormaps)) {
        layer = 0;
    }
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_t color;
        memcpy_P(&color, &colormap_palette[pgm_read_byte(&colormaps[layer][i])], sizeof(color));
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }

    const uint8_t mods    = get_mods();
    const uint8_t os_mods = get_oneshot_mods();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led < led_min || led >= led_max) {
                continue;
            }

            const keypos_t pos = {.col = col, .row = row};
            const uint16_t kc  = keymap_key_to_keycode(layer_switch_get_layer(pos), pos);

            if (IS_QK_ONE_SHOT_MOD(kc) && (os_mods & osm_to_mod_mask(kc))) {
                rgb_matrix_set_color(led, 0xba, 0xff, 0xc9);
            } else if ((matrix_get_row(row) & ((matrix_row_t)1 << col)) && (IS_QK_ONE_SHOT_MOD(kc) || IS_QK_MOMENTARY(kc) || (IS_MODIFIER_KEYCODE(kc) && (mods & MOD_BIT(kc))))) {
                rgb_matrix_set_color(led, 0xff, 0xff, 0xba);
            }
        }
    }

    const led_t host_leds = host_keyboard_led_state();
    if (host_leds.caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[1][7], 255, 0, 128); // Tab
    }
    if (host_leds.num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[0][7], 255, 0, 128); // Esc
    }
    return false;
}
