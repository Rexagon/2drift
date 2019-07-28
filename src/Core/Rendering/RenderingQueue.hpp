#pragma once

#include <map>

#include <SFML/Graphics/Drawable.hpp>

namespace core
{
class RenderingQueue
{
public:
    struct Item
    {
        int8_t order;
        sf::Drawable *drawable = nullptr;
        sf::RenderStates renderStates;
    };

    void push(uint8_t layer, Item &&item);

    void sort();

    void clear();

    const std::map<uint8_t, std::vector<Item>> &getLayers() const;

private:
    std::map<uint8_t, std::vector<Item>> m_layers;
};

}  // namespace core
