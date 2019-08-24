#pragma once

namespace core
{
class Core;

/**
 * @brief   Base class for all managers
 */
class Manager
{
public:
    explicit Manager(Core &core);

    virtual ~Manager() = default;

    /**
     * @brief   Initialize manager
     *
     * If manager was not initialized call onInit,
     * do nothing otherwise
     */
    void init();

    inline bool isInitialized() const;

protected:
    /**
     * @brief   Called during initialization
     */
    virtual void onInit();

    Core &getCore();

private:
    Core &m_core;

    bool m_isInitialized{false};
};


inline bool Manager::isInitialized() const
{
    return m_isInitialized;
}

}  // namespace core
