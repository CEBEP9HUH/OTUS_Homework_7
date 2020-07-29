#pragma once

#include <memory>

#include "IObserver.hpp"
#include "IPublisher.hpp"
#include "CommandPool.hpp"


namespace Bulk{
    class CommandHandler : public IObserver, public IPublisher{
    private:
        using cmdList_t = CommandPool;
        using pool_ptr = std::shared_ptr<cmdList_t>;
        pool_ptr _cmdPool;
    public:
        CommandHandler() = delete;
        CommandHandler(const CommandHandler&) = delete;
        CommandHandler(CommandHandler&&) = delete;
        CommandHandler& operator=(const CommandHandler&) = delete;
        CommandHandler& operator=(CommandHandler&&) = delete;

        CommandHandler(pool_ptr cmdPool);
        virtual ~CommandHandler() = default;
        virtual void execute() override;
    };
}