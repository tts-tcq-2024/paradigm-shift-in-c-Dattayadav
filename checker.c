#include <stdio.h>
#include <assert.h>

typedef struct {
    int warningEnabled;         // 1 for enabled, 0 for disabled
    float min;
    float max;
    float warningTolerance;     // Tolerance value for warnings
} ParameterConfig;

void checkAndPrintWarning(float value, ParameterConfig config, const char* warningMessage) {
    if (!config.warningEnabled) return;  // Skip if warnings are disabled

    // Unified warning conditions
    if (value < config.min + config.warningTolerance) {
        printf("Warning: Approaching discharge\n");
    } 
    if (value > config.max - config.warningTolerance) {
        printf("Warning: Approaching charge-peak\n");
    }
}

int isParameterOutOfRange(float value, ParameterConfig config, const char* message) {
    if (value < config.min || value > config.max) {
        printf("%s\n", message);
        return 1;
    }
    return 0;
}

int batteryIsOk(float temperature, float soc, float chargeRate, ParameterConfig tempConfig, ParameterConfig socConfig, ParameterConfig chargeRateConfig) {
    float parameters[] = {temperature, soc, chargeRate};
    ParameterConfig configs[] = {tempConfig, socConfig, chargeRateConfig};
    const char* warnings[] = {"Temperature out of range!", "State of Charge out of range!", "Charge Rate out of range!"};
    
    for (int i = 0; i < 3; i++) {
        checkAndPrintWarning(parameters[i], configs[i], warnings[i]);
        if (isParameterOutOfRange(parameters[i], configs[i].min, configs[i].max, warnings[i])) {
            return 0;
        }
    }
    return 1;
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
 
 
