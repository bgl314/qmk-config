#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/
//#define EE_HANDS

#define TAPPING_TERM 200
// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TOGGLE 4
#define COMBO_COUNT 27
// having trouble getting override to trigger caps word, below is working
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD