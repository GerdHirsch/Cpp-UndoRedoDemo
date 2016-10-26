#include <iostream>

/*
 * Übung:
 * Schritt für Schritt Entwicklung
 * UndoRedoManager/Command Pattern
 * CompositeCommand auf der Basis UndoRedoManager
 * Diskussion: Copyable? Moveable?
 * Commands verwalten: SmartPointer?
 * doIt(Command const& cmd) Lebensdauer cmd?
 * Wie Copy? Move?
 *
 */

#include "UndoRedoManagerImpl.h"
#include "Calculator.h"
#include "CalculaturCommands.h"

using namespace std;

void demoCompositeCommand();
void demoSimpleCommand(UndoRedoManager& urMngr);
void demoUniquePtrStack();

int main()
{
	cout << boolalpha;
	{
		UndoRedoManagerImpl urMngr;
		demoSimpleCommand(urMngr);
	}
	demoCompositeCommand();
//	demoUniquePtrStack();
}

void demoSimpleCommand(UndoRedoManager& urMngr){
	// Demo temporäre und lokale Objekte als Argumente
	cout << "demoSimpleCommand()" << endl;
	Calculator calculator;
	cout << "Result: " << calculator.getResult() << endl;

	cout << "Plus 42" << endl;
//	PlusCommand plus(calculator, 42);
//	urMngr.doIt(plus);
	// sollten wir hier mit dem plus noch etwas tun können?

	urMngr.doIt(PlusCommand(calculator, 42));
	cout << "Result: " << calculator.getResult() << endl;

	cout << "Minus 24" << endl;
	MinusCommand minus(calculator, 24);
	MinusCommand minusTemp(minus);

	urMngr.doIt(minus);
	// sollten wir hier mit dem minus noch etwas tun können?

	cout << "Result: " << calculator.getResult() << endl;

	cout << "before reset isModified: " << urMngr.isModified() << endl;
	urMngr.resetModified();
	cout << "after  reset isModified: " << urMngr.isModified() << endl;

	cout << "urMngr.undo()" << endl;
	urMngr.undo();
	cout << "Result: " << calculator.getResult() << endl;
	cout << "isModified: " << urMngr.isModified() << endl;

	cout << "urMngr.redo()" << endl;
	urMngr.redo();
	cout << "Result: " << calculator.getResult() << endl;
	cout << "isModified: " << urMngr.isModified() << endl;

	while(urMngr.canUndo())
		urMngr.undo();
	cout << "Result: " << calculator.getResult() << endl;
	cout << "isModified: " << urMngr.isModified() << endl;
}

void demoUniquePtrStack(){
//	typedef std::shared_ptr<Command> SmartPointer;
	typedef std::unique_ptr<Command> SmartPointer;

	Calculator calculator;
	PlusCommand plus(calculator, 42);
	Command & command = plus;
	std::stack<SmartPointer> undoStack;
	std::stack<SmartPointer> redoStack;


	undoStack.push( std::move(PlusCommand(calculator, 43).clone()) );
	undoStack.push( std::move(command).clone() );
	redoStack.push( std::move(undoStack.top()) );

	std::stack<SmartPointer> tempStack( std::move(undoStack));
}
