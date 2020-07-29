#include <chrono>

#include "Logger.hpp"

using namespace Bulk;


Logger::Logger(pool_ptr cmdPool, bool writeIntoFile, std::ostream& out) :   _cmdPool{cmdPool}, 
                                                                            _writeIntoFile{writeIntoFile}, 
                                                                            _console(out) {
    if(_writeIntoFile){
        _logDir = filesystem::current_path();
        _logDir.append("Logs");
        if(!filesystem::exists(_logDir)){
            filesystem::create_directory(_logDir);
        }
    }
}


Logger::~Logger(){
    close();
}


void Logger::close(){
    if(_file.is_open()){
        _file.close();
    }
}


void Logger::createNew(){ 
    auto now {std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    filesystem::path path = _logDir; 
    path.append("bulk" + std::to_string(now) + ".log");
    _file = std::ofstream(path, std::ios::app);
}



void Logger::execute(){
    std::string tmp = "bulk: ";
    tmp += _cmdPool->begin();
    for(auto it = _cmdPool->begin()+1; it != _cmdPool->end(); ++it){
        tmp += ", ";
        tmp += it;
    }
    tmp += "\n";
    _console << tmp;
    if(_writeIntoFile){
        createNew();
        _file << tmp;
        close();
    }
}