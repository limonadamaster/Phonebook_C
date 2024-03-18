#include "pch.h"
#include "CitiesData.h"
#include "CitiesTable.h"

CCitiesData::CCitiesData() {

}
CCitiesData:: ~CCitiesData() {

}

// Selecting all cities from city table
BOOL CCitiesData::SelectAllFromCities(CCitiesTypedPtrArray& oCitiesArray) {
	//Select all records from DB
	BOOL bSelected = oCitiesTable.SelectAll(oCitiesArray);

	//Check that select is correct
	if (!bSelected)
	{
		return FALSE;
	}

	return TRUE;

}

// Selecting city by ID 
BOOL CCitiesData::SelectWhereIdFromCities(const long lID, CITIES& recCities) {
	//Select the record by ID
	BOOL bFinded = oCitiesTable.SelectWhereID(lID, recCities);

	//Check that select is correct
	if (!bFinded)
	{
		return FALSE;
	}

	return TRUE;
}

/// Updating record into DB
BOOL CCitiesData::UpdateWhereID(const long lID, CITIES& recCities) {
	//Perform update operation
	BOOL bUpdated = oCitiesTable.UpdateWhereID(lID, recCities);

	//Check that update is correct
	if (!bUpdated)
	{
		return FALSE;
	}

	return TRUE;
}

/// Inserting new record into DB
BOOL CCitiesData::InsertInCities(CITIES& recCities) {
	//Perform insertt operation
	BOOL bInserted = oCitiesTable.Insert(recCities);

	//Check that insert is correct
	if (!bInserted)
	{
		return FALSE;
	}

	return TRUE;
}

// Deleting record from DB
BOOL CCitiesData::DeleteWhereIdInCities(long lID) {
	//Perform delete operation
	BOOL bDeleted = oCitiesTable.DeleteWhereID(lID);

	//Check that insert is correct
	if (!bDeleted)
	{
		return FALSE;
	}

	return TRUE;
}

