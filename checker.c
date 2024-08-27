#include <stdio.h>

#include <assert.h>
 
int isParameterOutOfRange(float value, float min, float max, const char* message) {

    if (value < min || value > max) {

        printf("%s\n", message);

        return 1;

    }

    return 0;

}
 
int batteryIsOk(float temperature, float soc, float chargeRate) {

    int isTempOutOfRange = isParameterOutOfRange(temperature, 0, 45, "Temperature out of range!");

    int isSocOutOfRange = isParameterOutOfRange(soc, 20, 80, "State of Charge out of range!");

    int isChargeRateOutOfRange = isParameterOutOfRange(chargeRate, 0, 0.8, "Charge Rate out of range!");
 
    return !(isTempOutOfRange || isSocOutOfRange || isChargeRateOutOfRange);

}
 
int main() {

    assert(batteryIsOk(25, 70, 0.7));

    assert(!batteryIsOk(50, 85, 0));

}
 
 
