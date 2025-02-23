#pragma once

#include "vec3.h"

using color = vec3;

namespace colors {
    const auto red = color(1.0f, 0.0f, 0.0f);
    const auto green = color(0.0f, 1.0f, 0.0f);
    const auto blue = color(0.0f, 0.0f, 1.0f);
    const auto white = color(1.0f, 1.0f, 1.0f);
    const auto black = color(0.0f, 0.0f, 0.0f);
    const auto yellow = color(1.0f, 1.0f, 0.0f);
    const auto cyan = color(0.0f, 1.0f, 1.0f);
    const auto magenta = color(1.0f, 0.0f, 1.0f);
} // namespace colors
