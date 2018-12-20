#include "StdAfx.h"
#include ".\yopcdevice.h"
#include "ItemBrowseDlg.h"
#include "resource.h"
YOPCDevice::YOPCDevice(void)
{
}

YOPCDevice::~YOPCDevice(void)
{
}
bool YOPCDevice::ShowItemBrowseDlg(CObArray* pDevItemArray)
{
	if(!pDevItemArray)return false;
	CItemBrowseDlg cItemDlg(this,pDevItemArray);
	return (cItemDlg.DoModal() == IDOK);
}

YOPCItem* YOPCDevice::GetItemById(DWORD dwItemID)const
{
	POSITION pos = m_ItemsArray.GetStartPosition();
	YOPCItem* pItem = NULL;
	CString strName;
	while(pos){
		m_ItemsArray.GetNextAssoc(pos,strName,(CObject*&)pItem);
		if(pItem->GetId()==dwItemID)return pItem;
	}
	return NULL;
}

YOPCItem* YOPCDevice::GetItemByName(const CString strName)const
{
	YOPCItem* pItem = NULL;
	m_ItemsArray.Lookup(strName,(CObject*&)pItem);
	return pItem;
}