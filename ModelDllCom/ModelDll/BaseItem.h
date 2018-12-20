#ifndef BASEITEM_H
#define BASEITEM_H

class CBaseItem 
{
public:
	CBaseItem(void);
	virtual ~CBaseItem(void);
public:
	void SetDeviceName(CString strName)
	{
		m_strDeviceName = strName;
	}
	CString GetDeviceName()
	{
		return m_strDeviceName;
	}
	int GetShortValue();
	void SetVarValue(CString strValue);
	void FormatVariant(CString &Str);

	CString GetTypeString(int *pnSel)const;
	CString SetVarType(int nType);
	void Copy(CBaseItem* pItem);
public:
	//与设备点相关联
	DWORD   m_dwItemID;
	//项名
	CString m_strItemName;
	//项值(包括类型和值)
	COleVariant	 m_vItemValue;
	//项的描述
	CString m_strItemDescription;
	//是否为只读
	BOOL	m_bReadOnly;
	//virtual void ItemUpdate(void) = 0;
protected:
	CString m_strDeviceName;
};
#endif