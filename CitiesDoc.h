
// CitiesDoc.h : interface of the CCitiesDoc class
//


#pragma once
#include "Cities.h"
#include "CitiesData.h"

/// <summary> 
/// Class representing document part of the application for cities
/// </summary>
class CCitiesDoc :
	public CDocument
{

	// Constructor / Destructor
	// ----------------
protected:
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc);
public:
	virtual ~CCitiesDoc();
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
	BOOL SelectRecord(long lId, CITIES& recCities);
	/// <summary>
	/// Update function which documnet use to call class Data
	/// </summary>
	BOOL Update(long ID, CITIES& recCities);
	/// <summary>
	/// Delete function which documnet use to call class Data
	/// </summary>
	BOOL Delete(long ID);
	/// <summary>
	/// Insert function whic document usee to call class Data
	/// </summary>
	BOOL Insert(CITIES& recCities);
	DECLARE_MESSAGE_MAP();

	// Overrides
	// ----------------
public:
	/// <summary>
	/// Virtual function which create ne document
	/// </summary>
	virtual BOOL OnNewDocument() override;
	virtual void Serialize(CArchive& ar);

	// Members
	// ----------------
public:
	/// <summary>
	/// Memeber for internal storage for data
	/// </summary>
	CCitiesTypedPtrArray m_oCitiesArray;
	/// <summary>
	/// Memeber for accsessing model class
	/// </summary>
	CCitiesData m_oCitiesDataModel;

};
