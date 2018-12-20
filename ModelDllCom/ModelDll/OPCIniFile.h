//////////////////////////////////////////////////////////////////////
// OPCIniFile.h   :  读取标准INI配置文件, 不提供搜索功能以提高读取速度
// Comment     :  首先用Open打开文件, 然后用ReadIniString或者ReadSection
//             :  读取需要的内容,全部读完后用Close关闭文件.
//             :  请查阅开发说明了解配置文件格式。
// Author      :  邹超群
// Date        :  2002.11.04
//                2003.05.30  将参数类型由const CString&改为LPCSTR
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__A7E1E6C3_2787_43A2_B887_6BD009D7EA47__INCLUDED_)
#define AFX_INIFILE_H__A7E1E6C3_2787_43A2_B887_6BD009D7EA47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COPCIniFile : public CStdioFile  
{
public:
	COPCIniFile();
	virtual ~COPCIniFile();
  
  // 顺序读取配置文件的一行内容，必须按照文件中的顺序依次读取
  //以分号（';'）开始的行为注释行
  // 不能跳过非空行，该行形如 Name=Value
  // 应指定pszName=Name，sValue用来接收结果
  // 其中 Name不能以'['开始，以区别于[Section]
  BOOL ReadIniString(LPCSTR pszName, CString& sValue);
  
  // 顺序读取配置文件中的一行节号，必须按照文件中的顺序依次读取
  // 自动跳过空行和注释行，该行形如 [Section]
  // 应指定pszSection=[Section]，用来核对配置文件中的内容是否正确
  BOOL ReadSection(LPCSTR pszSection);
  
	// 读取配置文件的一个配置项，在节内无须按照文件中的顺序依次读取
	// 要求项目名称在节内唯一
	BOOL ReadIniUniItem(LPCSTR pszSection,LPCSTR pszName, CString& sValue);
	
	// 顺序读取配置文件的一个配置项，忽略非法行
	BOOL ReadIniItem(LPCSTR pszName, CString& sValue);
	// 读取配置文件中的一行节号，无须按照文件中的顺序依次读取
	BOOL ReadNoSeqSection(LPCSTR pszSection);

	//提取字段值，字段之间以逗号（','）分隔
	BOOL ExtractSubValue(LPCSTR pszSrc,CString& strValue,int nSplit)const;
	
	// 计算节内有效的ITEM项数量
	int GetItemsCount(LPCSTR pszSection,LPCSTR pszItem);

	BOOL Endof(){ return feof(m_pStream) ? TRUE : FALSE; }

};

#endif // !defined(AFX_INIFILE_H__A7E1E6C3_2787_43A2_B887_6BD009D7EA47__INCLUDED_)

