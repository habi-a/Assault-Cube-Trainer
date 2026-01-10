#pragma once

#include <Windows.h>
#include <string>
#include <cstdint>


class Memory
{
public:
    Memory() = default;
    ~Memory() noexcept;

    [[nodiscard]] bool Attach(const std::wstring& processName, DWORD desiredAccess) noexcept;

    bool Read(uintptr_t address, void* buffer, SIZE_T size, SIZE_T* bytesRead = nullptr) const noexcept;
    bool Write(uintptr_t address, const void* buffer, SIZE_T size, SIZE_T* bytesWritten = nullptr) const noexcept;

    [[nodiscard]] uintptr_t ResolveAddress(uintptr_t address, uintptr_t offset) const noexcept;

    [[nodiscard]] uintptr_t GetBase() const noexcept { return m_base; }
    [[nodiscard]] DWORD     GetPid()  const noexcept { return m_pid; }

private:
    [[nodiscard]] bool ResolveProcess(const std::wstring& processName) noexcept;
    [[nodiscard]] bool ResolveModule(const std::wstring& moduleName) noexcept;

private:
    HANDLE    m_hProcess = nullptr;
    DWORD     m_pid = 0;
    uintptr_t m_base = 0;
};
