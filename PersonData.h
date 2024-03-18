#pragma once
#include "Persons.h"
#include "CPerson.h"
#include "PhoneTypes.h"
#include "PersonTable.h"
#include "CitiesTable.h"
#include "PhoneTypesTable.h"
#include "PhoneNumbersTable.h"

/// <summary>
/// Connection with table class for separating the DB from Application
/// </summary>
class CPersonData
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPersonData();
	virtual ~CPersonData();


	// Methods
	// ----------------
	/// <summary>
	/// Method for getting all records from DB table CITIES
	/// </summary>
	/// <param name="oCitiesArray">CTypedPtrArray which store records</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL SelectAllFromPersons(CPersonsTypedPtrArray& oPersonArray);
	/// <summary>
	/// Method for getting specific element from DB table CITIES
	/// </summary>
	/// <param name="lID">ID for searching</param>
	/// <param name="recCities">Variable for saving founded record</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL SelectWhereIdFromPersons(const long lID, PERSONS& recPerson);
	/// <summary>
	/// Method for updating record in DB table CITIES
	/// </summary>
	/// <param name="lID">ID for searching</param>
	/// <param name="recCities">Variable where we store and then update founded data</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL UpdateWhereID(const long lID, PERSONS& recPerson);
	/// <summary>
	/// Method which insert new data into DB
	/// </summary>
	/// <param name="recCities">Variable which stores the new data </param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL InsertInPersons(PERSONS& recPerson);
	/// <summary>
	/// Method which delete record from DB
	/// </summary>
	/// <param name="lID"> ID for searching</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL DeleteWhereIdInPersons(const long lID);

	BOOL SetPersonCity(CPerson* pPerson, CCitiesTypedPtrArray& oCitiesArray);

	BOOL SetPersonNumbersAndPhoneTypes(CPerson* pPerson, CPhoneNumbersTypedPtrArray& oPhoneNumbersArray, CPhoneTypesTypedPtrArray& oPhoneTypesArray);


	/// <summary>
	/// This method will retunr all data from tables we need
	/// </summary>
	/// <returns>
	/// TRUE - if selected all data
	/// FALSE - if we catch and error
	/// </returns>




	BOOL CreatePersons(CPersonDataTypedPtrArray& m_oPersonDataTypedArray);

	void SetPhoneNumberPersonId(PERSONS& recPerson, CPhoneNumbersTypedPtrArray& currentPersonPhoneNumberArray, CPhoneTypesTypedPtrArray& currentPersonPhoneTypesArray);

	BOOL InsertCPersonDataIntoDB(CPerson& recCPerson);

	BOOL DelteteDataFromDB(CPerson& recCPerson);

	BOOL UpdateDataFromDB(CPerson& recPersonOld, CPerson& recPersonNew);

	CCitiesTypedPtrArray& GetCities();

	CPhoneTypesTypedPtrArray& GetPhoneTypes();

	void CPersonData::SetTypeRowSet(CDBPropSet& oUpdateDBPropSet);

	// Overrides
	// ----------------


	// Members
	// ----------------

	/// <summary>
	/// Members wich represent table objects
	/// </summary>
	CPersonTable m_oPersonTable;
	CCitiesTable m_oCitiesTable;
	CPhoneNumbersTable m_oPhoneNumbersTable;
	CPhoneTypesTable m_oPhoneTypesTable;

	/// <summary>
	/// Members which represent storage for data
	/// </summary>
	CPersonsTypedPtrArray m_oPersonArray;
	CCitiesTypedPtrArray m_oCitiesArray;
	CPhoneNumbersTypedPtrArray m_oPhoneNumbersArray;
	CPhoneTypesTypedPtrArray m_oPhoneTypesArray;

	/// <summary>
	/// Member for session
	/// </summary>
	CSession m_oSession;

	/// <summary>
	/// Member which represent storage for transprt class
	/// </summary>
	CPersonDataTypedPtrArray m_oPersonDataTypedArray;


};