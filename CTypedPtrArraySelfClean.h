#pragma once
#include <afxtempl.h>

template<class TYPE>
class CTypedPtrArraySelfClean : public CTypedPtrArray<CPtrArray, TYPE>
{

	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	virtual ~CTypedPtrArraySelfClean()
	{
		RemoveAllAndDelete();
	};


	// Methods
	// ----------------
private:
	void RemoveAllAndDelete()
	{
		// Delete the objects in the array
		INT_PTR nSize = GetCount();
		for (INT_PTR nIndex = 0; nIndex < nSize; nIndex++)
		{
			TYPE pObj = GetAt(nIndex);
			delete pObj;
		}

		// Remove all elements from the array
		RemoveAll();
	}

	// Overrides
	// ----------------


	// Members
	// ----------------

};

