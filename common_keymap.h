#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include <stdio.h>
#include <string.h>
#endif 
#ifdef OLED_ENABLE
    void oled_request_wakeup(void);
#endif

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                                      │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                                 │
// └───────────────────────────────────────────────────────────┘
enum layers {
    _COLEMAK,
    _GAMES,
    _GAMES_ALT,
    _REAPER,
    _MOUSE,
    _SYMBOLS,
    _NUMBERS,
    _NAV,
    _ADJUST
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   h o m e r o w   m o d s                     │
// └───────────────────────────────────────────────────────────┘
#define GUI_A MT(MOD_LGUI, KC_A)
#define SHT_T MT(MOD_LSFT, KC_T)
#define CTL_S MT(MOD_LCTL, KC_S)
#define ALT_R MT(MOD_LALT, KC_R)
#define SHT_N MT(MOD_LSFT, KC_N)
#define CTL_E MT(MOD_RCTL, KC_E)
#define ALT_I MT(MOD_RALT, KC_I)
#define GUI_O MT(MOD_RGUI, KC_O)

#define SHT_LPRN MT(MOD_LSFT, LSFT(KC_9))
#define CTL_LCBR MT(MOD_LCTL, LSFT(KC_LBRC))
#define ALT_LBRC MT(MOD_LALT, KC_LBRC)

#define SHT_RPRN MT(MOD_RSFT, RSFT(KC_0))
#define CTL_RCBR MT(MOD_RCTL, RSFT(KC_RBRC))
#define ALT_RBRC MT(MOD_RALT, KC_RBRC)

#define SHT_MPLY MT(MOD_RSFT, KC_MPLY)
#define CTL_MSTP MT(MOD_RCTL, KC_MSTP)
#define ALT_MPRV MT(MOD_RALT, KC_MPRV)

#define CTL_MPLY MT(MOD_RCTL, KC_MPLY)
#define GUI_MNXT MT(MOD_RGUI, KC_MNXT)

enum combos{
    DBL_PRN,
    DBL_BRC,
    DBL_CBR,
    DBL_GTLT,
    SCLN_RET
};

enum custom_keycodes{
   SCROLL=SAFE_RANGE,
   VSCROLL
};

enum tdkeys{
    DOT_ENT,
    Z_ENT,
    D_DELETE,
    P_SPACE,
    S_ALT_S,
    T_TAKE,
    SLASH_ENT,
    SCLN_ENT,
     // tap ent, hold shift, doubletap semicolon enter

