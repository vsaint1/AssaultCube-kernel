#pragma once
#include "defs.h"
#include <stdio.h>

class Driver {
	HANDLE handle = 0;

	int process_id = 0;

public:

	Driver() {
		void* tmp_handle = CreateFile(L"\\\\.\\acube", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

		if ((long long)tmp_handle == 0xFFFFFFFFFFFFFFFF) { // INVALID_HANDLE_VALUE
			MessageBox(NULL, L"Failed to open driver connection", L"Error", MB_ICONERROR);
			exit(0);
		}

		this->handle = tmp_handle;
	}

	~Driver() {
		CloseHandle(handle);
	}

	int get_process_id(UNICODE_STRING process_name) {

		KPROCESSID_REQUEST request = { 0 };
		request.process_name = process_name;

		DWORD bytes_returned;
		DeviceIoControl(handle, PROCESS_ID_REQUEST, &request, sizeof(request), NULL, NULL, &bytes_returned, NULL);
		process_id = (int)bytes_returned;

		return process_id;
	}


	uintptr_t get_module_base(UNICODE_STRING module_name) {

		KERNEL_MODULE_REQUEST request = { 0 };
		request.pid = this->process_id;
		request.module_name = module_name;

		DWORD bytes_returned;
		DeviceIoControl(handle, MODULE_BASE_REQUEST, &request, sizeof(request), NULL,NULL, &bytes_returned, NULL);
		uintptr_t base = (uintptr_t)bytes_returned;
		return base;
	}

	template <typename T>
	T readv(uintptr_t address) {
		T buffer{ 0 };
		_KERNEL_READ_REQUEST request = { 0 };
		request.src_pid = process_id;
		request.src_address = address;
		request.p_buffer = &buffer;
		request.size = sizeof(T);

		if (DeviceIoControl(handle, READ_REQUEST, &request, sizeof(request), &request, sizeof(request), NULL, NULL))
			return buffer;
		return 0;
	}


};

inline Driver driver;