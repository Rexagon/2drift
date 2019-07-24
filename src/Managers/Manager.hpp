#pragma once

namespace app
{
class Core;

class Manager
{
public:
    explicit Manager(Core &core);

    virtual ~Manager() = default;

    void init();

    inline bool isInitialized() const
    {
        return m_isInitialized;
    }

protected:
    virtual void onInit();

    Core &getCore();

private:
    Core &m_core;

    bool m_isInitialized;
};

}  // namespace app
