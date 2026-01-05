#pragma once

#include <Windows.h>

class Bypass
{
public:
	Bypass() = default;
	~Bypass();
	bool Attach(DWORD desiredAccess, DWORD pid);
	bool Read(uintptr_t lpBaseAddress, void *lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead = nullptr);
	bool Write(uintptr_t lpBaseAddress, void *lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten = nullptr);

private:
	HANDLE m_hProcess = nullptr;
};