     //DBL_GTLT
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   o v e r r i d e s                           │
// └───────────────────────────────────────────────────────────┘
const key_override_t cw_override = ko_make_basic(MOD_MASK_SHIFT, OSM(MOD_RSFT), QK_CAPS_WORD_TOGGLE);

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   c o m b o s                                 │
// └───────────────────────────────────────────────────────────┘
const uint16_t PROGMEM slash_nav_combo[] = {KC_SLSH, LT(_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM o_nav_combo[] = {KC_O, LT(_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM a_bksp_combo[] = {MT(MOD_LCTL,KC_BSPC), KC_A, COMBO_END};
const uint16_t PROGMEM rh_combo[] = {LT(_NAV,KC_SPC),OSM(MOD_RSFT), COMBO_END};

const uint16_t PROGMEM lmt4_combo[] = {  KC_A,KC_Q, COMBO_END};
const uint16_t PROGMEM lmt3_combo[] = {  ALT_R, KC_W, COMBO_END};
const uint16_t PROGMEM lmt2_combo[] = {  CTL_S, KC_F, COMBO_END};
const uint16_t PROGMEM lmt1_combo[] = {  SHT_T, KC_P, COMBO_END};
const uint16_t PROGMEM lmt0_combo[] = {  KC_D, KC_G, COMBO_END};
const uint16_t PROGMEM rmt0_combo[] = {  KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM rmt1_combo[] = {  SHT_N, KC_L, COMBO_END};
const uint16_t PROGMEM rmt2_combo[] = {  CTL_E, KC_U, COMBO_END};
const uint16_t PROGMEM rmt3_combo[] = {  ALT_I, KC_Y, COMBO_END};
const uint16_t PROGMEM rmt4_combo[] = {  KC_O, KC_QUOT, COMBO_END};


const uint16_t PROGMEM lmb4_combo[] = {  KC_A,KC_Z, COMBO_END};
const uint16_t PROGMEM lmb3_combo[] = {  ALT_R, KC_X, COMBO_END};
const uint16_t PROGMEM lmb2_combo[] = {  CTL_S, KC_C, COMBO_END};
const uint16_t PROGMEM lmb1_combo[] = {  SHT_T, KC_V, COMBO_END};
const uint16_t PROGMEM lmb0_combo[] = {  KC_D, KC_B, COMBO_END};
const uint16_t PROGMEM rmb0_combo[] = {  KC_H, KC_K, COMBO_END};
const uint16_t PROGMEM rmb1_combo[] = {  SHT_N, KC_M, COMBO_END};
const uint16_t PROGMEM rmb2_combo[] = {  CTL_E, KC_COMM, COMBO_END};
const uint16_t PROGMEM rmb3_combo[] = {  ALT_I, KC_DOT, COMBO_END};
const uint16_t PROGMEM rmb4_combo[] = {  KC_O, KC_SLSH, COMBO_END};
const uint16_t PROGMEM rtm4_combo[] = {  KC_O, KC_QUOT, COMBO_END};
const uint16_t PROGMEM lth_combo[] = {  MT(MOD_LCTL,KC_BSPC), LT(_NUMBERS, KC_TAB), COMBO_END};

// doubles
const uint16_t PROGMEM pr_combo[] = { KC_H, SHT_N, COMBO_END};
const uint16_t PROGMEM cbr_combo[] = { KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM br_combo[] = { KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM gt_combo[] = { SHT_N, CTL_E, COMBO_END};

// ┌───────────────────────────────────────────────────────────┐
// │ c o m b o s                                               │
// └───────────────────────────────────────────────────────────┘
combo_t key_combos[COMBO_COUNT] = {
    // these have to go first to match custom combos
    [DBL_PRN]=COMBO_ACTION(pr_combo),
    [DBL_BRC]=COMBO_ACTION(br_combo),
    [DBL_CBR]=COMBO_ACTION(cbr_combo),
    [DBL_GTLT]=COMBO_ACTION(gt_combo),
    [SCLN_RET]=COMBO_ACTION(rmb4_combo),
    
    //COMBO(br_combo, DBL_BRC),
    //COMBO(cbr_combo, DBL_CBR),
    //COMBO(rmb4_combo, SCLN_RET),
    // ok order doesn't matter anymore
    COMBO(slash_nav_combo, KC_ENT),
    COMBO(o_nav_combo, KC_ENT),
    COMBO(rh_combo, MO(_ADJUST)),
    COMBO(a_bksp_combo, KC_ENT),
    
    //COMBO(gt_combo, DBL_GTLT),
    // middle/bottom combos
    COMBO(lmb4_combo, KC_TILD),
    COMBO(lmb3_combo, KC_GRAVE),
    COMBO(lmb2_combo, KC_UNDS),
    COMBO(lmb1_combo, KC_MINUS),
    COMBO(lmb0_combo, KC_PLUS),
    COMBO(rmb0_combo, KC_PIPE),
    COMBO(rmb1_combo, KC_EQUAL),
    // COMBO(rmb2_combo, LSFT(KC_SEMICOLON)),
    // COMBO(rmb3_combo, KC_SEMICOLON),
     COMBO(rmb2_combo, RSFT(KC_SCLN)),
    COMBO(rmb3_combo, KC_SCLN),
    COMBO(rtm4_combo, KC_DQUO),
    // middle / top combos
    COMBO(lmt4_combo, KC_EXLM),
    COMBO(lmt3_combo, KC_AT),
    COMBO(lmt2_combo, KC_HASH),
    COMBO(lmt1_combo, KC_DLR),
    COMBO(lmt0_combo, KC_PERC),
    COMBO(rmt0_combo, KC_CIRC),
    COMBO(rmt1_combo, KC_AMPR),
    COMBO(rmt2_combo, KC_ASTR),
    COMBO(rtm4_combo, KC_DQUO),
    COMBO(lth_combo, KC_DEL),
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   t a p d a n c e                             │
// └───────────────────────────────────────────────────────────┘
void scln_ent_sent_finished(tap_dance_state_t *state, void *user_data);
void scln_ent_sent_reset(tap_dance_state_t *state, void *user_data);
tap_dance_action_t tap_dance_actions[] = {
    [DOT_ENT]= ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),
    [D_DELETE] = ACTION_TAP_DANCE_DOUBLE(KC_D, KC_DEL),
    [P_SPACE] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_SPACE),
    [S_ALT_S] = ACTION_TAP_DANCE_DOUBLE(KC_S, LALT(KC_S)),
    [T_TAKE] = ACTION_TAP_DANCE_DOUBLE(KC_T, LALT(LSFT(KC_T))),
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset)
};


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ B E H A V I O U R S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘
// ┌───────────────────────────────────────────────────────────┐
// │ t a p d a n c e                                           │
// └───────────────────────────────────────────────────────────┘
// SHIFT-ENTER-SEMICOLON/ENTER
// Handle the possible states for each tapdance keycode you define:
void scln_ent_sent_finished(tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_SCLN);
     }else {
        register_code16(KC_SCLN);
        register_code16(KC_ENT);
     }
}
void scln_ent_sent_reset(tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
         unregister_code16(KC_SCLN);
     }else {
            unregister_code16(KC_SCLN);
             unregister_code16(KC_ENT);
     }
}

// ┌───────────────────────────────────────────────────────────┐
// │ o v e r r i d e s                                         │
// └───────────────────────────────────────────────────────────┘
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &cw_override,
    NULL // Null terminate the array of overrides!
};

// ┌───────────────────────────────────────────────────────────┐
// │ c a p s w o r d                                           │
// └───────────────────────────────────────────────────────────┘
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}



// ┌───────────────────────────────────────────────────────────┐
// │ p e r - k e y  a c t i o n s                              │
// └───────────────────────────────────────────────────────────┘
uint8_t mod_state;
#ifdef POINTING_DEVICE_ENABLE
static bool vscrolling_mode = false;
static bool scrolling_mode = false;
#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    if(record->event.key.col!=0 ||record->event.key.row !=0)
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, time: %u,  count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.time, record->tap.count);
    #endif

