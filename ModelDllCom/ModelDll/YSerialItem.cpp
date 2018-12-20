#include "StdAfx.h"
#include "YSerialItem.h"
#include "common.h"

YSerialItem::YSerialItem(DWORD dwItemId,LPCTSTR sItemName,LPCTSTR sItemDesc)
{
	m_bReadOnly = false;
	CString strDeviceName;
	strDeviceName.LoadString(IDS_DEVICENAME);
	SetDeviceName(strDeviceName);
	m_dwItemID = dwItemId;
	m_strItemName = sItemName;
	m_strItemDescription = sItemDesc;
}

YSerialItem::~YSerialItem(void)
{
}

YBoolItem::YBoolItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc)
:YSerialItem(dwItemId,sItemName,sItemDesc)
{
	SetVarType(YSerialItem::vtBool);
	SetVarValue(CString(_T("FALSE")));
}

YBoolItem::~YBoolItem()
{
}

bool YBoolItem::OnUpdate(CString strVal)
{
	if(m_vItemValue.vt != VT_BOOL) return false;
	HWND hWnd;
	SetVarValue(strVal);
	GET_EXE_HWND(hWnd);
	::SendMessage(hWnd,CW_UPDATEITEMVALUE,DIC_ITEM_UPDATE,(LPARAM)this);
	return true;
}

YShortItem::YShortItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc)
:YSerialItem(dwItemId,sItemName,sItemDesc)
{
	SetVarType(YSerialItem::vtShort);
	SetVarValue(CString(_T("0")));
}

YShortItem::~YShortItem()
{
}

bool YShortItem::OnUpdate(CString strVal)
{
	if(m_vItemValue.vt != VT_I2) return false;
	HWND hWnd;
	SetVarValue(strVal);
	GET_EXE_HWND(hWnd);
	::SendMessage(hWnd,CW_UPDATEITEMVALUE,DIC_ITEM_UPDATE,(LPARAM)this);
	return true;
}

YFloatItem::YFloatItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc)
:YSerialItem(dwItemId,sItemName,sItemDesc)
{
	SetVarType(YSerialItem::vtFloat);
	SetVarValue(CString(_T("0.0")));
}

YFloatItem::~YFloatItem()
{
}

bool YFloatItem::OnUpdate(CString strVal)
{
	if(m_vItemValue.vt != VT_R4) return false;
	HWND hWnd;
	SetVarValue(strVal);
	GET_EXE_HWND(hWnd);
	::SendMessage(hWnd,CW_UPDATEITEMVALUE,DIC_ITEM_UPDATE,(LPARAM)this);
	return true;
}

YStringItem::YStringItem(DWORD dwItemId,LPCSTR sItemName,LPCSTR sItemDesc)
:YSerialItem(dwItemId,sItemName,sItemDesc)
{
	SetVarType(YSerialItem::vtString);
	SetVarValue(CString(_T("null")));
}

YStringItem::~YStringItem()
{
}

bool YStringItem::OnUpdate(CString strVal)
{
	if(m_vItemValue.vt != VT_BSTR) return false;
	CString strOldVal;
	strOldVal = GetStringValue();
	if(strOldVal == strVal)return false;
	HWND hWnd;
	SetVarValue(strVal);
	GET_EXE_HWND(hWnd);
	::SendMessage(hWnd,CW_UPDATEITEMVALUE,DIC_ITEM_UPDATE,(LPARAM)this);
	return true;
}

