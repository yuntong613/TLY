#pragma once
#include "basedevice.h"
#include "BaseItem.h"
#include "YOPCItem.h"
#include "CnComm.h"


class YOPCDevice :
	public CBaseDevice
{
public:
	YOPCDevice(void);
	virtual ~YOPCDevice(void);
	virtual void OnUpdate()=0;
	virtual bool SetDeviceItemValue(CBaseItem* pAppItem)=0;
	YOPCItem* GetItemById(DWORD dwItemID)const;
	YOPCItem* GetItemByName(const CString strName)const;
	int GetItemsCount()const{ return (int)(m_ItemsArray.GetCount());}
	const CMapStringToOb* GetItemArray()const{ return &m_ItemsArray;}
	bool ShowItemBrowseDlg(CObArray* pDevItemArray);
	virtual void HandleData() = 0;
	virtual void BeginUpdateThread() = 0;
	virtual void EndUpdateThread() = 0;

protected:
	CMapStringToOb m_ItemsArray;
public:
	CnComm m_Com;
};