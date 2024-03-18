#include "pch.h"
#include "framework.h"
#include "PersonDoc.h"
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
// CPersonDoc


// Macros
// ----------------
IMPLEMENT_DYNCREATE(CPersonDoc, CDocument)
BEGIN_MESSAGE_MAP(CPersonDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CPersonDoc::CPersonDoc() noexcept
{
}

CPersonDoc::~CPersonDoc()
{
}

// Methods
// ----------------

BOOL CPersonDoc::SelectRecord(long lId, PERSONS& recPerson) {

	// Call model to perform select 
	BOOL bFlag = m_oPersonDataModel.SelectWhereIdFromPersons(lId, recPerson);
	// Check if select is not successful
	if (bFlag == FALSE)
	{
		return FALSE;
	}
	// Update the views and return
	return TRUE;

}

BOOL CPersonDoc::Update(long ID, CPerson& recPersonOld, CPerson& recPersonNew)
{
	// Call model and perform the update
	BOOL bFlag = m_oPersonDataModel.UpdateDataFromDB(recPersonOld, recPersonNew);
	//Check the update is not successful
	if (bFlag == FALSE)
	{
		return FALSE;
	}

	//Iterate trough the array store 
	for (long i = 0; i < m_oPersonArray.GetCount(); i++)
	{
		//Find the corespondenting record in the array
		if (m_oPersonDataTypedArray[i]->GetPerson().lId == ID)
		{
			//Update properties of the finded record from array
			m_oPersonArray[i]->lUpdateCounter = recPersonNew.GetPerson().lUpdateCounter;
			wcscpy_s(m_oPersonArray[i]->szName, recPersonNew.GetPerson().szName);
			wcscpy_s(m_oPersonArray[i]->szSurname, recPersonNew.GetPerson().szSurname);
			wcscpy_s(m_oPersonArray[i]->szFamily, recPersonNew.GetPerson().szFamily);
			wcscpy_s(m_oPersonArray[i]->szUCN, recPersonNew.GetPerson().szUCN);
			m_oPersonArray[i]->lCityId = recPersonNew.GetPerson().lCityId;

			break;
		}
	}
	//Update the view using update hint
	UpdateAllViews(NULL, HINT_UPDATE);
	return TRUE;
}

BOOL CPersonDoc::Insert(CPerson& recPerson)
{
	// Call model and perform the insert 
	BOOL bFlag = m_oPersonDataModel.InsertCPersonDataIntoDB(recPerson);
	//Check if insert operation is succesful
	if (bFlag != FALSE)
	{

		//Add the record to the application starage - array
		CPerson* newPerson = &recPerson;
		m_oPersonDataTypedArray.Add(newPerson);
		//Update the view using insert hint
		UpdateAllViews(NULL, HINT_INSERT);

		return TRUE;
	}

	return FALSE;
}



BOOL CPersonDoc::Delete(CPerson& recCPerson)
{
	//Call model and perform the delte 
	BOOL bFlag = m_oPersonDataModel.DelteteDataFromDB(recCPerson);
	//Check if delete operation is succesful
	if (!bFlag)
	{
		return FALSE;
	}

	//Iterate trough the array store
	for (long lIndex = 0; lIndex < m_oPersonArray.GetCount(); lIndex++)
	{
		//Find the corespondenting record in array 
		if (m_oPersonDataTypedArray[lIndex]->GetPerson().lId == recCPerson.GetPerson().lId)
		{
			// Remove finded elemnt form array
			m_oPersonDataTypedArray.RemoveAt(lIndex);
		}
	}

	//Update the view using delte hint	
	UpdateAllViews(NULL, HINT_DELETE);

	return TRUE;
}

// In your document class implementation (.cpp) file
BOOL CPersonDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// Display the Open File dialog
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

	if (fileDlg.DoModal() == IDOK)
	{
		// Get the selected file path
		CString filePath = fileDlg.GetPathName();

		// Now you have the file path in the 'filePath' variable.
		// You can do further processing with the file here.

		// Return TRUE to indicate that the document was successfully opened.
		return TRUE;
	}

	// Return FALSE to indicate that the document was not opened.
	return FALSE;
}


CCitiesTypedPtrArray& CPersonDoc::CitiesArrayForComboBox()
{
	return m_oPersonDataModel.GetCities();
}

CPhoneTypesTypedPtrArray& CPersonDoc::PhoneTypedForInsertDialogComboBox()
{
	return m_oPersonDataModel.GetPhoneTypes();
}


BOOL CPersonDoc::OnNewDocument()
{
	// Inherit the method from parent
	if (!__super::OnNewDocument())
		return FALSE;


	//Fill the array with records from DataBase using model class
	m_oPersonDataModel.CreatePersons(m_oPersonDataTypedArray);

	return TRUE;
}

// CPersonDoc serialization

void CPersonDoc::Serialize(CArchive& ar)
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

// CPersonDoc diagnostics

#ifdef _DEBUG
void CPersonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPersonDoc commands
