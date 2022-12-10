#include "utils.hpp"

#include <array>

namespace utils
{
    float maxOfPositions(std::vector<float> coordinates, unsigned position)
    {
        float max{coordinates.at(position)};

        for (unsigned index{position}; index < std::size(coordinates); index += numberOfDimentions)
            if (coordinates.at(index) > max)
                max = coordinates.at(index);

        return max;
    }

    std::array<float, numberOfDimentions> maxOfPositions(std::vector<float> coordinates)
    {
        std::array<float, numberOfDimentions> maxArray;

        for (unsigned position{0u}; position < std::size(maxArray); ++position)
            for (unsigned index{position}; index < std::size(coordinates); index += numberOfDimentions)
                if (coordinates.at(index) > maxArray.at(position))
                    maxArray.at(position) = coordinates.at(index);

        return maxArray;
    }

    float minOfPositions(std::vector<float> coordinates, unsigned position)
    {
        float min{coordinates.at(position)};

        for (unsigned index{position}; index < std::size(coordinates); index += numberOfDimentions)
            if (coordinates.at(index) < min)
                min = coordinates.at(index);

        return min;
    }

    std::array<float, numberOfDimentions> minOfPositions(std::vector<float> coordinates)
    {
        std::array<float, numberOfDimentions> minArray;

        for (unsigned position{0u}; position < std::size(minArray); ++position)
            for (unsigned index{position}; index < std::size(coordinates); index += numberOfDimentions)
                if (coordinates.at(index) > minArray.at(position))
                    minArray.at(position) = coordinates.at(index);

        return minArray;
    }
}
