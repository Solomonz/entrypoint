#include QMK_KEYBOARD_H
#include "transactions.h"

enum layers {
    _BSE, // Graphite (Base)
    _QWR, // QWERTY
    _NUM, // Num
    _SYM, // Symbol
    _NAV, // Navigation

    NUM_LAYERS
};

enum tap_dance_codes {
    COMMA_PLAY_TD,
};

enum custom_keycodes {
    BOOT_OR_SCREEN_LOCK = SAFE_RANGE,
    SHIFT_CW,
};

// The key used to Enter the layer
#define ___E___ _______

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BSE] = LAYOUT_split_3x6_3(
        KC_AUDIO_VOL_UP,KC_B,           KC_L,           KC_D,           KC_W,           KC_Z,                                           KC_QUOT,        KC_F,           KC_O,               KC_U,               KC_J,               KC_SCLN,
        KC_AUDIO_VOL_DOWN,LCTL_T(KC_N), LALT_T(KC_R),   LGUI_T(KC_T),   LSFT_T(KC_S),   KC_G,                                           KC_Y,           KC_H,           RGUI_T(KC_A),       RALT_T(KC_E),       RCTL_T(KC_I),       TD(COMMA_PLAY_TD),
        LT(_BSE,BOOT_OR_SCREEN_LOCK),KC_Q,KC_X,         KC_M,           KC_C,           KC_V,                                           KC_K,           KC_P,           KC_DOT,             KC_MINUS,           KC_SLSH,            KC_NO,
                                                        LT(_NUM, KC_ENTER),LT(_NAV, KC_SPC),KC_NO,                                      KC_BSPC,        SHIFT_CW,       LT(_SYM, KC_ESCAPE)
    ),

    [_QWR] = LAYOUT_split_3x6_3(
        _______,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,               KC_O,               KC_P,               KC_BSLS,
        _______,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,               KC_L,               KC_SCLN,            KC_QUOT,
        _______,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,           KC_DOT,             KC_SLSH,            TO(_BSE),
                                                        _______,        _______,        _______,                                        _______,        _______,        _______
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_PLUS,        KC_7,           KC_8,               KC_9,               KC_HASH,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_EQUAL,       KC_4,           KC_5,               KC_6,               KC_PERC,            KC_NO,
        _______,        _______,        _______,        _______,        _______,        _______,                                        KC_MINUS,       KC_1,           KC_2,               KC_3,               KC_COMMA,           KC_NO,
                                                        ___E___,        _______,        _______,                                        _______,        KC_DOT,         KC_0
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        _______,        KC_ASTR,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_CIRC,                                        _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_EXLM,        KC_GRAVE,       KC_LPRN,        KC_RPRN,        KC_DLR,                                         _______,        _______,        _______,            _______,            _______,            _______,
        _______,        KC_AMPR,        KC_PIPE,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT,                                 _______,        _______,        _______,            _______,            _______,            _______,
                                                        KC_UNDS,        _______,        _______,                                        _______,        _______,        ___E___
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        _______,        _______,        _______,        _______,        _______,        _______,                                        A(KC_LEFT),     G(A(KC_LEFT)),  G(A(KC_RIGHT)),     A(KC_RIGHT),        _______,            _______,
        _______,        KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_GUI,    KC_LEFT_SHIFT,  _______,                                        KC_LEFT,        KC_DOWN,        KC_UP,              KC_RIGHT,           _______,            _______,
        _______,        _______,        _______,        _______,        _______,        _______,                                        G(KC_LEFT),     G(C(KC_LEFT)),  G(C(KC_RIGHT)),     G(KC_RIGHT),        _______,            _______,
                                                        _______,        ___E___,        _______,                                        G(KC_GRAVE),    S(KC_TAB),      KC_TAB
    )

};

// clang-format on

/************************/
/* COMBOS SECTION BEGIN */
/************************/

enum combos {
    QWERTY_COMBO,

    NUM_COMBOS
};

