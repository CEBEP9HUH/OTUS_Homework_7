#pragma once

#include <vector>
#include <map>

#include "CommandWrapper.hpp"


namespace Bulk{
    class CommandPool{
    private:
        using command_t = CommandWrapper<int>;
        using container_t = std::vector<std::string>;
        using iter_t = container_t::iterator;
        container_t _commands;
    public:
        using allCmdContainer_t = std::map<std::string, command_t>;
        static allCmdContainer_t _allCmdList;
        class iterator{
        private:
            iter_t _ptr;
        public:
            iterator() : _ptr{nullptr} {};
            iterator(iter_t ptr) : _ptr{ptr} {};
            iterator operator++() { iterator i = *this; _ptr++; return i; }
            iterator operator++(int) { _ptr++; return *this; }
            iterator operator+(const int a) { iterator i = *this; i._ptr+=a; return i; }
            command_t& operator*() const { return _allCmdList.at(*_ptr); }
            command_t* operator->() const { return &_allCmdList.at(*_ptr); }
            bool operator==(const iterator& rhs) const { return _ptr == rhs._ptr; }
            bool operator!=(const iterator& rhs) const { return _ptr != rhs._ptr; }
            operator std::string() {return *_ptr;}
        };
        CommandPool() = default;
        CommandPool(const CommandPool&) = default;
        CommandPool(CommandPool&&) = default;
        CommandPool& operator=(const CommandPool&) = default;
        CommandPool& operator=(CommandPool&&) = default;
        ~CommandPool() = default;
        bool addCommand(const std::string& cmdName);
        iterator begin();
        iterator end();
        void clear();
        void reserve(const size_t size);
        bool empty();
    };
}