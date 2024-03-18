#pragma once
#include "afxwin.h"
#include "afxdialogex.h"
#include "CPerson.h"
#include "Validator.h"



// CPersonDialog dialog

class CPersonDialog : public CDialog
{
	DECLARE_DYNAMIC(CPersonDialog)

public:
	CPersonDialog(CWnd* pParent = nullptr);   // standard constructor
	CPersonDialog(int nHint, CPerson* recPerson = nullptr, CPhoneTypesTypedPtrArray* pPhoneTypeArray = nullptr, CCitiesTypedPtrArray* pCitiesArray = nullptr, CWnd* pParent = nullptr); // constructor with cities object parameter
	virtual ~CPersonDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSON_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;
	void SetDialogTitle(const CString& title);
	void SetDialogFields(CPerson* pPerson);
	void SetReadOnlyControls();
	void SetCitiesComboBox(CCitiesTypedPtrArray* oCitiesArray);
	bool ValidateFields(CEdit& editControl);
	void OnOK();
	afx_msg void OnRButtonUp(UINT, CPoint point);
	afx_msg void OnContextMenu(CWnd*, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	void GetDialogFields(CPerson& recPerson);
	CPerson& GetPersonDataFromDialog();

public:
	CEdit m_editPersonName;
	CEdit m_editPersonSurname;
	CEdit m_editPersonFamily;
	CEdit m_editPersonUCN;
	CComboBox m_comboBoxPersonCity;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_LstCtrlPhoneNumbers;


	enum {
		DialogUpdateHint = 1,
		DialogInsertHint,
		DialogReadOnlyHint
	};

	enum {
		ListCtrPhoneNumbers,
		ListCtrlPhoneTypes
	};


	CPerson* m_recPerson;
	int m_nHint;
	CCitiesTypedPtrArray* m_oCitiesArray;
	CPhoneTypesTypedPtrArray* m_oPhoneTypes;

private:
	Validator m_validator;
	CPerson recPersonForReturn;


public:
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	afx_msg void OnEnChangeEdbPersonCity();
	afx_msg void OnCbnSelchangeCombo1();
};
