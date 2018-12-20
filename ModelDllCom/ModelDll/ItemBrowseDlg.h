#pragma once

#include "YOPCDevice.h"
#include "resource.h"
// CItemBrowseDlg 对话框

class CItemBrowseDlg : public CDialog
{
	DECLARE_DYNAMIC(CItemBrowseDlg)

public:
	CItemBrowseDlg(YOPCDevice* pDevice,CObArray * pDevItemArray,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CItemBrowseDlg();

// 对话框数据
	enum { IDD = IDD_ADDITEMDLG };
public:
	CObArray* m_pMainArray;
	YOPCDevice* y_pDevice;
public:
	bool SetItemArray(CObArray* pDevItemArray);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListItems(NMHDR *pNMHDR, LRESULT *pResult);
};
