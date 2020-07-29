#pragma once

#include <functional>


namespace Bulk{
    template<typename return_t = void, typename...Args>
    class CommandWrapper{
    private:
        using funcSignature = std::function<return_t(Args...)>;
        funcSignature _func;
    public:
        CommandWrapper() = delete;
        CommandWrapper(const CommandWrapper&) = default;
        CommandWrapper(CommandWrapper&&) = default;
        CommandWrapper& operator=(const CommandWrapper&) = default;
        CommandWrapper& operator=(CommandWrapper&&) = default;
        ~CommandWrapper() = default;

        CommandWrapper(funcSignature func) : _func{func} {};
        return_t execute(Args&...args) {
            return _func(args...);
        }
    };
}