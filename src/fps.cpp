#include "fps.hpp"

FramesPerSecond::FramesPerSecond(double rate) : rate(rate), fps(0.0), time_since_calc(0.0), updates_since_calc(0) {}

bool FramesPerSecond::update(double delta) {
    updates_since_calc++;
    time_since_calc += delta;

    if(time_since_calc >= rate) {
        fps = static_cast<double>(updates_since_calc) / time_since_calc;

        updates_since_calc = 0;
        time_since_calc = 0.0;

        return true;
    }

    return false;
}

double FramesPerSecond::get() const {
    return fps;
}
