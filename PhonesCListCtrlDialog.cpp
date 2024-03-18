// PhonesCListCtrlDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBookLts.h"
#include "afxdialogex.h"
#include "PhonesCListCtrlDialog.h"
#include "PhoneTypes.h"


// CPhonesCListCtrlDialog dialog

IMPLEMENT_DYNAMIC(CPhonesCListCtrlDialog, CDialog)

CPhonesCListCtrlDialog::CPhonesCListCtrlDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DILG_CLISTCTRL_DIALOG, pParent)
{

}

CPhonesCListCtrlDialog::CPhonesCListCtrlDialog(CPhoneTypesTypedPtrArray* pPhoneTypeArray, CWnd* pParent/*=nullptr*/)
	: CDialog(IDD_DILG_CLISTCTRL_DIALOG, pParent), m_oPhoneTypes(pPhoneTypeArray)
{
}

CPhonesCListCtrlDialog::~CPhonesCListCtrlDialog()
{

}
BOOL CPhonesCListCtrlDialog::OnInitDialog() {
	CDialog::OnInitDialog();

	// Additional initialization logic 
	CDataExchange dataExhange(this, TRUE);
	DoDataExchange(&dataExhange);

	m_editPhoneNumber.SetWindowText(_T("+359"));

	SetPhoneTypesComboBox(m_oPhoneTypes);






	return TRUE;
}
void CPhonesCListCtrlDialog::SetPhoneTypesComboBox(CPhoneTypesTypedPtrArray* oPhoneTypeArray) {
	if (oPhoneTypeArray != nullptr) {
		for (INT_PTR nIndex = 0; nIndex < oPhoneTypeArray->GetCount(); nIndex++)
		{
			CString strCurrentCity = oPhoneTypeArray->GetAt(nIndex)->szPhoneType;
			int nIdx = m_cmbPhoneTypes.AddString(strCurrentCity);
			m_cmbPhoneTypes.SetItemData(nIdx, oPhoneTypeArray->GetAt(nIndex)->lId);
		}
	}
}

CString CPhonesCListCtrlDialog::GetPhoneNumber() const
{
	CString strCurrentPhoneNumber;
	m_editPhoneNumber.GetWindowText(strCurrentPhoneNumber);
	return strCurrentPhoneNumber;
}

CString CPhonesCListCtrlDialog::GetPhoneType() const
{
	CString strCurrentPhoneType;

	m_cmbPhoneTypes.GetWindowText(strCurrentPhoneType);


	return strCurrentPhoneType;
}

void CPhonesCListCtrlDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_PHONE_NUMBER_DIALOG, m_staticPhoneNumber);
	DDX_Control(pDX, IDC_STT_PHONE_TYPE_DIALOG, m_staticPhoneType);
	DDX_Control(pDX, IDC_EDT_PHONE_NUMBER_DIALOG, m_editPhoneNumber);
	DDX_Control(pDX, IDC_CMB_DIALOG_PHONE_TYPES, m_cmbPhoneTypes);
}

void CPhonesCListCtrlDialog::OnOK()
{

	m_strPhoneNumber = GetPhoneNumber();
	m_strPhoneType = GetPhoneType();

	CDialog::OnOK();
}


BEGIN_MESSAGE_MAP(CPhonesCListCtrlDialog, CDialog)
	ON_STN_CLICKED(IDC_STT_PHONE_TYPE_DIALOG, &CPhonesCListCtrlDialog::OnStnClickedSttPhoneTypeDialog)
	ON_EN_CHANGE(IDC_EDT_PHONE_NUMBER_DIALOG, &CPhonesCListCtrlDialog::OnEnChangeEdtPhoneNumberDialog)
END_MESSAGE_MAP()


// CPhonesCListCtrlDialog message handlers


void CPhonesCListCtrlDialog::OnStnClickedSttPhoneTypeDialog()
{
	// TODO: Add your control notification handler code here
}


void CPhonesCListCtrlDialog::OnEnChangeEdtPhoneNumberDialog()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
