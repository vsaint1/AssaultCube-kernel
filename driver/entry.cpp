#include "communications/communication.h"


UNICODE_STRING device_name = RTL_CONSTANT_STRING(L"\\Device\\acube");
UNICODE_STRING device_link = RTL_CONSTANT_STRING(L"\\DosDevices\\acube");
PDEVICE_OBJECT device_object;

NTSTATUS driver_unload(PDRIVER_OBJECT driver_object) {
	UNREFERENCED_PARAMETER(driver_object);

	printf("unloaded successfully\n");

	IoDeleteDevice(device_object);
	IoDeleteSymbolicLink(&device_link);
	return STATUS_SUCCESS;
}

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
	UNREFERENCED_PARAMETER(registry_path);

	driver_object->DriverUnload = *(DRIVER_UNLOAD*)driver_unload;

	printf("driver loaded successfully");

	if (DRIVER_RUNNING("FACEIT.sys") || DRIVER_RUNNING("gamersclub.sys") || DRIVER_RUNNING("bedaisy.sys") || DRIVER_RUNNING("vgk.sys") || DRIVER_RUNNING("EasyAntiCheat_EOS.sys")) {
		printf("Aborting Anti-cheat driver was found running\n");
		return STATUS_UNSUCCESSFUL;
	}


	IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_object);
	IoCreateSymbolicLink(&device_link, &device_name);


	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = com::on_request;
	driver_object->MajorFunction[IRP_MJ_CREATE] = com::on_create;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = com::on_close;

	device_object->Flags |= DO_DIRECT_IO;
	device_object->Flags &= ~DO_DEVICE_INITIALIZING;


	return STATUS_SUCCESS;
}

