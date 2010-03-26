#include <string.h>
#include <avr/io.h>

#include "extmem.h"
#include "font.h"
#include "lcd.h"

#include "john.h"

void
draw_initial_screen (void)
{
}

void
hide_bias (void)
{
}

void
hide_gear (void)
{
}

void
john_init (void)
{
	DDRC |= _BV (PC7);
	PORTC |= _BV (PC7);

	DDRD |= _BV (PD7);
	PORTD &= ~_BV (PD7);

	extmem_init ();

	lcd_reset ();
	lcd_system_set (0x28,0x2c);
	lcd_init ();
	lcd_clear_screen ();

	font_init ();
}

void
show_bias (void)
{
}

void
show_gear (void)
{
}

void
update_bias (uint8_t bias)
{
}

void
update_gear (uint8_t gear)
{
}
