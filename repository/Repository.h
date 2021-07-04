//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_REPOSITORY_H
#include "Observer.h"
#include <fstream>
#include <vector>
#define QT_DEV_TESTS_REPOSITORY_H

template <class TElem>
class Repository {
private:
    virtual void loadFromFile()=0;
    virtual void saveToFile()=0;
public:
    Repository(){;}
    ~Repository(){;}
    virtual bool add(const TElem& tElem)=0;
};


#endif //QT_DEV_TESTS_REPOSITORY_H
