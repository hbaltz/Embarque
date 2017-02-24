#include <bcm2835.h>
#include <stdio.h>
#include <stdbool.h>

// Input on RPi pin GPIO 37
#define PIN_IN RPI_V2_GPIO_P1_37

void prendrePhoto(){
   printf("Yeah");
   system("raspistill -vf -hf -t 1 -o Capture.jpg");
}

int main(int argc, char **argv)
{
    if (!bcm2835_init()){
        return 1;
    }

    int prevValue = 0;
    bool cam_status = false;

    // Set RPI pin P1-37 to be an input
    bcm2835_gpio_fsel(PIN_IN, BCM2835_GPIO_FSEL_INPT);
    // And a low detect enable
    bcm2835_gpio_len(PIN_IN);
    
    while (1){
        uint8_t value = bcm2835_gpio_lev(PIN_IN);
        //printf("read from pin 37: %d\n", value);

        printf("%d \n",value);

        if(value != prevValue && prevValue == 1){ // Si l'état est différent de l'état précédent, on change le statue du button
            cam_status = !cam_status;               
        }

        if(cam_status){
           prendrePhoto(); 
           cam_status = false;
        }

        prevValue = value;

        // Attente
        bcm2835_delay(100);
    }

    bcm2835_close();
    return 0;
}
