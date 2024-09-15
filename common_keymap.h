#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include <stdio.h>
#include <string.h>
#endif 
#ifdef HAS_PASSWORDS
#include "passwords.h"
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
    _MOUSE,
    _SYMBOLS,
    _NUMBERS,
    _NAV,
    _ADJUST
#ifdef HAS_PASSWORDS
    ,_PWDS
#endif
    ,_ADJUST_ALT
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

#define SHT_LPRN MT(MOD_LSFT, KC_LPRN)
#define CTL_LCBR MT(MOD_LCTL, LSFT(KC_LCBR))
#define ALT_LBRC MT(MOD_LALT, KC_LBRC)

#define SHT_RPRN MT(MOD_RSFT, KC_RPRN)
#define CTL_RCBR MT(MOD_RCTL, RSFT(KC_RCBR))
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
    DBL_GT,
    //SCLN_RET
};

enum custom_keycodes{
   SCROLL=SAFE_RANGE,
   CPI_UP,
   CPI_DN,
   SCLN_RET,
#ifdef HAS_PASSWORDS
   PWD_S,
   PWD_L,
   PWD_D,
   PWD_G,
   PWD_N,
#endif
};


#ifdef COMBO_ENABLE
// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   c o m b o s                                 │
// └───────────────────────────────────────────────────────────┘
const uint16_t PROGMEM scln_ent_combo[] = {KC_Y, ALT_I, COMBO_END};
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
//const uint16_t PROGMEM rmb4_combo[] = {  KC_O, KC_SLSH, COMBO_END};
const uint16_t PROGMEM rtm4_combo[] = {  KC_O, KC_QUOT, COMBO_END};
const uint16_t PROGMEM lth_combo[] = {  MT(MOD_LCTL,KC_BSPC), LT(_NUMBERS, KC_TAB), COMBO_END};
// doubles 
const uint16_t PROGMEM pr_combo[] = { KC_H, SHT_N,  COMBO_END};
const uint16_t PROGMEM cbr_combo[] = { KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM br_combo[] = { KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM gt_combo[] = { KC_COMM, KC_DOT, COMBO_END};

// ┌───────────────────────────────────────────────────────────┐
// │ c o m b o s                                               │
// └───────────────────────────────────────────────────────────┘
combo_t key_combos[COMBO_COUNT] = {
    // these have to go first to match custom combos
    [DBL_PRN]=COMBO_ACTION(pr_combo),
    [DBL_BRC]=COMBO_ACTION(br_combo),
    [DBL_CBR]=COMBO_ACTION(cbr_combo),
    [DBL_GT]=COMBO_ACTION(gt_combo),
    //[SCLN_RET]=COMBO_ACTION(rmb4_combo),
    
    //COMBO(br_combo, DBL_BRC),
    //COMBO(cbr_combo, DBL_CBR),
    //COMBO(rmb4_combo, SCLN_RET),
    // ok order doesn't matter anymore
    COMBO(scln_ent_combo, SCLN_RET),
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
#endif


// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y   o v e r r i d e s         │
// └─────────────────────────────────────────────────┘


// const key_override_t sve_key_override = ko_make_basic(MOD_MASK_GUI, KC_S, C(KC_S));

// // This globally defines all key overrides to be used ├───────────┐
// const key_override_t **key_overrides = (const key_override_t *[]){
//   &sve_key_override,
//   NULL // Null terminate the array of overrides!
// };


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ B E H A V I O U R S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   t a p d a n c e                             │
// └───────────────────────────────────────────────────────────┘
// void scln_ent_sent_finished(tap_dance_state_t *state, void *user_data);
// void scln_ent_sent_reset(tap_dance_state_t *state, void *user_data);

enum tdkeys{
    DOT_ENT,
    TD_PAREN,
    TD_CBRC,
    TD_BKT,
    TD_GTLT

};
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;



// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

tap_dance_action_t tap_dance_actions[] = {
    [DOT_ENT]= ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),
    [TD_PAREN]= ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_CBRC]= ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_BKT]= ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_GTLT]= ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT)
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
static bool scrolling_mode = false;
static int curr_cpi=800;
static int curr_scroll_cpi = 30;

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);  // always required before the auto mouse feature will work
}

