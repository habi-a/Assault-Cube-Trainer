#include "Memory.h"
#include <TlHelp32.h>


Memory::~Memory() noexcept
{
    if (m_hProcess)
        CloseHandle(m_hProcess);
}

bool Memory::Attach(const std::wstring& processName, DWORD desiredAccess) noexcept
{
    if (!ResolveProcess(processName))
        return false;
    if (!ResolveModule(processName))
        return false;

    m_hProcess = OpenProcess(desiredAccess, FALSE, m_pid);
    return m_hProcess != nullptr;
}

bool Memory::ResolveProcess(const std::wstring& processName) noexcept
{
    PROCESSENTRY32W entry{};
    entry.dwSize = sizeof(entry);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    auto close = [&]() { CloseHandle(snapshot); };

    if (!Process32FirstW(snapshot, &entry))
    {
        close();
        return false;
    }

    do {
        if (processName == entry.szExeFile)
        {
            m_pid = entry.th32ProcessID;
            close();
            return true;
        }
    } while (Process32NextW(snapshot, &entry));

    close();
    return false;
}

bool Memory::ResolveModule(const std::wstring& moduleName) noexcept
{
    MODULEENTRY32W entry{};
    entry.dwSize = sizeof(entry);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_pid);
    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    auto close = [&]() { CloseHandle(snapshot); };

    if (!Module32FirstW(snapshot, &entry))
    {
        close();
        return false;
    }

    do {
        if (moduleName == entry.szModule)
        {
            m_base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
            close();
            return true;
        }
    } while (Module32NextW(snapshot, &entry));

    close();
    return false;
}

uintptr_t Memory::ResolveAddress(uintptr_t address, uintptr_t offset) const noexcept
{
    uintptr_t addr = m_base + address;
    if (!Read(addr, &addr, sizeof(addr)))
        return 0;

    return addr + offset;
}

bool Memory::Read(uintptr_t address, void* buffer, SIZE_T size, SIZE_T* bytesRead) const noexcept
{
    return ReadProcessMemory(m_hProcess, reinterpret_cast<LPCVOID>(address), buffer, size, bytesRead) != FALSE;
}

bool Memory::Write(uintptr_t address, const void* buffer, SIZE_T size, SIZE_T* bytesWritten) const noexcept
{
    return WriteProcessMemory(m_hProcess, reinterpret_cast<LPVOID>(address), buffer, size, bytesWritten) != FALSE;
}
