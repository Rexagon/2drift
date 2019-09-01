#pragma once

#include <map>
#include <vector>

#include "Core/Rendering/Material.hpp"
#include "Core/Rendering/Mesh.hpp"
#include "ShaderParameters.hpp"

namespace core
{
/**
 * @brief   Rendering queue
 */
class RenderingQueue
{
public:
    struct Item
    {
        int8_t order = 0;
        Mesh *mesh = nullptr;
        Material *material = nullptr;
        std::unique_ptr<ShaderParameters> materialParameters{};
    };

    void push(uint8_t layer, Item &&item);

    void sort();

    void clear();

    const std::map<uint8_t, std::vector<Item>> &getLayers() const;

private:
    std::map<uint8_t, std::vector<Item>> m_layers{};
};

}  // namespace core
