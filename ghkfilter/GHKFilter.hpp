#ifndef GHK_FILTER_H
#define GHK_FILTER_H

#include <vector>

class GHKFilter {
public:
    GHKFilter(double alpha, double beta, double gamma, double delta_t);
    virtual ~GHKFilter();

    virtual void initialize(double initial_position, double initial_velocity, double initial_acceleration = 0);
    virtual void update(double measurement);
    virtual void extrapolate();

    double getPositionEstimate() const;
    double getVelocityEstimate() const;
    double getAccelerationEstimate() const;

protected:
    double alpha_;
    double beta_;
    double gamma_;
    double delta_t_;
    double position_estimate_;
    double velocity_estimate_;
    double acceleration_estimate_;

    double position_prediction_;
    double velocity_prediction_;
    double acceleration_prediction_;
};

#endif
