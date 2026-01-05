#include "Module.h"
#include <TlHelp32.h>

bool Module::Attach(DWORD pid, const std::wstring& moduleName)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
		pid
	);

	if (snapshot == INVALID_HANDLE_VALUE)
		return false;

	MODULEENTRY32W entry{};
	entry.dwSize = sizeof(entry);

	if (!Module32FirstW(snapshot, &entry)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (moduleName == entry.szModule) {
			m_base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			m_size = entry.modBaseSize;
			CloseHandle(snapshot);
			return true;
		}
	} while (Module32NextW(snapshot, &entry));

	CloseHandle(snapshot);
	return false;
}

uintptr_t Module::getBase() const
{
	return m_base;
}

DWORD Module::getSize() const
{
	return m_size;
}

bool Module::IsValid() const
{
	return m_base != 0;
}