#include QMK_KEYBOARD_H

enum layers {
    _BSE,  // Base
    _GRPH, // Graphite
    _NUM,  // Num
    _SYM,  // Symbol
    _NAV,  // Navigation
    NUM_LAYERS
};

enum tap_dance_codes {
    COMMA_PLAY_TD,
    PERIOD_PLAY_TD,
};

enum custom_keycodes {
    BOOT_OR_SCREEN_LOCK = SAFE_RANGE,
};

// The key used to Enter the layer
#define ___E___ _______

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BSE] = LAYOUT_split_3x6_3(
        KC_AUDIO_VOL_UP,KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,               KC_O,               KC_P,               KC_BSLS,
        KC_AUDIO_VOL_DOWN,LCTL_T(KC_A), LALT_T(KC_S),   LGUI_T(KC_D),   LSFT_T(KC_F),   KC_G,                                           KC_H,           KC_J,           RGUI_T(KC_K),       RALT_T(KC_L),       RCTL_T(KC_SCLN),    KC_QUOT,
        LT(_BSE,BOOT_OR_SCREEN_LOCK),KC_Z,KC_X,         KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           TD(COMMA_PLAY_TD),  KC_DOT,             KC_SLSH,            PDF(_GRPH),
                                                        LT(_NUM, KC_TAB),LT(_NAV, KC_SPC),KC_NO,                                        KC_BSPC,        KC_LEFT_SHIFT,  LT(_SYM, KC_DELETE)
    ),

    [_GRPH] = LAYOUT_split_3x6_3(
        KC_AUDIO_VOL_UP,KC_B,           KC_L,           KC_D,           KC_W,           KC_Z,                                           KC_QUOT,        KC_F,           KC_O,               KC_U,               KC_J,               KC_SCLN,
        KC_AUDIO_VOL_DOWN,LCTL_T(KC_N), LALT_T(KC_R),   LGUI_T(KC_T),   LSFT_T(KC_S),   KC_G,                                           KC_Y,           KC_H,           RGUI_T(KC_A),       RALT_T(KC_E),       RCTL_T(KC_I),       KC_COMMA,
        LT(_GRPH,BOOT_OR_SCREEN_LOCK),KC_Q,KC_X,        KC_M,           KC_C,           KC_V,                                           KC_K,           KC_P,           TD(PERIOD_PLAY_TD), KC_MINUS,           KC_SLSH,            PDF(_BSE),
                                                        LT(_NUM, KC_TAB),LT(_NAV, KC_SPC),KC_NO,                                        KC_BSPC,        KC_LEFT_SHIFT,  LT(_SYM, KC_DELETE)
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_PLUS,        KC_7,           KC_8,               KC_9,               KC_HASH,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_EQUAL,       KC_4,           KC_5,               KC_6,               KC_PERC,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_MINUS,       KC_1,           KC_2,               KC_3,               KC_KP_COMMA,        KC_NO,
                                                        ___E___,        _______,        _______,                                        _______,        KC_DOT,         KC_0
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        _______,        KC_KP_ASTERISK, KC_AT,          KC_LCBR,        KC_RCBR,        KC_CIRC,                                        _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_EXLM,        KC_GRAVE,       KC_LPRN,        KC_RPRN,        KC_DLR,                                         _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_AMPR,        KC_PIPE,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT,                                 _______,        _______,        _______,            _______,            _______,            _______,
                                                        KC_UNDS,        _______,        _______,                                        _______,        _______,        ___E___
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        _______,        _______,        MS_WHLL,        MS_UP,          MS_WHLR,        MS_WHLU,                                        A(KC_LEFT),     G(A(KC_LEFT)),  G(A(KC_RIGHT)),     A(KC_RIGHT),        _______,            _______,
        _______,        _______,        MS_LEFT,        MS_DOWN,        MS_RGHT,        MS_WHLD,                                        KC_LEFT,        KC_DOWN,        KC_UP,              KC_RIGHT,           _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        G(KC_LEFT),     G(C(KC_LEFT)),  G(C(KC_RIGHT)),     G(KC_RIGHT),        _______,            KC_NO,
                                                        _______,        ___E___,        _______,                                        KC_NO,          MS_BTN1,        MS_BTN2
    )

};

