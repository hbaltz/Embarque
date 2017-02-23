#include <bcm2835.h>
#include <stdio.h>

// Input on RPi pin GPIO 37
#define PIN_IN RPI_V2_GPIO_P1_37
// Blinks on RPi Plug P1 pin 15 (which is GPIO pin 22)
#define PIN RPI_V2_GPIO_P1_22


void clignote(int pin, int dly){
   // Turn it on
    bcm2835_gpio_write(pin, HIGH);
    
    // wait a bit
    bcm2835_delay(dly);
    
    // turn it off
    bcm2835_gpio_write(pin, LOW);
    
    // wait a bit
    bcm2835_delay(dly);
}

int main(int argc, char **argv)
{
    if (!bcm2835_init()){
        return 1;
    }

    int prevValue = 0;
    int blink_status = 0;


    // Set RPI pin P1-37 to be an input
    bcm2835_gpio_fsel(PIN_IN, BCM2835_GPIO_FSEL_INPT);
    // And a low detect enable
    bcm2835_gpio_len(PIN_IN);
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    while (1){
    	uint8_t value = bcm2835_gpio_lev(PIN_IN);
        //printf("read from pin 37: %d\n", value);

        if(value != prevValue && prevValue == 0){ // Si l'état est différent de l'état précédent, on change le statue du button
            if(blink_status == 0) {
                blink_status = 1;
            }else {
                blink_status = 0;
            }                   
        }

        if(blink_status == 1){
           clignote(PIN,100); 
        }

        prevValue = value;

    }

    bcm2835_close();
    return 0;
}

