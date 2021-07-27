# NtCreateUserProcess

Attempt to get NtCreateUserProcess working as direct syscall. Contains `main.c` which is a raw implementation of the API, and `hook.cpp` which attempts to hook the NTDLL call and call the original by passing the parameters received from `CreateProcessA()`.

*Note: probably needs a trampoline to not mess with the register state*



Sources: [https://github.com/Microwave89/createuserprocess/](https://github.com/Microwave89/createuserprocess/)

> Using [SysWhispers](https://github.com/jthuraisamy/SysWhispers) and [InlineWhispers](https://github.com/outflanknl/InlineWhispers) to generate the direct syscalls
