#include <memory>
#include <sstream>
#include <random>

#include "gtest/gtest.h"
#include "CommandReader.hpp"
#include "CommandHandler.hpp"
#include "CommandPool.hpp"
#include "Logger.hpp"
#include "experimental/filesystem"


size_t mainLoop(std::stringstream& input, std::stringstream& output, size_t repeats, bool logIntoFile = false){
    std::random_device rand;
    size_t blockSize = rand() % repeats;
    std::shared_ptr<Bulk::CommandPool> cmdPool{new Bulk::CommandPool()};
    std::unique_ptr<Bulk::Logger> logger{new Bulk::Logger(cmdPool, logIntoFile, output)};
    std::unique_ptr<Bulk::CommandHandler> handler{new Bulk::CommandHandler(cmdPool)};
    Bulk::CommandReader reader(cmdPool, blockSize, input);
    handler->attach(logger.get());
    reader.attach(handler.get());
    reader.run();
    reader.detach(handler.get());
    handler->detach(logger.get());
    return blockSize;
}


TEST(bulk, simple){
    // preparation
    const size_t repeats = 100;
    std::array<std::string, repeats> cmds;
    std::stringstream input, output;
    for(size_t i=0; i<repeats; ++i){
        cmds[i] = "cmd" + std::to_string(i);
        input << cmds[i] << '\n';
    }
    // main loop
    size_t blockSize = mainLoop(input, output, repeats);
    // check results
    std::string cmd, result;
    size_t j, i = 0;
    while(std::getline(output, cmd)){
        result = "bulk: " + cmds[i++];
        j=i+blockSize-1;
        while(i<j && i<cmds.size()){
            result += ", " + cmds[i++];
        }
        ASSERT_EQ(cmd, result);
    }
}


TEST(bulk, braces_1){
    // preparation
    const size_t repeats = 100;
    std::array<std::string, repeats> cmds;
    std::stringstream input, output;
    input << "{\n";
    for(size_t i=0; i<repeats; ++i){
        cmds[i] = "cmd" + std::to_string(i);
        input << cmds[i] << '\n';
    }
    // main loop
    mainLoop(input, output, repeats);
    // check results
    ASSERT_TRUE(output.rdbuf()->in_avail() == 0);
}


TEST(BULK, braces_2){
    // preparation
    std::random_device rand;
    const size_t repeats = 100;
    std::array<std::string, repeats> cmds;
    std::stringstream input, output;
    std::string result;
    size_t openBrace = 0;
    size_t closeBrace = 0;
    while(openBrace == closeBrace){
        size_t tmp_1 = rand()%repeats;
        size_t tmp_2 = rand()%repeats;
        openBrace = std::min(tmp_1, tmp_2);
        closeBrace = std::max(tmp_1, tmp_2);
    }
    for(size_t i=0; i<repeats; ++i){
        cmds[i] = "cmd" + std::to_string(i);
        if(i==openBrace){
            result = "bulk: " + cmds[i];
            input << "{\n";
        }
        if(i==closeBrace){
            input << "}\n";
        }
        if(openBrace < i && i < closeBrace){
            result += ", " + cmds[i];
        }
        input << cmds[i] << '\n';
    }
    // main loop
    size_t blockSize = mainLoop(input, output, repeats);
    // check results
    std::string cmd;
    size_t i = 0;
    openBrace = openBrace % blockSize ? openBrace / blockSize + 1 : openBrace / blockSize;
    while(std::getline(output, cmd)){
        if(i++ != openBrace){
            continue;
        }
        ASSERT_EQ(cmd, result);
        break;
    }
}

TEST(bulk, loggerPath){
    // preparation
    const size_t repeats = 100;
    std::array<std::string, repeats> cmds;
    std::stringstream input, output;
    auto _logDir = std::experimental::filesystem::current_path();
    _logDir.append("Logs");
    if(!std::experimental::filesystem::exists(_logDir)){
        // main loop
        mainLoop(input, output, repeats, true);
        ASSERT_TRUE(std::experimental::filesystem::exists(_logDir));
    }
}