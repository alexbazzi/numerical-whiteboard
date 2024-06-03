#include "RadarFilter.hpp"
#include <iostream>

RadarFilter::RadarFilter(double alpha, double beta, double gamma, double delta_t)
    : GHKFilter(alpha, beta, gamma, delta_t) {}

void RadarFilter::initialize(const std::vector<double>& measurements, double initial_position, double initial_velocity, double initial_acceleration) {
    measurements_ = measurements;
    GHKFilter::initialize(initial_position, initial_velocity, initial_acceleration);
    true_positions_ = measurements;

    position_estimates_.clear();
    velocity_estimates_.clear();
    acceleration_estimates_.clear();
    position_predictions_.clear();
    velocity_predictions_.clear();
    acceleration_predictions_.clear();
}

void RadarFilter::runFilter() {
    for (const double& measurement : measurements_) {
        extrapolate();
        position_predictions_.push_back(position_prediction_);
        velocity_predictions_.push_back(velocity_prediction_);
        acceleration_predictions_.push_back(acceleration_prediction_);

        update(measurement);
        position_estimates_.push_back(getPositionEstimate());
        velocity_estimates_.push_back(getVelocityEstimate());
        acceleration_estimates_.push_back(getAccelerationEstimate());

        std::cout << "Position estimate: " << getPositionEstimate()
                  << ", Velocity estimate: " << getVelocityEstimate()
                  << ", Acceleration estimate: " << getAccelerationEstimate() << std::endl;
    }
}
