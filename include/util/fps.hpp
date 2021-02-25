#pragma once

namespace util {
    class FramesPerSecond {
    public:
        FramesPerSecond(double rate);
        /// Returns true when FPS is recalculated.
        bool update(double delta);
        double get() const;

    private:
        double fps;

        /// Time since FPS was last calculated.
        double time_since_calc;

        /// Number of times the update method has been called since FPS was last calculated.
        unsigned int updates_since_calc;

        /// Time that needs to pass before FPS will be recalculated.
        const double rate;
    };
}
