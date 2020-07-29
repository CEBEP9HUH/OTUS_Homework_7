#pragma once

#include <list>

#include "IObserver.hpp"


class IPublisher{
protected:
    std::list<IObserver* > _observers;
public:
    void attach(IObserver* observer){
        _observers.emplace_back(observer);
    }
    void detach(IObserver* observer){
        _observers.remove(observer);
    }
    virtual void notify(){
        for(auto& observer : _observers){
            observer->execute();
        }
    }
    virtual ~IPublisher() = default;
};