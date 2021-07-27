#include <Windows.h>
#include <stdio.h>
#include "syscalls-asm.h"

int main()
{
    UNICODE_STRING uImageName;
    WCHAR imageName[] = { L"\\??\\C:\\Windows\\System32\\calc.exe" };
    uImageName.Buffer = imageName;
    uImageName.Length = sizeof(imageName) - sizeof(UNICODE_NULL);
    uImageName.MaximumLength = sizeof(imageName);
    PUNICODE_STRING pProcessImageName = &uImageName;

    PS_CREATE_INFO procInfo;
    RTL_USER_PROCESS_PARAMETERS userParams;
    PS_ATTRIBUTE_LIST attrList;
    PS_PROTECTION protectionInfo;

    NTSTATUS status = STATUS_PENDING;
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    ///We should supply a minimal environment (environment variables). Following one is simple yet fits our needs.
    char data[2 * sizeof(ULONGLONG)] = { 'Y', 0x00, 0x3D, 0x00, 'Q', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    if (pProcessImageName) {
        protectionInfo.Signer = (UCHAR)PsProtectedSignerNone;
        protectionInfo.Type = (UCHAR)PsProtectedTypeNone;
        protectionInfo.Audit = 0;

        RtlSecureZeroMemory(&userParams, sizeof(RTL_USER_PROCESS_PARAMETERS));
        RtlSecureZeroMemory(&attrList, sizeof(PS_ATTRIBUTE_LIST) - sizeof(PS_ATTRIBUTE));
        RtlSecureZeroMemory(&procInfo, sizeof(PS_CREATE_INFO));

        userParams.Length = sizeof(RTL_USER_PROCESS_PARAMETERS);
        userParams.MaximumLength = sizeof(RTL_USER_PROCESS_PARAMETERS);
        attrList.TotalLength = sizeof(PS_ATTRIBUTE_LIST) - sizeof(PS_ATTRIBUTE);
        procInfo.Size = sizeof(PS_CREATE_INFO);

        userParams.Environment = (WCHAR*)data;
        userParams.EnvironmentSize = sizeof(data);
        userParams.Flags = RTL_USER_PROCESS_PARAMETERS_NORMALIZED;

        attrList.Attributes[0].Attribute = PsAttributeValue(PsAttributeImageName, FALSE, TRUE, FALSE);
        attrList.Attributes[0].Size = pProcessImageName->Length;
        attrList.Attributes[0].Value = (ULONG_PTR)pProcessImageName->Buffer;

        status = NtCreateUserProcess(&hProcess, &hThread, MAXIMUM_ALLOWED, MAXIMUM_ALLOWED, NULL, NULL, 0, /*THREAD_CREATE_FLAGS_CREATE_SUSPENDED*/0x1, &userParams, &procInfo, &attrList);
    }
    return 0;
}