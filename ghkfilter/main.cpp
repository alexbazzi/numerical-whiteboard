#include "RadarFilter.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

double add_noise(double value, double noise_level) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-noise_level, noise_level);
    return value + dis(gen);
}

int main() {
    // Parameters for the filter
    double alpha = 0.3;
    double beta = 0.15;
    double gamma = 0.025;
    double delta_t = 1.0;

    // Instantiate filter
    RadarFilter radar_filter(alpha, beta, gamma, delta_t);

    // Simulate a series of position measurements
    std::vector<double> measurements(100);
    double initial_time = 0.0;
    double initial_position = 0.0;
    double initial_velocity = 100.0;
    double initial_acceleration = 9.8;
    double position = initial_position;

    double time = initial_time;
    double velocity = initial_velocity;
    double newpos = initial_position;
    std::cout << "(Position, Measurements, Time): ";
    for (double& measurement : measurements) {
        // Simulate 1-D kinematics 
        position = initial_position + time * initial_velocity + 0.5 * initial_acceleration * time * time; 
        std::cout  << "(" << position << ", ";
        measurement = add_noise(position, 1.0);
        std::cout  << measurement << ", ";
        time += delta_t;
        std::cout << time << "); ";
    }
    std::cout << std::endl;

    // Initialize filter with initial conditions
    radar_filter.initialize(measurements, initial_position, initial_velocity, initial_acceleration);

    // Run the filter
    radar_filter.runFilter();

    // Save data to a CSV file
    std::ofstream file("filter_data.csv");
    file << "true_position,measurement,position_prediction,velocity_prediction,acceleration_prediction,position_estimate,velocity_estimate,acceleration_estimate\n";
    for (size_t i = 0; i < measurements.size(); ++i) {
        file << radar_filter.true_positions_[i] << ","
             << radar_filter.measurements_[i] << ","
             << radar_filter.position_predictions_[i] << ","
             << radar_filter.velocity_predictions_[i] << ","
             << radar_filter.acceleration_predictions_[i] << ","
             << radar_filter.position_estimates_[i] << ","
             << radar_filter.velocity_estimates_[i] << ","
             << radar_filter.acceleration_estimates_[i] << "\n";
    }
    file.close();

    return 0;
}
