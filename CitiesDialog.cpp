#include "pch.h"
#include "PhoneBookLts.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "CitiesDialog.h"

// CCitiesDialog message handlers

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)
BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)

END_MESSAGE_MAP()
CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_UPDATE_CITY_DIALOG, pParent)
{
	// Constructor logic here
}

CCitiesDialog::CCitiesDialog(int nHint /*= 0*/, CITIES& recCity, CWnd* pParent)
	: CDialog(IDD_UPDATE_CITY_DIALOG, pParent), m_recCity(recCity), m_nHint(nHint)
{
}

CCitiesDialog::~CCitiesDialog()
{
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_editCityName);
	DDX_Control(pDX, IDC_EDB_CITIES_DISTRICT, m_editCityDistrict);
}

BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Additional initialization logic 
	CDataExchange dataExhange(this, TRUE);
	DoDataExchange(&dataExhange);

	// Set the values from the cities object to the edit controls


	switch (m_nHint) {
	case DialogUpdateHint:
		SetDialogTitle(L"Обновяване на град");


		SetCityName(m_recCity.szCityName);
		SetCityDistrict(m_recCity.szDistrict);

		break;
	case DialogInsertHint:
		SetDialogTitle(L"Нов град");

		break;
	case DialogReadOnlyHint:

		SetDialogTitle(L"Преглед на града");


		SetCityName(m_recCity.szCityName);
		SetCityDistrict(m_recCity.szDistrict);

		ReadOnlyControls();

		CWnd* pOKButton = GetDlgItem(IDOK);
		if (pOKButton)
			pOKButton->ShowWindow(SW_HIDE);
		break;
	}

	return TRUE;
}

void CCitiesDialog::SetDialogTitle(const CString& title)
{
	SetWindowText(title);
}

void CCitiesDialog::SetCityName(const CString& strCityName)
{
	m_editCityName.SetWindowText(strCityName);
}

CString CCitiesDialog::GetCityName()
{
	CString strCityName;
	m_editCityName.GetWindowText(strCityName);
	return strCityName;
}

CString CCitiesDialog::ReturnCityName() {
	return m_recCity.szCityName;
}

CString CCitiesDialog::ReturnDistrictName() {
	return m_recCity.szDistrict;
}

void CCitiesDialog::SetCityDistrict(const CString& cityDistrict)
{
	m_editCityDistrict.SetWindowText(cityDistrict);
}


CString CCitiesDialog::GetCityDistrict()
{
	CString cityDistrict;
	m_editCityDistrict.GetWindowText(cityDistrict);
	return cityDistrict;
}


void CCitiesDialog::ReadOnlyControls() {
	m_editCityName.SetReadOnly(TRUE);
	m_editCityDistrict.SetReadOnly(TRUE);
}



void CCitiesDialog::OnOK()
{

	//Validation the fields of dialog if they are empty
	if (m_oValidator.IsEmtyString(GetCityName()) || m_oValidator.IsEmtyString(GetCityDistrict()))
	{
		//MessageBox
		AfxMessageBox(_T("Моля, попълнете всички полета."), MB_ICONWARNING);
		// Do not close the dialog if fields are empty
		return;
	}

	//Validation the fields fo dialog if they are onnly with leters
	if (!m_oValidator.IsAlphaString(GetCityName()) || !m_oValidator.IsAlphaString(GetCityDistrict()))
	{
		//Messagebox
		AfxMessageBox(_T("Имената трябва да съдържат само букви."), MB_ICONWARNING);
		// Do not close the dialog if names contain numbers
		return;
	}

	lstrcpy(m_recCity.szCityName, GetCityName());
	lstrcpy(m_recCity.szDistrict, GetCityDistrict());




	CDialog::OnOK();
}





