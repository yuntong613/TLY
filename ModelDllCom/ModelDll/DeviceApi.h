
#ifndef DEVICEAPI_H
#define DEVICEAPI_H
/*
* Copyright (c) 2004,清华同方有限公司eHome研究院
* All rights reserved.
* 
* 文件名称：DeviceApi.h
* 文件标识：见配置管理计划书
* 摘    要：设备树形设备中的TreeView
* 
* 当前版本：1.5
* 作    者：杨洪涛
* 完成日期：2005年5月10日
*
* 取代版本：1.0 
* 原作者  ：杨洪涛
* 完成日期：2004年12月10日
*/

//DLL要实现函数的定义

/*''''''''''''''''''''''''''''''''''''''''''''''

//	在DLL中要实现窗体的显示必须加上
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

''''''''''''''''''''''''''''''''''''''''''''''''*/
//*******************
//1.5版新函数
//*******************
/*
//返回DLL的版
DEVICE_API WORD ht_GetDeviceVersion()
{
	int nMajorVer = 2;//主版本号
	int nMinorVer = 0;//副版本号
	WORD wVersion = MAKEWORD(nMajorVer,nMinorVer);
	return wVersion;
}
*/

DEVICE_API void* ht_NewDevice();

DEVICE_API void ht_DeleteDevice(void *pDevice);

DEVICE_API WORD ht_GetDeviceVersion();


//---------------------------------------
/*
此函数提供DLL所实现设备的名称
参数传进来的是指针。

例: *pName = "Simulate Device";
return true;
*/
DEVICE_API bool ht_GetDeviceName(CString /*[out]*/*pName);


//*******************
//1.5版新函数
//*******************
/*
*/
DEVICE_API HICON ht_GetDeviceIcon();


//*******************
//1.5版新函数
//*******************
//
DEVICE_API bool ht_GetArrayItemByName(CObArray *pItemOutArray, const CStringArray *pStringArray = NULL);

//---------------------------------------
/*	
ht_ShowProDlg
此函数提供DLL中设备的参数设置的窗体
例:
AFX_MANAGE_STATE(AfxGetStaticModuleState());
//这里需要实现非模式的窗口.所以要Create窗体
//因为此窗体是显示是主程序建立设备向导里的
//所以要对窗体的属性进行以下设置:
//	Border = None
//	Stytle = Child

pSettingDlg = new CSettingDlg();
ASSERT(pSettingDlg);
if(!pSettingDlg->Create(CSettingDlg::IDD))
return NULL;
pSettingDlg->ShowWindow(SW_SHOW);
pSettingDlg->UpdateWindow();

return m_pSettingDlg->m_hWnd;	

*/
DEVICE_API HWND ht_ShowProDlg(VOID  /*[in out]*/*pSetting = NULL);


//检测设置信息是否输入正确
DEVICE_API bool ht_CheckSetting();

/*
此函数提供DLL中设备参数设置的保存，存在DLL中，以
供DLL的使用
*/
DEVICE_API LPVOID ht_SaveDeviceSetting();

/*
此函数提供DLL中设备的运行。如：连接到相应的硬件设备
上。使DLL工作起来。即启动设备线程
*/
DEVICE_API bool ht_RunDevice();

/*
此函数提供DLL中设备的停止。即停止设备线程
*/
DEVICE_API bool ht_StopDevice();

/*
此函数提供DLL中显示设备数据项的窗体。如果各种数据点
*/
DEVICE_API bool ht_ShowItemBrowseDlg(CObArray /*[in out]*/*pDevItemArray);

/*
注意:DLL菜单 ID的范围是20500到20900，共400项
此函数提供DLL设备在主程序的菜单中注册此设备的菜单项
*/
DEVICE_API bool ht_AddDllMenu(CMenu /*[in out]*/*pMenu);

/*
此函数提供处理DLL设备在主程序中注册的菜单项的操作
*/
DEVICE_API void ht_OnCommand(UINT /*[in]*/nID);

/*
平台向DLL进行写值操作
参数是CBaseItem的指针，用于保存要更新项的新值和各种信息
*/
DEVICE_API bool ht_SetDeviceItemValue(LPVOID /*[in]*/);

#endif