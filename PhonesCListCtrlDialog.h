#pragma once
#include "PhoneTypes.h"
#include "afxdialogex.h"


// CPhonesCListCtrlDialog dialog

class CPhonesCListCtrlDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhonesCListCtrlDialog)

public:
	CPhonesCListCtrlDialog(CWnd* pParent = nullptr);   // standard constructor
	CPhonesCListCtrlDialog(CPhoneTypesTypedPtrArray* pPhoneTypeArray, CWnd* pParent = nullptr);   // standard constructor

	virtual ~CPhonesCListCtrlDialog();

	BOOL OnInitDialog();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DILG_CLISTCTRL_DIALOG };
#endif
	void SetPhoneTypesComboBox(CPhoneTypesTypedPtrArray* oPhoneTypeArray);
	CString GetPhoneNumber() const;
	CString GetPhoneType() const;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV support
	virtual void OnOK() override;

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticPhoneNumber;
	CStatic m_staticPhoneType;
	CEdit m_editPhoneNumber;
	CComboBox m_cmbPhoneTypes;

	CPhoneTypesTypedPtrArray* m_oPhoneTypes;

	CString m_strPhoneNumber;
	CString m_strPhoneType;
	long* m_lPhoneTypeId;
	afx_msg void OnStnClickedSttPhoneTypeDialog();
	afx_msg void OnEnChangeEdtPhoneNumberDialog();
};
