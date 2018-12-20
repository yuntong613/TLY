#pragma once
#include "yopcitem.h"
#include "resource.h"

class CItemException : public CArchiveException
{
public:
	enum{invalidId=CArchiveException::badSchema+100,invalidAddress,dupId,dupAddress};
	CItemException(int cause = CArchiveException::none,LPCTSTR lpszArchiveName = NULL)
		:CArchiveException(cause,lpszArchiveName){}
};


class YSerialItem :
	public YOPCItem
{
public:
public:
	enum VarType{ vtBool=0,vtByte,vtInterger,vtShort,vtLong,vtFloat,vtDouble,vtString};
	YSerialItem(DWORD dwItemId,LPCTSTR sItemName,LPCTSTR sItemDesc);
	virtual ~YSerialItem(void);
	virtual bool OnUpdate(CString strVal)=0;
	virtual bool SetDeviceItemValue(CBaseItem* pAppItem){ return true;}
};


class YBoolItem : public YSerialItem
{
public:
	enum { DEVICEITEMTYPE = IDS_ITEM_BOOL };
	YBoolItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc);
	virtual ~YBoolItem();
	virtual bool OnUpdate(CString strVal);
	
};

class YShortItem : public YSerialItem
{
public:
	enum { DEVICEITEMTYPE = IDS_ITEM_SHORT };
	YShortItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc);
	virtual ~YShortItem();
	virtual bool OnUpdate(CString strVal);
};

class YFloatItem : public YSerialItem
{
public:
	enum { DEVICEITEMTYPE = IDS_ITEM_FLOAT };
	YFloatItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc);
	virtual ~YFloatItem();
	virtual bool OnUpdate(CString strVal);
};

class YStringItem : public YSerialItem
{
public:
	enum { DEVICEITEMTYPE = IDS_ITEM_STRING };
	YStringItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc);
	virtual ~YStringItem();
	virtual bool OnUpdate(CString strVal);
};

