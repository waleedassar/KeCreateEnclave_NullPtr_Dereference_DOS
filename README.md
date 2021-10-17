# KeCreateEnclave_NullPtr_Dereference_DOS

POC for a denial of service bug in the Windows kernel.

 A null-pointer dereference bug in the "nt!KeCreateEnclave" function, due to lack of sanitization on its 4th parameter.

Tested on Windows 10 (19041.1.amd64fre.vb_release.191206-1406)

N.B. Intel SGX must be enabled in BIOS and activated on the OS.

Reported to Microsoft on 25/02/2020.
