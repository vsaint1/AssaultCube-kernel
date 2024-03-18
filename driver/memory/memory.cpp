#include "memory.h"

NTSTATUS memory::write(int pid,void* address, void* target, size_t size)
{
	UNREFERENCED_PARAMETER(pid);
	UNREFERENCED_PARAMETER(address);
	UNREFERENCED_PARAMETER(target);
	UNREFERENCED_PARAMETER(size);

	return STATUS_SUCCESS;
}

NTSTATUS memory::write_safe(int pid,void* address, void* target, size_t size)
{
	UNREFERENCED_PARAMETER(pid);
	UNREFERENCED_PARAMETER(address);
	UNREFERENCED_PARAMETER(target);
	UNREFERENCED_PARAMETER(size);

	return STATUS_SUCCESS;
}

NTSTATUS memory::read(int pid, void* address,void* target, size_t size)
{
	size_t bytes = { 0 };

	NTSTATUS status = STATUS_SUCCESS;
	PEPROCESS target_process = {};

	if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)pid, &target_process)))
		return STATUS_UNSUCCESSFUL;

	status = MmCopyVirtualMemory(target_process, address, PsGetCurrentProcess(), target, size, KernelMode, &bytes);

	return status;
}
