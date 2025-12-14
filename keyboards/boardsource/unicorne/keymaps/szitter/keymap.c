#include QMK_KEYBOARD_H

enum layers {
    _BSE, // Base
    _NUM, // Num
    _SYM, // Symbol
    _NAV, // Navigation
    _MSE, // Mouse
    _SYS, // System Control
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BSE] = LAYOUT_split_3x6_3(
        C(G(KC_Q)),     KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,               KC_O,               KC_P,               KC_BSLS,
        _______,        LCTL_T(KC_A),   LALT_T(KC_S),   LGUI_T(KC_D),   LSFT_T(KC_F),   KC_G,                                           KC_H,           RSFT_T(KC_J),   RGUI_T(KC_K),       RALT_T(KC_L),       RCTL_T(KC_SCLN),    KC_QUOT,
        QK_BOOT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMM,            KC_DOT,             KC_SLSH,            _______,
                                                                        LT(_NUM, KC_TAB),LT(_NAV, KC_SPC),LT(_MSE, KC_NO),                               C(KC_BSPC),     KC_NO,          LT(_SYM, KC_DELETE)
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_PLUS,        KC_7,           KC_8,               KC_9,               KC_HASH,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_EQUAL,       KC_4,           KC_5,               KC_6,               KC_PERC,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_MINUS,       KC_1,           KC_2,               KC_3,               KC_KP_COMMA,        _______,
                                                                _______,                _______,    _______,                _______,                KC_DOT,                 KC_0
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        _______,        KC_KP_ASTERISK, KC_AT,          KC_LCBR,        KC_RCBR,        KC_CIRC,                                        _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_EXLM,        KC_GRAVE,       KC_LPRN,        KC_RPRN,        KC_DLR,                                         _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_AMPR,        KC_PIPE,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT,                                 _______,        _______,        _______,            _______,            _______,            _______,
                                                                    KC_UNDS,                    _______,                        _______,            _______,            _______,                 _______
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        A(KC_LEFT),     G(A(KC_LEFT)),  G(A(KC_RIGHT)),     A(KC_RIGHT),        _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_LEFT,        KC_DOWN,        KC_UP,              KC_RIGHT,           _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        G(KC_LEFT),     G(C(KC_LEFT)),  G(C(KC_RIGHT)),     G(KC_RIGHT),        _______,            _______,
                                                                    _______,                    _______,                        _______,            _______,            _______,                 _______
    ),

    [_MSE] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        _______,        _______,        MS_UP,              _______,            _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        _______,        MS_LEFT,        MS_DOWN,            MS_RGHT,            _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        MS_WHLL,        MS_WHLD,        MS_WHLU,            MS_WHLR,            _______,            _______,
                                                                    _______,                    _______,                        _______,            _______,            MS_BTN1,                 MS_BTN2
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
        case LT(_MSE, KC_TAB):
            if (is_holding_k_cmd && record->tap.count && record->event.pressed) {
                is_in_command_tab = true;
            }
            break;
        case KC_J:
            if (is_in_command_tab) {
                tap_code(KC_ESC);
                is_in_command_tab = false;
                return false;
            }
            break;
        case C(KC_BSPC):
            if (record->event.pressed && (get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_BSPC);
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}
