#ifndef TESTCHILD_H
#define TESTCHILD_H

#include "testbase.h"

class testChild : public testBase
{
public:
    testChild();
    virtual int test() override;
private:
    int i = 4;
};

#endif // TESTCHILD_H
