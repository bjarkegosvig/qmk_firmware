// Copyright 2026 Bjarke Gosvig Knudsen (@bjarkegosvig)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Port of the Kaleidoscope Model100 sketch. Danish letters are typed through
// the host's compose key (Right Alt; WinCompose on Windows).

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _COLEMAK,
    _GAME,
    _GAMEFCN,
    _FUNCTION,
    _ARROW,
    _LAYSEL,
    _NUMPAD,
};

enum custom_keycodes {
    BASE_QW = QK_USER,
    BASE_CM,
    BASE_GM,
    DK_AE,
    DK_OE,
    DK_AA,
};

enum tap_dances {
    CT_LCK,
    CT_CLN,
    CT_MNS,
    CT_CP,
    CT_WEZ,
};

tap_dance_action_t tap_dance_actions[] = {
    [CT_LCK] = ACTION_TAP_DANCE_DOUBLE(G(KC_L), C(A(KC_DEL))),
    [CT_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
    [CT_MNS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
    [CT_CP]  = ACTION_TAP_DANCE_DOUBLE(C(KC_INS), S(KC_INS)),
    [CT_WEZ] = ACTION_TAP_DANCE_DOUBLE(A(KC_L), C(S(KC_P))),
};

#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define LAUNCH  G(A(KC_SPC))

/* Windows window management */
#define WN_VDL  G(C(KC_LEFT))     // previous virtual desktop
#define WN_VDR  G(C(KC_RGHT))     // next virtual desktop
#define WN_MONL G(S(KC_LEFT))     // move window to left monitor
#define WN_MONR G(S(KC_RGHT))     // move window to right monitor
#define WN_VDML G(C(S(KC_LEFT)))  // move window to previous desktop
#define WN_VDMR G(C(S(KC_RGHT)))  // move window to next desktop
#define WN_SNPL G(KC_LEFT)        // snap window left
#define WN_SNPR G(KC_RGHT)        // snap window right
#define WN_MAX  G(KC_UP)
#define WN_MIN  G(KC_DOWN)
#define WN_GMX  G(S(KC_GRV))

/* WezTerm */
#define WZ_SPLV C(S(KC_ENT))      // split pane vertically
#define WZ_SPLH C(S(KC_EQL))      // split pane horizontally
#define WZ_ROTP C(A(KC_F))        // rotate/promote pane
#define WZ_NXTP C(S(KC_LBRC))     // next pane
#define WZ_PRVP C(S(KC_RBRC))     // previous pane
#define WZ_INCF C(KC_EQL)         // increase font size
#define WZ_DECF C(KC_MINS)        // decrease font size
#define WZ_RSTF C(KC_0)           // reset font size

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    KC_ESC,        KC_1,          KC_2,          KC_3,          KC_4,          KC_5,          KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          TG(_NUMPAD),
    KC_TAB,        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,          LAUNCH,        TD(CT_WEZ),    KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          KC_EQL,
    OS_LCTL,       KC_A,          KC_S,          KC_D,          KC_F,          KC_G,          KC_TAB,        KC_ESC,        KC_H,          KC_J,          KC_K,          KC_L,          KC_SCLN,       KC_QUOT,
    OS_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,          TD(CT_CLN),    KC_MINS,       KC_N,          KC_M,          KC_COMM,       KC_DOT,        KC_SLSH,       KC_MINS,
    OS_LCTL,       OS_LALT,
    KC_SPC,        KC_BSPC,
    KC_ENT,        OS_LSFT,
    KC_ESC,        KC_LGUI,
    MO(_FUNCTION), MO(_ARROW)
    ),
    [_COLEMAK] = LAYOUT(
    KC_ESC,        KC_1,          KC_2,          KC_3,          KC_4,          KC_5,          KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          OSL(_LAYSEL),
    KC_TAB,        KC_Q,          KC_W,          KC_F,          KC_P,          KC_B,          A(KC_P),       TD(CT_CP),     KC_J,          KC_L,          KC_U,          KC_Y,          KC_SCLN,       KC_EQL,
    OS_LCTL,       KC_A,          KC_R,          KC_S,          KC_T,          KC_G,          TD(CT_CLN),    TD(CT_MNS),    KC_M,          KC_N,          KC_E,          KC_I,          KC_O,          KC_QUOT,
    OS_LSFT,       KC_Z,          KC_X,          KC_C,          KC_D,          KC_V,          KC_ESC,        KC_DEL,        KC_K,          KC_H,          KC_COMM,       KC_DOT,        KC_SLSH,       KC_MINS,
    OS_LCTL,       OS_RCTL,
    KC_SPC,        KC_BSPC,
    KC_ENT,        OS_LSFT,
    OS_LSFT,       OS_LALT,
    MO(_FUNCTION), MO(_ARROW)
    ),
    [_GAME] = LAYOUT(
    KC_ESC,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,         KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         OSL(_LAYSEL),
    KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_N,         XXXXXXX,      XXXXXXX,      KC_HOME,      KC_UP,        KC_END,       KC_INS,       KC_PLUS,
    KC_LCTL,      KC_A,         KC_S,         KC_D,         KC_F,         KC_G,         KC_M,         KC_GT,        XXXXXXX,      KC_LEFT,      KC_DOWN,      KC_RGHT,      XXXXXXX,      XXXXXXX,
    KC_LSFT,      KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_ENT,       KC_PGDN,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_BSLS,      KC_PIPE,
    KC_LCTL,      XXXXXXX,
    KC_SPC,       XXXXXXX,
    KC_LSFT,      XXXXXXX,
    KC_LALT,      XXXXXXX,
    MO(_GAMEFCN), MO(_GAMEFCN)
    ),
    [_GAMEFCN] = LAYOUT(
    KC_NUM,        KC_F1,         KC_F2,         KC_F3,         KC_F4,         XXXXXXX,       KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,        OSL(_LAYSEL),
    KC_CAPS,       KC_P7,         KC_P8,         KC_P9,         KC_R,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
    KC_PGUP,       KC_P4,         KC_P5,         KC_P6,         KC_P0,         XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
    KC_PGDN,       KC_P1,         KC_P2,         KC_P3,         XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
    KC_LCTL,       OS_LALT,
    KC_SPC,        KC_BSPC,
    KC_LSFT,       OS_LSFT,
    KC_LALT,       KC_DEL,
    MO(_FUNCTION), MO(_ARROW)
    ),
    [_FUNCTION] = LAYOUT(
    KC_GRV,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,
    KC_PLUS,     KC_PIPE,     KC_LCBR,     KC_PERC,     KC_RCBR,     KC_AMPR,     _______,     _______,     KC_MUTE,     KC_HOME,     KC_UP,       KC_END,      KC_INS,      KC_PLUS,
    _______,     KC_HASH,     KC_LPRN,     KC_DLR,      KC_RPRN,     KC_ASTR,     KC_LT,       KC_GT,       KC_MPLY,     KC_LEFT,     KC_DOWN,     KC_RGHT,     _______,     TD(CT_LCK),
    _______,     KC_AT,       KC_LBRC,     KC_CIRC,     KC_RBRC,     KC_TILD,     KC_PGUP,     KC_PGDN,     KC_VOLD,     KC_VOLU,     KC_MPRV,     KC_MNXT,     KC_BSLS,     KC_PIPE,
    OS_LCTL,     _______,
    _______,     KC_DEL,
    _______,     _______,
    _______,     _______,
    _______,     MO(_LAYSEL)
    ),
    [_ARROW] = LAYOUT(
    _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     XXXXXXX,
    WZ_SPLH,     WZ_SPLV,     WZ_NXTP,     WZ_PRVP,     WZ_ROTP,     WZ_RSTF,     WZ_INCF,     RCTL(KC_F),  _______,     KC_HOME,     KC_UP,       KC_END,      _______,     XXXXXXX,
    _______,     WN_MONL,     WN_MONR,     WN_SNPL,     WN_SNPR,     WN_MAX,      WZ_DECF,     _______,     C(KC_RBRC),  KC_LEFT,     KC_DOWN,     KC_RGHT,     _______,     _______,
    _______,     WN_VDML,     WN_VDMR,     WN_VDL,      WN_VDR,      WN_MIN,      WN_GMX,      KC_GRV,      _______,     _______,     _______,     _______,     _______,     _______,
    _______,     _______,
    _______,     KC_DEL,
    _______,     _______,
    _______,     _______,
    MO(_LAYSEL), _______
    ),
    [_LAYSEL] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, BASE_QW, BASE_CM, BASE_GM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, DK_AE,   DK_OE,   DK_AA,   _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,
    _______, _______,
    _______, _______,
    _______, _______,
    _______, _______
    ),
    [_NUMPAD] = LAYOUT(
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_MINS,      TG(_NUMPAD),
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      OSL(_LAYSEL), KC_DOT,       KC_7,         KC_8,         KC_9,         KC_PLUS,      KC_LPRN,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_0,         KC_4,         KC_5,         KC_6,         KC_EQL,       KC_QUOT,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      KC_COMM,      KC_1,         KC_2,         KC_3,         KC_SLSH,      TG(_NUMPAD),
    _______,      _______,
    _______,      _______,
    _______,      _______,
    _______,      _______,
    _______,      _______
    ),
};
// clang-format on

