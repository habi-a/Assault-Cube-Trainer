#include "Memory.h"
#include <TlHelp32.h>


Memory::~Memory()
{
    if (m_hProcess)
        CloseHandle(m_hProcess);
}

bool Memory::Attach(const std::wstring &processName, DWORD desiredAccess)
{
    if (!ResolveProcess(processName))
        return false;
    if (!ResolveModule(processName))
        return false;

    m_hProcess = OpenProcess(desiredAccess, FALSE, m_pid);

    return m_hProcess != nullptr;
}

bool Memory::ResolveProcess(const std::wstring &processName)
{
    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    if (!Process32FirstW(snapshot, &pe))
    {
        CloseHandle(snapshot);
        return false;
    }

    do
    {
        if (processName == pe.szExeFile)
        {
            m_pid = pe.th32ProcessID;
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32NextW(snapshot, &pe));

    CloseHandle(snapshot);
    return false;
}

bool Memory::ResolveModule(const std::wstring &moduleName)
{
    MODULEENTRY32W me{};
    me.dwSize = sizeof(me);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_pid);

    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    if (!Module32FirstW(snapshot, &me))
    {
        CloseHandle(snapshot);
        return false;
    }

    do
    {
        if (moduleName == me.szModule)
        {
            m_base = reinterpret_cast<uintptr_t>(me.modBaseAddr);
            CloseHandle(snapshot);
            return true;
        }
    } while (Module32NextW(snapshot, &me));

    CloseHandle(snapshot);
    return false;
}

uintptr_t Memory::ResolveAddress(uintptr_t address, uintptr_t offset) const
{
    uintptr_t addr = m_base + address;

    if (!Read(addr, &addr, sizeof(addr)))
        return 0;
    return addr + offset;
}

bool Memory::Read(uintptr_t address, void *buffer, SIZE_T size, SIZE_T *bytesRead) const
{
    return ReadProcessMemory(m_hProcess, (LPCVOID)address, buffer, size, bytesRead) != FALSE;
}

bool Memory::Write(uintptr_t address, void *buffer, SIZE_T size, SIZE_T *bytesWritten) const
{
    return WriteProcessMemory(m_hProcess, (LPVOID)address, buffer, size, bytesWritten) != FALSE;
}

uintptr_t Memory::GetBase() const
{
    return m_base;
}

DWORD Memory::GetPid() const
{
    return m_pid;
}
