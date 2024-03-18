#include "pch.h"
#include "Validator.h"

bool Validator::IsAlphaString(const CString& str)
{
	// Iterate trough string and check if the caracters are letters
	for (int i = 0; i < str.GetLength(); ++i)
	{
		if (_istdigit(str[i]))
			return false; // Found a numeric character
	}
	return true; // Only alphabetic characters found
}

bool Validator::IsEmtyString(const CString& str) {

	if (str.IsEmpty()) {
		return true;
	}

	return false;
}
