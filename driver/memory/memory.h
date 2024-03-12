#pragma once
#include "../utils/defs.h"


namespace memory {
	NTSTATUS write(void* address, void* target, size_t size);

	NTSTATUS write_safe(void* address, void* target, size_t size);

	NTSTATUS read(int pid, void* address, void* target,size_t size);
}