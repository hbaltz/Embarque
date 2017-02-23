#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }

    bcm2835_spi_begin();

    int result;

    while(1){
        
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);      // The default
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
        bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_512); // The default
        bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
        bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
        
    
        char buf[] = { 0x01, 0x02 }; // Data to send
        bcm2835_spi_transfern(buf, sizeof(buf));
        // buf will now be filled with the data that was read from the slave
        result = (buf[1]<<6)|buf[0];
        //printf("Read from SPI: %d  %d  \n", buf[0], buf[1]);
        printf("Read from SPI: %d \n", result);

        bcm2835_delay(1000);
        
        
    }

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}