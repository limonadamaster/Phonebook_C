// CCitiesDialog.h
#pragma once
#include "afxwin.h"
#include "afxdialogex.h"
#include "Validator.h"
#include "Cities.h"

// CCitiesDialog dialog
class CCitiesDialog : public CDialog
{
	// Macros
	// ----------------
protected:
	DECLARE_MESSAGE_MAP();
private:
	DECLARE_DYNAMIC(CCitiesDialog);

	// Constants
	// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_UPDATE_DIALOG };
#endif

	// Constructor / Destructor
	// ----------------
public:
	CCitiesDialog(CWnd* pParent = nullptr);   // standard constructor
	CCitiesDialog(int nHint, CITIES& cityObj, CWnd* pParent = nullptr); // constructor with cities object parameter
	virtual ~CCitiesDialog();

	// Virtual methods
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	virtual BOOL OnInitDialog() override;

	// Methods
	// ----------------
public:
	void SetDialogTitle(const CString& title);
	void SetCityName(const CString& strCityName);
	CString GetCityName();
	CString ReturnCityName();
	CString ReturnDistrictName();
	void SetCityDistrict(const CString& cityDistrict);
	CString GetCityDistrict();
	void ReadOnlyControls();
protected:

	void OnOK();

	// Members
	// ----------------
private:
	CEdit m_editCityName;// Edit control for city name
	CEdit m_editCityDistrict; // Edit control for city district
	int m_nHint;
	int m_nMaxCityNameFieldSize = nMaxCityNameFiledSize;
	int m_nMaxCityDistrictFieldSize = nMaxCityDistrictFieldSize;
	Validator m_oValidator;
	CITIES m_recCity; // Member variable to hold the cities object

	enum {
		DialogUpdateHint = 1,
		DialogInsertHint,
		DialogReadOnlyHint
	};
};
