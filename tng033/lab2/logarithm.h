/*************************
* Class Log              *
* TNG033: Lab 3          *
**************************/


#ifndef LOG_H
#define LOG_H

#include <iostream>

using namespace std;

#include "expression.h"

class Log : public Expression
{
public:
	//Constructor
	Log();
	Log(const Expression& E, double c1, double c2, int base);

	//Copy constructor
   Log(const Log& l);

	//Destrcutor
	~Log();

	//Assignment operator
	Log& operator=(const Log& l);

    //Function call operator
	double operator()(double d) const override;

	Log* Clone() const override;

protected:

	double c1;
	double c2;
	int base;
	Expression* e;

	void display(ostream& os) const override;

};

#endif
