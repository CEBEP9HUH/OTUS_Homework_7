#include "CommandReader.hpp"

using namespace Bulk;


CommandReader::CommandReader(pool_ptr cmdPool, const size_t blockSize, std::istream& in) :  _cmdPool{cmdPool}, 
                                                                                            _blockSize{blockSize},
                                                                                            _in{in} {
    _cmdPool->reserve(_blockSize);
}

void CommandReader::readDynamicBlock(){
    notify();
    size_t braceCounter = 1;
    std::string cmd;
    while(std::getline(_in, cmd)){
        if(cmd == "{"){
            ++braceCounter;
            continue;
        }
        if(cmd == "}"){
            if(--braceCounter == 0){
                break;
            }
            continue;
        }
        _cmdPool->addCommand(cmd);
    }
    if(braceCounter == 0){
        notify();
    }
}


void CommandReader::run(){
    std::string cmd;
    size_t ind = 0;
    while(std::getline(_in, cmd)){
        if(cmd == "{"){
            readDynamicBlock();
            ind = 0;
            continue;
        }
        _cmdPool->addCommand(cmd);
        ind = (ind+1) % _blockSize;
        if(ind == 0){
            notify();
        }
    }
    if(ind != 0){
        notify();
    }
}