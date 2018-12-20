/********************************************************************
	created:	2004/05/07
	created:	7:5:2004   14:38
	filename: 	e:\sourcecode\mfc\newopcserver\comm\common.h
	file path:	e:\sourcecode\mfc\newopcserver\comm
	file base:	common
	file ext:	h
	author:		Hotyoung
	
	purpose:	这是里主程序和DLL通用的定义
*********************************************************************/
#ifndef COMMON_H
#define COMMON_H


/////////////////////////////////////////////////////////
//宏定义

#define DEVICE_API extern "C"  __declspec(dllexport)
//Dll菜单ID的开始ID
#define DLL_MENU_ID		20500
#define DLL_BEGIN_UPDATE		DLL_MENU_ID + 1
#define DLL_END_UPDATE			DLL_MENU_ID + 2

/////////////////////////////////////////////////////////
#define GET_DLL_PROC(DllName,APIVAR,APITYPE,APINAME)			\
		HINSTANCE hDll = AfxLoadLibrary(DllName);				\
		ASSERT(hDll);											\
		APITYPE APIVAR = (APITYPE)GetProcAddress(hDll,APINAME); \
		ASSERT(APIVAR)	

////////////////////////////////////////////////////////////
#define FREE_DLL(hDll) AfxFreeLibrary(hDll)
///////////////////////////////////////////////////////////

#define MAX_BUFF_LEN	2048

//辅助宏
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
//
#if defined(_INTERIM_RELEASE) || defined(_DEBUG)
#define OPC_TRY
#define OPC_CATCH
#define OPC_CATCH2
#else
#define OPC_TRY try{
#define OPC_CATCH }\
catch(CString &str){ try{LogError(GetResString(IDS_EXCEPTION_MSG1),__FUNCTION__,__FILE__, __LINE__,str);}catch(...){} }\
catch(CException *err){ try{  TCHAR  szCause[255];   err->GetErrorMessage(szCause, 255);\
LogError(GetResString(IDS_EXCEPTION_MSG1),__FUNCTION__,__FILE__, __LINE__,szCause);err->Delete();}catch(...){} }\
catch(...){ try{LogError(GetResString(IDS_EXCEPTION_MSG1),__FUNCTION__,__FILE__, __LINE__,_T(""));}catch(...){} }
#define OPC_CATCH2 } catch(...){}
#endif

//更新项消息定义

//单项进行更新
#define CW_UPDATEITEMVALUE WM_USER+1011 
/*
 其中 WPARAM wParam 包含下面的更新标记
	  LPARAM lParam 存放CBaseItem类型的指针
	  用户需要自行为此指针管理内存
	  处理成功返回0
*/

//一组数据进行更新
#define CW_UPDATEGROUPITEM (CW_UPDATEITEMVALUE + 1) 
/*
 其中 WPARAM wParam 包含下面的更新标记
	  LPARAM lParam 存放包含CBaseItem类型CPtrArray的指针
	  用户需要自行为此指针管理内存
	  处理成功返回0
*/

//更新标记定义 做为WPARAM参数
#define DIC_ITEM_UPDATE  0xFF01 //设备项值好变化
#define DIC_ITEM_DELEATE 0xFF02	//设备项被删除
#define DIC_ITEM_INVALID 0xFF03 //些项为效项

#define MY_TIMER 2013

#ifdef _MAIN_PROGRAMER

//主程序中定义标识
#define HINT_LOAD_PROJECT		1060
#define HINT_CLOSE_PROJECT		1061
#define HINT_REFRESH_GROUPVIEW	1062
#define HINT_REFRESH_ITEMVIEW	1063
//DLL的菜单范围
#define MIN_DLL_MENU_ID			DLL_MENU_ID
#define MAX_DLL_MENU_ID			DLL_MENU_ID + 400
#else
//////////////////////////////////////////////////////////////////
//取得主程序句柄宏
#define GET_EXE_HWND(hWnd)										\
		{														\
			typedef HWND (*GETTHEWND)();						\
			GETTHEWND GetTheWnd = (GETTHEWND)GetProcAddress(GetModuleHandle(""),"mn_GetMainWnd");\
			ASSERT(GetTheWnd != NULL);							\
			(hWnd) = GetTheWnd();								\
		}														\
//////////////////////////////////////////////////////////////////

bool GetAppPath(CString& strPath);

#endif
#include <atlbase.h>
#endif