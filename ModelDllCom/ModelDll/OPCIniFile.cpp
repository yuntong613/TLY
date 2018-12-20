// OPCIniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPCIniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COPCIniFile::COPCIniFile()
{
}

COPCIniFile::~COPCIniFile()
{
}

BOOL COPCIniFile::ReadIniString(LPCSTR pszName, CString& sValue)
{
   if (m_hFile == hFileNull)
     return FALSE;
   
   DWORD dwPosition = (DWORD)GetPosition();
   
   CString strBuf, strSub;
   
   do
   {
      if (!ReadString(strBuf))
      {
         Seek(dwPosition, CFile::begin);
         return FALSE;
      }
      strBuf.TrimLeft();
      strBuf.TrimRight();
      
   }while ( (strBuf.GetLength() < 1) || (strBuf[0] == _T(';')));// || (strBuf[0] == _T('[')) );
   
   int nSubPos = strBuf.Find(_T("="), 0);
   if (nSubPos < 1)
   {
      Seek(dwPosition, CFile::begin);
      return FALSE;
   }
   int i=0;
   for(i=0;i<nSubPos;i++){
	   if((strBuf[i] >= '0') && (strBuf[i] <= '9')) break;
   }
   strSub = strBuf.Left(i);
   if (strSub.CompareNoCase(pszName) != 0)
   {
      Seek(dwPosition, CFile::begin);
      return FALSE;
   }
   
   sValue = strBuf.Right(strBuf.GetLength() - nSubPos - 1);
   return TRUE;
}

BOOL COPCIniFile::ReadSection(LPCSTR pszSection)
{
   if (m_hFile == hFileNull)
     return FALSE;
   
   CString strBuf;
   DWORD dwPosition = (DWORD)GetPosition();
   
   do
   {
      if (!ReadString(strBuf))
      {
         Seek(dwPosition, CFile::begin);
         return FALSE;
      }
      strBuf.TrimLeft();
      strBuf.TrimRight();
      
   }while ( (strBuf.GetLength() < 1) || (strBuf.Find(_T(';')) == 0) );
   
   if (strBuf.CompareNoCase(pszSection) != 0)
   {
      Seek(dwPosition, CFile::begin);
      return FALSE;
   }
   
   return TRUE;
}

BOOL COPCIniFile::ReadNoSeqSection(LPCSTR pszSection)
{
	if (m_hFile == hFileNull) return FALSE;

	CString strSection(_T("["));strSection += pszSection;strSection += _T(']');
	CString strBuf;

	//search from current position
	if(ReadSection(strSection))return TRUE;
	Seek(0L, CFile::begin);
	//search from CFile::begin
	do{
		if(ReadSection(strSection))return TRUE;
	}while(ReadString(strBuf));
	return FALSE;
}

BOOL COPCIniFile::ReadIniUniItem(LPCSTR pszSection,LPCSTR pszName, CString& sValue)
{
	if (m_hFile == hFileNull) return FALSE;
	DWORD dwPosition;
	Seek(0L, CFile::begin);
	if(! ReadNoSeqSection(pszSection)) return FALSE;
	dwPosition = (DWORD)GetPosition();
	while(! Endof()){
		if(ReadIniString(pszName,sValue)) return TRUE;
		dwPosition = (DWORD)GetPosition();
		if(! ReadString(sValue)) break;
		if(sValue.Find('[') == 0){
			Seek(dwPosition, CFile::begin);
			break;
		}
	}
	return FALSE;
}

BOOL COPCIniFile::ReadIniItem(LPCSTR pszName, CString& sValue)
{
	if (m_hFile == hFileNull) return FALSE;
	DWORD dwPosition = (DWORD)GetPosition();
	while(! Endof()){
		if(ReadIniString(pszName,sValue)) return TRUE;
		dwPosition = (DWORD)GetPosition();
		if(! ReadString(sValue)) break;
		if(sValue.Find(_T('[')) == 0){
			Seek(dwPosition,CFile::begin);
			break;
		}
	}
	return FALSE;
}

int COPCIniFile::GetItemsCount(LPCSTR pszSection,LPCSTR pszItem)
{
	if(! ReadNoSeqSection(pszSection)) return 0;
	int nItems = 0;
	DWORD dwPosition = (DWORD)GetPosition();
	CString strBuf;
	while(! Endof())
	{
		if(ReadIniString(pszItem,strBuf)) nItems++;
		else{
			ReadString(strBuf);
			if(strBuf.Find('[') == 0) break;
		}
	}
	Seek(dwPosition,CFile::begin);
	return nItems;
}

BOOL COPCIniFile::ExtractSubValue(LPCSTR pszSrc,CString& strValue,int nSplit)const
{
	const char cSplit(',');
	int iPos=0,iPos1=0,iPos2=0;
	CString strTmp(_T(pszSrc));
	while(nSplit>1){
		if((iPos=strTmp.Find(cSplit,iPos))>0){
			--nSplit;
//			iPos1=iPos2;
			iPos2=iPos++;
		}
		else return FALSE;
	}
	iPos1= (iPos2 > 0) ? (iPos2 + 1) : 0;
	iPos=strTmp.Find(cSplit,iPos);
	iPos2=(iPos>0) ? iPos : (strTmp.GetLength()+1);
	strValue=strTmp.Mid(iPos1,iPos2-iPos1);
	return TRUE;
}
