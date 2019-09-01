// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core/Rendering/Stuff/RenderingQueue.hpp"

#include <algorithm>

namespace core
{
void RenderingQueue::push(uint8_t layer, RenderingQueue::Item &&item)
{
    m_layers[layer].emplace_back(std::move(item));
}


void RenderingQueue::sort()
{
    for (auto &m_layer : m_layers)
    {
        auto &layer = m_layer.second;
        std::sort(layer.begin(), layer.end(), [](const Item &l, const Item &r) { return l.order < r.order; });
    }
}


void RenderingQueue::clear()
{
    for (auto &m_layer : m_layers)
    {
        auto &layer = m_layer.second;
        layer.clear();
    }
}


const std::map<uint8_t, std::vector<RenderingQueue::Item>> &RenderingQueue::getLayers() const
{
    return m_layers;
}


}  // namespace core
