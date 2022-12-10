#include "writeglTF.hpp"

int main()
{
    writeglTF("../input/data.json", "../input/model.gltf", "../output/model.gltf", "../output/buffer.bin");
}