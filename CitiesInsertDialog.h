#pragma once
#include "afxdialogex.h"
#include "Validator.h"


// CitiesInsertDialog dialog
class CitiesInsertDialog : public CDialog
{
	// Macros
	// ----------------
protected:
	DECLARE_MESSAGE_MAP();
private:
	DECLARE_DYNAMIC(CitiesInsertDialog);

	// Constants
	// ----------------s
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_CITY_DIALOG };
#endif

	// Constructor / Destructor
	// ----------------
public:
	CitiesInsertDialog(CWnd* pParent = nullptr);   // standard constructor

	//Virtual methods
	// ----------------
public:
	virtual ~CitiesInsertDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	// Methods
	// ----------------
protected:
	void OnOK();

	// Members
	// ----------------
public:
	/// <summary>
	/// Member for getting City Name 
	/// </summary>
	CString m_strCityName;
	/// <summary>
	/// The max number of characters for that field
	/// </summary>
	int m_nMaxCityNameFiledSize = nMaxCityNameFiledSize;
	/// <summary>
	/// Member for getting District Name
	/// </summary>
	CString m_strCityDistrict;
	/// <summary>
	/// The max number of characters for that field
	/// </summary>
	int m_nMaxCityNameFieldSize = nMaxCityDistrictFieldSize;
	/// <summary>
	/// The validator class which help us with fields constains 
	/// </summary>
	Validator m_oValidator;
};
