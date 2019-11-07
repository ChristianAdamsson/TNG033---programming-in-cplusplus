/*************************
* Class Polynomial       *
* TNG033: Lab 3          *
**************************/

#ifndef POL_H
#define POL_H

#include <iostream>

using namespace std;

#include "expression.h"


class Polynomial : public Expression
{
public:


        Polynomial(int ind, double* inArray); // initialisera polynomet med givet koefficient array och grader
        ~Polynomial() {delete[] Koefficients;} // destructor
        Polynomial(double ind); //skapa polynom av en double
        Polynomial(const Polynomial &p); // copy constructor
        Polynomial* Clone() const override;

        double operator()(double d) const override;
        double operator[](int i) const;
        double& operator[](int i);
        //Polynomial operator+(const Polynomial& P) const;
       friend const Polynomial operator+(const Polynomial &p1, const Polynomial &p2) ;
//        Polynomial operator+(const Polynomial& p) const override ;


        Polynomial& operator=(const Polynomial & inP);


protected:
        double * Koefficients; // array som lagrar koefifcienterna
        int degree; // graden av polynomet
        void display(ostream& os) const override;
};


#endif
