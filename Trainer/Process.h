#pragma once

#include <Windows.h>
#include <string>

class Process
{
public:
	Process() = default;

	bool Attach(const std::wstring& processName);

	DWORD  Pid() const;
	HANDLE Handle() const;

private:
	DWORD m_pid = 0;
};