// clang-format on

/************************/
/* COMBOS SECTION BEGIN */
/************************/

enum combos {
    BASE_ESCAPE_COMBO,
    BASE_ENTER_COMBO,
    BASE_CAPS_WORD_COMBO,
    GRAPHITE_ESCAPE_COMBO,
    GRAPHITE_ENTER_COMBO,
    GRAPHITE_CAPS_WORD_COMBO,

    NUM_COMBOS
};

const uint16_t PROGMEM base_escape_combo[]        = {KC_J, RGUI_T(KC_K), COMBO_END};
const uint16_t PROGMEM base_enter_combo[]         = {LSFT_T(KC_F), LGUI_T(KC_D), COMBO_END};
const uint16_t PROGMEM base_caps_word_combo[]     = {LSFT_T(KC_F), KC_J, COMBO_END};
const uint16_t PROGMEM graphite_escape_combo[]    = {KC_H, RGUI_T(KC_A), COMBO_END};
const uint16_t PROGMEM graphite_enter_combo[]     = {LSFT_T(KC_S), LGUI_T(KC_T), COMBO_END};
const uint16_t PROGMEM graphite_caps_word_combo[] = {LSFT_T(KC_S), KC_H, COMBO_END};

combo_t key_combos[] = {
    [BASE_ESCAPE_COMBO] = COMBO(base_escape_combo, KC_ESCAPE),
    [BASE_ENTER_COMBO] = COMBO(base_enter_combo, KC_ENTER),
    [BASE_CAPS_WORD_COMBO] = COMBO(base_caps_word_combo, QK_CAPS_WORD_TOGGLE),
    [GRAPHITE_ESCAPE_COMBO] = COMBO(graphite_escape_combo, KC_ESCAPE),
    [GRAPHITE_ENTER_COMBO] = COMBO(graphite_enter_combo, KC_ENTER),
    [GRAPHITE_CAPS_WORD_COMBO] = COMBO(graphite_caps_word_combo, QK_CAPS_WORD_TOGGLE),
};


bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    return combo_index == BASE_ENTER_COMBO || combo_index == GRAPHITE_ENTER_COMBO;
}

/**********************/
/* COMBOS SECTION END */
/**********************/

/***************************/
/* TAP DANCE SECTION START */
/***************************/

tap_dance_action_t tap_dance_actions[] = {
    [COMMA_PLAY_TD]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MEDIA_PLAY_PAUSE),
    [PERIOD_PLAY_TD] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_MEDIA_PLAY_PAUSE),
};

/*************************/
/* TAP DANCE SECTION END */
/*************************/

/*********************/
/* RGB SECTION BEGIN */
/*********************/

#ifdef RGB_MATRIX_ENABLE

// 0..100. 100 means "no limiting" (except whatever QMK brightness is set to).
#    ifndef RGB_GLOBAL_BUDGET_PERCENT
#        define RGB_GLOBAL_BUDGET_PERCENT 25
#    endif

// clang-format off
const uint8_t PROGMEM RGB_LAYER_COLORS[NUM_LAYERS][3] = {
    [_BSE] = {0x7d, 0xdc, 0xf8},
    [_GRPH] = {0xfa, 0xb6, 0x19},
    [_NUM] = {0xf6, 0x3b, 0x74},
    [_SYM] = {0xe2, 0x31, 0xed},
    [_NAV] = {0x12, 0xff, 0x12},
};
// clang-format on

typedef struct {
    uint8_t r, g, b;
    bool    used;
} led_rgb_t;

static inline uint8_t read_layer_color(uint8_t layer, uint8_t chan) {
    return pgm_read_byte(&RGB_LAYER_COLORS[layer][chan]);
}

