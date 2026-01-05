#include <iostream>
#include <Windows.h>

#include "Bypass.h"
#include "Module.h"
#include "Player.h"
#include "Process.h"

int main()
{
	Bypass mem;
	Process process;
	Module game;

	if (!process.Attach(L"ac_client.exe")) {
		std::cout << "Process not found\n";
		return EXIT_FAILURE;
	}
	if (!mem.Attach(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, process.Pid())) {
		std::cout << "Failed to attach memory\n";
		return EXIT_FAILURE;
	}
	if (!game.Attach(process.Pid(), L"ac_client.exe")) {
		std::cout << "Module not found\n";
		return EXIT_FAILURE;
	}

	Player player(game.getBase());

	while (!GetAsyncKeyState(VK_END)) {
		player.SetAmmo(mem, 20);
		Sleep(50);
	}

	return EXIT_SUCCESS;
}
