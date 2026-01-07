#pragma once

#include <Windows.h>
#include <string>


class Memory
{
public:
    Memory() = default;
    ~Memory();

    bool Attach(const std::wstring &processName, DWORD desiredAccess);
    bool Read(uintptr_t address, void *buffer, SIZE_T size, SIZE_T *bytesRead = nullptr) const;
    bool Write(uintptr_t address, void *buffer, SIZE_T size, SIZE_T *bytesWritten = nullptr) const;

    uintptr_t ResolveAddress(uintptr_t address, uintptr_t offset) const;

    uintptr_t GetBase() const;
    DWORD     GetPid() const;

private:
    bool ResolveProcess(const std::wstring &processName);
    bool ResolveModule(const std::wstring &moduleName);

private:
    HANDLE    m_hProcess = nullptr;
    DWORD     m_pid = 0;
    uintptr_t m_base = 0;
};
