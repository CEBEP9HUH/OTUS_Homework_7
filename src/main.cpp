#include <iostream>
#include <memory>

#include "CommandReader.hpp"
#include "CommandHandler.hpp"
#include "CommandPool.hpp"
#include "Logger.hpp"


bool getBlockSize(int argc, char** argv, size_t& blockSize){
    if(argc < 2){
        std::cerr << argv[0] << " must be runned with 1 parameter\n";
        return false;
    }
    try{
        auto tmp = std::stod(argv[1]);
        if(tmp < 1 || tmp-int(tmp)>0){
            throw std::invalid_argument(argv[1]);
        }
        blockSize = static_cast<size_t>(tmp);
    }
    catch(std::invalid_argument& e){
        std::cerr << argv[0] << "'s parameter must be a non-negative integer value, but " << e.what() << " were given\n";
        return false;
    }
    return true;
}


int main(int argc, char** argv){
    size_t blockSize;
    if(!getBlockSize(argc, argv, blockSize)){
        return 1;
    }
    std::shared_ptr<Bulk::CommandPool> cmdPool{new Bulk::CommandPool()};
    std::unique_ptr<Bulk::Logger> logger{new Bulk::Logger(cmdPool, true)};
    std::unique_ptr<Bulk::CommandHandler> handler{new Bulk::CommandHandler(cmdPool)};
    Bulk::CommandReader reader(cmdPool, blockSize);
    handler->attach(logger.get());
    reader.attach(handler.get());
    reader.run();
    reader.detach(handler.get());
    handler->detach(logger.get());
    return 0;
}