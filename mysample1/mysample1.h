#ifndef __MYSAMPLE_H__
#define __MYSAMPLE_H__

#include <fltKernel.h>

extern PFLT_FILTER FilterHandle;
extern FLT_REGISTRATION FilterRegistration;
extern FLT_OPERATION_REGISTRATION Callbacks[];

NTSTATUS MiniUnload(
	_In_ FLT_FILTER_UNLOAD_FLAGS Flags
);

FLT_POSTOP_CALLBACK_STATUS MiniPostCreate(
	_Inout_ PFLT_CALLBACK_DATA Data, 
	_In_ PCFLT_RELATED_OBJECTS FltObjects, 
	_In_opt_ PVOID* CompletionContext, 
	_In_ FLT_POST_OPERATION_FLAGS Flags
);

FLT_PREOP_CALLBACK_STATUS MiniPreCreate(
	_Inout_ PFLT_CALLBACK_DATA Data, 
	_In_ PCFLT_RELATED_OBJECTS FltObjects, 
	_Out_ PVOID* CompletionContext
);

FLT_PREOP_CALLBACK_STATUS MiniPreWrite(
	_Inout_ PFLT_CALLBACK_DATA Data, 
	_In_ PCFLT_RELATED_OBJECTS FltObjects, 
	_Out_ PVOID* CompletionContext);

#endif