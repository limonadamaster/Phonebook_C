// CPersonDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBookLts.h"
#include "afxdialogex.h"
#include "PersonDialog.h"
#include "CitiesDialog.h"
#include "PhonesCListCtrlDialog.h"


// CPersonDialog dialog

IMPLEMENT_DYNAMIC(CPersonDialog, CDialog)

CPersonDialog::CPersonDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSON_DIALOG, pParent)
{

}
CPersonDialog::CPersonDialog(int nHint /*= 0*/, CPerson* pPerson /*=nullptr*/, CPhoneTypesTypedPtrArray* pPhoneTypeArray /*=nullptr*/, CCitiesTypedPtrArray* pCitiesArray /*=nullptr*/, CWnd* pParent /*=nullptr*/)
	:CDialog(IDD_PERSON_DIALOG, pParent), m_recPerson(pPerson), m_oCitiesArray(pCitiesArray), m_nHint(nHint), m_oPhoneTypes(pPhoneTypeArray)
{

}


CPersonDialog::~CPersonDialog()
{
}

void CPersonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_EDB_PERSON_NAME, m_editPersonName);
	DDX_Control(pDX, IDC_EDB_PERSON_SURNAME, m_editPersonSurname);
	DDX_Control(pDX, IDC_EDB_PERSON_FAMILY, m_editPersonFamily);
	DDX_Control(pDX, IDC_EDB_PERSON_UCN, m_editPersonUCN);
	DDX_Control(pDX, IDC_CMB_PERSON_CITY, m_comboBoxPersonCity);
	DDX_Control(pDX, IDC_LIC_PERSON_PHONE_NUMBERS, m_LstCtrlPhoneNumbers);
}



BOOL CPersonDialog::OnInitDialog() {
	CDialog::OnInitDialog();
	// Additional initialization logic 
	CDataExchange dataExhange(this, TRUE);
	DoDataExchange(&dataExhange);


	m_LstCtrlPhoneNumbers.SetExtendedStyle(m_LstCtrlPhoneNumbers.GetExtendedStyle() | LVS_EX_GRIDLINES);

	//Insert the columns

	m_LstCtrlPhoneNumbers.InsertColumn(ListCtrPhoneNumbers, _T("Тел"), LVCFMT_LEFT, 200);
	m_LstCtrlPhoneNumbers.InsertColumn(ListCtrlPhoneTypes, _T("Вид"), LVCFMT_LEFT, 200);

	switch (m_nHint) {
	case DialogUpdateHint:
		SetDialogTitle(L"Обнови абонат");
		SetDialogFields(m_recPerson);
		SetCitiesComboBox(m_oCitiesArray);
		break;
	case DialogInsertHint:
		SetDialogTitle(L"Добави абонат");
		SetCitiesComboBox(m_oCitiesArray);


		break;
	case DialogReadOnlyHint:
		SetDialogTitle(L"Абонат");
		SetDialogFields(m_recPerson);
		SetReadOnlyControls();


		CWnd* pOKButton = GetDlgItem(IDOK);
		if (pOKButton)
			pOKButton->ShowWindow(SW_HIDE);
		break;
	}

	return TRUE;
}

void CPersonDialog::SetDialogTitle(const CString& title)
{
	SetWindowText(title);
}

