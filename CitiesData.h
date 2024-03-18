#pragma once
#include "Cities.h"
#include "CitiesTable.h"

/// <summary>
/// Connection with table class for separating the DB from Application
/// </summary>
class CCitiesData
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CCitiesData();
	virtual ~CCitiesData();


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
	BOOL SelectAllFromCities(CCitiesTypedPtrArray& oCitiesArray);
	/// <summary>
	/// Method for getting specific element from DB table CITIES
	/// </summary>
	/// <param name="lID">ID for searching</param>
	/// <param name="recCities">Variable for saving founded record</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL SelectWhereIdFromCities(const long lID, CITIES& recCities);
	/// <summary>
	/// Method for updating record in DB table CITIES
	/// </summary>
	/// <param name="lID">ID for searching</param>
	/// <param name="recCities">Variable where we store and then update founded data</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL UpdateWhereID(const long lID, CITIES& recCities);
	/// <summary>
	/// Method which insert new data into DB
	/// </summary>
	/// <param name="recCities">Variable which stores the new data </param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL InsertInCities(CITIES& recCities);
	/// <summary>
	/// Method which delete record from DB
	/// </summary>
	/// <param name="lID"> ID for searching</param>
	/// <returns>
	/// TRUE -> If the operation is valid
	/// FALSE -> If the opreation is not valid
	/// </returns>
	BOOL DeleteWhereIdInCities(const long lID);

	// Overrides
	// ----------------


	// Members
	// ----------------

	/// <summary>
	/// Member wich represent table object
	/// </summary>
	CCitiesTable oCitiesTable;


};