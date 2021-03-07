#pragma once

namespace TriangleShader {
    const unsigned int POSITION = 0;
    const unsigned int POSITION_SIZE = 3;
    const unsigned int COLOR = 1;
    const unsigned int COLOR_SIZE = 3;
    const unsigned int COLOR_OFFSET = 3 * sizeof(float);
    const unsigned int STRIDE = 6 * sizeof(float);
}