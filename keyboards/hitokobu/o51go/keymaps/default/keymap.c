#include QMK_KEYBOARD_H

// --- 物理的な位置を明示するためのエイリアス ---
#define P_TOP_RIGHT KC_GRV  // 一番右上の物理キー（レイヤー0の最右上）
#define P_BTM_RIGHT KC_RGHT // 一番右下の物理キー（レイヤー0の最右下）
// -------------------------------------------------------------

// カスタムキーコードの定義
enum custom_keycodes {
    // クリップボード操作（★グループの先頭にのみ SAFE_RANGE を指定）
    CMB_COPY = SAFE_RANGE, // I + A (コピー)
    CMB_PASTE,             // A + O (ペースト)
    CMB_CUT,               // I + O (切り取り)
    CMB_UNDO,              // Z + X (元に戻す)
    CMB_REDO,              // X + C (やり直し)
    CMB_ALL,               // I + A + O (すべて選択)

    // ウインドウ/アプリ管理
    CMB_CLOSE, // L + U (ウインドウを閉じる)
    CMB_QUIT,  // L + U + , (終了)

    // IME文字変換
    CMB_TN,  // T + N (Mac Ctrl+J / Win F6)
    CMB_NS,  // N + S (Mac Ctrl+K / Win F7)
    CMB_TNS, // T + N + S (Mac Ctrl+L / Win F8)
    CMB_TS,  // T + S (Mac Ctrl+; / Win F9)

    // その他
    CMB_P_GRV,  // P + ` (Delete)
    CMB_U_COMM, // U + , (Enter)
    CMB_RY,     // R + Y (Tab)
    CMB_WR,     // W + R (Shift+Tab)

    // Maccy 呼び出し
    CMB_MACCY_L, // U + O (Maccy呼び出し)
    CMB_MACCY_R, // R + T (Maccy呼び出し)

    // ハードリセット
    CMB_HARD_RESET, // 一番右上 + 一番右下 でリセット
};

// 同時押しするキーの組み合わせ（Chord）
const uint16_t PROGMEM combo_copy[]       = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM combo_paste[]      = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM combo_cut[]        = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_undo[]       = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_redo[]       = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_all[]        = {KC_I, KC_A, KC_O, COMBO_END};

const uint16_t PROGMEM combo_close[]      = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_quit[]       = {KC_L, KC_U, KC_COMM, COMBO_END};

const uint16_t PROGMEM combo_tn[]         = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM combo_ns[]         = {KC_N, KC_S, COMBO_END};
const uint16_t PROGMEM combo_tns[]        = {KC_T, KC_N, KC_S, COMBO_END};
const uint16_t PROGMEM combo_ts[]         = {KC_T, KC_S, COMBO_END};