void CPersonDialog::GetDialogFields(CPerson& recPerson) {


	//Get the person name from dialog
	CString strPersonName;
	m_editPersonName.GetWindowText(strPersonName);
	lstrcpy(recPerson.recPerson.szName, strPersonName);

	// Get person surname from dialog
	CString strPersonSurname;
	m_editPersonSurname.GetWindowText(strPersonSurname);
	lstrcpy(recPerson.recPerson.szSurname, strPersonSurname);

	// Get person family from dialog
	CString strPersonFamily;
	m_editPersonFamily.GetWindowText(strPersonFamily);
	lstrcpy(recPerson.recPerson.szFamily, strPersonFamily);

	// Get person UCN from dialog
	CString strPersonUCN;
	m_editPersonUCN.GetWindowText(strPersonUCN);
	lstrcpy(recPerson.recPerson.szUCN, strPersonUCN);

	// Create varaible to store the city name and it's id
	long lPersonCityId;
	CString strPersonCity;

	//Get text from combo box and set it to the person 
	m_comboBoxPersonCity.GetWindowText(strPersonCity);
	recPerson.strCityName = strPersonCity;

	//Get the combo box item data
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_CMB_PERSON_CITY);
	int selectedIndex = pComboBox->GetCurSel();
	//Get the city id
	lPersonCityId = m_comboBoxPersonCity.GetItemData(selectedIndex);
	//Set the city id to the person
	recPerson.recPerson.lCityId = lPersonCityId;


	// Get number of CListCtrl
	int nItemCount = m_LstCtrlPhoneNumbers.GetItemCount();
	//Create new phone number
	// Enum for columns
	enum {
		PhoneNumber,
		PhoneType
	};

	//Iterate the columns
	for (int nColumn = 0; nColumn < nItemCount; ++nColumn) {
		PHONE_NUMBERS* newPhoneNumber = new PHONE_NUMBERS;

		//Get phone number from first column
		CString strPhoneNumber = m_LstCtrlPhoneNumbers.GetItemText(nColumn, PhoneNumber);
		//Get phone type from second column
		CString strPhoneType = m_LstCtrlPhoneNumbers.GetItemText(nColumn, PhoneType); // Assuming data from column 2

		// Set the phone number to the object phone number
		lstrcpy(newPhoneNumber->szPhoneNumber, strPhoneNumber);

		//Iterate the phone types we get from constructor
		for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypes->GetCount(); nIndex++)
		{
			//Where the the phonetype from ListCtrl is the same with phone type of array from constructor
			if (strPhoneType == m_oPhoneTypes->GetAt(nIndex)->szPhoneType) {
				// Set the phone number field to be equal to phone type from array
				newPhoneNumber->lPhoneTypeId = m_oPhoneTypes->GetAt(nIndex)->lId;
				// Add phone type to person
				recPerson.personPhoneTypes.Add(m_oPhoneTypes->GetAt(nIndex));
				break;
			}

		}
		// Add phone number to person
		recPerson.personPhoneNumbers.Add(newPhoneNumber);

	}



}

CPerson& CPersonDialog::GetPersonDataFromDialog()
{
	return recPersonForReturn;
}


void CPersonDialog::SetDialogFields(CPerson* pPerson) {

	if (pPerson == nullptr) {
		return;
	}
	m_editPersonName.SetWindowText(pPerson->GetPerson().szName);
	m_editPersonSurname.SetWindowText(pPerson->GetPerson().szSurname);
	m_editPersonFamily.SetWindowText(pPerson->GetPerson().szFamily);
	m_editPersonUCN.SetWindowText(pPerson->GetPerson().szUCN);
	m_comboBoxPersonCity.SetWindowText(pPerson->strCityName);

	int nItemCount = pPerson->personPhoneNumbers.GetCount();

	for (int nIndex = 0; nIndex < nItemCount; nIndex++)
	{
		PHONE_NUMBERS* pRecCurrentPhoneNumber = pPerson->personPhoneNumbers.GetAt(nIndex);
		m_LstCtrlPhoneNumbers.InsertItem(nIndex, pRecCurrentPhoneNumber->szPhoneNumber);
		for (INT_PTR nIndx = 0; nIndx < pPerson->personPhoneTypes.GetCount(); nIndx++)
		{
			PHONE_TYPES* pRecPhoneType = pPerson->personPhoneTypes.GetAt(nIndx);
			if (pRecPhoneType && pRecCurrentPhoneNumber->lPhoneTypeId == pRecPhoneType->lId) {

				m_LstCtrlPhoneNumbers.SetItemText(nIndex, ListCtrlPhoneTypes, pRecPhoneType->szPhoneType);
				break;
			}
		}
	}


}

void CPersonDialog::SetReadOnlyControls() {
	m_editPersonName.SetReadOnly(TRUE);
	m_editPersonSurname.SetReadOnly(TRUE);
	m_editPersonFamily.SetReadOnly(TRUE);
	m_editPersonUCN.SetReadOnly(TRUE);
	m_comboBoxPersonCity.EnableWindow(FALSE);
	m_LstCtrlPhoneNumbers.ModifyStyle(0, LVS_SINGLESEL);
}

