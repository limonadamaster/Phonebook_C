#include <cstdlib>
#include "pch.h"
#include "framework.h"
#include "PersonDoc.h"
#include "PersonView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#ifndef SHARED_HANDLERS
#include "PhoneBookLts.h"
#endif
#include "PersonDialog.h"

// Messages for delete operation using message box
#define ON_DELETE_MESSAGE_BOX_CAPTION	_T("Изтриване на лчиност")
#define ON_DELETE_MESSAGE_BOX_TEXT _T("Сигурни ли сте, че искате да изтриете избраната личност?")


// CRUD Operations
enum
{
	ON_UPDATE,
	ON_INSERT,
	ON_DELETE,
};

/////////////////////////////////////////////////////////////////////////////
// CPersonView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CPersonView, CListView)
BEGIN_MESSAGE_MAP(CPersonView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, OnContextUpdate)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, OnContextInsert)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, OnContextDelete)
	ON_NOTIFY(NM_DBLCLK, AFX_IDW_PANE_FIRST, ShowRecord)
END_MESSAGE_MAP();


// Constructor / Destructor
// ----------------
CPersonView::CPersonView() noexcept
{
}

CPersonView::~CPersonView()
{
}

// Methods
// ----------------

void CPersonView::OnInitialUpdate()
{
	//Call the method of parent class
	__super::OnInitialUpdate();
	//Create the columns
	ShowOnCreate();


	//Get docuemnt
	GetDocument();


}

void CPersonView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Context menu popup
	OnContextMenu(this, point);
}


void CPersonView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

	// Load the context menu from the resource
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);

	CMenu* pContextMenu = menu.GetSubMenu(0);
	//oburni
	if (!pContextMenu)
	{
		return;
	}
	// Check if an item is selected on the display
	int nSelectedItem = m_oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// If there is a selection, enable update and delete menu items and perform these actions
	if (nSelectedItem >= 0)
	{
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_UPDATE, MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_INSERT, MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DELETE, MF_ENABLED);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		// Perform the action for selected item

	}
	// No item is selected, enable/disable relevant menu items and perform other action
	else
	{
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_UPDATE, MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_INSERT, MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DELETE, MF_GRAYED);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CPersonView::OnContextUpdate()
{
	// Get the selected item data from CListCtrl
	CPerson* pPerson = GetSelectedItemData();

	/// Check if Personn exists, if not never open dialog
	if (pPerson == nullptr) {
		return;
	}

	//Array of cities and phone types for combox
	CCitiesTypedPtrArray* pArrayForComboBox = &GetDocument()->CitiesArrayForComboBox();
	CPhoneTypesTypedPtrArray* pArrayForInserDialogComboBox = &GetDocument()->PhoneTypedForInsertDialogComboBox();

	CPersonDialog oUpdateDialog(DialogUpdateHint, pPerson, pArrayForInserDialogComboBox, pArrayForComboBox);


	HRESULT nResponse = oUpdateDialog.DoModal();

	if (nResponse == IDOK)
	{
		// Get the data entered by the user from the dialog

		GetDocument()->Update(pPerson->recPerson.lId, *pPerson, oUpdateDialog.GetPersonDataFromDialog());
	}


}

void CPersonView::OnContextInsert()
{
	// Create the insert dialog and pass the newCity object to it
	CPerson oPersonForFill;
	oPersonForFill.GetPerson().lId = 0;
	//Аrray of cities and phonetypes for combox
	CCitiesTypedPtrArray* pArrayForComboBox = &GetDocument()->CitiesArrayForComboBox();
	CPhoneTypesTypedPtrArray* pArrayForInserDialogComboBox = &GetDocument()->PhoneTypedForInsertDialogComboBox();
	CPersonDialog oInsertDialog(DialogInsertHint, nullptr, pArrayForInserDialogComboBox, pArrayForComboBox);

	//// Display the insert dialog
	INT_PTR nResponse = oInsertDialog.DoModal();

	// Check if the user clicked the "OK" button in the dialog
	if (nResponse == IDOK)
	{
		// Perform the insert operation
		GetDocument()->Insert(oInsertDialog.GetPersonDataFromDialog());
	}
}

void CPersonView::OnContextDelete()
{

	int nResult = MessageBox(ON_DELETE_MESSAGE_BOX_TEXT, ON_DELETE_MESSAGE_BOX_CAPTION, MB_YESNO | MB_ICONQUESTION);
	CPerson* pPersons = GetSelectedItemData();
	//Chech the reponse
	if (nResult != IDYES)
	{
		return;
	}
	//Perform the opration
	GetDocument()->Delete(*pPersons);

}

void CPersonView::CListCtrlUpdate()
{

}

void CPersonView::CListCtrlInsert()
{

	//Create new variables, object props
	//Get array storage length
	long lIndex = GetDocument()->m_oPersonDataTypedArray.GetCount();

	// Create new city pointer
	CPerson* pPerson = NULL;

	//Get the last empty place
	pPerson = GetDocument()->m_oPersonDataTypedArray[lIndex - 1];

	//Check if is NULL
	if (pPerson == NULL) {
		return;
	}

	// Insert new record in CListCtrl
	int nItemIndex = m_oListCtrl.InsertItem(lIndex, pPerson->recPerson.szName);
	//Insert city district to the second column
	m_oListCtrl.SetItemText(nItemIndex, PersonColumnSurname, pPerson->recPerson.szSurname);
	m_oListCtrl.SetItemText(nItemIndex, PersonColumnFamily, pPerson->recPerson.szFamily);
	m_oListCtrl.SetItemText(nItemIndex, PersonColumnUCN, pPerson->recPerson.szUCN);
	m_oListCtrl.SetItemText(nItemIndex, PersonColumCityId, pPerson->strCityName);

	//Set city data
	m_oListCtrl.SetItemData(nItemIndex, (DWORD_PTR)pPerson);
}

