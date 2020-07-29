#pragma once

#include <iostream>
#include <memory>

#include "IPublisher.hpp"
#include "CommandPool.hpp"


namespace Bulk{
    class CommandReader : public IPublisher{
    private:
        using cmdList_t = CommandPool;
        using pool_ptr = std::shared_ptr<cmdList_t>;
        pool_ptr _cmdPool;
        size_t _blockSize;
        std::istream& _in;
        void readDynamicBlock();
    public:
        CommandReader() = delete;
        CommandReader(const CommandReader&) = delete;
        CommandReader(CommandReader&&) = delete;
        CommandReader& operator=(const CommandReader&) = delete;
        CommandReader& operator=(CommandReader&&) = delete;

        CommandReader(pool_ptr cmdPool, const size_t blockSize, std::istream& in = std::cin);
        virtual ~CommandReader() = default;
        void run();
    };
}