    #ifdef OLED_ENABLE
        oled_request_wakeup();
    #endif
    mod_state = get_mods();
    switch (keycode) {
    #ifdef POINTING_DEVICE_ENABLE
// ┌─────────────────────────────────────────────────┐
// │ m o u s e   s c r o l l   l o c k               │
// └─────────────────────────────────────────────────┘
     case VSCROLL:
        if (record->event.pressed) {
            vscrolling_mode = true;
            pointing_device_set_cpi(50);
            #ifdef HAPTIC_ENABLE
            DRV_pulse(sharp_click);
            #endif // HAPTIC
        } else {
            vscrolling_mode = false;
            pointing_device_set_cpi(500);
            #ifdef HAPTIC_ENABLE
            DRV_pulse(sharp_click);
            #endif // HAPTIC
        }
        return false;
    case SCROLL:
        if (record->event.pressed) {
            scrolling_mode = true;
            pointing_device_set_cpi(50);
            #ifdef HAPTIC_ENABLE
            DRV_pulse(sharp_click);
            #endif // HAPTIC
        } else {
            scrolling_mode = false;
            pointing_device_set_cpi(500);
            #ifdef HAPTIC_ENABLE
            DRV_pulse(sharp_click);
            #endif // HAPTIC
        }
        return false;
    #endif
// ┌─────────────────────────────────────────────────┐
// │ m o d   m o r p h s                             │
// └─────────────────────────────────────────────────┘
    // case KC_COMMA:
    //      if ((get_mods() & MOD_MASK_SHIFT) ) {
    //         // shift is already pressed
    //         if (record->event.pressed) {
    //             register_code(KC_LT);
    //         } else {
    //             unregister_code(KC_LT);
    //         }
    //         // Do not let QMK process the keycode further
    //         return false;
    //      }
    //      break;
    // case KC_DOT:
    //      if ((get_mods() & MOD_MASK_SHIFT) ) {
    //         if (record->event.pressed) {
    //             //del_mods(MOD_MASK_SHIFT);
    //             register_code(KC_GT);
    //             //set_mods(mod_state);
    //         } else {
    //             unregister_code(KC_GT);
    //         }
    //         // Do not let QMK process the keycode further
    //         return false;
    //      }
    //      break;
// ┌─────────────────────────────────────────────────┐
// │ a u d i o / h a p t i c                         │
// └─────────────────────────────────────────────────┘
    case KC_MPLY:
        if (record->event.pressed) {
          #ifdef HAPTIC_ENABLE
                  DRV_pulse(sharp_click);
          #endif // HAPTIC_ENABLE
        }
        break;

    case KC_CAPS:
        if (record->event.pressed) {
          #ifdef HAPTIC_ENABLE
                  DRV_pulse(medium_click1);
          #endif // HAPTIC_ENABLE
          #ifdef AUDIO_ENABLE
              led_t led_usb_state = host_keyboard_led_state();
              if (led_usb_state.caps_lock) {
                  PLAY_SONG(capson_song);
              }
              else {
                  PLAY_SONG(capsoff_song);
              }
          #endif // AUDIO_ENABLE
        }
        break;

    }

