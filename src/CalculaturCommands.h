#ifndef CALCULATOR_COMMANDS
#define CALCULATOR_COMMANDS

#include "Command.h"

#include <iostream>
#include "Calculator.h"

class PlusCommand : public Command
{
public:
	PlusCommand(Calculator& calculator, double summand) :
		calculator(calculator), summand(summand){}

	PlusCommand(const PlusCommand& source) :
		calculator(source.calculator), summand(source.summand) {}

	virtual void doIt() override
	{
		calculator.plus(summand);
	}
	virtual void undo() override
	{
		calculator.minus(summand);
	}

	virtual std::unique_ptr<Command> clone() const & override
	{
		using namespace std;
		cout << "PlusCommand::clone() const &" << endl;
		return std::unique_ptr<Command>( new PlusCommand(*this));
	}

	virtual std::unique_ptr<Command> clone() && override
	{
		using namespace std;
		cout << "PlusCommand::clone() &&" << endl;
		return std::unique_ptr<Command>( new PlusCommand( std::move(*this) ));
	}
private:
	Calculator& calculator;
	double summand;
};

class MinusCommand : public Command
{
public:
	MinusCommand(Calculator& calculator, double subtrahent):calculator(calculator), subtrahent(subtrahent){}
	virtual void doIt() override
	{
		calculator.minus(subtrahent);
	}
	virtual void undo() override
	{
		calculator.plus(subtrahent);
	}

	virtual std::unique_ptr<Command> clone() const& override
	{
		using namespace std;
		cout << "MinusCommand::clone() const&" << endl;
		return std::unique_ptr<Command>( new MinusCommand( std::move(*this) ));
	}
	virtual std::unique_ptr<Command> clone() && override
	{
		using namespace std;
		cout << "MinusCommand::clone() &&" << endl;
		return std::unique_ptr<Command>( new MinusCommand( std::move(*this) ));
	}
private:
	Calculator& calculator;
	double subtrahent;
};

#endif //CALCULATOR_COMMANDS
