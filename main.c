#include <avr/interrupt.h>
#include <avr/io.h>

#include "can.h"
#include "john.h"

static mob_config_t gear_mob, shift_mob, engine_ack_mob;
static mob_config_t bias_mob, bias_adjust_mob, bias_ack_mob;

static volatile uint8_t gear = 0;
static volatile uint8_t bias = 50;

//
// Bias Adjustment Knob
//

ISR (INT3_vect)
{
	if (PIND & _BV (PD2))
	{
		// + 1
	}
	else
	{
		// - 1
	}
}

//
// Upshift
//

ISR (INT6_vect)
{

}

//
// Downshift
//

ISR (INT7_vect)
{

}

void
gear_rx_callback (uint8_t mob_index, uint32_t id, packet_type_t type)
{
	uint8_t data;

	can_load_data (0, &data, 1);
	gear = data;

	update_gear (gear);
}

void
engine_ack_rx_callback (uint8_t mob_index, uint32_t id, packet_type_t type)
{
}

void
bias_rx_callback (uint8_t mob_index, uint32_t id, packet_type_t type)
{
	uint8_t data;

	can_load_data (3, &data, 1);
	bias = data;

	update_bias (bias);
}

void
bias_ack_rx_callback (uint8_t mob_index, uint32_t id, packet_type_t type)
{
}

void
io_init (void)
{
	//
	//	PD3,PD2: 	VDM encoder
	// 	PE6: 		Upshift
	//	PE7: 		Downshift
	//	PF1: 		Button1
	//

	DDRG |= _BV (PG3);
	PORTG |= _BV (PG3);

	PORTD |= _BV (PD2) | _BV (PD3);
	PORTE |= _BV (PE6) | _BV (PE7);
	PORTF |= _BV (PF1);

	EICRA |= _BV (ISC31);
	EICRB |= _BV (ISC70) | _BV (ISC61);
	EIMSK |= _BV (INT3) | _BV (INT6) | _BV (INT7);
}

void
mob_config (void)
{
	gear_mob.id = 0x10;
	gear_mob.id_type = id_standard;
	gear_mob.mask = 0x7ff;
	gear_mob.rx_callback_ptr = gear_rx_callback;
	gear_mob.tx_callback_ptr = 0;

	can_config_mob (0, &gear_mob);

	shift_mob.id = 0x11;
	shift_mob.id_type = id_standard;
	shift_mob.mask = 0x7ff;
	shift_mob.rx_callback_ptr = 0;
	shift_mob.tx_callback_ptr = 0;

	can_config_mob (1, &shift_mob);

	engine_ack_mob.id = 0x12;
	engine_ack_mob.id_type = id_standard;
	engine_ack_mob.mask = 0x7ff;
	engine_ack_mob.rx_callback_ptr = engine_ack_rx_callback;
	engine_ack_mob.tx_callback_ptr = 0;

	can_config_mob (2, &engine_ack_mob);

	bias_mob.id = 0x20;
	bias_mob.id_type = id_standard;
	bias_mob.mask = 0x7ff;
	bias_mob.rx_callback_ptr = bias_rx_callback;
	bias_mob.tx_callback_ptr = 0;

	can_config_mob (3, &bias_mob);

	bias_adjust_mob.id = 0x21;
	bias_adjust_mob.id_type = id_standard;
	bias_adjust_mob.mask = 0x7ff;
	bias_adjust_mob.rx_callback_ptr = 0;
	bias_adjust_mob.tx_callback_ptr = 0;

	can_config_mob (4, &bias_adjust_mob);

	bias_ack_mob.id = 0x22;
	bias_ack_mob.id_type = id_standard;
	bias_ack_mob.mask = 0x7ff;
	bias_ack_mob.rx_callback_ptr = bias_ack_rx_callback;
	bias_ack_mob.tx_callback_ptr = 0;

	can_config_mob (5, &bias_ack_mob);
}

int
main (void)
{
	io_init ();
	john_init ();
	draw_initial_screen ();

//	can_init (can_baud_100);
//	mob_config ();
//
//	sei ();
//
//	can_remote_request (0, 1);
//	can_remote_request (3, 1);

	while (1)
		;

	return 0;
}
