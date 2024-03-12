#include "process.h"

uintptr_t process::get_kernel_module_base(char* module_name)
{

	ULONG64 module_base = 0;
	ULONG module_size = 0;
	PRTL_PROCESS_MODULES modules = NULL;
	NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, 0, 0, &module_size);

	if (status != STATUS_INFO_LENGTH_MISMATCH)
		return 0;


	modules = (PRTL_PROCESS_MODULES)ExAllocatePool2(POOL_FLAG_NON_PAGED, module_size, KM_POOL_TAG);
	if (!modules)
		return 0;

	status = ZwQuerySystemInformation(SystemModuleInformation, modules, module_size, &module_size);
	if (!NT_SUCCESS(status)) {
		ExFreePoolWithTag(modules, KM_POOL_TAG);
		return 0;
	}

	PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
	for (ULONG i = 0; i < modules->NumberOfModules; i++) {
#if _DEBUG
		printf("Module Name: %s\n", module[i].FullPathName + module[i].OffsetToFileName);
		printf("Module Base: %p\n", module[i].ImageBase);
		printf("Module Size: %d\n", module[i].ImageSize);
#endif
		if (strcmp((char*)module[i].FullPathName + module[i].OffsetToFileName, module_name) == 0) {
			module_base = (ULONG64)module[i].ImageBase;
			break;
		}
	}

	ExFreePoolWithTag(modules, KM_POOL_TAG);
	return module_base;
}

// https://www.vergiliusproject.com/kernels/x64/Windows%2010%20%7C%202016 
// windows 22h2 version

int process::get_process_id_by_name(const char* name)
{

	PEPROCESS proc;
	PEPROCESS sysproc = PsInitialSystemProcess;
	LIST_ENTRY* list = (LIST_ENTRY*)((char*)sysproc + 0x448); // _EPROCESS.ActiveProcessLinks
	LIST_ENTRY* head = list;

	do {
		proc = (PEPROCESS)((char*)list - 0x448); // _EPROCESS.ActiveProcessLinks
		if (strstr((char*)proc + 0x5a8, name)) { // _EPROCESS.ImageFileName
			return (int)PsGetProcessId(proc);
		}
		list = list->Flink;
	} while (list != head);

	return 0;
}
