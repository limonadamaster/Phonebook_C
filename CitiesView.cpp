#include <cstdlib>
#include "pch.h"
#include "framework.h"
#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CitiesDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#ifndef SHARED_HANDLERS
#include "PhoneBookLts.h"
#endif

// Messages for delete operation using message box
#define ON_DELETE_MESSAGE_BOX_CAPTION	_T("Изтриване на град")
#define ON_DELETE_MESSAGE_BOX_TEXT _T("Сигурни ли сте, че искате да изтриете избрания град?")


// CRUD Operations
enum
{
	ON_UPDATE,
	ON_INSERT,
	ON_DELETE,
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCitiesView, CListView)
BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, OnContextUpdate)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, OnContextInsert)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, OnContextDelete)
	ON_NOTIFY(NM_DBLCLK, AFX_IDW_PANE_FIRST, ShowRecord)
END_MESSAGE_MAP();


// Constructor / Destructor
// ----------------
CCitiesView::CCitiesView() noexcept
{
}

CCitiesView::~CCitiesView()
{
}

// Methods
// ----------------

void CCitiesView::OnInitialUpdate()
{
	//Call the method of parent class
	__super::OnInitialUpdate();
	//Create the columns
	ShowOnCreate();
	//Get docuemnt
	GetDocument();
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Context menu popup
	OnContextMenu(this, point);
}


void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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

void CCitiesView::OnContextUpdate()
{
	// Handle the "Update" menu item selection for CListCtrl

	//Create dialog for upadate
	//Create varable for Id  and UpdateCounter
	CITIES* pCity;
	long lUpdateCounter = 0;
	//Find the item slected row from CListCtrl
	pCity = GetSelectedItemData();
	//Check if the id is zero
	if (pCity == nullptr) {
		return;
	}
	//Take data from pointer
	CITIES recCity = *pCity;
	//Create dialog
	CCitiesDialog oUpdateDialog(DialogUpdateHint, recCity);

	//Iterate trough the array of cities 
	for (long i = 0; i < GetDocument()->m_oCitiesArray.GetCount(); i++)

		// Check for match between the two IDs
		if (GetDocument()->m_oCitiesArray[i]->lId == pCity->lId)
		{
			// Get the update counter
			lUpdateCounter = GetDocument()->m_oCitiesArray[i]->lUpdateCounter;
			// Fill the fields of the dialog with the city data
			break;
		}

	//Open update dialog
	INT_PTR nResopnse = oUpdateDialog.DoModal();

	//Check the response
	if (nResopnse != IDOK) {
		return;
	}
	// Set the data
	GetCities().lId = pCity->lId;
	GetCities().lUpdateCounter = lUpdateCounter;
	lstrcpy(GetCities().szCityName, oUpdateDialog.ReturnCityName());
	lstrcpy(GetCities().szDistrict, oUpdateDialog.ReturnDistrictName());
	// Perform update operation
	GetDocument()->Update(pCity->lId, GetCities());

}

void CCitiesView::OnContextInsert() {

	// Set the ID to zero
	GetCities().lId = 0;

	// Create the insert dialog and pass the newCity object to it
	CCitiesDialog oInsertDialog(DialogInsertHint, GetCities());


	// Display the insert dialog
	INT_PTR nResponse = oInsertDialog.DoModal();

	// Check if the user clicked the "OK" button in the dialog
	if (nResponse == IDOK)
	{
		// Get the data entered by the user from the dialog
		lstrcpy(GetCities().szCityName, oInsertDialog.ReturnCityName());
		lstrcpy(GetCities().szDistrict, oInsertDialog.ReturnDistrictName());
		// Perform the insert operation
		GetDocument()->Insert(GetCities());
	}
}
void CCitiesView::OnContextDelete()
{
	// Handle the "Delete" menu item selection for CCtrList

	//Createe message box to ask user if he i ssure he want to delte record
	int nResult = MessageBox(ON_DELETE_MESSAGE_BOX_TEXT, ON_DELETE_MESSAGE_BOX_CAPTION, MB_YESNO | MB_ICONQUESTION);
	CITIES* pCity = GetSelectedItemData();
	//Chech the reponse
	if (nResult != IDYES)
	{
		return;
	}
	//Perform the opration
	GetDocument()->Delete(pCity->lId);
}

