#include QMK_KEYBOARD_H

enum layers {
    _BSE, // Base
    _NUM, // Num
    _SYM, // Symbol
    _NAV, // Navigation
    _MSE, // Mouse
};

enum tap_dance_codes {
    LOCK_SCREEN_TD,
    COMMA_PLAY_TD,
};

enum custom_keycodes {
    BOOT_KEY = SAFE_RANGE,
};

// The key used to Enter the layer
#define ___E___ _______

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BSE] = LAYOUT_split_3x6_3(
        KC_AUDIO_VOL_UP,TD(LOCK_SCREEN_TD),KC_W,        KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,               KC_O,               KC_P,               KC_BSLS,
        KC_AUDIO_VOL_DOWN,LCTL_T(KC_A), LALT_T(KC_S),   LGUI_T(KC_D),   LSFT_T(KC_F),   KC_G,                                           KC_H,           RSFT_T(KC_J),   RGUI_T(KC_K),       RALT_T(KC_L),       RCTL_T(KC_SCLN),    KC_QUOT,
        LT(_BSE,BOOT_KEY),KC_Z,         KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           TD(COMMA_PLAY_TD),  KC_DOT,             KC_SLSH,            _______,
                                                        LT(_NUM, KC_TAB),LT(_NAV, KC_SPC),LT(_MSE, KC_NO),                              KC_BSPC,        KC_NO,          LT(_SYM, KC_DELETE)
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_PLUS,        KC_7,           KC_8,               KC_9,               KC_HASH,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_EQUAL,       KC_4,           KC_5,               KC_6,               KC_PERC,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_MINUS,       KC_1,           KC_2,               KC_3,               KC_KP_COMMA,        _______,
                                                        ___E___,        _______,        _______,                                        _______,        KC_DOT,         KC_0
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        _______,        KC_KP_ASTERISK, KC_AT,          KC_LCBR,        KC_RCBR,        KC_CIRC,                                        _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_EXLM,        KC_GRAVE,       KC_LPRN,        KC_RPRN,        KC_DLR,                                         _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_AMPR,        KC_PIPE,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT,                                 _______,        _______,        _______,            _______,            _______,            _______,
                                                        KC_UNDS,        _______,        _______,                                        _______,        _______,        ___E___
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        A(KC_LEFT),     G(A(KC_LEFT)),  G(A(KC_RIGHT)),     A(KC_RIGHT),        _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_LEFT,        KC_DOWN,        KC_UP,              KC_RIGHT,           _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        G(KC_LEFT),     G(C(KC_LEFT)),  G(C(KC_RIGHT)),     G(KC_RIGHT),        _______,            _______,
                                                        _______,        ___E___,        _______,                                        _______,        _______,        _______
    ),

    [_MSE] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        _______,        _______,        MS_UP,              _______,            _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        _______,        MS_LEFT,        MS_DOWN,            MS_RGHT,            _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        MS_WHLL,        MS_WHLD,        MS_WHLU,            MS_WHLR,            _______,            _______,
                                                        _______,        _______,        ___E___,                                        _______,        MS_BTN1,        MS_BTN2
    ),

};

// clang-format on

/************************/
/* COMBOS SECTION BEGIN */
/************************/

const uint16_t PROGMEM escape_combo[]    = {RSFT_T(KC_J), RGUI_T(KC_K), COMBO_END};
const uint16_t PROGMEM enter_combo[]     = {LSFT_T(KC_F), LGUI_T(KC_D), COMBO_END};
const uint16_t PROGMEM caps_word_combo[] = {LSFT_T(KC_F), RSFT_T(KC_J), COMBO_END};

combo_t key_combos[] = {
    COMBO(escape_combo, KC_ESC),
    COMBO(enter_combo, KC_ENTER),
    COMBO(caps_word_combo, QK_CAPS_WORD_TOGGLE),
};

/**********************/
/* COMBOS SECTION END */
/**********************/

/***************************/
/* TAP DANCE SECTION START */
/***************************/

tap_dance_action_t tap_dance_actions[] = {
    [LOCK_SCREEN_TD] = ACTION_TAP_DANCE_DOUBLE(KC_Q, C(G(KC_Q))),
    [COMMA_PLAY_TD]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MEDIA_PLAY_PAUSE),
};

/*************************/
/* TAP DANCE SECTION END */
/*************************/

/*********************/
/* RGB SECTION BEGIN */
/*********************/

#ifdef RGB_MATRIX_ENABLE

const uint8_t PROGMEM RGB_LAYER_COLORS[5][3] = {[_BSE] = {0x7d, 0xdc, 0xf8}, [_NUM] = {0xf6, 0x3b, 0x74}, [_SYM] = {0xe2, 0x31, 0xed}, [_NAV] = {0x12, 0xff, 0x12}, [_MSE] = {0xf9, 0x92, 0x1d}};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t red   = 0;
    uint8_t green = 0;
    uint8_t blue  = 0;

#    define SET_COLOR(layer)                \
        red   = RGB_LAYER_COLORS[layer][0]; \
        green = RGB_LAYER_COLORS[layer][1]; \
        blue  = RGB_LAYER_COLORS[layer][2];

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (!(index >= led_min && index <= led_max)) continue;
            if (index == NO_LED) continue;
            if (!(g_led_config.flags[index] & (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER))) continue;

            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (kc == KC_NO || kc == KC_TRNS) {
                rgb_matrix_set_color(index, RGB_OFF);
                continue;
                // } else if ((kc & QK_LAYER_TAP) && ((kc & QK_TAP_DANCE) != QK_TAP_DANCE)) {
            } else if (QK_LAYER_TAP_GET_LAYER(kc)) {
                SET_COLOR(QK_LAYER_TAP_GET_LAYER(kc));
            } else {
                SET_COLOR(layer);
            }
            rgb_matrix_set_color(index, red >> 1, green >> 1, blue >> 1);
        }
    }
    return false;
}
#endif

/*******************/
/* RGB SECTION END */
/*******************/

static bool is_holding_k_cmd  = false;
static bool is_in_command_tab = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGUI_T(KC_K):
            if (!record->tap.count) {
                if (record->event.pressed) {
                    is_holding_k_cmd = true;
                } else {
                    is_holding_k_cmd  = false;
                    is_in_command_tab = false;
                }
            }
            break;

        case LT(_NUM, KC_TAB):
            if (is_holding_k_cmd && record->tap.count && record->event.pressed) {
                is_in_command_tab = true;
            }
            break;

        case RSFT_T(KC_J):
            if (is_in_command_tab) {
                tap_code(KC_ESC);
                is_in_command_tab = false;
                return false;
            }
            break;

        case LT(_BSE, BOOT_KEY):
            if (!record->tap.count) {
                reset_keyboard();
            }
            return false;

        default:
            break;
    }
    return true;
}
