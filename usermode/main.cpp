#include "driver/driver.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

	UNICODE_STRING name;
	RtlInitUnicodeString(&name, L"ac_client.exe");
	int pid = driver.get_process_id(name);

	printf("pid: %d\n", pid);

	UNICODE_STRING module_base;
	RtlInitUnicodeString(&module_base, L"ac_client.exe");
	uintptr_t base = driver.get_module_base(module_base);
	printf("base: %p\n", base);

	auto local_player_sig = driver.find_pattern("8B 0D ? ? ? ? 56 57 8B 3D");

	uint32_t player = driver.readv<uint32_t>(base + 0x18AC00);
	int health = driver.readv<int>(player + 0xEC);
	std::string player_name = driver.read_str(player + 0x205);

	printf("local_player: %p, health: %d, name: %s\n", player, health, player_name.c_str());

	printf("lp_sig: %p\n", local_player_sig.value());
	system("pause");
	return 0;
}