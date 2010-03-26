#ifndef _JOHN_H
#define _JOHN_H

#include <inttypes.h>

void
draw_initial_screen (void);

void
hide_bias (void);

void
hide_gear (void);

void
john_init (void);

void
show_bias (void);

void
show_gear (void);

void
update_bias (uint8_t bias);

void
update_gear (uint8_t gear);

#endif