static void set_base_layer(uint8_t layer) {
    default_layer_set((layer_state_t)1 << layer);
    layer_clear();
}

/* Compose sequences: æ = a e, ø = o /, å = o a; Æ = A E, Ø = O /, Å = o A. */
static void send_danish(uint16_t keycode) {
    static const uint16_t seq[][2][2] = {
        [DK_AE - DK_AE] = {{KC_A, KC_E}, {S(KC_A), S(KC_E)}},
        [DK_OE - DK_AE] = {{KC_O, KC_SLSH}, {S(KC_O), KC_SLSH}},
        [DK_AA - DK_AE] = {{KC_O, KC_A}, {KC_O, S(KC_A)}},
    };
    const uint8_t mods    = get_mods();
    const bool    shifted = (mods | get_oneshot_mods() | get_weak_mods()) & MOD_MASK_SHIFT;

    clear_oneshot_mods();
    del_mods(MOD_MASK_SHIFT);
    clear_weak_mods();
    send_keyboard_report();

    tap_code(KC_RALT);
    tap_code16(seq[keycode - DK_AE][shifted][0]);
    tap_code16(seq[keycode - DK_AE][shifted][1]);

    set_mods(mods);
    send_keyboard_report();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case KC_ESC:
            /* Esc cancels pending one-shot modifiers/layers instead of typing. */
            if (get_oneshot_mods() || get_oneshot_locked_mods() || is_oneshot_layer_active()) {
                clear_oneshot_mods();
                clear_oneshot_locked_mods();
                if (is_oneshot_layer_active()) {
                    layer_off(get_oneshot_layer());
                    reset_oneshot_layer();
                }
                return false;
            }
            return true;
        case BASE_QW:
            set_base_layer(_QWERTY);
            return false;
        case BASE_CM:
            set_base_layer(_COLEMAK);
            return false;
        case BASE_GM:
            set_base_layer(_GAME);
            return false;
        case DK_AE:
        case DK_OE:
        case DK_AA:
            send_danish(keycode);
            return false;
    }
    return true;
}

