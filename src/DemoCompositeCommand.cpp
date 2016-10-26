#include "UndoRedoManagerImpl.h"
#include "Calculator.h"
#include "CalculaturCommands.h"

#include <CompositeCommand.h>

#include <iostream>
using namespace std;

void demoCompositeCommand(){
	cout << "demoCompositeCommand()" << endl;
	Calculator calculator;

	UndoRedoManagerImpl urMngr;

	// nur mit move() möglich
	//	UndoRedoManagerImpl urCCMngr;
	//	CompositeCommand ccmd1(urCCMngr );
	CompositeCommand ccmd((UndoRedoManagerImpl()) );


	cout << "Result: " << calculator.getResult() << endl;
	{
		cout << "ccmd.doIt(plus 42)" << endl;
		PlusCommand plus(calculator, 42);
		ccmd.doIt(plus);
		// sollten wir hier mit dem plus noch etwas tun können?
	}
	cout << "Result: " << calculator.getResult() << endl;
	{
		cout << "ccmd.doIt(minus 24)" << endl;
//		MinusCommand minus(calculator, 24);
		ccmd.doIt( MinusCommand(calculator, 24) );
	}
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.doIt(ccmd)" << endl;
	urMngr.doIt( std::move(ccmd) );
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.doIt(plus 42)" << endl;
	PlusCommand plus(calculator, 42);
	urMngr.doIt(plus);
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.undo();" << endl;
	urMngr.undo();
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.undo();" << endl;
	urMngr.undo();
	cout << "Result: " << calculator.getResult() << endl;

}
