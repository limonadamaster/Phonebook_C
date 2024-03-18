#include "pch.h"
#include "PersonData.h"
#include "PersonTable.h"
#include "DataBaseSingleton.h"

CPersonData::CPersonData() {

}
CPersonData:: ~CPersonData() {

}

// Selecting all cities from city table
BOOL CPersonData::SelectAllFromPersons(CPersonsTypedPtrArray& oPersonArray) {
	//Select all records from DB
	BOOL bSelected = m_oPersonTable.SelectAll(oPersonArray);

	//Check that select is correct
	if (!bSelected)
	{
		return FALSE;
	}

	return TRUE;

}

// Selecting city by ID 
BOOL CPersonData::SelectWhereIdFromPersons(const long lID, PERSONS& recPerson) {
	//Select the record by ID
	BOOL bFinded = m_oPersonTable.SelectWhereID(lID, recPerson);

	//Check that select is correct
	if (!bFinded)
	{
		return FALSE;
	}

	return TRUE;
}

/// Updating record into DB
BOOL CPersonData::UpdateWhereID(const long lID, PERSONS& recPerson) {
	//Perform update operation
	BOOL bUpdated = m_oPersonTable.UpdateWhereID(lID, recPerson);

	//Check that update is correct
	if (!bUpdated)
	{
		return FALSE;
	}

	return TRUE;
}

/// Inserting new record into DB
BOOL CPersonData::InsertInPersons(PERSONS& recPerson) {
	//Perform insertt operation
	BOOL bInserted = m_oPersonTable.Insert(recPerson);

	//Check that insert is correct
	if (!bInserted)
	{
		return FALSE;
	}

	return TRUE;
}

// Deleting record from DB
BOOL CPersonData::DeleteWhereIdInPersons(long lID) {
	//Perform delete operation
	BOOL bDeleted = m_oPersonTable.DeleteWhereID(lID);

	//Check that insert is correct
	if (!bDeleted)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonData::SetPersonCity(CPerson* pPerson, CCitiesTypedPtrArray& oCitiesArray) {

	CString strCityName;

	if (pPerson == nullptr) {
		return FALSE;
	}

	for (INT_PTR nIndex = 0; nIndex < oCitiesArray.GetCount(); nIndex++) {
		CITIES* pCurrentCity = oCitiesArray.GetAt(nIndex);
		if (pCurrentCity && pCurrentCity->lId == pPerson->GetPerson().lCityId) {
			strCityName = pCurrentCity->szCityName;
			pPerson->strCityName = strCityName;
			break;
		}
	}

	return TRUE;
}






BOOL CPersonData::SetPersonNumbersAndPhoneTypes(CPerson* pPerson, CPhoneNumbersTypedPtrArray& oPhoneNumbersArray, CPhoneTypesTypedPtrArray& oPhoneTypesArray) {

	if (pPerson == nullptr) {
		return FALSE;
	}

	if (oPhoneNumbersArray.IsEmpty()) {
		return FALSE;
	}

	if (oPhoneTypesArray.IsEmpty()) {
		return FALSE;
	}

	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++) {

		PHONE_NUMBERS* pCurrentNumber = oPhoneNumbersArray.GetAt(nIndex);

		if (pCurrentNumber && pCurrentNumber->lPersonId == pPerson->GetPerson().lId) {
			pPerson->personPhoneNumbers.Add(pCurrentNumber);

			for (INT_PTR nIndx = 0; nIndx < oPhoneTypesArray.GetCount(); nIndx++)
			{
				PHONE_TYPES* pCurrentType = oPhoneTypesArray.GetAt(nIndx);

				if (pCurrentType && pCurrentNumber->lPhoneTypeId == pCurrentType->lId) {
					pPerson->personPhoneTypes.Add(pCurrentType);
					break;
				}
			}
		}

	}
	return TRUE;
}


BOOL CPersonData::CreatePersons(CPersonDataTypedPtrArray& m_oPersonDataTypedArray) {

	if (!m_oPersonTable.SelectAll(m_oPersonArray)) {
		return FALSE;
	}

	if (!m_oCitiesTable.SelectAll(m_oCitiesArray)) {
		return FALSE;
	};
	if (!m_oPhoneNumbersTable.SelectAll(m_oPhoneNumbersArray)) {
		return FALSE;
	};
	if (!m_oPhoneTypesTable.SelectAll(m_oPhoneTypesArray)) {
		return FALSE;
	};
	for (INT_PTR nIndex = 0; nIndex < m_oPersonArray.GetCount(); nIndex++) {
		PERSONS* pCurrentPerson = m_oPersonArray.GetAt(nIndex);
		CPerson* pPerson = new CPerson(pCurrentPerson);
		SetPersonCity(pPerson, m_oCitiesArray);
		SetPersonNumbersAndPhoneTypes(pPerson, m_oPhoneNumbersArray, m_oPhoneTypesArray);
		m_oPersonDataTypedArray.Add(pPerson);
	}
	return TRUE;


}

void CPersonData::SetPhoneNumberPersonId(PERSONS& recPerson, CPhoneNumbersTypedPtrArray& currentPersonPhoneNumberArray, CPhoneTypesTypedPtrArray& currentPersonPhoneTypesArray) {

	for (INT_PTR nIndex = 0; nIndex < currentPersonPhoneNumberArray.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = currentPersonPhoneNumberArray.GetAt(nIndex);
		pPhoneNumber->lPersonId = recPerson.lId;

	}
}




