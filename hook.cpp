#include <Windows.h>
#include <cstdio>
//#include "syscalls-asm.h"

FARPROC NtCreateUserProcessAddr = NULL;
SIZE_T bytesWritten = 0;
char NtCreateUserProcessOriginalBytes[6] = {};

NTSTATUS __stdcall HookedNtCreateUserProcess(PHANDLE ProcessHandle, PHANDLE ThreadHandle, ACCESS_MASK ProcessDesiredAccess, ACCESS_MASK ThreadDesiredAccess, POBJECT_ATTRIBUTES ProcessObjectAttributes, POBJECT_ATTRIBUTES ThreadObjectAttributes, ULONG ProcessFlags, ULONG ThreadFlags, PRTL_USER_PROCESS_PARAMETERS ProcessParameters, PPS_CREATE_INFO CreateInfo, PPS_ATTRIBUTE_LIST AttributeList)
{
    printf("Hello from hooked NtCreateUserProcess ;)\n");

    // unpatch
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)NtCreateUserProcessAddr, NtCreateUserProcessOriginalBytes, sizeof(NtCreateUserProcessOriginalBytes), &bytesWritten);

    // call the original
    printf("Calling original\n");
    return &NtCreateUserProcessAddr(ProcessHandle, ThreadHandle, ProcessDesiredAccess, ThreadDesiredAccess, ProcessObjectAttributes, ThreadObjectAttributes, ProcessFlags, ThreadFlags, ProcessParameters, CreateInfo, AttributeList);
}

int main()
{
    HINSTANCE library = LoadLibraryA("ntdll.dll");
    SIZE_T bytesRead = 0;

    // get address of the NtCreateUserProcess function in memory
    NtCreateUserProcessAddr = GetProcAddress(library, "NtCreateUserProcess");

    // save the first 6 bytes of the original NtCreateUserProcess function - will need for unhooking
    ReadProcessMemory(GetCurrentProcess(), (LPCVOID)NtCreateUserProcessAddr, NtCreateUserProcessOriginalBytes, 6, &bytesRead);

    // create a patch "push <address of new NtCreateUserProcess); ret"
    // 0x68 = push imm32, 0xC3 = ret
    void *hookedNtCreateUserProcessAddr = reinterpret_cast<void*>(&HookedNtCreateUserProcess);//wonky cast to get around C++ ISO rules - https://stackoverflow.com/questions/45134220/how-to-convert-a-pointer-of-type-void-to-void
    char patch[6] = { 0 };

    memcpy_s(patch, 1, "\x68", 1);
    memcpy_s(patch + 1, 4, &hookedNtCreateUserProcessAddr, 4);
    memcpy_s(patch + 5, 1, "\xC3", 1);

    // patch NtCreateUserProcess
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)NtCreateUserProcessAddr, patch, sizeof(patch), &bytesWritten);

    // Execute code after hooking
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));

    CreateProcessA("C:\\Windows\\System32\\calc.exe", NULL, NULL, NULL, FALSE, /*CREATE_SUSPENDED*/NULL, NULL, NULL, &si, &pi);
    return 0;
}