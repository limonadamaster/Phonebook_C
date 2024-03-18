#pragma once
#include "atldbcli.h"
#include <atldbcli.h>
#include <afxtempl.h>


#include <windows.h>
#include <oledb.h>
#include <atlbase.h>
#include <atlstr.h>
#include <iostream>

#define UNABLE_TO_CONNECT_WITH_DB  _T("Unable to connect with the database.")
#define SQLLEDB "SQLOLEDB.1"


class DataBaseSingleton : public CDataSource {
	//Make with pointer
private:
	CDataSource m_oDataSource;

	DataBaseSingleton() {
		InitializeDatabase();
	}

	~DataBaseSingleton() {
		m_oDataSource.Close();
	}

	DataBaseSingleton(const DataBaseSingleton&) = delete;
	DataBaseSingleton& operator=(const DataBaseSingleton&) = delete;

public:
	//TODO - Check if we have isntance 
	static DataBaseSingleton& GetInstance() {
		static DataBaseSingleton oDataBaseInstance;
		return oDataBaseInstance;
	}

	BOOL InitializeDatabase() {

		// Create and set Propset
		CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
		DBPropSetInitializer(oDBPropSet);

		// Check DB
		HRESULT hResult = m_oDataSource.Open(_T(SQLLEDB), &oDBPropSet);
		if (FAILED(hResult)) {
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}

		return TRUE;
	}

	void DBPropSetInitializer(CDBPropSet& oDBPropSet) {
		oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-E29C6J2\\MSSQLSERVER_WORK"));
		oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
		oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook_DB"));
		oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
		oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
		oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
	}
public:

};
