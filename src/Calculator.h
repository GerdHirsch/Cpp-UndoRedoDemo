#ifndef SIMPLE_CALCULATOR_H
#define SIMPLE_CALCULATOR_H

class Calculator
{
public:
	Calculator() : result(0){};
	~Calculator(){};

	void plus(double summand){ result += summand; }
	void minus(double subtrahent){ result -= subtrahent; }
	double getResult(){ return result; }
	void clear() { result = 0; }
private:
	double result;
};



#endif //SIMPLE_CALCULATOR_H

