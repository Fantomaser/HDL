#include "DllLoader.h"
#include <iostream>

namespace at_dll {

	int at_SetDir(const char* path)
	{
		return SetDllDirectoryA(path);
	}

	DLLID* at_LoadLib(const char* name)
	{
		return (new DLLID(LoadLibrary(name), name));
	}

	int at_UnloadLib(DLLID* dll)
	{
		int res = FreeLibrary(dll->ID);
		delete dll;
		return res;
	}

	int at_Reset(DLLID* dll)
	{
		int res = FreeLibrary(dll->ID);
		dll->ID = LoadLibrary(dll->name);
		return res;
	}

	DLLID* at_FindAllLib(const char* path, int& count)
	{
		count = 0;
		WIN32_FIND_DATA FILE;
		HANDLE hl = FindFirstFile(path, &FILE);
		DLLID * DllList;
		int Count;

		if (hl == INVALID_HANDLE_VALUE) return nullptr;

		DllList = at_LoadLib(FILE.cFileName);
		count++;

		while (FindNextFile(hl, &FILE) != 0) {

			((&DllList)[count++] = at_LoadLib(FILE.cFileName));
		}
		FindClose(hl);
		return DllList;
	}


}