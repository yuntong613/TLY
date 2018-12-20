/*
* Copyright (c) 2004,清华同方有限公司eHome研究院
* All rights reserved.
* 
* 文件名称：BaseItem.cpp
* 文件标识：见配置管理计划书
* 摘    要：项基类
* 
* 当前版本：2.0
* 作    者：杨洪涛
* 完成日期：2004年3月20日
*
* 取代版本：1.0 
* 原作者  ：杨洪涛
* 完成日期：2004年1月10日
*/

#include "StdAfx.h"
#include "baseitem.h"
#include <shlwapi.h>


CBaseItem::CBaseItem(void)
{
	m_dwItemID			 = -1;
	m_strItemName		 = "";
	m_strItemDescription = "";
//	VariantInit(&m_vItemValue);
	m_vItemValue.vt      = VT_R4;
	m_vItemValue.fltVal  = 0.0;
	m_strDeviceName		 = _T("");
	m_bReadOnly			 = FALSE;
}

CBaseItem::~CBaseItem(void)
{
// 	if(m_vItemValue.vt!=VT_EMPTY)
// 		VariantClear(&m_vItemValue);
}

int CBaseItem::GetShortValue()
{
	if(m_vItemValue.vt != VT_I2) return 0;
	int iRet = m_vItemValue.iVal;
	return iRet;
}

CString CBaseItem::GetTypeString(int *pnSel) const
{
	CString strType = "Default";
	switch (m_vItemValue.vt)
	{
	case VT_I1:
	case VT_UI1:		// BYTE 1
		strType = "Byte";
		*pnSel  = 1;
		break;
	case VT_UI2:// UNSIGNED SHORT
	case VT_I2:			// SHORT3
		strType = "Short";
		*pnSel  = 3;
		break;
	case VT_UI4:		// UNSIGNED LONG
	case VT_I4:			// LONG 4
		strType = "Long";
		*pnSel  = 4;
		break;
	case VT_UINT:		// UNSIGNED INTEGER
	case VT_INT:		// INTEGER 2
		strType = "Integer";
		*pnSel  = 2;
		break;
	case VT_R4:			// FLOAT 5
		strType = "Float";
		*pnSel  = 5;
		break;
	case VT_R8:			// DOUBLE 6
		strType = "Double";
		*pnSel  = 6;
		break;
	case VT_BSTR:		//BSTR 7
		strType = "String";
		*pnSel  = 7;
		break;
	case VT_BOOL: //0
		strType = "Bool";
		*pnSel  = 0;
		break;

	}
	return strType;
}

CString CBaseItem::SetVarType(int nType)
{
	CString strType = "Default";
	switch (nType)
	{
	case 0: //0
		strType = "Bool";
		m_vItemValue.vt = VT_BOOL;
		break;

	case 2:		// INTEGER 2
		strType = "Integer";
		m_vItemValue.vt = VT_INT;
		break;

	case 1:		// BYTE 1
		m_vItemValue.vt = VT_I1;
		strType = "Byte";
		break;

	case 3:			// SHORT3
		strType = "Short";
		m_vItemValue.vt = VT_I2;
		break;

	case 4:			// LONG 4
		strType = "Long";
		m_vItemValue.vt = VT_I4;
		break;


	case 5:			// FLOAT 5
		strType = "Float";
		m_vItemValue.vt = VT_R4;

		break;
	case 6:			// DOUBLE 6
		strType = "Double";
		m_vItemValue.vt = VT_R8;

		break;
	case 7:		//BSTR 7
		strType = "String";
		m_vItemValue.vt = VT_BSTR;
		break;

	default:
		strType = "Default";
		m_vItemValue.vt = VT_BSTR;
	}
	return strType;
}
void CBaseItem::FormatVariant(CString &Str)
{
	switch(m_vItemValue.vt)
	{
	case VT_I1:
	case VT_UI1:		// BYTE
		Str.Format("%d", m_vItemValue.bVal );
		break;
	case VT_I2:			// SHORT
		Str.Format("%d", m_vItemValue.iVal );
		break;
	case VT_UI2:		// UNSIGNED SHORT
		Str.Format("%d", m_vItemValue.uiVal );
		break;
	case VT_I4:			// LONG
		Str.Format("%ld", m_vItemValue.lVal );
		break;
	case VT_UI4:		// UNSIGNED LONG
		Str.Format("%ld", m_vItemValue.ulVal );
		break;
	case VT_INT:		// INTEGER
		Str.Format("%ld", m_vItemValue.intVal );
		break;
	case VT_UINT:		// UNSIGNED INTEGER
		Str.Format("%ld", m_vItemValue.uintVal );
		break;
	case VT_R4:			// FLOAT
		Str.Format("%5.2f", m_vItemValue.fltVal );
		break;
	case VT_R8:			// DOUBLE
		Str.Format("%9.4f", m_vItemValue.dblVal );
		break;
	case VT_BSTR:		//BSTR
		//Str.Format( "%s ", m_vItemValue.bstrVal );
		Str = CString(m_vItemValue.bstrVal);
		break;
	case VT_BOOL:
		if (m_vItemValue.boolVal)
			Str = "TRUE";
		else
			Str =  "FALSE";
		break;
	default:
		Str.Format("Unknow Type:%d", m_vItemValue.vt );
		break;
	}
}


void CBaseItem::SetVarValue(CString strValue)
{
	int tmpInt;
	FLOAT tmpFloat;
	switch(m_vItemValue.vt)
	{
	case VT_BOOL://Boolean
		if(strValue.MakeLower() == "true" || StrToInt(strValue) > 0)
			m_vItemValue.boolVal = VARIANT_TRUE;
		else
			m_vItemValue.boolVal = VARIANT_FALSE;
		break;
	case VT_I1://
	case VT_UI1:
		sscanf(strValue.GetBuffer(),"%d",&tmpInt);
		m_vItemValue.bVal = (BYTE)tmpInt;
		break;
	case VT_INT:
		sscanf(strValue,"%d",&tmpInt);
		m_vItemValue.intVal = tmpInt;
		break;
	case VT_I2:

		sscanf(strValue,"%d",&tmpInt);
		m_vItemValue.iVal = (SHORT)tmpInt;
		break;
	case VT_I4:
		sscanf(strValue,"%d",&tmpInt);
		m_vItemValue.lVal = (LONG)tmpInt;
		break;
	case VT_R4:
		sscanf(strValue,"%f",&tmpFloat);
		m_vItemValue.fltVal = tmpFloat;
		break;
	case VT_R8:
		sscanf(strValue,"%f",&tmpFloat);
		m_vItemValue.dblVal = tmpFloat;
		break;
	case VT_BSTR:
		m_vItemValue.SetString(strValue,VT_BSTR);
		break;
	}
}

void CBaseItem::Copy(CBaseItem* pItem)
{
	m_bReadOnly = pItem->m_bReadOnly;
	m_dwItemID = pItem->m_dwItemID;
	m_strItemDescription = pItem->m_strItemDescription;
	m_strItemName = pItem->m_strItemName;
	VariantCopy(&m_vItemValue,&pItem->m_vItemValue);
	SetDeviceName(pItem->GetDeviceName());
}