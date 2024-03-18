#pragma once

#include <iostream>
#include <cstring>
#include "CitiesAccessor.h"
#include "PersonsAccessor.h"
#include "PhoneNumbersAccessor.h"
#include "PhoneTypesAccessor.h"
#include "Cities.h"
#include "Persons.h"
#include "PhoneNumbers.h"
#include "PhoneTypes.h"
#include "CTypedPtrArraySelfClean.h"
#include "DataBaseSingleton.h"



#define UNABLE_TO_OPEN_SESSION _T("Unable to open session.")
#define UNABLE_TO_EXECUTE_QUERY _T("Unable to execute query.")
#define UNABLE_TO_OPEN_RECORD _T("Unable to open record.")
#define UNABLE_TO_INSERT_RECORD _T("Unable to insert record.")
#define UNABLE_TO_START_TRANSACTION _T("Unable to start transaction.")
#define UNABLE_TO_COMMIT_TRANSACTION _T("Unable to commit transaction.")
#define UNABLE_TO_UPDATE_COUNTER _T("Update counter error.")

#define SQLLEDB "SQLOLEDB.1"
#define FORMAT_CITIES _T("ID: %d, City Name: %s, Distict: %s")



template <typename RecordType, typename Access, typename TypedPtrAray>
class CTableBase : private CCommand<CAccessor<Access>>
{
public:
	CTableBase() {};
	virtual ~CTableBase() {};

