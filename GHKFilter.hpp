#include <iostream>
#include <vector>

class GHKFilter {
public:

    GHKFilter(double g, double h, double k)
        : _g{g}, _h{h}, _k{k} {}

    ~GHKFilter() {}
    
    virtual auto next_est(int index) -> const double {
        return 0.0;
    }
    virtual auto curr_est(int index) -> const double {
        return 0.0;
    }
    virtual auto extrapolate_state() -> const double {
        return 0.0;
    }
    virtual auto update_state() -> const double {
        return 0.0;
    }
    auto g() -> const double { return _g; }
    auto h() -> const double { return _h; }
    auto k() -> const double { return _k; }
    auto idx() -> const int { return _curr_idx; }
    auto meas(const int idx) -> const double { return _meas[idx]; }
    auto meas() -> const std::vector<double>& { return _meas; }
    static auto est(const int idx) -> const double { return _estimates[idx]; }

protected: 

    /// @brief Factors for the filter
    double _g, _h, _k;

    /// @brief Prediction of next state
    double _next_state;
    double _curr_state;

    /// @brief Holds the estimates for each time step (index)
    static std::vector<double> _estimates;

    /// @brief Current index
    int _curr_idx;

    /// @brief Current measurement
    std::vector<double> _meas;
};