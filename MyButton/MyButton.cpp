// Button Implementation

#include "MyButton.h"

// constructor
MyButton::MyButton(int pin) {
	pinNum = pin;
	lastButtonState = 0;
	debounce = new EventTimer();
}

// destructor
MyButton::~MyButton() {
	delete debounce;
}

// check if button is engaged
bool MyButton::checkButtonEvent() {

	// update current state
	int currentState = digitalRead(pinNum);

	// check for change in state and that it is not within 10ms of last change in state
	if (currentState != lastButtonState && (debounce->checkExpired() || !debounce->getIsRunning())) {
		// start timer at change of stat
		debounce->start(100);

		// check if button was pushed (not released)
		if (currentState == 1)
		{
			// update last state and return true
			lastButtonState = currentState;
			return true;
		}

		// update last state and exit 
		lastButtonState = currentState;
	}
	return false;
}

// set the new pin number
void MyButton::setPin(int pin) {
	pinNum = pin;
}