#include "mysample1.h"

PFLT_FILTER FilterHandle;

NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegPath)
{
	UNREFERENCED_PARAMETER(pRegPath);

	NTSTATUS status;

	status = FltRegisterFilter(pDrvObj, &FilterRegistration, &FilterHandle);

	if (NT_SUCCESS(status)) {

		status = FltStartFiltering(FilterHandle);

		if (!NT_SUCCESS(status)) {

			FltUnregisterFilter(FilterHandle);
		}

	}

	return status;
}