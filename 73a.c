#include <Windows.h>
#include <stdio.h>
#define FILENAME "C:\\operatingsystems\\exercises\\gibrish.bin"
int main()
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	int mem_buffer_size = sys_info.dwAllocationGranularity;
	int buffer_number = 0;
	int file_location = buffer_number * mem_buffer_size;
	HANDLE hMapFile = OpenFileMappingA(FILE_MAP_WRITE, TRUE, "myFile");
	if (hMapFile == NULL) {
		HANDLE hFile;
		LPCSTR pFileName = FILENAME;
		hFile = CreateFileA(
			pFileName, // file name
			GENERIC_ALL, // access type
			0, // other processes can't share
			NULL, // security
			OPEN_EXISTING, // open only if file exists
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD file_size = GetFileSize(hFile, NULL);
		// create file mapping object
		hMapFile = CreateFileMappingA(
			hFile, // file handle
			NULL, // default security
			PAGE_READWRITE, // read access
			0,
			0,
			"myFile");
		LPSTR pBuf;
		pBuf = (LPSTR)MapViewOfFile(
			hMapFile, // handle to map object
			FILE_MAP_READ, // read/write permission
			0, // start point (upper word)
			file_location, // start point (lower word)
			mem_buffer_size); // how many bytes to read
		if (pBuf == NULL) {
			printf("%d\n", GetLastError());
		}
		printf("hola");
		Sleep(10000);
	}
	else {
		LPSTR pBuf1;
		pBuf1 = (LPSTR)MapViewOfFile(
			hMapFile, // handle to map object
			FILE_MAP_WRITE, // read/write permission
			0, // start point (upper word)
			file_location, // start point (lower word)
			mem_buffer_size); // how many bytes to read
		if (pBuf1 == NULL) {
			printf("%d\n", GetLastError());
		}
		else {
			pBuf1[0] = (LPSTR)"*";
		}
		CloseHandle(hMapFile);
		printf("else");
		Sleep(10000);
	}
	return 0;
}