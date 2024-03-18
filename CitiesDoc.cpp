#include "pch.h"
#include "framework.h"
#include "CitiesDoc.h"
#include <propkey.h>

#ifndef SHARED_HANDLERS
#include "PhoneBookLts.h"
#endif


// Hints for UpdateAllViews method
enum {
	HINT_UPDATE,
	HINT_INSERT,
	HINT_DELETE,
};


/////////////////////////////////////////////////////////////////////////////
// CCitiesDoc


// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)
BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CCitiesDoc::CCitiesDoc() noexcept
{
}

CCitiesDoc::~CCitiesDoc()
{
}

// Methods
// ----------------

BOOL CCitiesDoc::SelectRecord(long lId, CITIES& recCities) {

	// Call model to perform select 
	BOOL bFlag = m_oCitiesDataModel.SelectWhereIdFromCities(lId, recCities);
	// Check if select is not successful
	if (bFlag == FALSE)
	{
		return FALSE;
	}
	// Update the views and return
	return TRUE;

}

BOOL CCitiesDoc::Update(long ID, CITIES& recCities)
{
	// Call model and perform the update
	BOOL bFlag = m_oCitiesDataModel.UpdateWhereID(ID, recCities);
	//Check the update is not successful
	if (bFlag == FALSE)
	{
		return FALSE;
	}

	//Iterate trough the array store 
	for (long i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		//Find the corespondenting record in the array
		if (m_oCitiesArray[i]->lId == ID)
		{
			//Update properties of the finded record from array
			m_oCitiesArray[i]->lUpdateCounter = recCities.lUpdateCounter;
			wcscpy_s(m_oCitiesArray[i]->szCityName, recCities.szCityName);
			wcscpy_s(m_oCitiesArray[i]->szDistrict, recCities.szDistrict);
			break;
		}
	}
	//Update the view using update hint
	UpdateAllViews(NULL, HINT_UPDATE);
	return TRUE;
}

BOOL CCitiesDoc::Insert(CITIES& recCities)
{
	// Call model and perform the insert 
	BOOL bFlag = m_oCitiesDataModel.InsertInCities(recCities);
	//Check if insert operation is succesful
	if (bFlag != FALSE)
	{

		//Create new city pointer
		CITIES* pCities = new CITIES();
		//Update the new record properties
		*pCities = recCities;
		//Add the record to the application starage - array
		m_oCitiesArray.Add(pCities);
		//Update the view using insert hint
		UpdateAllViews(NULL, HINT_INSERT);

		return TRUE;
	}

	return FALSE;
}


BOOL CCitiesDoc::Delete(long ID)
{
	//Call model and perform the delte 
	BOOL bFlag = m_oCitiesDataModel.DeleteWhereIdInCities(ID);
	//Check if delete operation is succesful
	if (!bFlag)
	{
		return FALSE;
	}

	//Iterate trough the array store
	for (long lIndex = 0; lIndex < m_oCitiesArray.GetCount(); lIndex++)
	{
		//Find the corespondenting record in array 
		if (m_oCitiesArray[lIndex]->lId == ID)
		{
			// Remove finded elemnt form array
			m_oCitiesArray.RemoveAt(lIndex);
		}
	}

	//Update the view using delte hint
	UpdateAllViews(NULL, HINT_DELETE);

	return TRUE;
}


BOOL CCitiesDoc::OnNewDocument()
{
	// Inherit the method from parent
	if (!__super::OnNewDocument())
		return FALSE;


	//Fill the array with records from DataBase using model class
	m_oCitiesDataModel.SelectAllFromCities(m_oCitiesArray);

	return TRUE;
}

// CCitiesDoc serialization

void CCitiesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCitiesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCitiesDoc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
