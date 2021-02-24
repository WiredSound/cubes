#include "fps.hpp"

FramesPerSecond::FramesPerSecond(double rate) : fps(0.0), time_since_calc(0.0), updates_since_calc(0), rate(rate) {}

bool FramesPerSecond::update(double delta) {
    updates_since_calc++;
    time_since_calc += delta;

    bool will_recalculate = time_since_calc >= rate;

    if(will_recalculate) {
        fps = static_cast<double>(updates_since_calc) / time_since_calc;

        updates_since_calc = 0;
        time_since_calc = 0.0;
    }

    return will_recalculate;
}

double FramesPerSecond::get() const {
    return fps;
}
