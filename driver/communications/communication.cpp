#include "communication.h"

NTSTATUS com::on_request(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

	switch (stack->Parameters.DeviceIoControl.IoControlCode)
	{
	case PROCESS_ID_REQUEST: {
		printf("PROCESS_ID_REQUEST\n");

		KPROCESSID_REQUEST* request = (KPROCESSID_REQUEST*)irp->AssociatedIrp.SystemBuffer;

		printf("request->process_name: %wZ\n", request->process_name);

		//TODO: CHANGE TO UNICODE_STRING
		const char* process_name = strcmp((char*)&request->process_name, "") != 0 ? "ac_client.exe" : (char*)&request->process_name;

		int pid = process::get_process_id_by_name(process_name);

		printf("pid %d\n", pid);

		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = *(int*)&pid;
		IoCompleteRequest(irp, IO_NO_INCREMENT);

		break;
	}
	case MODULE_BASE_REQUEST: {
		printf("MODULE_BASE_REQUEST\n");

		KERNEL_MODULE_REQUEST* request = (KERNEL_MODULE_REQUEST*)irp->AssociatedIrp.SystemBuffer;

		uintptr_t base = process::get_module_base(request->pid, request->module_name);

		printf("base %p\n", base);

		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = *(uintptr_t*)&base;
		IoCompleteRequest(irp, IO_NO_INCREMENT);
		break;
	}

	default:
		irp->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST;
		irp->IoStatus.Information = 0;
		IoCompleteRequest(irp, IO_NO_INCREMENT);
		break;
	}


	return STATUS_SUCCESS;
}

NTSTATUS com::on_create(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

NTSTATUS com::on_close(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);


	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

NTSTATUS com::unsupported_io(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	irp->IoStatus.Status = STATUS_NOT_IMPLEMENTED;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return irp->IoStatus.Status;

}