    return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    mod_state = get_mods();
    switch(combo_index) {
// ┌─────────────────────────────────────────────────┐
// │ d o u b l e  s e p a r a t o r s                │
// └─────────────────────────────────────────────────┘
    case DBL_PRN:
        if (pressed) {
            if(!(get_mods() & MOD_MASK_SHIFT))
                set_mods(MOD_MASK_SHIFT);
            register_code(KC_9);
            register_code(KC_0);
            set_mods(mod_state);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_9);
            unregister_code(KC_0);
            unregister_code(KC_LEFT);
        }
        break;
    case DBL_BRC:
        if (pressed) {
            register_code(KC_LBRC);
            register_code(KC_RBRC);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_LBRC);
            unregister_code(KC_RBRC);
            unregister_code(KC_LEFT);
        }
        break;
    case DBL_CBR:
         if (pressed) {
            if(!(get_mods() & MOD_MASK_SHIFT))
                set_mods(MOD_MASK_SHIFT);
            register_code(KC_LBRC);
            register_code(KC_RBRC);
            set_mods(mod_state);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_LBRC);
            unregister_code(KC_RBRC);
            unregister_code(KC_LEFT);
        }
        break;
    // case DBL_GTLT:
    //      if (record->event.pressed) {
    //         if(!(get_mods() & MOD_MASK_SHIFT))
    //             set_mods(MOD_MASK_SHIFT);
    //         register_code(KC_COMMA);
    //         register_code(KC_DOT);
    //         set_mods(mod_state);
    //         register_code(KC_LEFT);
    //     } else {
    //         unregister_code(KC_COMMA);
    //         unregister_code(KC_DOT);
    //         unregister_code(KC_LEFT);
    //     }
    //     // Do not let QMK process the keycode further
    //     return false;
// ┌─────────────────────────────────────────────────┐
// │ c u s t o m  k e y c o d e s                    │
// └─────────────────────────────────────────────────┘
    case SCLN_RET:
        if (pressed) {
            register_code(KC_SCLN);
            register_code(KC_ENT);
        } else {
            unregister_code(KC_SCLN);
            unregister_code(KC_ENT);
        }
        break;
  }
}
