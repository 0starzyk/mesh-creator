#include "writeglTF.hpp"
#include "utils.hpp"

#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <nlohmann/json.hpp>

using namespace nlohmann;

void writeglTF(const std::string &geometryDataFileName, const std::string &inputModelFileName, const std::string &outputModelFileName, const std::string &binaryFileName)
{
    std::ifstream inputFile;

    inputFile.open(geometryDataFileName);
    auto geometryData = json::parse(inputFile);
    inputFile.close();

    std::vector<uint16_t> indexes = geometryData["indexes"];
    std::vector<float> verticles = geometryData["verticles"];

    using namespace utils;

    inputFile.open(inputModelFileName);
    auto model = ordered_json::parse(inputFile);
    inputFile.close();

    size_t numberOfIndexesBytes{std::size(indexes) * sizeof(uint16_t)};
    size_t reminder{numberOfIndexesBytes % sizeof(float)};
    size_t numberOfPaddingBytes{reminder ? sizeof(float) - reminder : 0};
    size_t numberOfVerticlesBytes{std::size(verticles) * sizeof(float)};
    size_t sumOfBytes{numberOfIndexesBytes + numberOfPaddingBytes + numberOfVerticlesBytes};

    std::vector<char> buffer(sumOfBytes);
    std::memcpy(buffer.data(), indexes.data(), numberOfIndexesBytes);
    std::memset(buffer.data() + numberOfIndexesBytes, 0, numberOfPaddingBytes);
    std::memcpy(buffer.data() + numberOfIndexesBytes + numberOfPaddingBytes, verticles.data(), numberOfVerticlesBytes);

    enum class Mode
    {
        points,
        lines,
        line_loop,
        line_strip,
        triangles,
        triangle_strip,
        triangle_fan
    };

    model["meshes"][0]["primitives"][0]["mode"] = static_cast<int>(Mode::triangles);
    model["buffers"][0]["byteLength"] = sumOfBytes;
    model["bufferViews"][0]["byteLength"] = numberOfIndexesBytes;
    model["bufferViews"][1]["byteOffset"] = numberOfIndexesBytes + numberOfPaddingBytes;
    model["bufferViews"][1]["byteLength"] = numberOfVerticlesBytes;
    model["accessors"][0]["count"] = std::size(indexes);
    model["accessors"][0]["max"] = {*std::ranges::max_element(indexes)};
    model["accessors"][0]["min"] = {*std::ranges::min_element(indexes)};
    model["accessors"][1]["count"] = std::size(verticles) / 3;
    model["accessors"][1]["max"] = maxOfPositions(verticles);
    model["accessors"][1]["min"] = minOfPositions(verticles);

    std::ofstream outputFile(outputModelFileName);
    outputFile << model;
    outputFile.close();

    std::ofstream binaryFile(binaryFileName, std::ofstream::binary);
    binaryFile.write(buffer.data(), sumOfBytes);
    binaryFile.close();
}