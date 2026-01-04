#include "Bypass.h"


Bypass::Bypass()
{
}

Bypass::~Bypass()
{
	if (this->m_hProcess != nullptr)
		CloseHandle(this->m_hProcess);
}

bool Bypass::Attach(DWORD desiredAccess, DWORD pid) 
{
	this->m_hProcess = OpenProcess(desiredAccess, false, pid);
	if (this->m_hProcess == nullptr)
		return false;
	return true;
}

bool Bypass::Read(uintptr_t lpBaseAddress, void *lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) 
{
	if (!ReadProcessMemory(this->m_hProcess, (LPCVOID)lpBaseAddress, (LPVOID)lpBuffer, nSize, lpNumberOfBytesRead))
		return false;
	return true;
}

bool Bypass::Write(uintptr_t lpBaseAddress, void *lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten)
{
	if (!WriteProcessMemory(this->m_hProcess, (LPVOID)lpBaseAddress, (LPCVOID)lpBuffer, nSize, lpNumberOfBytesWritten))
		return false;
	return true;
}