static inline void set_layer_color(uint8_t layer, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = read_layer_color(layer, 0);
    *g = read_layer_color(layer, 1);
    *b = read_layer_color(layer, 2);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    // Buffer for this frame
    static led_rgb_t buf[RGB_MATRIX_LED_COUNT];

    // Clear "used" markers
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        buf[i].used = false;
    }

    // -------- Pass 1: decide intended colors and compute total intensity --------
    uint32_t sum        = 0;
    uint8_t  used_count = 0;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (!(index >= led_min && index <= led_max)) continue;

            uint8_t r = 0, g = 0, b = 0;

            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});

            switch (kc) {
                case KC_NO:
                case KC_TRNS:
                    rgb_matrix_set_color(index, RGB_OFF);
                    break;
                case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                    set_layer_color(QK_LAYER_TAP_GET_LAYER(kc), &r, &g, &b);
                    break;
                case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
                    set_layer_color(QK_LAYER_TAP_TOGGLE_GET_LAYER(kc), &r, &g, &b);
                    break;
                case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
                    set_layer_color(QK_ONE_SHOT_LAYER_GET_LAYER(kc), &r, &g, &b);
                    break;
                case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
                    set_layer_color(QK_DEF_LAYER_GET_LAYER(kc), &r, &g, &b);
                    break;
                case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
                    set_layer_color(QK_PERSISTENT_DEF_LAYER_GET_LAYER(kc), &r, &g, &b);
                    break;
                default:
                    set_layer_color(layer, &r, &g, &b);
                    break;
            }

            buf[index].r    = r;
            buf[index].g    = g;
            buf[index].b    = b;
            buf[index].used = true;

            sum += (uint32_t)r + g + b;
            used_count++;
        }
    }

    if (!(used_count && sum)) {
        return false;
    }

    // -------- Compute budget and scale (if needed) --------
    // Budget is relative to "all used LEDs at 255,255,255"
    const uint32_t max_sum_for_used = (uint32_t)used_count * 765u; // 255*3
    uint32_t       budget           = (max_sum_for_used * (uint32_t)RGB_GLOBAL_BUDGET_PERCENT) / 100u;

    // Safety: never let budget go to 0 unless percent is 0
    if (RGB_GLOBAL_BUDGET_PERCENT > 0 && budget == 0) budget = 1;

    uint32_t scale_q16 = (1u << 16); // 1.0
    if (RGB_GLOBAL_BUDGET_PERCENT < 100 && sum > budget) {
        scale_q16 = (budget << 16) / sum;
    }

    // -------- Pass 2: apply scale and push to LEDs --------
    for (uint8_t i = led_min; i <= led_max && i < RGB_MATRIX_LED_COUNT; i++) {
        // Ensure that we only set LEDs that we have already checked should be set
        if (!buf[i].used) continue;

        uint8_t r = (uint8_t)(((uint32_t)buf[i].r * scale_q16) >> 16);
        uint8_t g = (uint8_t)(((uint32_t)buf[i].g * scale_q16) >> 16);
        uint8_t b = (uint8_t)(((uint32_t)buf[i].b * scale_q16) >> 16);

        rgb_matrix_set_color(i, r, g, b);
    }

    return false;
}
#endif

/*******************/
/* RGB SECTION END */
/*******************/

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

static bool is_holding_right_cmd = false;
static bool is_in_command_tab    = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGUI_T(KC_K):
        case RGUI_T(KC_A):
            if (!record->tap.count) {
                if (record->event.pressed) {
                    is_holding_right_cmd = true;
                } else {
                    is_holding_right_cmd = false;
                    is_in_command_tab    = false;
                }
            }
            break;

        case LT(_NUM, KC_TAB):
            if (is_holding_right_cmd && record->tap.count && record->event.pressed) {
                is_in_command_tab = true;
            }
            break;

        case KC_J:
        case KC_H:
            if (is_in_command_tab) {
                tap_code(KC_ESC);
                is_in_command_tab = false;
                return false;
            }
            break;

        case LT(_BSE, BOOT_OR_SCREEN_LOCK):
        case LT(_GRPH, BOOT_OR_SCREEN_LOCK):
            if (!record->tap.count) {
                reset_keyboard();
            } else if (record->tap.count == 2) {
                tap_code16(C(G(KC_Q)));
            }
            return false;

        default:
            break;
    }
    return true;
}