BOOL CPersonData::InsertCPersonDataIntoDB(CPerson& recCPerson) {

	//// Open DB connection using singleton class 
	//DataBaseSingleton& oDataBaseSingleton = DataBaseSingleton::GetInstance();

	////Open and seeting session
	//CSession oSession;

	//// Set the PropSet
	//CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
	//SetTypeRowSet(oInsertDBPropSet);

	//// Start transaction
	//if (SUCCEEDED(oSession.StartTransaction())) {
	//	oSession.Abort();
	//	oSession.Close();
	//	return FALSE;

	//}

	if (!m_oPersonTable.Insert(recCPerson.recPerson))
	{
		//oSession.Abort();
		//oSession.Close();
		return FALSE;

	}

	CPhoneNumbersTypedPtrArray& currentPersonPhoneNumberArray = recCPerson.personPhoneNumbers;
	CPhoneTypesTypedPtrArray& currentPersonPhoneTypesArray = recCPerson.personPhoneTypes;

	for (INT_PTR nIndex = 0; nIndex < currentPersonPhoneNumberArray.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = currentPersonPhoneNumberArray.GetAt(nIndex);
		pPhoneNumber->lPersonId = recCPerson.recPerson.lId;

		if (!m_oPhoneNumbersTable.Insert(*pPhoneNumber))
		{
			//oSession.Abort();
			//oSession.Close();
			return FALSE;

		}
	}

	for (INT_PTR nIndx = 0; nIndx < currentPersonPhoneTypesArray.GetCount(); nIndx++)
	{
		PHONE_TYPES* pPhoneType = currentPersonPhoneTypesArray.GetAt(nIndx);
		if (!m_oPhoneTypesTable.Insert(*pPhoneType))
		{
			//oSession.Abort();
			//oSession.Close();
			return FALSE;
		}
	}




	//oSession.Commit();
	//oSession.Close();
	return TRUE;



}


BOOL CPersonData::DelteteDataFromDB(CPerson& recCPerson) {
	//// Open DB connection using singleton class 
	//DataBaseSingleton& oDataBaseSingleton = DataBaseSingleton::GetInstance();

	////Open and seeting session
	//CSession oSession;

	//// Set the PropSet
	//CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
	//SetTypeRowSet(oInsertDBPropSet);

	//// Start transaction
	//if (SUCCEEDED(oSession.StartTransaction())) {
	//	oSession.Abort();
	//	oSession.Close();
	//	return FALSE;

	//}



	for (INT_PTR nIndex = 0; nIndex < recCPerson.personPhoneNumbers.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* currentPhoneNumber = recCPerson.personPhoneNumbers.GetAt(nIndex);

		if (!m_oPhoneNumbersTable.DeleteWhereID(currentPhoneNumber->lId)) {
			//oSession.Abort();
			//oSession.Close();
			return FALSE;
		}

	}



	if (!m_oPersonTable.DeleteWhereID(recCPerson.GetPerson().lId))
	{
		//oSession.Abort();
		//oSession.Close();
		return FALSE;

	}


	//oSession.Commit();
	//oSession.Close();
	//return TRUE;



}



BOOL CPersonData::UpdateDataFromDB(CPerson& recPersonOld, CPerson& recPersonNew) {


	//TODO session

	CPhoneNumbersTypedPtrArray& oldPersonPhoneNumberArray = recPersonOld.personPhoneNumbers;
	CPhoneTypesTypedPtrArray& oldPersonPhoneTypesArray = recPersonOld.personPhoneTypes;


	CPhoneNumbersTypedPtrArray& newPersonPhoneNumberArray = recPersonNew.personPhoneNumbers;
	CPhoneTypesTypedPtrArray& newPersonPhoneTypesArray = recPersonNew.personPhoneTypes;



	// Iterate array after user edit data
	for (int i = 0; i < newPersonPhoneNumberArray.GetSize(); ++i)
	{
		// Get phone number from this array
		PHONE_NUMBERS* newPhoneNumber = newPersonPhoneNumberArray.GetAt(i);

		// Iterate array before user edit data
		for (int j = 0; j < oldPersonPhoneNumberArray.GetSize(); ++j)
		{
			// Get phone number from this array
			PHONE_NUMBERS* oldPhoneNumber = oldPersonPhoneNumberArray.GetAt(j);

			// Check if the IDs are the same
			if (newPhoneNumber->lId != oldPhoneNumber->lId)
			{
				// Perform update with old phone number id and new one 
				if (!m_oPhoneNumbersTable.Insert(*newPhoneNumber))
				{
					//oSession.Abort();
					//oSession.Close();
					return FALSE;

				}

			}
			else {

			}
		}


	}

	// Iterate the old phone numbers
	for (int i = 0; i < oldPersonPhoneNumberArray.GetSize(); ++i)
	{
		//Get old phone number
		PHONE_NUMBERS* oldPhoneNumber = oldPersonPhoneNumberArray.GetAt(i);
		bool found = false;

		// Iterate the new phone numbers
		for (int j = 0; j < newPersonPhoneNumberArray.GetSize(); ++j)
		{
			// Get new phone number
			PHONE_NUMBERS* newPhoneNumber = newPersonPhoneNumberArray.GetAt(j);

			// If there a phone number 
			if (oldPhoneNumber->lId == newPhoneNumber->lId)
			{
				found = true;
				if (!found)
				{
					if (!m_oPhoneNumbersTable.DeleteWhereID(oldPhoneNumber->lId)) {
						//oSession.Abort();
						//oSession.Close();
						return FALSE;
					}
				}

			}
		}

	}




}
CCitiesTypedPtrArray& CPersonData::GetCities()
{
	return m_oCitiesArray;
}

CPhoneTypesTypedPtrArray& CPersonData::GetPhoneTypes()
{
	return m_oPhoneTypesArray;
}







void CPersonData::SetTypeRowSet(CDBPropSet& oUpdateDBPropSet)
{
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

};
