// ModelDll.h : ModelDll DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "DllMainFrame.h"
#include "BaseItem.h"
#include "BaseDevice.h"
// CModelDllApp
// 有关此类实现的信息，请参阅 ModelDll.cpp
//

class CModelDllApp : public CWinApp
{
public:
	CModelDllApp();
	CDllMainFrame* pFrame;
// 重写
public:
	virtual BOOL InitInstance();
	CDllMainFrame* GetMainWindow(){return pFrame;}
	void* NewDevice(LPCTSTR pszAppPath);
	void DeleteDevice(void *pDevice);

	bool RunDevice();
	bool StopDevice();

	bool ShowItemBrowseDlg(CObArray* pDevItemArray);
	bool GetArrayItemByName(CObArray* pItemOutArray,const CStringArray* pStringArray = NULL);

	bool AddDllMenu(CMenu* pMenu);
	void OnCommand(UINT nID);
	bool SetDeviceItemValue(CBaseItem* pAppItem);
	bool GetAppPath(CString& strPath)const;


	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
