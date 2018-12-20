// ItemBrowseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModelDll.h"
#include "ItemBrowseDlg.h"
#include ".\itembrowsedlg.h"


// CItemBrowseDlg 对话框

IMPLEMENT_DYNAMIC(CItemBrowseDlg, CDialog)
CItemBrowseDlg::CItemBrowseDlg(YOPCDevice* pDevice,CObArray * pDevItemArray,CWnd* pParent /*=NULL*/)
	: CDialog(CItemBrowseDlg::IDD, pParent)
{
	m_pMainArray = NULL;
	y_pDevice = pDevice;
	SetItemArray(pDevItemArray);
}

CItemBrowseDlg::~CItemBrowseDlg()
{
}

void CItemBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CItemBrowseDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ITEMS, OnLvnItemchangedListItems)
END_MESSAGE_MAP()


// CItemBrowseDlg 消息处理程序

void CItemBrowseDlg::OnBnClickedOk()
{
	if(! m_pMainArray) return;

	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST_ITEMS);
	ASSERT(pList != NULL);

	CBaseItem *  pItem = NULL;
	m_pMainArray->RemoveAll();
	POSITION p = pList->GetFirstSelectedItemPosition();
	while (p)
	{
		int nSelected = pList->GetNextSelectedItem(p);
		pItem = (CBaseItem *)pList->GetItemData(nSelected);
		if(pItem != NULL)
		{

			m_pMainArray->Add((CObject *)pItem);
		}
	}
	OnOK();
}

static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// lParamSort contains a pointer to the list view control.
	YOPCItem* pItem1 = (YOPCItem*)lParam1;
	YOPCItem* pItem2 = (YOPCItem*)lParam2;
	return (int)(pItem1->GetName().Compare(pItem2->GetName()));
}


BOOL CItemBrowseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_ITEMS);
	ASSERT(pList!=NULL);
	pList->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
	pList->InsertColumn (0, "名称", LVCFMT_LEFT, 100);
	pList->InsertColumn (1, "类型", LVCFMT_LEFT, 100);
	pList->InsertColumn (2, "说明", LVCFMT_LEFT, 200);
	YOPCItem* pItem = NULL;
	CString strAddr;
	int tItem;
	const CMapStringToOb* pItemArray = y_pDevice->GetItemArray();
	if(pItemArray!=NULL)
	{
		POSITION pos = y_pDevice->GetItemArray()->GetStartPosition();
		CString strName;
		int i=0;
		while(pos){
			pItemArray->GetNextAssoc(pos,strName,(CObject*&)pItem);
			ASSERT(pItem != NULL);

			pList->InsertItem(i,pItem->GetName());
			pList->SetItemText(i,1,pItem->GetTypeString(&tItem));
			pList->SetItemText(i,2,pItem->GetDescription());
			pList->SetItemData(i,(DWORD)pItem);

			i++;
		}
	}
	pList->SortItems(MyCompareProc,(DWORD)pList);
	return TRUE;  
}

void CItemBrowseDlg::OnLvnItemchangedListItems(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}

bool CItemBrowseDlg::SetItemArray(CObArray* pDevItemArray)
{
	if(pDevItemArray==NULL) return false;
	m_pMainArray = pDevItemArray;
	return true;
}
