/*********************************************************
* Class Expression member functions implementation       *
* TNG033: Lab 3                                          *
**********************************************************/

#include "expression.h"
#include <cmath>

    bool Expression:: isRoot(const double x) const{
        return (fabs((*this)(x) < EPSILON));
    }

    ostream& operator<<(ostream &os,const Expression & E){
    E.display(os);
    return os;
    }


//ADD implementation of the member functions for class Expression