/* Per-layer colormap (palette indices by LED index) and pastel palette, from
 * the Kaleidoscope Colormap setup. */
static const uint8_t PROGMEM colormap[][RGB_MATRIX_LED_COUNT] = {
    [_QWERTY] = {
         0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    },
    [_COLEMAK] = {
         0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  8,  8,  5,  0,  0,  0,  0,  0,
    },
    [_GAME] = {
         0,  0,  0,  3,  0,  0,  8,  0,  0,  8,  8,  0,  0,  0,  8,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    },
    [_GAMEFCN] = {
         8,  8, 11,  5,  1,  5,  5,  5,  5,  5,  5,  1,  1,  5,  5,  5,
         0,  5,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,
         0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,
    },
    [_FUNCTION] = {
         0,  0,  5,  0,  7,  5,  5,  5,  3,  3,  3,  7,  7,  5,  5,  5,
         3,  3,  3,  7,  7,  5,  5,  5, 10,  9,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  4,  0,  0,  9, 10,  2,  2,  2,  7,  7,  6,  1,  2,
         2,  1,  1,  7,  7,  6,  1,  2,  5,  0,  6,  7,  7,  5, 12,  5,
    },
    [_ARROW] = {
         0,  0,  2,  0,  0,  2,  8,  0,  0,  8,  1,  0,  0,  1,  8,  5,
         5,  8, 10,  0,  0,  3,  0,  0,  2,  3,  3,  0,  0,  0,  0,  0,
         0,  0,  0,  4,  0,  0,  0,  0,  0, 11,  0,  0,  0,  6,  1,  0,
         0,  1,  1,  0,  0,  6,  1,  0,  0,  0,  0,  0, 12, 12,  0,  0,
    },
    [_LAYSEL] = {
         0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  2,  0,  0,  3,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,
         0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    },
    [_NUMPAD] = {
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  7,  0,  0,  2, 10,  2,  0,  0, 10, 10, 10,
        10, 10, 10,  0,  0, 10, 10, 10,  2,  2,  2,  2, 12,  2,  2, 12,
    },
};

