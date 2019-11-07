/*************************
* Class Expression       *
* TNG033: Lab 3          *
**************************/

#ifndef EXP_H
#define EXP_H

#include <iostream>

using namespace std;

const double EPSILON = 1.0e-5;


class Expression //abstract
{
public:

    bool isRoot(const double x) const;
    virtual double operator()(double d) const = 0;
    virtual Expression* Clone() const = 0;
    virtual ~Expression() {};
    friend ostream& operator<<(ostream& os, const Expression &E);

protected:

    virtual void display(ostream& os) const = 0;


};


#endif
