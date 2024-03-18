#pragma once
#include "Cities.h"            
#include "CitiesAccessor.h"    
#include "CTypedPtrArraySelfClean.h"
#include <atldbcli.h>
#include "Table.h"
#include <atlstr.h>

/// <summary>
/// Class which give accsess to DB. With this class we can make CRUD operations. 
/// </summary>
class CCitiesTable :
	public CTableBase<CITIES, CCitiesAccessor, CCitiesTypedPtrArray>
{

	//Constructor / Destructor
	//----------------
public:
	CCitiesTable();
	virtual ~CCitiesTable();






};

