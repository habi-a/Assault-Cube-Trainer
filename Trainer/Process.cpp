#include "Process.h"
#include <TlHelp32.h>

bool Process::Attach(const std::wstring& processName)
{
	PROCESSENTRY32W entry{};
	entry.dwSize = sizeof(entry);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
		return false;

	if (Process32FirstW(snapshot, &entry)) {
		do {
			if (processName == entry.szExeFile) {
				m_pid = entry.th32ProcessID;
				CloseHandle(snapshot);
				return true;
			}
		} while (Process32NextW(snapshot, &entry));
	}

	CloseHandle(snapshot);
	return false;
}

DWORD Process::Pid() const
{
	return m_pid;
}
