//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_OBSERVER_H
#include <vector>
#include <algorithm>
#define QT_DEV_TESTS_OBSERVER_H


class Observer {
public:
    virtual void update()=0;
    virtual ~Observer(){};
};
class ObserverUpdate{
private:
    std::vector<Observer*> observers;
public:
    virtual ~ObserverUpdate(){;};
    void addObserver(Observer* observer){
        this->observers.push_back(observer);
    }
    void removeObserver(Observer* observer){
        auto it = std::find(this->observers.begin(), this->observers.end(), observer);
        if(it != this->observers.end())
            this->observers.erase(it);
    }
    void notify(){
        for (auto observer:this->observers)
            observer->update();
    }
};


#endif //QT_DEV_TESTS_OBSERVER_H
