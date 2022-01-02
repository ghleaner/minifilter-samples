#include "mysample1.h"

FLT_OPERATION_REGISTRATION Callbacks[] = {
	{IRP_MJ_CREATE, 0, MiniPreCreate, MiniPostCreate, NULL},
	{IRP_MJ_WRITE, 0, MiniPreWrite, NULL, NULL},
	{IRP_MJ_OPERATION_END}
};


FLT_POSTOP_CALLBACK_STATUS MiniPostCreate(
	PFLT_CALLBACK_DATA Data, 
	PCFLT_RELATED_OBJECTS FltObjects, 
	PVOID* CompletionContext, 
	FLT_POST_OPERATION_FLAGS Flags
)
{
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(Flags);
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(FltObjects);

	//KdPrint(("post create is running \n"));
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, "post create is running \n");
	return FLT_POSTOP_FINISHED_PROCESSING;
}

FLT_PREOP_CALLBACK_STATUS MiniPreCreate(
	PFLT_CALLBACK_DATA Data,
	PCFLT_RELATED_OBJECTS FltObjects, 
	PVOID* CompletionContext
)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

	PFLT_FILE_NAME_INFORMATION FileNameInfo;
	NTSTATUS status;
	WCHAR Name[200] = { 0 };

	status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &FileNameInfo);

	if (NT_SUCCESS(status)) {
		status = FltParseFileNameInformation(FileNameInfo);

		if (NT_SUCCESS(status)) {

			if (FileNameInfo->Name.MaximumLength < 260) {
				memcpy(Name, FileNameInfo->Name.Buffer, FileNameInfo->Name.MaximumLength);
				//RtlCopyMemory(Name, FileNameInfo->Name.Buffer, FileNameInfo->Name.MaximumLength);

				//KdPrint(("Create file: (%wZ) \r\n", Name));
				DbgPrintEx(DPFLTR_IHVAUDIO_ID, 0, "Create File: (%ws) \n", Name);
			}
		}
		FltReleaseFileNameInformation(FileNameInfo);

		return FLT_PREOP_SUCCESS_WITH_CALLBACK;
	}

	return FLT_PREOP_SUCCESS_NO_CALLBACK;
}

FLT_PREOP_CALLBACK_STATUS MiniPreWrite(
	PFLT_CALLBACK_DATA Data, 
	PCFLT_RELATED_OBJECTS FltObjects, 
	PVOID* CompletionContext
)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

	PFLT_FILE_NAME_INFORMATION FileNameInfo;
	NTSTATUS status;
	WCHAR Name[200] = { 0, };

	status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &FileNameInfo);

	if (NT_SUCCESS(status)) {
		status = FltParseFileNameInformation(FileNameInfo);

		if (NT_SUCCESS(status)) {

			if (FileNameInfo->Name.MaximumLength < 260) {
				memcpy(Name, FileNameInfo->Name.Buffer, FileNameInfo->Name.MaximumLength);
				//RtlCopyMemory(Name, FileNameInfo->Name.Buffer, FileNameInfo->Name.MaximumLength);
				//KdPrint(("Create file: %ws \n", Name));

				_wcsupr(Name);
				if (wcsstr(Name, L"OPEN.TXT") != NULL) {
					//KdPrint(("write file: %ws blocked \n", Name));
					DbgPrintEx(DPFLTR_IHVAUDIO_ID, 0, "write file: %ws blocked\n", Name);
					Data->IoStatus.Status = STATUS_INVALID_PARAMETER;
					Data->IoStatus.Information = 0;
					FltReleaseFileNameInformation(FileNameInfo);
					return FLT_PREOP_COMPLETE;
				}

				DbgPrintEx(DPFLTR_IHVAUDIO_ID, 0, "Create File: %ws \n", Name);
			}
		}
		FltReleaseFileNameInformation(FileNameInfo);
	}

	return FLT_PREOP_SUCCESS_NO_CALLBACK;
}