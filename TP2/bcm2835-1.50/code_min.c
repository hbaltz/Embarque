#include <bcm2835.h>
#include <stdio.h>

int main()
{
    if (!bcm2835_init()){
    	printf("Problème init lib");
    }      

  
    bcm2835_close();
    return 0;
}
