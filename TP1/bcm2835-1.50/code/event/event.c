#include <bcm2835.h>
#include <stdio.h>

// Input on RPi pin GPIO 37
#define PIN RPI_V2_GPIO_P1_37

int main(int argc, char **argv)
{
    if (!bcm2835_init()){
        return 1;
    }
	

    // Set RPI pin P1-37 to be an input
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    // And a low detect enable
    bcm2835_gpio_len(PIN);

    while (1){
    	uint8_t value = bcm2835_gpio_lev(PIN);
        printf("read from pin 37: %d\n", value);
    }

    bcm2835_close();
    return 0;
}

