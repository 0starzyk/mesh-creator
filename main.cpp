#include "writeglTF.hpp"

int main()
{
    writeglTF("../input/data.json", "../input/model-template.gltf", "../output/buffer.bin", "../output/model.gltf");
}