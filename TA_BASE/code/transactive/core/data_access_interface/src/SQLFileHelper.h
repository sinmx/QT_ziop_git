//////////////////////////////////////////////////////////////////////
///		@file		SQLFileHelper.h
///		@author		zhilin,ouyang
///		@date		2010-12-9 14:44:41
///
///		@brief	    to load the sql.dat file and store the SQL statements
///                 into a hash-table for later retrieve.
//////////////////////////////////////////////////////////////////////
#ifndef SQLFILEHELPER_H
#define SQLFILEHELPER_H
#include "SQLCommonDef.h"
#include <string>
#include <vector>
#include "boost/unordered_map.hpp"
#include "core/database/src/CommonType.h"

NS_BEGIN(TA_Base_Core)

class SQLFileHelper
{
private:	
	typedef  unsigned long   u_long;
	typedef boost::unordered_map<u_long, std::string> SQLHashTable;
	typedef boost::unordered_map<u_long, std::string>::value_type SQLValueType; 

	typedef boost::unordered_map<std::string, std::string> strSQLHashTableT;
	typedef boost::unordered_map<std::string, std::string>::value_type strSQLValueType;
	typedef std::vector<std::string>::const_iterator cStrIterT;


public:
	// SQLFileHelper Constructors and destructor
	SQLFileHelper();
	SQLFileHelper(const char* pszSQLFile);
	~SQLFileHelper();

	/**
	* GetSQLString
	*
	* @brief: to retrieve the SQL statement from the hash-table which
	*         store the SQL statements loaded from the sql.dat file.
	*         It's match the SQL statement based on the input SQL ID
	*
	* @param  pszSQLID  the SQL statement id which map into
	*                   the sql.dat file
	* Returns the SQL statement.
	*/
	std::string getSQLString(u_long uSQLID);

	/**
	* GetSQLString
	*
	* @brief: to retrieve the SQL statement from the hash-table which
	*         store the SQL statements loaded from the sql.dat file.
	*         It's match the SQL statement based on the input SQL Key
	*
	* @param  pszSQLID  the SQL statement key which map into
	*                   the sql.dat file
	* Returns the SQL statement.
	*/
	std::string getSQLString(int nDbType, const std::string& strSQLKey);
	void  getSQLString(const std::string& strSQLKey, SQLStatement& rSqlStatements);

#if defSQL_MODE_TXT
private:
	bool _LoadSQLFile();
	bool _DeEncrySQLFile(const std::string&);
	bool _ReadAllLines(std::vector<std::string>&, const std::string&);
	bool _FillHashData(const std::vector<std::string>&);
	bool _FillAllHashData(const std::vector<std::string>&);
	void _FillOneHashData(cStrIterT&, strSQLHashTableT&, cStrIterT&);
#endif  // end of text mode

private:

	std::string  m_strSQLFile;
	SQLHashTable m_SQLHashTable;

	strSQLHashTableT m_SQLCommonHashTable;
	strSQLHashTableT m_SQLOracleHashTable;
	strSQLHashTableT m_SQLMySQLHashTable;
};

NS_END(TA_Base_Core)

#endif  /// SQLFILEHELPER_H