// call this from 
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//     #ifdef CONSOLE_ENABLE
//     uprintf("mouse col: %u, row: %u\n",mouse_report.h, mouse_report.v);
// #endif
    
    if (scrolling_mode) {
        // only vertical scrolling.
        mouse_report.h = 0;//mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
        
    return mouse_report;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
// layer_state_t layer_state_set_user(layer_state_t state) {
//     // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
//     if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
//         scrolling_mode=false;
//         pointing_device_set_cpi(curr_cpi);
//     }
//     return state;
// }

#endif


bool subScrollPressed=false;


// layer_state_t layer_state_set_kb(layer_state_t state) {
//      #ifdef POINTING_DEVICE_ENABLE
//      pointing_device_set_cpi(curr_cpi);
     
//      #endif
//      return state;
// }


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
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
    case KC_A:
        if (record->event.pressed) {
            subScrollPressed =true;
             pointing_device_set_cpi(curr_scroll_cpi);
        }else{
            subScrollPressed =false;
             pointing_device_set_cpi(curr_cpi);
           
        }
        return true;
    case SCROLL:
        if (record->event.pressed) {
            scrolling_mode = true;
            pointing_device_set_cpi(curr_scroll_cpi);
            
        } else {
            scrolling_mode = false;
            pointing_device_set_cpi(curr_cpi);
           
        }
        return false;
    case CPI_UP:
        if(!record->event.pressed){
            curr_cpi += 100;
            pointing_device_set_cpi(curr_cpi);       
           
        }
        return false;
    case CPI_DN:
        if(!record->event.pressed){
            curr_cpi -= 100;
            pointing_device_set_cpi(curr_cpi);
           
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
         
        }
        break;
    case SCLN_RET:
        if (record->event.pressed) {
            register_code(KC_SCLN);
            register_code(KC_ENT);
        } else {
            unregister_code(KC_SCLN);
            unregister_code(KC_ENT);
        }
        break;
    case KC_CAPS:
        if (record->event.pressed) {
          #ifdef HAPTIC_ENABLE
                  drv2605l_pulse(17);
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

#ifdef HAS_PASSWORDS
    case PWD_L:
        if(record->event.pressed){ 
            SEND_STRING(PWD_long);
        }
        break;
    case PWD_S:
        if(record->event.pressed){ 
            SEND_STRING(PWD_short);
        }
        break;
    case PWD_D:
        if(record->event.pressed){ 
            SEND_STRING(PWD_diorite);
        }
        break;
    case PWD_N:
        if(record->event.pressed){ 
            SEND_STRING(PWD_nyeeqamc);
        }
        break;
    case PWD_G:
        if(record->event.pressed){ 
            SEND_STRING(PWD_godfrebr);
        }
        break;
#endif
    default:
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
    
    case DBL_GT:
         if (pressed) {
            if(!(get_mods() & MOD_MASK_SHIFT))
                set_mods(MOD_MASK_SHIFT);
            register_code(KC_COMMA);
            register_code(KC_DOT);
            set_mods(mod_state);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_COMMA);
            unregister_code(KC_DOT);
            unregister_code(KC_LEFT);
        }
        break;
// ┌─────────────────────────────────────────────────┐
// │ c u s t o m  k e y c o d e s                    │
// └─────────────────────────────────────────────────┘
    // case SCLN_RET:
    //     if (pressed) {
    //         register_code(KC_SCLN);
    //         register_code(KC_ENT);
    //     } else {
    //         unregister_code(KC_SCLN);
    //         unregister_code(KC_ENT);
    //     }
    //     break;
  }
}
