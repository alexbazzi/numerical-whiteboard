#ifndef RADAR_FILTER_H
#define RADAR_FILTER_H

#include "GHKFilter.hpp"
#include <vector>

class RadarFilter : public GHKFilter {
public:
    RadarFilter(double alpha, double beta, double gamma, double delta_t);
    void initialize(const std::vector<double>& measurements, double initial_position, double initial_velocity, double initial_acceleration = 0);
    void runFilter();

    std::vector<double> position_estimates_;
    std::vector<double> velocity_estimates_;
    std::vector<double> acceleration_estimates_;

    std::vector<double> position_predictions_;
    std::vector<double> velocity_predictions_;
    std::vector<double> acceleration_predictions_;

    std::vector<double> true_positions_;
    std::vector<double> measurements_;
};

#endif
