#include <Windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		return 0;
	}
	int id = atoi(argv[1]);
	HANDLE hMyMutex = CreateMutexA(NULL, FALSE, "Hello");
	DWORD waitResult = WaitForSingleObject(hMyMutex, 10000);
	if (waitResult == WAIT_OBJECT_0)
	{
		printf("Hello World! Process got parameter %d\n", id);
		Sleep(5000);
		ReleaseMutex(hMyMutex);
	}
	else
		printf("Mutex could not be obtained for too long\n");
	CloseHandle(hMyMutex);
	return 1;
}