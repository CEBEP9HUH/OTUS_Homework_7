#include "CommandPool.hpp"

using namespace Bulk;

CommandPool::allCmdContainer_t CommandPool::_allCmdList{};


bool CommandPool::addCommand(const std::string& cmdName){
    /* 
        the _allCmdList insertion is shouldn't be here. 
        it should be filled from other place (main or smth).
        but for example with unknown commands list _allCmdList insertion were placed here
    */
    _allCmdList.emplace(cmdName, [](){return 0;});
    if(CommandPool::_allCmdList.count(cmdName) > 0){
        _commands.emplace_back(cmdName);
        return true;
    }
    return false;
}


CommandPool::iterator CommandPool::begin(){
    return iterator(_commands.begin());
}


CommandPool::iterator CommandPool::end(){
    return iterator(_commands.end());
}


void CommandPool::clear(){
    return _commands.clear();
}


void CommandPool::reserve(const size_t size){
    _commands.reserve(size);
}


bool CommandPool::empty(){
    return _commands.empty();
}