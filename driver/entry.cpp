#include "memory/process.h"
#include "memory/memory.h"

NTSTATUS driver_unload(PDRIVER_OBJECT driver_object) {
	UNREFERENCED_PARAMETER(driver_object);

	printf("unloaded successfully");

	return STATUS_SUCCESS;
}

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
	UNREFERENCED_PARAMETER(registry_path);

	driver_object->DriverUnload = *(DRIVER_UNLOAD*)driver_unload;

	printf("driver loaded successfully");

	if (DRIVER_RUNNING("FACEIT.sys") || DRIVER_RUNNING("gamersclub.sys") || DRIVER_RUNNING("bedaisy.sys") || DRIVER_RUNNING("vgk.sys") || DRIVER_RUNNING("EasyAntiCheat_EOS.sys")) {
		printf("Aborting Anti-cheat driver was found running");
		return STATUS_UNSUCCESSFUL;
	}

	int pid = process::get_process_id_by_name("ac_client.exe");


	uintptr_t module_base = process::get_module_base(pid,"ac_client.exe");

	printf("AssaultCube PID: %d, Module Base: %p", pid,module_base);

	uintptr_t local_player = 0;
	int health = 0;

	memory::read(pid, (void*)(module_base + 0x18AC00), &local_player, sizeof(local_player));
	memory::read(pid, (void*)(local_player + 0x00EC), &health, sizeof(health));

	printf("LOCALPLAYER %p, HEALTH %d", local_player, health);

	return STATUS_SUCCESS;
}

