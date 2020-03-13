#pragma once

#include <Windows.h>


namespace at_dll {

	struct DLLID
	{
		DLLID(HINSTANCE _ID, const char* _name) { ID = _ID; name = _name; };
		HINSTANCE ID = NULL;
		const char* name;
	};


	DLLID* at_LoadLib(const char*);
	int at_UnloadLib(DLLID*);
	int at_Reset(DLLID*);
	int at_SetDir(const char*);
	DLLID* at_FindAllLib(const char*, int&);

	template < typename T >
	HRESULT at_LoadFunktion(DLLID* dll, const char* name, T& funk)
	{
		HRESULT hr;
		funk = (T)GetProcAddress(dll->ID, name);
		(dll->ID == 0) ? hr = GetLastError(): hr = ERROR_SUCCESS;
		return hr;
	}

}

