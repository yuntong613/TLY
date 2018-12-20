#pragma once
#include "baseitem.h"

class YOPCItem :
	public CBaseItem
{
public:
	YOPCItem(void);
	virtual ~YOPCItem(void);
	float GetFloatValue();
	bool GetBoolValue();
	CString GetStringValue();
	virtual bool OnUpdate(CString strVal) = 0;
	virtual bool SetDeviceItemValue(CBaseItem* pAppItem) = 0;
	DWORD GetId()const{ return m_dwItemID;}
	CString GetName()const{ return m_strItemName;}
	CString GetDescription()const{ return m_strItemDescription;}
	BOOL IsReadOnly(){ return m_bReadOnly;}
};