const uint16_t PROGMEM combo_p_grv[]      = {KC_P, KC_GRV, COMBO_END};
const uint16_t PROGMEM combo_u_comm[]     = {KC_U, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_ry[]         = {KC_R, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_wr[]         = {KC_W, KC_R, COMBO_END};

const uint16_t PROGMEM combo_maccy_l[]    = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM combo_maccy_r[]    = {KC_R, KC_T, COMBO_END};

const uint16_t PROGMEM combo_hard_reset[] = {P_TOP_RIGHT, P_BTM_RIGHT, COMBO_END};

// コンボの登録
combo_t key_combos[] = {
    COMBO(combo_copy, CMB_COPY),
    COMBO(combo_paste, CMB_PASTE),
    COMBO(combo_cut, CMB_CUT),
    COMBO(combo_undo, CMB_UNDO),
    COMBO(combo_redo, CMB_REDO),
    COMBO(combo_all, CMB_ALL),

    COMBO(combo_close, CMB_CLOSE),
    COMBO(combo_quit, CMB_QUIT),

    COMBO(combo_tn, CMB_TN),
    COMBO(combo_ns, CMB_NS),
    COMBO(combo_tns, CMB_TNS),
    COMBO(combo_ts, CMB_TS),

    COMBO(combo_p_grv, CMB_P_GRV),
    COMBO(combo_u_comm, CMB_U_COMM),
    COMBO(combo_ry, CMB_RY),
    COMBO(combo_wr, CMB_WR),

    COMBO(combo_maccy_l, CMB_MACCY_L),
    COMBO(combo_maccy_r, CMB_MACCY_R),

    COMBO(combo_hard_reset, CMB_HARD_RESET),
};

// コンボ成立時の処理（process_record_user）
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 現在のレイヤーが 4, 5, 6, 7 のいずれか（Windows）なら true
    // bool is_windows = layer_state_is(4) || layer_state_is(5) || layer_state_is(6) || layer_state_is(7);
    bool is_windows = false; // Windows/Macのレイヤー分けはしていないため、常にMacとして扱う

    switch (keycode) {
        case CMB_COPY:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LCTL(KC_C));
                } else {
                    tap_code16(LGUI(KC_C));
                }
            }
            return false;

        case CMB_PASTE:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LCTL(KC_V));
                } else {
                    tap_code16(LGUI(KC_V));
                }
            }
            return false;

        case CMB_CUT:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LCTL(KC_X));
                } else {
                    tap_code16(LGUI(KC_X));
                }
            }
            return false;

        case CMB_UNDO:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LCTL(KC_Z));
                } else {
                    tap_code16(LGUI(KC_Z));
                }
            }
            return false;

        case CMB_REDO:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(S(LCTL(KC_Z)));
                } else {
                    tap_code16(S(LGUI(KC_Z)));
                }
            }
            return false;

        case CMB_ALL:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LCTL(KC_A));
                } else {
                    tap_code16(LGUI(KC_A));
                }
            }
            return false;

        case CMB_CLOSE:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LCTL(KC_W));
                } else {
                    tap_code16(LGUI(KC_W));
                }
            }
            return false;

        case CMB_QUIT:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LALT(KC_F4));
                } else {
                    tap_code16(LGUI(KC_Q));
                }
            }
            return false;

        case CMB_TN:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(KC_F6);
                } else {
                    tap_code16(LCTL(KC_J));
                }
            }
            return false;

        case CMB_NS:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(KC_F7);
                } else {
                    tap_code16(LCTL(KC_K));
                }
            }
            return false;

        case CMB_TNS:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(KC_F8);
                } else {
                    tap_code16(LCTL(KC_L));
                }
            }
            return false;

        case CMB_TS:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(KC_F9);
                } else {
                    tap_code16(LCTL(KC_SCLN));
                }
            }
            return false;

        case CMB_P_GRV:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
            }
            return false;

        case CMB_U_COMM:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
            }
            return false;

        case CMB_RY:
            if (record->event.pressed) {
                tap_code16(KC_TAB);
            }
            return false;

        case CMB_WR:
            if (record->event.pressed) {
                tap_code16(S(KC_TAB));
            }
            return false;

        case CMB_MACCY_L:
            if (record->event.pressed) {
                tap_code16(HYPR(KC_V));
            }
            return false;

        case CMB_MACCY_R:
            if (record->event.pressed) {
                tap_code16(HYPR(KC_V));
            }
            return false;

        case CMB_HARD_RESET:
            if (record->event.pressed) {
                reset_keyboard();
            }
            return false;

        case LT(1, KC_BSPC):
            if (get_highest_layer(layer_state) == 2) {
                if (record->tap.count > 0) {
                    if (record->event.pressed) {
                        // LALT + Backspace
                        tap_code16(LALT(KC_BSPC));
                    }
                    return false;
                }
            }
            break;

        case LT(2, KC_ENT):
            if (get_highest_layer(layer_state) == 1) {
                if (record->tap.count > 0) {
                    if (record->event.pressed) {
                        // LALT + Space
                        tap_code16(LALT(KC_SPC));
                    }
                    return false;
                }
            }
            break;

        case LSFT_T(KC_SPC):
            // Layer 0: 左 Alt キーが押されている場合、Alt を一時解除して Shift + Space を送信
            if (get_highest_layer(layer_state) == 0 && record->event.pressed && (get_mods() & MOD_BIT(KC_LALT))) {
                uint8_t mods_backup = get_mods();
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code16(S(KC_SPC));
                set_mods(mods_backup);
                return false;
            }
            // Layer 2 (Raise): タップで Shift + Space を送信
            if (get_highest_layer(layer_state) == 2 && record->tap.count > 0 && record->event.pressed) {
                tap_code16(S(KC_SPC));
                return false;
            }
            break;

        case LCTL_T(KC_SCLN):
            if (get_highest_layer(layer_state) == 2) {
                if (record->tap.count > 0) {
                    if (record->event.pressed) {
                        // Shift + Semicolon
                        tap_code16(S(KC_SCLN));
                    }
                    return false;
                }
            }
            break;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // L1 + L2 -> L3
    state = update_tri_layer_state(state, 1, 2, 3);
    return state;
}