void CCitiesView::CListCtrlUpdate()
{
	//Create variable
	long lArraySize;
	//Find selected item from CListCtrl
	CITIES* pCity = GetSelectedItemData();
	//Check for finded data
	if (pCity == nullptr) {
		return;
	}
	//Find selected index from CListCtrl
	long lItemIndex = GetSelectedItemIndex();
	if (lItemIndex == -1) {
		return;
	}
	// Get document array memeber size
	lArraySize = GetDocument()->m_oCitiesArray.GetCount();

	// Iterate through array storage and update record there
	for (long lIndex = 0; lIndex < lArraySize; lIndex++)

		//Find selected 
		if (GetDocument()->m_oCitiesArray[lIndex]->lId == pCity->lId)
		{
			//Change data into display
			m_oListCtrl.SetItemText(lItemIndex, CitiesColumnsName, GetDocument()->m_oCitiesArray[lIndex]->szCityName);
			m_oListCtrl.SetItemText(lItemIndex, CitiesColumnsDistrict, GetDocument()->m_oCitiesArray[lIndex]->szDistrict);
			break;
		}
}

void CCitiesView::CListCtrlInsert()
{

	//Create new variables, object props
	//Get array storage length
	long lIndex = GetDocument()->m_oCitiesArray.GetCount();

	// Create new city pointer
	CITIES* pCities = NULL;

	//Get the last empty place
	pCities = GetDocument()->m_oCitiesArray[lIndex - 1];

	//Check if is NULL
	if (pCities == NULL) {
		return;
	}

	// Insert new record in CListCtrl
	int nItemIndex = m_oListCtrl.InsertItem(lIndex, pCities->szCityName);
	//Insert city district to the second column
	m_oListCtrl.SetItemText(nItemIndex, CitiesColumnsDistrict, pCities->szDistrict);
	//Set city data
	m_oListCtrl.SetItemData(nItemIndex, reinterpret_cast<DWORD_PTR>(pCities));
}

void CCitiesView::CListCtrlDelete()
{
	//Fined selected item in CListCtrl
	long lItemIndex = GetSelectedItemIndex();
	//Delete it
	m_oListCtrl.DeleteItem(lItemIndex);
}

long CCitiesView::GetSelectedItemIndex()
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

CITIES* CCitiesView::GetSelectedItemData()
{
	// Find index from selected item from CListCtrl
	long lSelectedItemIndex = GetSelectedItemIndex();
	if (lSelectedItemIndex != -1) {

		DWORD_PTR pCurrentData = m_oListCtrl.GetItemData(lSelectedItemIndex);

		//Cast it to the coorect type
		CITIES* pCurrentCity = reinterpret_cast<CITIES*>(pCurrentData);
		//Return data
		return pCurrentCity;

	}

	return nullptr;
}

void CCitiesView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
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

void CCitiesView::ShowRecord(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Get the selected item data from CListCtrl
	CITIES* pCity = GetSelectedItemData();

	if (pCity == nullptr) {
		return;
	}

	CITIES cityData;

	GetDocument()->SelectRecord(pCity->lId, cityData);


	CCitiesDialog oSingleRecordDialog(DialogReadOnlyHint, cityData);


	oSingleRecordDialog.DoModal();


	*pResult = 0;
}

void CCitiesView::ShowOnCreate() {

	// Set styles to CListTrl
	m_oListCtrl.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
	m_oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//Insert the columns
	m_oListCtrl.InsertColumn(CitiesColumnsName, _T("Име"), LVCFMT_LEFT, 150);
	m_oListCtrl.InsertColumn(CitiesColumnsDistrict, _T("Област"), LVCFMT_LEFT, 150);

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
	m_oListCtrl.SetItemText(lIndex, CitiesColumnsName, strEmpty);
	m_oListCtrl.SetItemText(lIndex, CitiesColumnsDistrict, strEmpty);

	//Iterate trough cities array and the records to CListCtrl
	for (INT_PTR nIndex = 0; nIndex < GetDocument()->m_oCitiesArray.GetCount(); nIndex++) {

		//Get pointer to ciry from array
		CITIES* pCurrentCity = GetDocument()->m_oCitiesArray[nIndex];

		if (pCurrentCity == NULL) {
			break;
		}
		//Insert city name at the first column and get its index
		int nItemIndex = m_oListCtrl.InsertItem(nIndex, pCurrentCity->szCityName);
		//Insert city district to the second column
		m_oListCtrl.SetItemText(nItemIndex, CitiesColumnsDistrict, pCurrentCity->szDistrict);
		//Set city pointer to index
		m_oListCtrl.SetItemData(nItemIndex, reinterpret_cast<DWORD_PTR>(pCurrentCity));
	};

}
CITIES& CCitiesView::GetCities()
{
	// Return the city member
	return m_recCities;
}



// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers
