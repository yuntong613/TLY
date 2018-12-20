#include "StdAfx.h"
#include "log.h"

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <ShlObj.h>
#pragma comment(lib, "shell32.lib")

CLog::CLog(void)
{
	m_LogOption = 1;

	m_WithThreadId = true;

	m_LastDay = 0;

	m_AutoDelLogFile = true;

	m_bEncrypt = false;

	m_pPSK = NULL;

	m_MaxLogFileNumber = 7;

	m_LogFileName = "";

}

CLog::~CLog(void)
{
	m_LogFile.Abort();

	if(m_pPSK != NULL)
	{
		delete m_pPSK;
		m_pPSK = NULL;
	}
}

bool CLog::GetWithThreadId() const
{
	return m_WithThreadId;
}

CString CLog::GetLogFileName() const
{
	return m_LogFileName;
}

void CLog::SetLogFileName( )
{		

	SYSTEMTIME systime ={0};

	GetLocalTime(&systime);

	CString strFileName;

	strFileName.AppendFormat(_T("%04d%02d%02d.log"), 
		systime.wYear, 
		systime.wMonth, 
		systime.wDay);

	if (IsHaveCustomName())
	{
         CString strTem = m_strCustomName;

		 strTem.Append(strFileName);

		 strFileName = strTem;
	}

	m_LogFileName = strFileName; // 日志文件名	


}

void CLog::SetWithThreadId( bool newVal )
{
	m_WithThreadId = newVal;
}

UINT CLog::GetLogOption() const
{
	return m_LogOption;
}

void CLog::SetLogOption( UINT newVal )
{
	m_LogOption = newVal;
}

bool CLog::LogBuf(const void* lpBuf, UINT nCount )
{
	bool bRet = false;

	CSingleLock(&m_cs, TRUE);

	if (!IsHaveFileName())
	{
		SetLogFileName();
	}

	try
	{
		OpenLogFile();
		m_LogFile.Write(lpBuf, nCount);
//		m_LogFile.Flush();
		m_LogFile.Abort();
		bRet = true;
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
	}
	
	return bRet;
}

bool CLog::LogInfo( CString strInfo )
{
	bool bRet = false;

	CSingleLock(&m_cs, TRUE);

	if (!IsHaveFileName())
	{
		SetLogFileName();
	}

	if(IsNeedEncrypt())
	{

		int iSize = strInfo.GetLength();

		BYTE * pString = new BYTE[iSize+1];

		memset(pString,0,iSize+1);

		memcpy(pString,strInfo,iSize);

		Encrypt(pString,iSize);

		strInfo = pString;

		delete pString;
		
		pString = NULL;
	}

	try
	{
		OpenLogFile();
		m_LogFile.Write(strInfo, strInfo.GetLength()* sizeof(TCHAR));
	//	m_LogFile.Flush();
		m_LogFile.Abort();
		bRet = true;
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
	}

	return bRet;
}

bool CLog::Write( LPCTSTR lpszMsg)
{
	CString strMsg;

	MakeLogInfoHead(strMsg);

	strMsg.Append(lpszMsg);

	strMsg.Append(_T("\r\n"));

	bool bRet =  LogInfo(strMsg);

	return bRet;
}

bool CLog::Write( LPCTSTR lpszMsg, UINT eLogType)
{
	if (!CheckLogOption(eLogType))
	{
		return false;
	}

	return Write(lpszMsg);
}

bool CLog::Write(const void* lpBuf, UINT nCount)
{
	CString strMsg;

	MakeLogInfoHead(strMsg);

	bool bRet = LogInfo(strMsg);

	bRet = LogBuf(lpBuf, nCount);

	strMsg.Empty();

	strMsg.Append(_T("\r\n"));

	bRet = LogInfo(strMsg);

	return bRet;
}

bool CLog::Write(const void* lpBuf, UINT nCount, UINT eLogType)
{
	if (!CheckLogOption(eLogType))
	{
		return false;
	}

	return Write(lpBuf, nCount);
}

bool CLog::WriteFormat(LPCTSTR lpszMsg, ... )
{
	CString strMsg;
	
	MakeLogInfoHead(strMsg);

	va_list argList;
	va_start(argList, lpszMsg);
	strMsg.AppendFormatV(lpszMsg, argList);
	va_end( argList );

	strMsg.Append(_T("\r\n"));

	bool bRet = LogInfo(strMsg);


	return bRet;
}

bool CLog::WriteFormat(UINT eLogType, LPCTSTR lpszMsg, ... )
{
	if (!CheckLogOption(eLogType))
	{
		return false;
	}

	CString strMsg;

	MakeLogInfoHead(strMsg);

	va_list argList;
	va_start(argList, lpszMsg);
	strMsg.AppendFormatV(lpszMsg, argList);
	va_end( argList );

	strMsg.Append(_T("\r\n"));

	bool bRet = LogInfo(strMsg);

	return bRet;
}

bool CLog::CheckLogOption(UINT eLogType )
{
	if (eLogType == 0) //DEBUG LOG
	{
#ifndef _DEBUG
		return false;
#else
		return true;
#endif
	}

	if (!(m_LogOption & eLogType))
	{
		return false;
	}

	return true;
}

