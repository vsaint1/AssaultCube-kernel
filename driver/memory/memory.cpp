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
	PEPROCESS proc = {};

	if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)pid, &proc)))
		return STATUS_UNSUCCESSFUL;

	status = MmCopyVirtualMemory(proc, address, proc, target, size, KernelMode, &bytes);

	return status;
}
