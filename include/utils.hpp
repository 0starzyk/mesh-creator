#pragma once

#include <vector>
#include <array>

namespace utils
{
    static constexpr inline unsigned numberOfDimentions{3u};
    
    float maxOfPositions(std::vector<float> coordinates, unsigned position);
    std::array<float, numberOfDimentions> maxOfPositions(std::vector<float> coordinates);

    float minOfPositions(std::vector<float> coordinates, unsigned position);
    std::array<float, numberOfDimentions> minOfPositions(std::vector<float> coordinates);
}
