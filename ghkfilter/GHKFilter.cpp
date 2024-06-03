#include "GHKFilter.hpp"

GHKFilter::GHKFilter(double alpha, double beta, double gamma, double delta_t)
    : alpha_(alpha), beta_(beta), gamma_(gamma), delta_t_(delta_t),
      position_estimate_(0.0), velocity_estimate_(0.0), acceleration_estimate_(0.0),
      position_prediction_(0.0), velocity_prediction_(0.0) {}

GHKFilter::~GHKFilter() {}

void GHKFilter::initialize(double initial_position, double initial_velocity, double initial_acceleration) {
    position_estimate_ = initial_position;
    velocity_estimate_ = initial_velocity;
    acceleration_estimate_ = initial_acceleration;
    position_prediction_ = initial_position;
    velocity_prediction_ = initial_velocity;
    acceleration_prediction_ = initial_acceleration;
}

void GHKFilter::update(double measurement) {
    double position_residual = measurement - position_prediction_;
    position_estimate_ = position_prediction_ + alpha_ * position_residual;
    velocity_estimate_ = velocity_prediction_ + beta_ * position_residual / delta_t_;
    acceleration_estimate_ = acceleration_prediction_ + gamma_ * position_residual / (delta_t_ * delta_t_);
}

void GHKFilter::extrapolate() {
    position_prediction_ = position_estimate_ + delta_t_ * velocity_estimate_ + 0.5 * delta_t_ * delta_t_ * acceleration_estimate_;
    velocity_prediction_ = velocity_estimate_ + delta_t_ * acceleration_estimate_;
    acceleration_prediction_ = acceleration_estimate_;
}

double GHKFilter::getPositionEstimate() const {
    return position_estimate_;
}

double GHKFilter::getVelocityEstimate() const {
    return velocity_estimate_;
}

double GHKFilter::getAccelerationEstimate() const {
    return acceleration_estimate_;
}
