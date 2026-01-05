#pragma once

#include <Windows.h>
#include <string>

class Module
{
public:
	Module() = default;
	~Module() = default;

	bool Attach(DWORD pid, const std::wstring& moduleName);
	uintptr_t getBase() const;
	DWORD     getSize() const;
	bool      IsValid() const;

private:
	uintptr_t m_base = 0;
	DWORD     m_size = 0;
};
