#include "Bypass.h"


Bypass::~Bypass()
{
	if (m_hProcess != nullptr)
		CloseHandle(m_hProcess);
}

bool Bypass::Attach(DWORD desiredAccess, DWORD pid) 
{
	if (m_hProcess)
		CloseHandle(m_hProcess);

	m_hProcess = OpenProcess(desiredAccess, false, pid);
	return m_hProcess != nullptr;
}

bool Bypass::Read(uintptr_t lpBaseAddress, void *lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) 
{
	if (!ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, (LPVOID)lpBuffer, nSize, lpNumberOfBytesRead))
		return false;
	return true;
}

bool Bypass::Write(uintptr_t lpBaseAddress, void *lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten)
{
	if (!WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, (LPCVOID)lpBuffer, nSize, lpNumberOfBytesWritten))
		return false;
	return true;
}
