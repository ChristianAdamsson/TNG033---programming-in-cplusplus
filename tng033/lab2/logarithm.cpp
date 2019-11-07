/*********************************************************
* Class Log member functions implementation              *
* TNG033: Lab 3                                          *
**********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <math.h>

Log::Log() // default constructor
:c1(0.0),c2(1.0),base(2)
{
    double v[2] = {0,1};
    e = new Polynomial(1,v);
}

Log::Log(const Expression& E,  double c1,  double c2,  int base)
: c1(c1), c2(c2), base(base)
{
   e = E.Clone();
}

void Log:: display(ostream& os) const{
 if(fabs(c1) < EPSILON){
 os << c2 << ".00* log_" << base << "( " << *e << ")";
 }
 else{
    os << c1 << ".00+" << c2 << ".00* log_" << base << "( " << *e << ")";
 }
}
Log::Log(const Log& l)
:e(l.e->Clone()), c1(l.c1), c2(l.c2), base(l.base)
{

}

Log* Log::Clone() const
{
    return (new Log(*this));
}

Log::~Log()
{
    delete e;
}
double Log::operator()(double d) const
{
    double result = c1;

    if(base== 2)
    {
         result += c2*log2(((*e)(d)));

    }
    else if(base == 10)
    {
        result += c2*log10(((*e)(d)));
    }
    return result;
}

Log& Log::operator=(const Log& l)
{
    Log temp(l);
    swap(e, temp.e);
    swap(c1, temp.c1);
    swap(c2, temp.c2);
    swap(base, temp.base);
    return *this;
}
