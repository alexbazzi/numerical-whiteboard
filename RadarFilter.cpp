#include "GHKFilter.hpp"
#include <memory>
#include <numeric>

class RadarFilter : public GHKFilter {
public:
    RadarFilter(double g, double h, double k)
     : GHKFilter(g, h, k), delta_t{0.1}, vel{0.0} {
        _curr_idx = 0;
        _pos_est.resize(10, 0.0);
        _vel_est.resize(10, 0.0);
        _pos_pred.resize(10, 0.0);
        _vel_pred.resize(10, 0.0);
    }

    ~RadarFilter() = default;

    auto next_est(int index) -> const double override {
        return 0.0;
    }

    auto init(std::vector<double>& measurements, double init_vel, double init_pos) -> void {
        std::copy(measurements.begin(), measurements.end(), std::back_inserter(this->_meas));
        this->_pos_pred[0] = init_pos;
        this->_vel_pred[0] = init_vel;
    }

    auto curr_est_pos(int index) -> const double {
        this->_pos_est[index] = this->_pos_pred[index] - g() \
            * (this->_meas[index] - this->_pos_pred[index]);
        return this->_pos_est[index];
    }

    auto curr_est_vel(int index) -> const double {
        _vel_est[index] = _vel_pred[index] - g() * (1 / delta_t) \
            * (_meas[index] - _vel_pred[index]);
        return _vel_est[index];
    }

    auto extrapolate_state() -> const double override {
        _next_state = _curr_state + delta_t * vel;
        return _next_state;
    }

private:

    /// @brief Time increment in seconds
    double delta_t;

    /// @brief Velocity of aircraft
    double vel;

    std::vector<double> _pos_est;
    std::vector<double> _vel_est;
    std::vector<double> _pos_pred;
    std::vector<double> _vel_pred;
};

auto main() -> int {
    const std::unique_ptr<RadarFilter> fighter_jet = std::make_unique<RadarFilter>(0.1, 0.2, 0.3);
    std::vector<double> position_vec(10);
    std::iota(position_vec.begin(), position_vec.end(), 1.1);
    fighter_jet->init(position_vec, 10'000, 40);
    const std::unique_ptr<std::vector<double>> &result = std::make_unique<std::vector<double>>(fighter_jet->meas());
    std::vector<double> test(10, 2.3);
    for (const double& val : *result.get()) {
        std::cout << val << " ";
    } std::cout << std::endl;
    std::cout << fighter_jet->curr_est_pos(5) << std::endl;

    return 0;
}