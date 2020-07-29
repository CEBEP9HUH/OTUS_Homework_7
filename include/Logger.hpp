#pragma once

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "IObserver.hpp"
#include "CommandPool.hpp"


namespace Bulk{
    namespace filesystem = std::experimental::filesystem;
    class Logger : public IObserver{
    private:
        using cmdList_t = CommandPool;
        using pool_ptr = std::shared_ptr<cmdList_t>;
        pool_ptr _cmdPool;
        bool _writeIntoFile;
        std::ostream& _console;
        std::ofstream _file;
        filesystem::path _logDir;
        void createNew();
        void close();
    public:
        Logger(pool_ptr cmdPool, bool writeIntoFile = false, std::ostream& out = std::cout);
        ~Logger();
        virtual void execute() override;
    };
}