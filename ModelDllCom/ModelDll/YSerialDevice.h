#pragma once
#include "YOPCDevice.h"
#include "Log.h"

#include "resource.h"

class YSerialDevice :
	public YOPCDevice
{
public:
	enum{ DEVICENAME = IDS_DEVICENAME};
	YSerialDevice(LPCSTR pszAppPath);
	virtual ~YSerialDevice(void);
	virtual bool SetDeviceItemValue(CBaseItem* pAppItem);
	virtual void OnUpdate();
	virtual void HandleData();
	virtual void Serialize(CArchive& ar);
	BOOL InitConfig(CString strFilePath);
	void Load(CArchive& ar);
	void MakeItems();
	void LoadItems(CArchive& ar);
	int QueryOnce();

	virtual void BeginUpdateThread();
	virtual void EndUpdateThread();

	BYTE Hex2Bin(CString strHex);
	int HexStr2Bin(BYTE * cpData,CString strData);
	CString Bin2HexStr(BYTE* cpData,int nLen);
public:
	long y_lUpdateTimer;
public:
	CString m_strConfigFile;
	int m_nComPort;
	int m_nBaudRate;
	int m_nParity;
	CStringArray m_strSlaveAddr;
public:
	int m_nUseLog;
	CLog m_Log;
	void OutPutLog(CString strMsg);
public:
	HANDLE m_hQueryThread;
	bool m_bStop;
};