void CLog::MakeLogInfoHead(CString& strMsg)
{
	SYSTEMTIME systime = {0};
	
	GetLocalTime(&systime);

	strMsg.Format(_T("[%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		systime.wYear, systime.wMonth, systime.wDay, systime.wHour,
		systime.wMinute, systime.wSecond, systime.wMilliseconds);

	if (GetWithThreadId())
	{
		strMsg.AppendFormat(_T(" %04d]"), GetCurrentThreadId());
	}

	strMsg.Append(_T(" - "));

	if (m_LastDay != systime.wDay)
	{
		m_LastDay = systime.wDay;
		ChangeLogFileName();
	}

}

void CLog::ChangeLogFileName()
{

	if("" == m_LogPath)
		SetLogPath();

	if (!PathFileExists(m_LogPath))
	{
		SHCreateDirectoryEx(NULL, m_LogPath, NULL);
	}

	CString strFileName;
	
	SYSTEMTIME systime ={0};

	GetLocalTime(&systime);

	strFileName.AppendFormat(_T("%04d-%02d-%02d.log"), 
		systime.wYear,
		systime.wMonth,
		systime.wDay);

	if(IsHaveCustomName())
	{
		CString strTem = m_strCustomName;

		strTem.Append(strFileName);

		strFileName = strTem;
	}

	m_LogFileName = strFileName;

	OpenLogFile();

	if (GetAutoDelLogFile())
	{
		DelLogFiles();
	}
}

void CLog::OpenLogFile()
{
	CSingleLock(&m_cs, TRUE);

	m_LogFile.Abort();

	CFileException ex;

	UINT nOpenFlag = CFile::modeWrite | CFile::shareDenyNone; 

	if (!PathFileExists(m_LogPath + m_LogFileName))
	{
		nOpenFlag |= CFile::modeCreate;
	}

	if (!m_LogFile.Open(m_LogPath + m_LogFileName, nOpenFlag, &ex))
	{
		ex.ReportError();
		return;
	}

#ifdef _UNICODE
	if (nOpenFlag & CFile::modeCreate)
	{
		m_LogFile.Write("\xff\xfe", 2);
	}
#endif // _UNICODE
	
	m_LogFile.SeekToEnd();
}

CString CLog::GetLogPath() const
{
	return m_LogPath;
}

void CLog::SetLogPath(CString pszPath /* = NULL*/)
{		
	m_LogPath = "";

	if (pszPath.IsEmpty())
	{
		m_LogPath = GetAppPath()+"Log\\";
	}
	else
	{
		m_LogPath = pszPath;
	}
	
}


bool CLog::GetAutoDelLogFile() const
{
	return m_AutoDelLogFile;
}

void CLog::SetAutoDelLogFile( bool newVal )
{
	m_AutoDelLogFile = newVal;
}

UINT CLog::GetMaxLogFileNumber() const
{
	return m_MaxLogFileNumber;
}

void CLog::SetMaxLogFileNumber( UINT newVal )
{
	m_MaxLogFileNumber = newVal;
}

// 清空日志内容
long CLog::CleanLog(void)
{
	LONG nRet = 0;
	FILE* f = fopen( (LPSTR)(LPCTSTR)m_LogFileName, "w+" );
	if( f == NULL )
		return -1L;
	fclose( f );
	return 0L;
}

void CLog::DelLogFiles()
{
	COleDateTime dtNow = COleDateTime::GetCurrentTime();
	
	COleDateTimeSpan dts(m_MaxLogFileNumber, 0, 0, 0);
	
	dtNow -= dts;
	
	CTime ctMinTime(dtNow.GetYear(),dtNow.GetMonth(),dtNow.GetDay(),0,0,0);

	CFileFind finder;

	try
	{

		CString strLogFileName(GetLogPath() + _T("*.log"));

		BOOL bResult = finder.FindFile(strLogFileName);

		while (bResult)
		{
			bResult = finder.FindNextFile();
			CTime ctLastModifyTime;
			if (finder.GetLastWriteTime(ctLastModifyTime))
			{
				if ( ctLastModifyTime < ctMinTime)
				{
					DeleteFile(finder.GetFilePath());
				}
			}

		}

	}
	catch (...)
	{
		
	}

	finder.Close();

}

CString CLog::GetAppPath() const
{
	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strPath(szPath);
	strPath = strPath.Left(strPath.ReverseFind(_T('\\'))+1);
	return strPath;
}

bool CLog::IsNeedEncrypt()
{
     if(NULL == m_pPSK || m_iPSKLen<=0 || strlen(m_pPSK) != m_iPSKLen)
		 return FALSE;

	 return TRUE;
}

void CLog::SetEncrypt(CString strPSK)
{
	if(strPSK == "") return;

	if(m_pPSK != NULL)
	{
		delete m_pPSK;
		m_pPSK = NULL;
	}

	m_iPSKLen = strPSK.GetLength();

	m_pPSK = new char[m_iPSKLen+1];

	memset(m_pPSK,0,m_iPSKLen+1);

	strcpy(m_pPSK,strPSK);
}

void CLog::Encrypt(BYTE  *buffer,DWORD bufsize)
{

	if(NULL == buffer|| !IsNeedEncrypt()) return;

	DWORD num=0;
	
	while(num<bufsize)
	{	
		for(DWORD i=0;i<m_iPSKLen;i++)
		{
			buffer[num]^= m_pPSK[i];
		}
	
		num++;
	}

}