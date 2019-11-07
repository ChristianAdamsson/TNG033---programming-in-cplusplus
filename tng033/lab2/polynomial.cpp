/*********************************************************
* Class Polynomial member functions implementation       *
* TNG033: Lab 3                                          *
**********************************************************/

#include "polynomial.h"
#include  <math.h>

Polynomial::Polynomial(int ind, double* inArray)
: Koefficients(new double[ind+1]), degree(ind)
{
    for(int i = 0; i <= degree; ++i)
    {
        Koefficients[i] = inArray[i];
    }

}

Polynomial::Polynomial(double ind)
:Koefficients(new double[1]), degree(0){

    Koefficients[0] = ind;

}
Polynomial::Polynomial(const Polynomial &p)
{
    degree = p.degree;
    Koefficients = new double[p.degree+1];
    for ( int i = 0; i <= degree; ++i)
    {
        Koefficients[i] = p.Koefficients[i];
    }


}

Polynomial& Polynomial:: operator=(const Polynomial & inP)
{
    Polynomial temp(inP);

    swap(Koefficients, temp.Koefficients);
    swap(degree, temp.degree);

    return *this;

}

double Polynomial:: operator()(double d) const
{
    double temp = 0;
    for(int i = 0; i <= degree; ++i)
    {
        temp += Koefficients[i] * pow(d, i);
    }
    return temp;
}

double Polynomial:: operator[](int c) const
{
    return(Koefficients[c]);
}
double& Polynomial:: operator[](int c)
{
    return(Koefficients[c]);
}



void Polynomial::display(ostream& os) const
{
    os << Koefficients[0];
    for(int i = 1; i <= degree; ++i)
    {
        if (fabs(Koefficients[i]) > EPSILON)
        {

                os << " + " << Koefficients[i] << " * X^" << i;
        }
    }
}


Polynomial* Polynomial:: Clone() const
{
    return (new Polynomial(*this));
}

const Polynomial  operator+(const Polynomial &p1,const Polynomial& p2)
{
    int Mindegree = min(p1.degree, p2.degree);
    int maxDegree = max(p1.degree, p2.degree);
//    if(p1.degree > p2.degree)
//        maxDegree = p1.degree;
//    else
//        maxDegree = p2.degree;

    double *newCoeff = new double[maxDegree+1] ;


    for(int i = 0; i <= Mindegree; ++i)
    {
        newCoeff[i] = p1.Koefficients[i] + p2.Koefficients[i];
    }


    for(int i = Mindegree + 1; i <= p1.degree; ++i)
    {
        newCoeff[i] = p1.Koefficients[i];

    }
        for(int i = Mindegree + 1; i <= p2.degree; ++i)
    {
        newCoeff[i] = p2.Koefficients[i];
    }

    Polynomial temp(maxDegree, newCoeff);

    delete [] newCoeff;

    return temp;

}




