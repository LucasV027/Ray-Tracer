#include "math.h"

namespace math
{
    double degrees_to_radians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

} // namespace math