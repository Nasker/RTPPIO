/*
	RTPRotaryClick.h - Class for reading and managing a Rotary QuadEncoder with click button.
	Updated by Oscar Martínez Carmona @ RockinTechProjects, January 17, 2022.
*/

#include "RTPRotaryClick.h"

void RTPRotaryClick::callbackOnRotation( void (*userFunc)(ControlCommand) ){
	long newPosition = read()/4;
  	if (newPosition < _oldPosition) {
		ControlCommand callbackCommand;
		callbackCommand.controlID = 4;
		callbackCommand.commandType = 0;
		callbackCommand.value = newPosition;
   		_oldPosition = newPosition;
   		(*userFunc)(callbackCommand);
  	}
  	else if (newPosition > _oldPosition) {
   		ControlCommand callbackCommand;
		callbackCommand.controlID = 4;
		callbackCommand.commandType = 1;
		callbackCommand.value = newPosition;
   		_oldPosition = newPosition;
   		(*userFunc)(callbackCommand);
  	}
}