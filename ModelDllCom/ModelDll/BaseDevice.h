#pragma once
#ifndef BASEDEVICE_H
#define BASEDEVICE_H

// CBaseDevice 命令目标

class CBaseDevice : public CObject
{
//public:
	//DECLARE_SERIAL(CBaseDevice)
public:
	CBaseDevice();
	virtual ~CBaseDevice();
protected:
	CString m_strDeviceName;//设备名称
	LONG	m_lRate;		//更新率（ms）
	BOOL	m_bUpdate;      //是否进行更新。就是是否运行线程
	CString m_strDeviceDescription;
public:
	//设置设备名称
	void SetDeviceName(CString strDeviceName){ m_strDeviceName = strDeviceName; }
	void SetDeviceDesc(CString strDeviceDesc){ m_strDeviceDescription = strDeviceDesc; }
	//取得设备名称
	CString GetDeviceName()	{ return m_strDeviceName;}
	CString GetDeviceDesc()	{ return m_strDeviceDescription;}
	//刷新数率
	void SetUpdateRate(LONG lRate){ m_lRate = lRate;}
	LONG GetUpdateRate(){ return m_lRate;}
	
	virtual void Serialize(CArchive& ar);
};

#endif

