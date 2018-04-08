#ifndef CONFIG_BGK_H
#define CONFIG_BGK_H

#include QMK_KEYBOARD_CONFIG_H
#include "stdint.h"

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 2000

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 1000


#undef TAPPING_TERM
#define TAPPING_TERM 300

//overrides
#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2


extern uint8_t is_game;
extern uint8_t is_game2;

#endif
