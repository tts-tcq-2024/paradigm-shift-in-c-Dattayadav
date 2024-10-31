#include <stdio.h>
#include <assert.h>

typedef struct {
    int warningEnabled;         // 1 for enabled, 0 for disabled
    float min;
    float max;
    float warningTolerance;     // Tolerance value for warnings
} ParameterConfig;

int checkParameter(float value, ParameterConfig config, const char* warningMessage) {
    // Check if value is out of range
    if (value < config.min) {
        printf("%s\n", warningMessage);
        return 1;
    } 
    if (value > config.max) {
        printf("%s\n", warningMessage);
        return 1;
    }
    
    // Print warning if close to threshold and warnings are enabled
    if (config.warningEnabled) {
        if (value < config.min + config.warningTolerance) {
            printf("Warning: Approaching discharge\n");
        }
        if (value > config.max - config.warningTolerance) {
            printf("Warning: Approaching charge-peak\n");
        }
    }
    return 0;
}

int batteryIsOk(float temperature, float soc, float chargeRate, ParameterConfig tempConfig, ParameterConfig socConfig, ParameterConfig chargeRateConfig) {
    // Check each parameter and accumulate any out-of-range conditions
    int isOutOfRange = 0;
    isOutOfRange |= checkParameter(temperature, tempConfig, "Temperature out of range!");
    isOutOfRange |= checkParameter(soc, socConfig, "State of Charge out of range!");
    isOutOfRange |= checkParameter(chargeRate, chargeRateConfig, "Charge Rate out of range!");

    return !isOutOfRange;  // Returns 1 if all parameters are within range, else 0
}

int main() {
    ParameterConfig temperatureConfig = {1, 0, 45, 0};  // Warning enabled, no tolerance for temperature
    ParameterConfig socConfig = {1, 20, 80, 4};         // Warning enabled, 4% tolerance for SOC
    ParameterConfig chargeRateConfig = {1, 0, 0.8, 0};  // Warning enabled, no tolerance for charge rate

    assert(batteryIsOk(25, 70, 0.7, temperatureConfig, socConfig, chargeRateConfig));
    assert(!batteryIsOk(50, 85, 0, temperatureConfig, socConfig, chargeRateConfig));

    return 0;
}
