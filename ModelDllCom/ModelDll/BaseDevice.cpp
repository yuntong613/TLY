/*
* Copyright (c) 2004,清华同方有限公司eHome研究院
* All rights reserved.
* 
* 文件名称：BaseDevice.cpp
* 文件标识：见配置管理计划书
* 摘    要：设备基本类
* 
* 当前版本：2.0
* 作    者：杨洪涛
* 完成日期：2004年3月20日
*
* 取代版本：1.0 
* 原作者  ：杨洪涛
* 完成日期：2004年1月10日
*/

// BaseDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "BaseDevice.h"



//IMPLEMENT_SERIAL(CBaseDevice,CObject,1)


// CBaseDevice

CBaseDevice::CBaseDevice()
{
	m_strDeviceName = "Unname";
	m_bUpdate	 = FALSE;
	m_lRate      = 5000;//ms
	m_strDeviceDescription = "unKnow";
}

CBaseDevice::~CBaseDevice()
{

}


// CBaseDevice 成员函数

void CBaseDevice::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	
		ar << m_strDeviceName;
		ar << m_lRate;		
		ar << m_bUpdate;      
		ar << m_strDeviceDescription;

	}
	else
	{	
		ar >> m_strDeviceName;
		ar >> m_lRate;		
		ar >> m_bUpdate;      
		ar >> m_strDeviceDescription;
	}

}


