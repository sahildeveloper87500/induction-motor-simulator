#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed random number generator
#include <cmath>    // For abs()

using namespace std;

// Threshold values for protection system
const float MAX_CURRENT = 10.0;          // Maximum current in Amperes
const float MAX_TEMPERATURE = 80.0;      // Maximum temperature in Celsius
const float VOLTAGE_IMBALANCE_THRESHOLD = 10.0; // Max allowable voltage difference in Volts

// Function prototypes
float generateCurrent();         // Function to simulate current reading
float generateTemperature();     // Function to simulate temperature reading
float generateVoltage(int phase); // Function to simulate voltage for each phase
void checkMotorStatus(float current, float temperature, float voltagePhase1, float voltagePhase2, float voltagePhase3);

int main() {
    // Seed the random number generator for simulation
    srand(time(0));
    
    // Simulate the system running
    while (true) {
        // Generate simulated sensor readings
        float current = generateCurrent();
        float temperature = generateTemperature();
        float voltagePhase1 = generateVoltage(1);
        float voltagePhase2 = generateVoltage(2);
        float voltagePhase3 = generateVoltage(3);

        // Check motor status based on the simulated readings
        checkMotorStatus(current, temperature, voltagePhase1, voltagePhase2, voltagePhase3);

        // Pause the simulation for a short duration (1 second)
        cout << "---------------------------------" << endl;
        cout << "Motor is running..." << endl;
        cout << "Current: " << current << " A, Temperature: " << temperature << " C" << endl;
        cout << "Voltages: Phase 1 = " << voltagePhase1 << " V, Phase 2 = " << voltagePhase2 << " V, Phase 3 = " << voltagePhase3 << " V" << endl;
        cout << "---------------------------------" << endl;

        // Simulate a 1-second delay
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}

// Function to simulate current reading
float generateCurrent() {
    // Randomly generate a current value between 5 and 15 Amperes
    return 5.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.0));
}

// Function to simulate temperature reading
float generateTemperature() {
    // Randomly generate a temperature value between 60 and 100 Celsius
    return 60.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 40.0));
}

// Function to simulate voltage reading for each phase
float generateVoltage(int phase) {
    // Randomly generate a voltage value between 200 and 240 Volts
    return 200.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 40.0));
}

// Function to check motor status and detect any fault conditions
void checkMotorStatus(float current, float temperature, float voltagePhase1, float voltagePhase2, float voltagePhase3) {
    // Check for overcurrent condition
    if (current > MAX_CURRENT) {
        cout << "Fault Detected: Overcurrent! Current: " << current << " A" << endl;
        cout << "Shutting down the motor..." << endl;
        exit(0);  // Simulate motor shutdown
    }

    // Check for overheating condition
    if (temperature > MAX_TEMPERATURE) {
        cout << "Fault Detected: Overheating! Temperature: " << temperature << " C" << endl;
        cout << "Shutting down the motor..." << endl;
        exit(0);  // Simulate motor shutdown
    }

    // Check for voltage imbalance
    float voltageDifference12 = abs(voltagePhase1 - voltagePhase2);
    float voltageDifference23 = abs(voltagePhase2 - voltagePhase3);
    float voltageDifference31 = abs(voltagePhase3 - voltagePhase1);

    if (voltageDifference12 > VOLTAGE_IMBALANCE_THRESHOLD ||
        voltageDifference23 > VOLTAGE_IMBALANCE_THRESHOLD ||
        voltageDifference31 > VOLTAGE_IMBALANCE_THRESHOLD) {
        cout << "Fault Detected: Voltage Imbalance!" << endl;
        cout << "Shutting down the motor..." << endl;
        exit(0);  // Simulate motor shutdown
    }
}
