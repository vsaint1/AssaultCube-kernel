#include <ntifs.h>
#include "utils/utils.h"
#include "utils/crt.h"


NTSTATUS driver_unload(PDRIVER_OBJECT driver_object) {
	UNREFERENCED_PARAMETER(driver_object);

	printf("unloaded successfully");

	return STATUS_SUCCESS;
}

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
	UNREFERENCED_PARAMETER(registry_path);


	printf("driver loaded successfully");

	
	driver_object->DriverUnload = *(DRIVER_UNLOAD*)driver_unload;

	return STATUS_SUCCESS;
}

