#pragma once

#include <iostream>
#include "InputException.h"

class InputValidator
{
public:
	InputValidator();
	~InputValidator();

	static bool IsInputCorrect(std::istream &in, char* buffer);
	static bool IsNumberInputCorrect(std::istream &in, char* buffer);
};

