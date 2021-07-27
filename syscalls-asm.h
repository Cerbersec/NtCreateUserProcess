#pragma once
//#include "syscalls.h"
#include "nttypes.h"
//crash line 55
//cmp word ptr [rax+0x120], 18362

/*
#define ZwCreateUserProcess NtCreateUserProcess
__asm__("NtCreateUserProcess: \n\
	mov rax, gs:[0x60]                          \n\
NtCreateUserProcess_Check_X_X_XXXX:                \n\
	cmp dword ptr [rax+0x118], 6 \n\
	je  NtCreateUserProcess_Check_6_X_XXXX \n\
	cmp dword ptr [rax+0x118], 10 \n\
	je  NtCreateUserProcess_Check_10_0_XXXX \n\
	jmp NtCreateUserProcess_SystemCall_Unknown \n\
NtCreateUserProcess_Check_6_X_XXXX:                \n\
	cmp dword ptr [rax+0x11c], 0 \n\
	je  NtCreateUserProcess_Check_6_0_XXXX \n\
	cmp dword ptr [rax+0x11c], 1 \n\
	je  NtCreateUserProcess_Check_6_1_XXXX \n\
	cmp dword ptr [rax+0x11c], 2 \n\
	je  NtCreateUserProcess_SystemCall_6_2_XXXX \n\
	cmp dword ptr [rax+0x11c], 3 \n\
	je  NtCreateUserProcess_SystemCall_6_3_XXXX \n\
	jmp NtCreateUserProcess_SystemCall_Unknown \n\
NtCreateUserProcess_Check_6_0_XXXX:                \n\
	cmp word ptr [rax+0x120], 6000 \n\
	je  NtCreateUserProcess_SystemCall_6_0_6000 \n\
	cmp word ptr [rax+0x120], 6001 \n\
	je  NtCreateUserProcess_SystemCall_6_0_6001 \n\
	cmp word ptr [rax+0x120], 6002 \n\
	je  NtCreateUserProcess_SystemCall_6_0_6002 \n\
	jmp NtCreateUserProcess_SystemCall_Unknown \n\
NtCreateUserProcess_Check_6_1_XXXX:                \n\
	cmp word ptr [rax+0x120], 7600 \n\
	je  NtCreateUserProcess_SystemCall_6_1_7600 \n\
	cmp word ptr [rax+0x120], 7601 \n\
	je  NtCreateUserProcess_SystemCall_6_1_7601 \n\
	jmp NtCreateUserProcess_SystemCall_Unknown \n\
NtCreateUserProcess_Check_10_0_XXXX:               \n\
	cmp word ptr [rax+0x120], 10240 \n\
	je  NtCreateUserProcess_SystemCall_10_0_10240 \n\
	cmp word ptr [rax+0x120], 10586 \n\
	je  NtCreateUserProcess_SystemCall_10_0_10586 \n\
	cmp word ptr [rax+0x120], 14393 \n\
	je  NtCreateUserProcess_SystemCall_10_0_14393 \n\
	cmp word ptr [rax+0x120], 15063 \n\
	je  NtCreateUserProcess_SystemCall_10_0_15063 \n\
	cmp word ptr [rax+0x120], 16299 \n\
	je  NtCreateUserProcess_SystemCall_10_0_16299 \n\
	cmp word ptr [rax+0x120], 17134 \n\
	je  NtCreateUserProcess_SystemCall_10_0_17134 \n\
	cmp word ptr [rax+0x120], 17763 \n\
	je  NtCreateUserProcess_SystemCall_10_0_17763 \n\
	cmp word ptr [rax+0x120], 18362 \n\
	je  NtCreateUserProcess_SystemCall_10_0_18362 \n\
	cmp word ptr [rax+0x120], 18363 \n\
	je  NtCreateUserProcess_SystemCall_10_0_18363 \n\
	cmp word ptr [rax+0x120], 19041 \n\
	je  NtCreateUserProcess_SystemCall_10_0_19041 \n\
	cmp word ptr [rax+0x120], 19042 \n\
	je  NtCreateUserProcess_SystemCall_10_0_19042 \n\
	jmp NtCreateUserProcess_SystemCall_Unknown \n\
NtCreateUserProcess_SystemCall_6_0_6000:           \n\
	mov eax, 0x00ac \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_6_0_6001:           \n\
	mov eax, 0x00aa \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_6_0_6002:           \n\
	mov eax, 0x00aa \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_6_1_7600:           \n\
	mov eax, 0x00aa \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_6_1_7601:           \n\
	mov eax, 0x00aa \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_6_2_XXXX:           \n\
	mov eax, 0x00b5 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_6_3_XXXX:           \n\
	mov eax, 0x00b7 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_10240:         \n\
	mov eax, 0x00ba \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_10586:         \n\
	mov eax, 0x00bb \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_14393:         \n\
	mov eax, 0x00bd \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_15063:         \n\
	mov eax, 0x00c0 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_16299:         \n\
	mov eax, 0x00c1 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_17134:         \n\
	mov eax, 0x00c2 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_17763:         \n\
	mov eax, 0x00c3 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_18362:         \n\
	mov eax, 0x00c4 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_18363:         \n\
	mov eax, 0x00c4 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_19041:         \n\
	mov eax, 0x00c8 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_10_0_19042:         \n\
	mov eax, 0x00c8 \n\
	jmp NtCreateUserProcess_Epilogue \n\
NtCreateUserProcess_SystemCall_Unknown:            \n\
	ret \n\
NtCreateUserProcess_Epilogue: \n\
	mov r10, rcx \n\
	syscall \n\
	ret \n\
");
*/

#define ZwCreateUserProcess NtCreateUserProcess
__asm__("NtCreateUserProcess:   \n\
	mov rax, gs:[0x60]          \n\
    mov eax, 0x00c8             \n\
    mov r10, rcx                \n\
    syscall                     \n\
    ret                         \n\
");