void CPersonView::CListCtrlDelete()
{
	//Fined selected item in CListCtrl
	long lItemIndex = GetSelectedItemIndex();
	//Delete it
	m_oListCtrl.DeleteItem(lItemIndex);
}

long CPersonView::GetSelectedItemIndex()
{

	//Create a variable which will store the selected data
	DWORD_PTR pCurrentData;

	//Itterate trough CListCtrl
	for (long lItemIndex = 0; lItemIndex < m_oListCtrl.GetItemCount(); lItemIndex++) {

		//Find selected item
		if (m_oListCtrl.GetItemState(lItemIndex, LVIS_SELECTED) == LVIS_SELECTED) {

			return lItemIndex;
		}
	}


	return -1;
}

CPerson* CPersonView::GetSelectedItemData()
{
	// Find index from selected item from CListCtrl
	long lSelectedItemIndex = GetSelectedItemIndex();
	if (lSelectedItemIndex != -1) {

		DWORD_PTR pCurrentData = m_oListCtrl.GetItemData(lSelectedItemIndex);

		//Cast it to the coorect type
		CPerson* pCurrentPerson = (CPerson*)pCurrentData;
		//Return data
		return pCurrentPerson;

	}

	return nullptr;
}

void CPersonView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
{

	//Cehck for update
	// Switch construction to perfrom diffrent operaions
	switch (lHint)
	{
	case ON_UPDATE:
		CListCtrlUpdate();
		break;

	case ON_INSERT:
		CListCtrlInsert();
		break;

	case ON_DELETE:
		CListCtrlDelete();
		break;
	}
}

void CPersonView::ShowRecord(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Get the selected item data from CListCtrl
	CPerson* pPerson = GetSelectedItemData();

	/// Check if Personn exists, if not never open dialog
	if (pPerson == nullptr) {
		return;
	}

	CPersonDialog oSingleRecordDialog(DialogReadOnlyHint, pPerson);


	oSingleRecordDialog.DoModal();


	*pResult = 0;
}

void CPersonView::ShowOnCreate() {

	// Set styles to CListTrl
	m_oListCtrl.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
	m_oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//Insert the columns
	m_oListCtrl.InsertColumn(PersonColumnName, _T("Име"), LVCFMT_LEFT, 150);
	m_oListCtrl.InsertColumn(PersonColumnSurname, _T("Презиме"), LVCFMT_LEFT, 150);
	m_oListCtrl.InsertColumn(PersonColumnFamily, _T("Фамилия"), LVCFMT_LEFT, 150);
	m_oListCtrl.InsertColumn(PersonColumnUCN, _T("ЕГН"), LVCFMT_LEFT, 150);
	m_oListCtrl.InsertColumn(PersonColumCityId, _T("Град"), LVCFMT_LEFT, 150);


	// Create variables
	CString strEmpty;
	strEmpty = _T(" ");
	long lIndex = 0;
	CString strId, strUpdateCounter;




	//Check if CListCtrl exists and clean it 
	//TODO
	if (!m_oListCtrl.DeleteAllItems())
	{
		return;
	}

	//Inser one empty item
	m_oListCtrl.SetItemText(lIndex, PersonColumnName, strEmpty);
	m_oListCtrl.SetItemText(lIndex, PersonColumnSurname, strEmpty);
	m_oListCtrl.SetItemText(lIndex, PersonColumnFamily, strEmpty);
	m_oListCtrl.SetItemText(lIndex, PersonColumnUCN, strEmpty);
	m_oListCtrl.SetItemText(lIndex, PersonColumCityId, strEmpty);


	//Iterate trough cities array and the records to CListCtrl
	for (INT_PTR nIndex = 0; nIndex < GetDocument()->m_oPersonDataTypedArray.GetCount(); nIndex++) {

		//Get pointer to ciry from array
		CPerson* pCurrentPerson = GetDocument()->m_oPersonDataTypedArray[nIndex];

		if (pCurrentPerson == NULL) {
			break;
		}
		//Insert city name at the first column and get its index
		int nItemIndex = m_oListCtrl.InsertItem(nIndex, pCurrentPerson->GetPerson().szName);
		//Insert city district to the second column
		m_oListCtrl.SetItemText(nItemIndex, PersonColumnSurname, pCurrentPerson->GetPerson().szSurname);
		m_oListCtrl.SetItemText(nItemIndex, PersonColumnFamily, pCurrentPerson->GetPerson().szFamily);
		m_oListCtrl.SetItemText(nItemIndex, PersonColumnUCN, pCurrentPerson->GetPerson().szUCN);
		m_oListCtrl.SetItemText(nItemIndex, PersonColumCityId, pCurrentPerson->strCityName);
		//Set city pointer to index
		m_oListCtrl.SetItemData(nItemIndex, reinterpret_cast<DWORD_PTR>(pCurrentPerson));
	};

}
PERSONS& CPersonView::GetPerson()
{
	// Return the city member
	return m_recPerson;
}



// CPersonView diagnostics

#ifdef _DEBUG
void CPersonView::AssertValid() const
{
	CListView::AssertValid();
}

void CPersonView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPersonDoc* CPersonView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonDoc)));
	return (CPersonDoc*)m_pDocument;
}
#endif //_DEBUG


// CPersonView message handlers