// ====================================================================
// キーマップの定義
// ====================================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // base
    [0] = LAYOUT(
        QK_GESC, KC_Q, KC_L, KC_U, KC_COMM, KC_DOT, KC_VOLU, KC_F, KC_W, KC_R, KC_Y, KC_P, KC_GRV,
        LGUI_T(KC_TAB), KC_E, KC_I, KC_A, KC_O, KC_MINS, KC_MUTE, KC_K, KC_T, KC_N, KC_S, KC_H, KC_B,
        LALT_T(KC_BSLS), LCTL_T(KC_SCLN), KC_Z, KC_X, KC_C, KC_V, KC_VOLD, KC_G, KC_D, KC_M, KC_J, KC_UP, RALT_T(KC_SLSH),
        MO(4), KC_LCTL, KC_LALT, LGUI_T(KC_LNG2), LT(1, KC_BSPC), LSFT_T(KC_SPC), RSFT_T(KC_SPC), LT(2, KC_ENT), RGUI_T(KC_LNG1), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // lower
    [1] = LAYOUT(
        KC_TRNS, LSFT(KC_SCLN), KC_SLSH, KC_MINS, KC_TRNS, KC_TRNS, LGUI(KC_EQL), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F11,
        LGUI_T(KC_CAPS), KC_1, KC_2, KC_3, KC_4, KC_5, LGUI(KC_P0), KC_6, KC_7, KC_8, KC_9, KC_0, KC_F12,
        KC_TRNS, LCTL_T(KC_6), KC_7, KC_8, KC_9, KC_0, LGUI(KC_MINS), KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO
    ),
    // raise
    [2] = LAYOUT(
        LSFT(KC_GRV), LSFT(KC_6), LSFT(KC_5), LSFT(KC_4), LSFT(KC_COMM), LSFT(KC_DOT), KC_BRIU, LSFT(KC_LBRC), KC_LBRC, KC_UP, KC_RBRC, LSFT(KC_RBRC), LSFT(KC_GRV),
        KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_EQL), LSFT(KC_MINS), SGUI(KC_5), LSFT(KC_SCLN), KC_LEFT, KC_DOWN, KC_RGHT, KC_EQL, KC_SCLN,
        KC_TRNS, KC_TRNS, LSFT(KC_BSLS), LSFT(KC_8), LSFT(KC_7), LSFT(KC_SLSH), KC_BRID, LSFT(KC_COMM), LSFT(KC_9), KC_QUOT, LSFT(KC_0), LSFT(KC_DOT), LSFT(KC_SLSH),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO
    ),
    // adjust
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    // assist
    [4] = LAYOUT(
        LCTL(LGUI(KC_Q)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};
