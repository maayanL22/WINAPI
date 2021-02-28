#include <Windows.h>

#define EXE_FILENAME "C:\\operatingsystems\\exercises\\44a\\Debug\\44a.exe"
#define PROCESS_ARG "4"

/* This code uses winapi (through the Windows.h header) in order to create a process that runs an exe file supplied by us
   (in this case the exe file is of a c program that gets the argument we send it and prints a message)*/
int main()
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	// create argument string
	CHAR exe_filename[] = EXE_FILENAME;
	CHAR process_arg[] = PROCESS_ARG;
	INT size = strlen(exe_filename) + strlen(process_arg) + 2;
	PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
	sprintf_s(param, size, "%s %s", exe_filename, process_arg);
	// Start the child process.
	CreateProcessA(NULL,
		param, // Command line
		NULL, // Process handle not inheritable
		NULL, // Thread handle not inheritable
		FALSE, // Set handle inheritance to FALSE
		0, // No creation flags
		NULL, // Use parent's environment block
		NULL, // Use parent's starting directory
		&si, // Pointer to STARTUPINFO structure
		&pi); // Pointer to PROCESS_INFORMATION structure
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	free(param);
	return 0;
}