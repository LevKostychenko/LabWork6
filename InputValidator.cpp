#include "pch.h"
#include "InputValidator.h"


InputValidator::InputValidator()
{
}


InputValidator::~InputValidator()
{
}

bool InputValidator::IsInputCorrect(std::istream &in, char* buffer)
{
	bool isCorrect = false;
	while (!isCorrect)
	{
		try
		{
			in.clear();
			in >> buffer;
			if (strlen(buffer) == 0)
			{
				throw InputException("NULL input", "ENG");
			}

			for (int i = 0; *(buffer + i) != '\0'; i++)
			{
				if (((*(buffer + i) < 'A' || *(buffer + i) > 'Z') && *(buffer + i) < 'a') || ((((*(buffer + i) < 'a') || *(buffer + i) > 'z')) && ((*(buffer + i) < 'A') && (*(buffer + i) > 'Z'))))
				{
					throw InputException("Invalid symbols", "ENG");
				}
			}
		}
		catch (const InputException& ex)
		{
			std::cout << "Error has occured. Details: " << ex.Description << ". Current language: " << ex.CurrentLang << "\n";
			continue;
		}

		isCorrect = true;
	}

	return true;
}

bool InputValidator::IsNumberInputCorrect(std::istream &in, char* buffer)
{
	bool isCorrect = false;

	while (!isCorrect)
	{
		try
		{
			in.clear();
			in >> buffer;
			if (strlen(buffer) == 0)
			{
				throw InputException("NULL input", "ENG");
			}

			for (int i = 0; *(buffer + i) != '\0'; i++)
			{
				if (*(buffer + i) > 57 || *(buffer + i) < 48)
				{
					throw InputException("Invalid symbols", "ENG");
				}
			}
		}
		catch (const InputException& ex)
		{
			std::cout << "Error has occured. Details: " << ex.Description << ". Current language: " << ex.CurrentLang << " \n";
			continue;
		}

		isCorrect = true;
	}

	return true;
}