#include <include/Calculator.h>
#include <include/CalculatorCommands.h>

#include <UndoRedoFramework/ByDelegation/UndoRedoManagerImpl.h>
#include <UndoRedoFramework/ByDelegation/UndoRedoStackImpl.h>
#include <UndoRedoFramework/CompositeCommandImpl.h>

#include <iostream>
using namespace std;

using namespace UndoRedoFramework;

void demoCompositeCommand(){
	using UndoRedoManagerImpl = ByDelegation::UndoRedoManagerImpl;
	using UndoRedoStackImpl = ByDelegation::UndoRedoStackImpl;

	cout << "demoCompositeCommand()" << endl;
	Calculator calculator;
	UndoRedoManagerImpl urMngr;
	CompositeCommandImpl ccmd(std::make_unique<UndoRedoStackImpl>());


	cout << "Result: " << calculator.getResult() << endl;
	{
		cout << "ccmd.doIt(plus 3)" << endl;
		Minus minus(calculator, 1);
		Plus plus(calculator, 3);
		Plus::throwException() = true;
		ccmd.doIt(minus);
		ccmd.doIt(minus);
		try{
			ccmd.doIt(plus);
		}catch(std::exception& e){
			cout << "catch ccmd.doIt(plus 3)" << endl;
			cout << "Result: " << calculator.getResult() << endl;
		}
		// sollten wir hier mit dem plus noch etwas tun können?
	}
	cout << "Result: " << calculator.getResult() << endl;
	{
		cout << "ccmd.doIt(minus 24)" << endl;
//		MinusCommand minus(calculator, 24);
		ccmd.doIt( Minus(calculator, 24) );
	}
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.doIt(ccmd)" << endl;
	urMngr.doIt( std::move(ccmd) );
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.doIt(plus 42)" << endl;
	Plus plus(calculator, 42);
	urMngr.doIt(plus);
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.undo();" << endl;
	urMngr.undo();
	cout << "Result: " << calculator.getResult() << endl;

	cout << "urMngr.undo();" << endl;
	urMngr.undo();
	cout << "Result: " << calculator.getResult() << endl;

}
