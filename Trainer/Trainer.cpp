#include <iostream>
#include <Windows.h>

#include "Bypass.h"


int main()
{
    int intToRead;
    int intToWrite = 999989;
    DWORD dummy_game_pid = 22816;
    DWORD desired_access = PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
    uintptr_t base_address = 0x0133F8E8;
    Bypass bypass;

    if (!bypass.Attach(desired_access, dummy_game_pid)) {
        std::cout << "OpenProcess failed. GetLastError = " << GetLastError() << "\n";
        std::cin.get();
        return EXIT_FAILURE;
    }

    if (!bypass.Read(base_address, &intToRead, sizeof(int))) {
        std::cout << "ERROR: final value not found" << "\n";
        std::cin.get();
        return EXIT_FAILURE;
    }
    std::cout << "intToRead = " << intToRead << "\n";

    if (!bypass.Write(base_address, &intToWrite, sizeof(int))) {
        std::cout << "ERROR: Write value failed" << "\n";
        std::cin.get();
        return EXIT_FAILURE;
    }
    std::cout << "Overwritten successfully" << "\n";
    return EXIT_SUCCESS;
}