	BOOL SelectAll(TypedPtrAray& oDataArray) {
		// Initialize DB, Session, and Propset
		if (!InitializeDatabase())
		{
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}

		// Execute the SELECT query and read data into the array
		if (!ExecuteSelectAllQuery(oDataArray))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}
		// Close the database and return the result
		CloseDatabase();
		return TRUE;
	};
	BOOL SelectWhereID(const long lID, RecordType& recData) {
		// Initialize DB, Session, and Propset
		if (!InitializeDatabase())
		{
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}
		// Construct query
		CString strQuery;
		strQuery.Format(QUERY_SELECT_WHERE_ID, lID);

		// Execute the select by ID query 
		if (!ExecuteSelectByIDQuery(strQuery, recData))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}
		// Close the database and return the result
		CloseDatabase();
		return TRUE;
	};
	BOOL UpdateWhereID(const long lID, RecordType& recData) {
		// Initialize DB, Session, and Propset
		if (!InitializeDatabase())
		{
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}
		// Start the transaction
		HRESULT hResult = m_oSession.StartTransaction(ISOLATIONLEVEL_READCOMMITTED);

		if (hResult != S_OK) {
			MessageBox(NULL, UNABLE_TO_START_TRANSACTION, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}
		// The query
		CString strQuery;
		strQuery.Format(QUERY_UPDATE_WHERE_ID, lID);

		//Update
		if (!ExecuteUpdateQuery(strQuery, recData))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			m_oSession.Abort();
			CloseDatabase();
			return FALSE;
		}
		// Close the database and return the result 
		if (m_oSession.Commit() != S_OK) {
			MessageBox(NULL, UNABLE_TO_COMMIT_TRANSACTION, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}
		CloseDatabase();
		return TRUE;
	};
	BOOL Insert(RecordType& recData) {
		// Initialize DB, Session, and Propset
		if (!InitializeDatabase())
		{
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}

		// Execute the INSERT query and insert the record
		CString strQuery;
		strQuery.Format(QUERY_INSERT);

		if (!ExecuteInsertQuery(strQuery, recData))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		// Close the database and return the result
		CloseDatabase();
		return TRUE;
	};
	BOOL DeleteWhereID(const long lID) {
		// Initialize DB, Session, and Propset
		if (!InitializeDatabase())
		{
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}

		// Execute the DELETE query and delete the record
		CString strQuery;
		strQuery.Format(QUERY_SELECT_WHERE_ID, lID);


		if (!ExecuteDeleteQuery(strQuery))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		// Close the database and return the result
		CloseDatabase();
		return TRUE;
	};

private:
	CString QUERY_SELECT_ALL = _T("SELECT * FROM [") + GetTableName() + _T("]");
	CString QUERY_SELECT_WHERE_ID = _T("SELECT * FROM [") + GetTableName() + _T("] WHERE [ID] = %d");
	CString QUERY_UPDATE_WHERE_ID = _T("SELECT * FROM [") + GetTableName() + _T("] WITH (UPDLOCK) WHERE ID = %d;");
	CString QUERY_INSERT = _T("SELECT TOP 0 * FROM [") + GetTableName() + _T("]");

	void DBPropSetInitializer(CDBPropSet& oDBPropSet)
	{
		oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-E29C6J2\\MSSQLSERVER_WORK"));
		oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
		oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook_DB"));
		oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
		oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
		oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
	};
	void SetTypeRowSet(CDBPropSet& oUpdateDBPropSet)
	{
		oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

	};
	BOOL InitializeDatabase() {
		//Check if DB is opened

		//Create and set Propset
		CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
		DBPropSetInitializer(oDBPropSet);

		// Check DB
		HRESULT hResult = m_oDataSource.Open(_T(SQLLEDB), &oDBPropSet);
		if (FAILED(hResult)) {
			MessageBox(NULL, UNABLE_TO_CONNECT_WITH_DB, NULL, MB_OK);
			return FALSE;
		}


		//Check session
		hResult = m_oSession.Open(m_oDataSource);
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			return FALSE;
		}

		return TRUE;
	};
	BOOL ExecuteSelectAllQuery(TypedPtrAray& oDataArray)
	{

		HRESULT hResult = Open(m_oSession, QUERY_SELECT_ALL);
		// Execute query
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		// Read all data and add it to the array 
		while (MoveNext() == S_OK)
		{
			//Create the dynamic pointer
			RecordType* pRecCity = new RecordType;
			std::memcpy(pRecCity, &m_recAccessorData, sizeof(RecordType));


			//Add them to the array
			oDataArray.Add(pRecCity);


		}

		return TRUE;
	};

	BOOL ExecuteSelectByIDQuery(const CString& QUERY, RecordType& recData) {



		HRESULT hResult = Open(m_oSession, QUERY);
		// Execute query
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		//Move it first
		hResult = MoveFirst();
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_OPEN_RECORD, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		//Save the record
		std::memcpy(&recData, &m_recAccessorData, sizeof(RecordType));


		return TRUE;
	};
	BOOL ExecuteUpdateQuery(const CString& QUERY, RecordType& recData)
	{//Create and set Propset
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		SetTypeRowSet(oUpdateDBPropSet);


		HRESULT hResult = Open(m_oSession, QUERY, &oUpdateDBPropSet);
		// Execute query
		if (FAILED(hResult))
		{
			return FALSE;
		}

		// Move to the first record
		hResult = MoveFirst();
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_OPEN_RECORD, NULL, MB_OK);
			return FALSE;
		}

		// Check and update the record
		// Check counters

		if (recData.lUpdateCounter != m_recAccessorData.lUpdateCounter)
		{
			MessageBox(NULL, UNABLE_TO_UPDATE_COUNTER, NULL, MB_OK);
			return FALSE;
		}

		// Update counter and the record
		std::memcpy(&m_recAccessorData, &recData, sizeof(RecordType));
		m_recAccessorData.lUpdateCounter++;
		recData.lUpdateCounter++;

		// Update the record
		hResult = SetData(1);
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_OPEN_RECORD, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		return TRUE;
	};
	BOOL ExecuteInsertQuery(const CString& QUERY, RecordType& recData)
	{
		CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
		SetTypeRowSet(oInsertDBPropSet);
		// Create and open a new rowset object


		// Execute query
		HRESULT hResult = Open(m_oSession, QUERY, &oInsertDBPropSet);
		if (FAILED(hResult))
		{
			CloseDatabase();
			return 0;
		}

		// Move to the first record
		hResult = MoveFirst();
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_OPEN_RECORD, NULL, MB_OK);
			return 0;
		}
		// Take the data
		std::memcpy(&m_recAccessorData, &recData, sizeof(RecordType));
		// Insert the data
		hResult = ATL::CRowset<ATL::CAccessor<Access>>::Insert(1);

		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_INSERT_RECORD, NULL, MB_OK);
			return 0;
		}
		hResult = MoveFirst();
		std::memcpy(&recData, &m_recAccessorData, sizeof(RecordType));
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_OPEN_RECORD, NULL, MB_OK);
			return 0;
		}

		return TRUE;
	};
	BOOL ExecuteDeleteQuery(const CString& strQuery) {
		CDBPropSet oDeleteDBPropSet(DBPROPSET_ROWSET);
		SetTypeRowSet(oDeleteDBPropSet);

		// Get the result
		HRESULT hResult = Open(m_oSession, strQuery, &oDeleteDBPropSet);
		if (FAILED(hResult))
		{

			MessageBox(NULL, UNABLE_TO_EXECUTE_QUERY, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		//Move to next record
		hResult = MoveNext();
		if (FAILED(hResult))
		{
			MessageBox(NULL, UNABLE_TO_OPEN_RECORD, NULL, MB_OK);
			CloseDatabase();
			return FALSE;
		}

		// Delete the record 
		hResult = Delete();

		if (FAILED(hResult))
		{
			CloseDatabase();
			return FALSE;
		}


		// Close the command, close the session, close the DB
		CloseDatabase();
		return TRUE;
	};
	void CloseDatabase() {
		Close();
		m_oSession.Close();
	};
	CString GetTableName() {
		CString typeName;
		typeName = typeid(RecordType).name();

		if (typeName.Left(7) == "struct ") {
			typeName = typeName.Mid(7);
		}

		return typeName;
	};

	// Members
	// ----------------
private:
	/// <summary>
	/// This memeber is our data soruce 
	/// </summary>
	DataBaseSingleton& m_oDataSource = DataBaseSingleton::GetInstance();
	//This memeber is our session
	CSession m_oSession;
	bool m_bIsDatabaseInitialized;

};
