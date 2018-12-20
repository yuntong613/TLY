#include "StdAfx.h"
#include ".\yopcitem.h"

YOPCItem::YOPCItem(void)
{
}

YOPCItem::~YOPCItem(void)
{
}

float YOPCItem::GetFloatValue()
{
	if(m_vItemValue.vt != VT_R4) return 0;
	float fVal = m_vItemValue.fltVal;
	return fVal;
}

bool YOPCItem::GetBoolValue()
{	
	if(m_vItemValue.vt != VT_BOOL) return 0;
	bool bRet = m_vItemValue.bVal ? true : false;
	return bRet;
}

CString YOPCItem::GetStringValue()
{
	if(m_vItemValue.vt != VT_BSTR) return false;
	CString strVal;
	FormatVariant(strVal);
	return strVal;
}
