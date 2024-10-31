#include <stdio.h>
#include <assert.h>
typedef struct {
    int warningEnabled;  // 1 for enabled, 0 for disabled
    float min;
    float max;
    float warningTolerance;  // Tolerance value for warnings
} ParameterConfig;
void checkAndPrintWarning(float value, ParameterConfig config, const char* warningMessage) {
    if (config.warningEnabled) {
        // Check for warning conditions
        if (value < config.min + config.warningTolerance) {
            printf("Warning: Approaching discharge\n");
        } else if (value > config.max - config.warningTolerance) {
            printf("Warning: Approaching charge-peak\n");
        }
    }
}
int isParameterOutOfRange(float value, float min, float max, const char* message) {
    if (value < min || value > max) {
        printf("%s\n", message);
        return 1;
    }
    return 0;
}
int batteryIsOk(float temperature, float soc, float chargeRate, ParameterConfig tempConfig, ParameterConfig socConfig, ParameterConfig chargeRateConfig) {
    checkAndPrintWarning(temperature, tempConfig, "Temperature out of range!");
    checkAndPrintWarning(soc, socConfig, "State of Charge out of range!");
    checkAndPrintWarning(chargeRate, chargeRateConfig, "Charge Rate out of range!");
    int isTempOutOfRange = isParameterOutOfRange(temperature, tempConfig.min, tempConfig.max, "Temperature out of range!");
    int isSocOutOfRange = isParameterOutOfRange(soc, socConfig.min, socConfig.max, "State of Charge out of range!");
    int isChargeRateOutOfRange = isParameterOutOfRange(chargeRate, chargeRateConfig.min, chargeRateConfig.max, "Charge Rate out of range!");
    return !(isTempOutOfRange || isSocOutOfRange || isChargeRateOutOfRange);
}
int main() 
{
    ParameterConfig temperatureConfig = {1, 0, 45, 0}; // Warning enabled, no tolerance for temperature
    ParameterConfig socConfig = {1, 20, 80, 4};       // Warning enabled, 5% tolerance for SOC
    ParameterConfig chargeRateConfig = {1, 0, 0.8, 0}; // Warning enabled, no tolerance for charge rate
    assert(batteryIsOk(25, 70, 0.7, temperatureConfig, socConfig, chargeRateConfig));
    assert(!batteryIsOk(50, 85, 0, temperatureConfig, socConfig, chargeRateConfig));
    return 0;
}
 
 