const uint16_t PROGMEM qwerty_combo[]    = {KC_Q, LALT_T(KC_R), LGUI_T(KC_T), KC_W, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [QWERTY_COMBO] = COMBO(qwerty_combo, TO(_QWR)),
};
// clang-format on

/**********************/
/* COMBOS SECTION END */
/**********************/

/***************************/
/* TAP DANCE SECTION START */
/***************************/

tap_dance_action_t tap_dance_actions[] = {
    [COMMA_PLAY_TD] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_MEDIA_PLAY_PAUSE),
};

/*************************/
/* TAP DANCE SECTION END */
/*************************/

static bool     custom_shift_held = false;
static uint16_t shift_cw_timer = 0;
static bool     shift_cw_tap_pending = false;

/****************************/
/* CAPS WORD SECTION BEGIN */
/****************************/

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Let our shift key pass through without deactivating caps word
        case SHIFT_CW:
        case KC_LSFT:
        case KC_RSFT:
            return true;

        // Keycodes that continue Caps Word, with shift applied (inverted if shift held)
        case KC_A ... KC_Z:
        case KC_MINS:
            // Implement CAPS_WORD_INVERT_ON_SHIFT behavior:
            // Use our own tracking flag instead of get_mods() since we don't
            // register_mods() when caps word is active
            if (!custom_shift_held) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // If custom_shift_held is true, we don't add shift = lowercase
            return true;

        // Keycodes that continue Caps Word, without shifting
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word
    }
}

/**************************/
/* CAPS WORD SECTION END */
/**************************/

/******************************/
/* KEY OVERRIDE SECTION BEGIN */
/******************************/

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {&delete_key_override};

/****************************/
/* KEY OVERRIDE SECTION END */
/****************************/

/*********************/
/* RGB SECTION BEGIN */
/*********************/

#ifdef RGB_MATRIX_ENABLE

// 0..100. 100 means "no limiting" (except whatever QMK brightness is set to).
#    ifndef RGB_GLOBAL_BUDGET_PERCENT
#        define RGB_GLOBAL_BUDGET_PERCENT 50
#    endif

// clang-format off
const uint8_t PROGMEM RGB_LAYER_COLORS[NUM_LAYERS][3] = {
    [_BSE] = {0x7d, 0xdc, 0xf8},
    [_QWR] = {0xff, 0x00, 0x00},
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
                case QK_TO ... QK_TO_MAX:
                    set_layer_color(QK_TO_GET_LAYER(kc), &r, &g, &b);
                    break;
                case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
                    set_layer_color(QK_LAYER_TAP_TOGGLE_GET_LAYER(kc), &r, &g, &b);
                    break;
                case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
                    set_layer_color(QK_ONE_SHOT_LAYER_GET_LAYER(kc), &r, &g, &b);
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

/*******************************/
/* SPLIT SYNC SECTION BEGIN    */
/*******************************/

#define SYNC_CAPS_WORD_BIT  0x01
#define SYNC_SHIFT_HELD_BIT 0x02

static uint8_t synced_state = 0;

static void state_sync_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    synced_state = *(const uint8_t*)in_data;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(CAPS_WORD_SYNC, state_sync_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        uint8_t current = 0;
        if (is_caps_word_on()) current |= SYNC_CAPS_WORD_BIT;
        if (custom_shift_held) current |= SYNC_SHIFT_HELD_BIT;
        if (current != synced_state) {
            synced_state = current;
            transaction_rpc_send(CAPS_WORD_SYNC, sizeof(current), &current);
        }
    }
}

/*****************************/
/* SPLIT SYNC SECTION END    */
/*****************************/

