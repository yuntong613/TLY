// ModelDll.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "ModelDll.h"
#include "common.h"
#include "DeviceApi.h"
#include "YOPCItem.h"
#include "YOPCDevice.h"
#include "YSerialDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CModelDllApp

BEGIN_MESSAGE_MAP(CModelDllApp, CWinApp)
END_MESSAGE_MAP()


// CModelDllApp 构造

CModelDllApp::CModelDllApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	pFrame = NULL;
}


// 唯一的一个 CModelDllApp 对象

CModelDllApp theApp;


// CModelDllApp 初始化

BOOL CModelDllApp::InitInstance()
{
	CWinApp::InitInstance();
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	pFrame = new CDllMainFrame;
	pFrame->Create(CDllMainFrame::IDD,NULL);
	return TRUE;
}

int CModelDllApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SendMessage(GetMainWindow()->m_hWnd,WM_CLOSE,0,0);
	if(pFrame)
		delete pFrame;
	return CWinApp::ExitInstance();
}

void* CModelDllApp::NewDevice(LPCTSTR pszAppPath)
{
	CString strPath;
	GetAppPath(strPath);
	return pFrame->NewDevice(pszAppPath);
}

void CModelDllApp::DeleteDevice(void *pDevice)
{
	return pFrame->DeleteDevice(pDevice);
}


bool CModelDllApp::RunDevice()
{
	return pFrame->RunDevice();
}

bool CModelDllApp::StopDevice()
{
	pFrame->StopDevice();
	return true;
}

bool CModelDllApp::ShowItemBrowseDlg(CObArray* pDevItemArray)
{
	return pFrame ? pFrame->ShowItemBrowseDlg(pDevItemArray) : false;
}

bool CModelDllApp::GetArrayItemByName(CObArray *pItemOutArray, const CStringArray *pStringArray)
{
	if(! pFrame) return false;
	if(pItemOutArray == NULL)
	{
		return false;
	}
	const YOPCDevice* pDevice = GetMainWindow()->GetDevice();
	if( pDevice == NULL ) return false;

	const CMapStringToOb* pItemArray = pDevice->GetItemArray();

	if(pItemArray->IsEmpty()) return false;
	if(pStringArray == NULL)
	{
		//返回所有值
		pItemOutArray->SetSize(pItemArray->GetCount());
		POSITION pos = pItemArray->GetStartPosition();
		YOPCItem* pItem = NULL;
		CString strName;
		while(pos){
			pItemArray->GetNextAssoc(pos,strName,(CObject*&)pItem);
			if(pItem)
				pItemOutArray->Add((CObject*)pItem);
		}
	}
	else
	{
		//根据提供的名子返回
		YOPCItem* pItem = NULL;
		for(INT_PTR i=0;i<pStringArray->GetCount();i++)
		{
			if(pItem=pDevice->GetItemByName((*pStringArray)[i]))
			{
				pItemOutArray->Add(static_cast<CObject*>((void*)pItem));
			}
		}
	}
	return true;
}

bool CModelDllApp::AddDllMenu(CMenu* pMenu)
{
	return false;
}

void CModelDllApp::OnCommand(UINT nID)
{
}

bool CModelDllApp::GetAppPath(CString& strPath)const
{
	char szPath[MAX_PATH];
	CString strTmp;
	if (!GetModuleFileName(m_hInstance, szPath, MAX_PATH))return false;
	strTmp=_T(szPath);
	int nPos = strTmp.ReverseFind(_T('\\'));
	if (nPos < 1)return false;
	strPath = strTmp.Left(nPos);
	return true;
}

bool CModelDllApp::SetDeviceItemValue(CBaseItem* pItem)
{
	return pFrame ? pFrame->SetDeviceItemValue(pItem) : false;
}


DEVICE_API void* ht_NewDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString strPath;
	GetAppPath(strPath);
	return theApp.NewDevice(strPath);
}

DEVICE_API void ht_DeleteDevice(void *pDevice)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.DeleteDevice(pDevice);
}

DEVICE_API WORD ht_GetDeviceVersion()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int nMajorVer = 1;//主版本号
	int nMinorVer = 0;//副版本号
	WORD wVersion = MAKEWORD(nMajorVer,nMinorVer);
	return wVersion;
}

//
DEVICE_API bool ht_GetDeviceName(CString *pName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString strDeviceName;
	strDeviceName.LoadString(IDS_DEVICENAME);
	*pName = strDeviceName;
	return true;
}

//
DEVICE_API HICON ht_GetDeviceIcon()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HICON hIcon = NULL;
	// 	AFX_MANAGE_STATE(   AfxGetStaticModuleState()   );   
	// 	hIcon = LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_OPCSAMPLEDLL));
	return hIcon;
}
//
DEVICE_API HWND ht_ShowProDlg(VOID *pSetting /*= NULL*/)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return NULL;
	//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//	return theApp.ShowSettingDlg(pSetting);	
}

DEVICE_API LPVOID ht_SaveDeviceSetting()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return NULL;
}

DEVICE_API bool ht_RunDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.RunDevice();
}

DEVICE_API bool ht_StopDevice() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.StopDevice();
}


DEVICE_API bool ht_ShowItemBrowseDlg(CObArray /*[in out]*/*pDevItemArray)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.ShowItemBrowseDlg(pDevItemArray);
}

//
DEVICE_API bool ht_GetArrayItemByName(CObArray *pItemOutArray, const CStringArray *pStringArray)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.GetArrayItemByName(pItemOutArray,pStringArray);
}	


DEVICE_API bool ht_AddDllMenu(CMenu *pMenu)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(theApp.GetMainWindow() != NULL);
	return theApp.AddDllMenu(pMenu);
}

/*
此函数提供处理DLL设备在主程序中注册的菜单项的操作
*/
DEVICE_API void ht_OnCommand(UINT nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(theApp.GetMainWindow() != NULL);
	theApp.OnCommand(nID);
}


DEVICE_API bool ht_SetDeviceItemValue(LPVOID /*[in]*/pItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(pItem == NULL) return false;
	return theApp.SetDeviceItemValue(static_cast<CBaseItem*>(pItem));
}

//////////////////////////////////////////////
//结束API

bool GetAppPath(CString& strPath)
{
	return theApp.GetAppPath(strPath);
}