#pragma once
#include "Persons.h"
#include "afxcview.h"
#include "PersonData.h"

/// <summary> 
/// Class representing document part of the application for persons
/// </summary>
class CPersonDoc :
	public CDocument
{

	// Constructor / Destructor
	// ----------------
protected:
	CPersonDoc() noexcept;
	DECLARE_DYNCREATE(CPersonDoc);
public:
	virtual ~CPersonDoc();
	// Methods
	// ----------------
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	/// <summary>
	/// Select method which document use to call class Data
	/// </summary>
	BOOL SelectRecord(long lId, PERSONS& recCities);
	/// <summary>
	/// Update function which documnet use to call class Data
	/// </summary>
	BOOL Update(long ID, CPerson& recPersonOld, CPerson& recPersonNew);
	/// <summary>
	/// Delete function which documnet use to call class Data
	/// </summary>
	BOOL Delete(CPerson& recCPerson);
	/// <summary>
	/// Insert function whic document usee to call class Data
	/// </summary>
	BOOL Insert(CPerson& recPerson);


	CCitiesTypedPtrArray& CitiesArrayForComboBox();

	CPhoneTypesTypedPtrArray& PhoneTypedForInsertDialogComboBox();



	DECLARE_MESSAGE_MAP();

	// Overrides
	// ----------------
public:
	/// <summary>
	/// Virtual function which create ne document
	/// </summary>
	virtual BOOL OnNewDocument() override;
	virtual void Serialize(CArchive& ar);
protected:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	// Members
	// ----------------
public:
	/// <summary>
	/// Memeber for internal storage for data
	/// </summary>
	CPersonsTypedPtrArray m_oPersonArray;
	/// <summary>
	/// Memeber for accsessing model class
	/// </summary>
	CPersonData m_oPersonDataModel;
	CPersonDataTypedPtrArray m_oPersonDataTypedArray;

};