void CPersonDialog::SetCitiesComboBox(CCitiesTypedPtrArray* oCitiesArray)
{
	if (oCitiesArray != nullptr) {
		for (INT_PTR nIndex = 0; nIndex < oCitiesArray->GetCount(); nIndex++)
		{
			CString strCurrentCity = oCitiesArray->GetAt(nIndex)->szCityName;
			int nIdx = m_comboBoxPersonCity.AddString(strCurrentCity);
			m_comboBoxPersonCity.SetItemData(nIdx, oCitiesArray->GetAt(nIndex)->lId);
		}
	}
}


bool CPersonDialog::ValidateFields(CEdit& editControl) {
	CString fieldValue;
	editControl.GetWindowText(fieldValue);

	if (!m_validator.IsAlphaString(fieldValue)) {
		CString message;
		message.Format(_T("Validation failed for field."));
		AfxMessageBox(message, MB_ICONWARNING);
		return false;
	}
	return true;
}


void CPersonDialog::OnOK()
{

	////Validation the fields of dialog if they are empty
	//if (!ValidateFields(m_editPersonName) ||
	//	!ValidateFields(m_editPersonSurname) ||
	//	!ValidateFields(m_editPersonFamily) ||
	//	!ValidateFields(m_editPersonUCN)) {
	//	// Validation failed, do not close the dialog
	//	return;
	//}




	GetDialogFields(recPersonForReturn);





	CDialog::OnOK();
}



BEGIN_MESSAGE_MAP(CPersonDialog, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIC_PERSON_PHONE_NUMBERS, &CPersonDialog::OnLvnItemchangedList1)
	ON_EN_CHANGE(IDC_EDB_PERSON_CITY, &CPersonDialog::OnEnChangeEdbPersonCity)
	ON_CBN_SELCHANGE(IDC_CMB_PERSON_CITY, &CPersonDialog::OnCbnSelchangeCombo1)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DIALOGCONTEXTMENU_INSERT, &CPersonDialog::OnAdd)
	ON_COMMAND(ID_DIALOGCONTEXTMENU_DELETE, &CPersonDialog::OnDelete)
END_MESSAGE_MAP()

void CPersonDialog::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Context menu popup
	OnContextMenu(this, point);
}


void CPersonDialog::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

	// Load the context menu from the resource
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU_DIALOG);

	CMenu* pContextMenu = menu.GetSubMenu(0);
	//oburni
	if (!pContextMenu)
	{
		return;
	}
	// Check if an item is selected on the display
	int nSelectedItem = m_LstCtrlPhoneNumbers.GetNextItem(-1, LVNI_SELECTED);

	// If there is a selection, enable update and delete menu items and perform these actions
	if (nSelectedItem >= 0)
	{
		pContextMenu->EnableMenuItem(ID_DIALOGCONTEXTMENU_INSERT, MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_DIALOGCONTEXTMENU_DELETE, MF_ENABLED);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		// Perform the action for selected item

	}
	// No item is selected, enable/disable relevant menu items and perform other action
	else
	{
		pContextMenu->EnableMenuItem(ID_DIALOGCONTEXTMENU_INSERT, MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_DIALOGCONTEXTMENU_DELETE, MF_GRAYED);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}
// CPersonDialog message handlers
void CPersonDialog::OnAdd() {

	CString strPhoneNumber;
	CString strPhoneType;
	// Implement code to add a new item 
	CPhonesCListCtrlDialog oPhoneNumberDialog(m_oPhoneTypes);

	if (oPhoneNumberDialog.DoModal() == IDOK) {
		int nIndex = m_LstCtrlPhoneNumbers.GetItemCount();
		m_LstCtrlPhoneNumbers.InsertItem(nIndex, oPhoneNumberDialog.m_strPhoneNumber);
		m_LstCtrlPhoneNumbers.SetItemText(nIndex, ListCtrlPhoneTypes, oPhoneNumberDialog.m_strPhoneType);

	}


}


void CPersonDialog::OnDelete() {
	POSITION pos = m_LstCtrlPhoneNumbers.GetFirstSelectedItemPosition();
	if (pos) {
		int nIndex = m_LstCtrlPhoneNumbers.GetNextSelectedItem(pos);
		m_LstCtrlPhoneNumbers.DeleteItem(nIndex);
	}
}



void CPersonDialog::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CPersonDialog::OnEnChangeEdbPersonCity()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CPersonDialog::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}



