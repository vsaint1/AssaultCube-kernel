#include "memory/process.h"


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

	printf("AssaultCube PID: %d", process::get_process_id_by_name("ac_client.exe"));


	return STATUS_SUCCESS;
}

