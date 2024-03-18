#pragma once

/// <summary>
/// The max size of fields
/// </summary>
const int nMaxCityNameFiledSize = 32 + 1;
const int nMaxCityDistrictFieldSize = 31 + 1;

/// <summary>
/// The validator class which help us with fields constrains
/// Here you can add your validation methods
/// </summary>
class Validator
{
public:
	/// <summary>
	/// Method that check if stirng is only wtih letters
	/// </summary>
	bool IsAlphaString(const CString& str);

	bool IsEmtyString(const CString& str);

};

