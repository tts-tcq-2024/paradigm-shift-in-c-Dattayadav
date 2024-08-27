#include <stdio.h>

#include <assert.h>
 
int Batterystate(float value, float min, float max, const char* message) {

    if (value < min || value > max) {

        printf("%s\n", message);

        return 1;

    }

    return 0;

}
 
int batteryIsOk(float temperature, float soc, float chargeRate) {

    int Temp = Batterystate(temperature, 0, 35, "Temperature out of range!");

    int SocRange = Batterystate(soc, 20, 75, "State of Charge out of range!");

    int ChargeRate = Batterystate(chargeRate, 0, 0.8, "Charge Rate out of range!");
 
    return !(Temp || SocRange || ChargeRate);

}
 
int main() {

    assert(batteryIsOk(25, 70, 0.7));

    assert(!batteryIsOk(50, 85, 0));

}
 
