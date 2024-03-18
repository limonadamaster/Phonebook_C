// CitiesView.h : interface of the CPersonView class
//

#pragma once
#include "Persons.h"
#include "PersonDoc.h"
#include "afxcview.h"
/// <summary>
/// Class representing view part of the application for cities
/// </summary>
class CPersonView : public CListView
{
	// Macros
	// ----------------

	/// <summary>
	/// Macro which support dynamic creation of objects
	/// </summary>
	DECLARE_DYNCREATE(CPersonView);


	// Constructor / Destructor
	// -----------------
protected:
	CPersonView() noexcept;

	// Methods
	// ----------------
protected:

	/// <summary>
	/// This method is called the first time after the constructor
	/// </summary>
	virtual void OnInitialUpdate();
	/// <summary>
	/// This method take care of context menu to pop up
	/// </summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	/// <summary>
	/// This method take care of that which buttons wll be active or not in context menu
	/// </summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	/// <summary>
	/// This is method from context menu. It update the record
	/// </summary>
	afx_msg void OnContextUpdate();
	/// <summary>
	/// This is method from context menu. It insert the record
	/// </summary>
	afx_msg void OnContextInsert();
	/// <summary>
	/// This is method from context menu. It delete the record
	/// </summary>
	afx_msg void OnContextDelete();
	/// <summary>
	/// This is method which perform update operation for CListCtrl and I call it at OnUpdate
	/// </summary>
	afx_msg void CListCtrlUpdate();
	/// <summary>
	/// This is method which perform insert operation for CListCtrl and I call it at OnUpdate
	/// </summary>
	afx_msg void CListCtrlInsert();
	/// <summary>
	/// This is method which perform delete operation for CListCtrl and I call it at OnUpdate
	/// </summary>
	afx_msg void CListCtrlDelete();
	/// <summary>
	/// This is method which returns the index of record the user clicked into the screen
	/// </summary>
	afx_msg CPerson* GetSelectedItemData();
	//TODO 
	long GetSelectedItemIndex();
	/// <summary>
	/// This method take care about logic for updating the screen after the crud operations
	/// </summary>
	void OnUpdate(CView*, LPARAM lHint, CObject*);
	/// <summary>
	/// Method show the data, when you double click at the recod from CListCtrl
	/// </summary>
	afx_msg void ShowRecord(NMHDR* pNMHDR, LRESULT* pResult);
	/// <summary>
	/// Method with logic of what happens after  OnInitialUpdate is called
	/// </summary>
	afx_msg void ShowOnCreate();
	/// <summary>
	/// Method that returns the current record
	/// </summary>
	PERSONS& GetPerson();
	///Method we use for accessing document
	/// </summary>
	CPersonDoc* GetDocument() const;

	DECLARE_MESSAGE_MAP();

	//Virtual  Methods
	// ----------------
public:
	virtual ~CPersonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Members
	// ----------------

protected:

	/// <summary>
	/// The List Control
	/// </summary>
	CListCtrl& m_oListCtrl = GetListCtrl();

	/// <summary>
	/// Memer which we use during the operationss
	/// </summary>
	PERSONS m_recPerson;

	/// <summary>
	/// Enumarate for columns
	/// </summary>
	enum {
		PersonColumnName,
		PersonColumnSurname,
		PersonColumnFamily,
		PersonColumnUCN,
		PersonColumCityId
	};

	/// <summary>
	/// Enumarate for dilog hints
	/// </summary>
	enum {
		DialogUpdateHint = 1,
		DialogInsertHint,
		DialogReadOnlyHint
	};


};

