#include <stdio.h>

#include <assert.h>
 
int Batterystate(float value, float min, float max, const char* message) {

    if (value < min || value > max) {

        printf("%s\n", message);

        return 1;

    }

    return 0;
}
 
int batterycondition(float temp, float stateofcharge, float percentageofcharge) {

    int tempcheck = Batterystate(temp, 15, 32, "Temperature out of range!");

    int soccheck = Batterystate(SOC, 0, 90, "StateofCharge out of range!");

    int chargeratecheck = Batterystate(percentageofcharge, 0, 0.6, "Charge Rate out of range!");
 
    return !(tempcheck || soccheck || chargeratecheck);

}
 
int main() {

    assert(batterycondition(15, 70, 0.6));

    assert(!batterycondition(50, 95, 0));

}
