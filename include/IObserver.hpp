#pragma once

class IObserver{
public:
    virtual void execute() = 0;
    virtual ~IObserver() = default;
};