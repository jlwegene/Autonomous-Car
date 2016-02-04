#include "mbed.h"
#include "HMC5883L.h"
#include "GPS.h"
#include "PID.h"
#include "map_calc.h"
#include "Driver.h"

Ticker system_tick;
void tick_handler();
DigitalOut tick_light(LED1);


Driver driver(D9,D10,D14,D15,PA_11,PA_12);

int main() {
    //baud(115200);
    printf("\a");
    system_tick.attach_us(tick_handler, 20000);
    driver.navigate();

}

void tick_handler(){
    static unsigned int ticks;
    ticks++;
    
    tick_light = !tick_light;
    driver._updateCompass = true;
    if(ticks % 20 == 0) driver._updateGPS = true;
    //if(ticks % 50 == 0) driver._updateLog = true;
}
