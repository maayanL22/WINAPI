#include <Windows.h>
#include <string.h>
#include <stdio.h>
#define FILENAME "C:\\operatingsystems\\exercises\\gibrish.bin"

int main1()
{
	HANDLE hFile;
	CHAR file_name[] = FILENAME;
	LPCSTR pFileName = file_name;
	hFile = CreateFileA(
		pFileName, // file name
		GENERIC_READ, // access type
		0, // other processes can't share
		NULL,
		OPEN_EXISTING, // open only if file exists
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	DWORD file_size = GetFileSize(hFile, NULL);
	LPVOID pBuf;
	LPSTR data;
	pBuf = malloc(file_size + 1);
	ReadFile(hFile, pBuf, file_size, NULL, NULL);
	data = (LPSTR)pBuf;
	Sleep(10000); // place the character count here, instead of
	// Sleep
	int cnt = 0;
	for (int i = 0; i < file_size + 1; i++) {
		if (data[i] == 'A') {
			cnt++;
		}
	}
	printf("number of A's: %d", cnt);
	free(pBuf);
	CloseHandle(hFile);
	return 0;
}