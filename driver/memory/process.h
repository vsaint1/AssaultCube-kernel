#pragma once
#include "../utils/defs.h"

#define DRIVER_RUNNING(name) process::get_kernel_module_base(name) != 0

#pragma warning( disable : 4311 4302)

namespace process {

	uintptr_t get_kernel_module_base(char* module_name);
	
	int get_process_id_by_name(const char* name);

	uintptr_t get_module_base(int pid, const char* module_name);
};