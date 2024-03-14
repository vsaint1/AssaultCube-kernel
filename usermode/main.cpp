#include "driver/driver.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

	UNICODE_STRING name;
	RtlInitUnicodeString(&name, L"ac_client.exe");
	int pid = driver.get_process_id(name);

	printf("pid: %d\n", pid);

	UNICODE_STRING module_base;
	RtlInitUnicodeString(&name, L"ac_client.exe");

	uintptr_t base = driver.get_module_base(module_base);

	system("pause");
	return 0;
}