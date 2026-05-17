#include "blinker_hal.h"
#include <stdlib.h>
#include <unistd.h>  // for usleep()

int main(int argc, char *argv[])
{
	//TODO: Initialize HAL layer
	init_HAL();

	while ( 1 )
	{
		usleep(1000);
		
		//TODO: Control LEDs with buttons
		uint8_t btn = read_btn();
        	set_led(btn);
	}

	return EXIT_SUCCESS;
}
