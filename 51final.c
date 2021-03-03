#include <Windows.h>

CRITICAL_SECTION ghCriticalSections[5];
INT sticks[] = { 0,1,2,3,4 };

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	INT id = *(PINT)(lpParameter);
	if (id == 4)
	{
		EnterCriticalSection(&ghCriticalSections[id]);
		BOOL success = TryEnterCriticalSection(&ghCriticalSections[0]);
		if (success)
		{
			printf("Philosophers number %d ate", id);
			LeaveCriticalSection(&ghCriticalSections[id]);
			LeaveCriticalSection(&ghCriticalSections[0]);
			return 1;
		}
		else
		{
			LeaveCriticalSection(&ghCriticalSections[id]);
			EnterCriticalSection(&ghCriticalSections[0]);
			EnterCriticalSection(&ghCriticalSections[id]);
			printf("Philosophers number %d ate", id);
			LeaveCriticalSection(&ghCriticalSections[id]);
			LeaveCriticalSection(&ghCriticalSections[0]);
			return 1;
		}
		//return 0;
	}

	else
	{
		EnterCriticalSection(&ghCriticalSections[id]);
		BOOL success = TryEnterCriticalSection(&ghCriticalSections[id + 1]);
		// Place critical code here
		if (success)
		{
			printf("Philosopher number %d ate\n", id);
			LeaveCriticalSection(&ghCriticalSections[id]);
			LeaveCriticalSection(&ghCriticalSections[id + 1]);
			return 1;
		}
		else
		{
			LeaveCriticalSection(&ghCriticalSections[id]);
			EnterCriticalSection(&ghCriticalSections[id + 1]);
			EnterCriticalSection(&ghCriticalSections[id]);
			printf("Philosopher number %d ate\n", id);
			LeaveCriticalSection(&ghCriticalSections[id]);
			LeaveCriticalSection(&ghCriticalSections[id + 1]);
			return 1;
		}
	}
	return 0;
	
}

int main(void)
{
	for (int i = 0; i < 5; i++) {
		InitializeCriticalSection(&ghCriticalSections[i]);
	}
	
	HANDLE threads[5] = { NULL, NULL, NULL, NULL, NULL};
	LPVOID ids[5];
	for (int i = 0; i < 5; i++) {
		ids[i] = &sticks[i];
		threads[i] = CreateThread(
			NULL, //default security attributes
			0, //default stack size
			ThreadProc, //thread function
			ids[i], //thread param
			0, //default creation flags
			NULL //return thread identifier
		);
	}
	WaitForMultipleObjects(5, threads, TRUE, INFINITE);
	
	for (int i = 0; i < 5; i++) {
		DeleteCriticalSection(&ghCriticalSections[i]);
	}
}