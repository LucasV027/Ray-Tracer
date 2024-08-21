#pragma once

#include <iostream>

#include "vec3.h"

using color = vec3;

namespace colors
{
    const color red = color(1.0f, 0.0f, 0.0f);
    const color green = color(0.0f, 1.0f, 0.0f);
    const color blue = color(0.0f, 0.0f, 1.0f);
    const color white = color(1.0f, 1.0f, 1.0f);
    const color black = color(0.0f, 0.0f, 0.0f);
    const color yellow = color(1.0f, 1.0f, 0.0f);
    const color cyan = color(0.0f, 1.0f, 1.0f);
    const color magenta = color(1.0f, 0.0f, 1.0f);
} // namespace colors
