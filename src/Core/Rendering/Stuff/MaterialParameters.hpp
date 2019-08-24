#pragma once

#include <tuple>

#include "../Shader.hpp"
#include "Core/Stuff/TypeString.hpp"

namespace core
{
class MaterialParametersBase
{
public:
    virtual ~MaterialParametersBase() = default;

    virtual void apply(Shader &shader) const = 0;
};

template <typename K, typename T>
struct Param
{
    using Key = K;
    using ValueType = T;

    explicit Param() = default;

    explicit Param(const K &, const T &v)
        : value{v}
    {
    }

    T value{};
    static constexpr auto key = K::data;
};

template <typename K, typename T>
Param(const K &, const T &)->Param<K, T>;

template <typename... Params>
class MaterialParameters : public MaterialParametersBase
{
public:
    explicit MaterialParameters() = default;

    explicit MaterialParameters(Params &&... args)
        : m_params{std::forward<Params>(args)...}
    {
    }

    void apply(Shader &shader) const override
    {
        using dummy = int[];
        static_cast<void>(dummy{(shader.setUniform(Params::key, std::get<Params>(m_params).value), 0)..., 0});
    }

    template <typename K, typename T>
    void set(const T &value)
    {
        static_assert((std::is_same_v<Param<K, T>, Params> || ...), "Material parameter key is not valid");
        std::get<Param<K, T>>(m_params).value = value;
    }

    template <typename K, typename T>
    void set(const K &, const T &value)
    {
        set<K>(value);
    }

private:
    std::tuple<Params...> m_params{};
};

}  // namespace core
