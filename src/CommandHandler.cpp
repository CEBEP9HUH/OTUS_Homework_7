#include "CommandHandler.hpp"

using namespace Bulk;


CommandHandler::CommandHandler(pool_ptr cmdPool) : _cmdPool{cmdPool}{

}


void CommandHandler::execute(){
    if(!_cmdPool->empty()){
        for(auto it = _cmdPool->begin(); it!=_cmdPool->end(); ++it){
            it->execute();
        }
        notify();
        _cmdPool->clear();
    }
}