/**********************/
/* OLED SECTION BEGIN */
/**********************/

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        char buf[6];

        // Build date
        buf[0] = __DATE__[0];
        buf[1] = __DATE__[1];
        buf[2] = __DATE__[2];
        buf[3] = __DATE__[4];
        buf[4] = __DATE__[5];
        buf[5] = '\0';
        oled_write_ln(buf, false);

        // Build time HH:MM
        buf[0] = __TIME__[0];
        buf[1] = __TIME__[1];
        buf[2] = __TIME__[2];
        buf[3] = __TIME__[3];
        buf[4] = __TIME__[4];
        buf[5] = '\0';
        oled_write_ln(buf, false);

        // Build time :SS
        buf[0] = ' ';
        buf[1] = ' ';
        buf[2] = __TIME__[5];
        buf[3] = __TIME__[6];
        buf[4] = __TIME__[7];
        buf[5] = '\0';
        oled_write_ln(buf, false);

        // Blank separator
        oled_write_ln_P(PSTR(""), false);

        // Uptime header
        oled_write_ln_P(PSTR("  UP"), false);

        // Uptime mm:ss
        uint32_t secs = timer_read32() / 1000;
        uint32_t mins = secs / 60;
        secs %= 60;
        if (mins > 99) {
            snprintf(buf, sizeof(buf), "C+:%2lu", (unsigned long)secs);
        } else {
            snprintf(buf, sizeof(buf), "%02lu:%02lu", (unsigned long)mins, (unsigned long)secs);
        }
        oled_write_ln(buf, false);
    } else {
        oled_write_P(PSTR("  "), false);
        switch (get_highest_layer(layer_state)) {
            case _BSE:
                oled_write_ln_P(PSTR("BSE"), false);
                break;
            case _QWR:
                oled_write_ln_P(PSTR("QWR"), false);
                break;
            case _NUM:
                oled_write_ln_P(PSTR("NUM"), false);
                break;
            case _SYM:
                oled_write_ln_P(PSTR("SYM"), false);
                break;
            case _NAV:
                oled_write_ln_P(PSTR("NAV"), false);
                break;
            default:
                oled_write_ln_P(PSTR("???"), false);
                break;
        }

        // Blank separator
        oled_write_ln_P(PSTR("     "), false);

        // Modifier state
        uint8_t mods = get_mods() | get_oneshot_mods();
        bool shift_active = (mods & MOD_MASK_SHIFT) || (synced_state & SYNC_SHIFT_HELD_BIT);
        oled_write_ln_P(shift_active            ? PSTR(" SHFT") : PSTR("     "), false);
        oled_write_ln_P(mods & MOD_MASK_GUI     ? PSTR("  GUI") : PSTR("     "), false);
        oled_write_ln_P(mods & MOD_MASK_ALT     ? PSTR("  ALT") : PSTR("     "), false);
        oled_write_ln_P(mods & MOD_MASK_CTRL    ? PSTR(" CTRL") : PSTR("     "), false);

        // Blank separator
        oled_write_ln_P(PSTR("     "), false);

        // Caps word state
        oled_write_ln_P((synced_state & SYNC_CAPS_WORD_BIT) ? PSTR("  C.W") : PSTR("     "), false);
    }

    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    if (bootloader) {
        oled_write_P(PSTR("BOOT"), false);
    } else {
        oled_write_P(PSTR("Rebooting "), false);
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);

    return false;
}

#endif

/********************/
/* OLED SECTION END */
/********************/

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_BSE, BOOT_OR_SCREEN_LOCK):
            if (!record->tap.count) {
                reset_keyboard();
            } else if (record->tap.count == 2) {
                tap_code16(C(G(KC_Q)));
            }
            return false;

        case SHIFT_CW:
            if (record->event.pressed) {
                custom_shift_held = true;
                if (shift_cw_tap_pending && timer_elapsed(shift_cw_timer) < TAPPING_TERM) {
                    // Double tap: toggle caps word
                    caps_word_toggle();
                    shift_cw_tap_pending = false;
                } else {
                    shift_cw_tap_pending = true;
                    shift_cw_timer = timer_read();
                    if (!is_caps_word_on()) {
                        register_mods(MOD_BIT(KC_LEFT_SHIFT));
                    }
                }
            } else {
                custom_shift_held = false;
                unregister_mods(MOD_BIT(KC_LEFT_SHIFT));
            }
            return false;

        default:
            break;
    }
    return true;
}
