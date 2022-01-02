#include "mysample1.h"

NTSTATUS MiniUnload(
	FLT_FILTER_UNLOAD_FLAGS Flags
)
{
	UNREFERENCED_PARAMETER(Flags);

	//KdPrint(("driver unload \n"));
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, "driver unload \n");

	FltUnregisterFilter(FilterHandle);

	return STATUS_SUCCESS;
}