static const rgb_t PROGMEM palette[] = {
    {  0,   0,   0}, // 0 black
    {150, 221, 243}, // 1 blue
    {155, 243, 150}, // 2 green
    {100, 245, 200}, // 3 cyan
    {230, 119, 107}, // 4 red
    {230, 128, 255}, // 5 magenta
    {255, 170, 200}, // 6 pink
    {242, 228, 110}, // 7 yellow
    {229, 119, 107}, // 8 peach
    {242, 242, 242}, // 9 white
    /* 10..15 unused (black) */
};

static void set_palette_color(uint8_t led, uint8_t index) {
    rgb_t c = {0, 0, 0};
    if (index < ARRAY_SIZE(palette)) {
        memcpy_P(&c, &palette[index], sizeof(c));
    }
    rgb_matrix_set_color(led, c.r, c.g, c.b);
}

static uint8_t osm_to_mod_mask(uint16_t keycode) {
    const uint8_t mods = QK_ONE_SHOT_MOD_GET_MODS(keycode);
    return (mods & 0x10) ? (mods & 0xF) << 4 : mods;
}

void keyboard_post_init_user(void) {
    /* The colormap is drawn as an indicator over the (otherwise unused)
     * base effect, so RGB Matrix must be on whatever EEPROM holds. */
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    for (uint8_t i = led_min; i < led_max; i++) {
        set_palette_color(i, pgm_read_byte(&colormap[layer][i]));
    }

    /* Approximates Kaleidoscope's ActiveModColor: pending one-shots, and held
     * modifier/one-shot/layer keys. */
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

    /* Num Lock and Caps Lock light their keys (top two on the left edge). */
    const led_t   host = host_keyboard_led_state();
    const uint8_t num  = g_led_config.matrix_co[0][7];
    const uint8_t caps = g_led_config.matrix_co[1][7];
    if (host.num_lock && num >= led_min && num < led_max) {
        rgb_matrix_set_color(num, 255, 0, 128);
    }
    if (host.caps_lock && caps >= led_min && caps < led_max) {
        rgb_matrix_set_color(caps, 255, 0, 128);
    }
    return false;
}
