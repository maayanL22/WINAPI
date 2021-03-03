#include <Windows.h>

#define NUM_THREADS 2
#define MAX 10000

VOID inc(PINT param) {
	INT temp = *param;
	temp++;
	*param = temp;
}

DWORD WINAPI thread_func(LPVOID param) {
	for (INT i = 0; i < MAX; i++) {
		inc((PINT)param);
	}
	return 1;
}

int main2()
{
	INT val = 0;
	LPVOID param = &val;
	HANDLE hThread[NUM_THREADS];
	for (INT i = 0; i < NUM_THREADS; i++) {
		hThread[i] = CreateThread(
			NULL, //default security attributes
			0, //default stack size
			thread_func,//thread function
			param, //thread param
			0, //default creation flags
			NULL //return thread identifier
		);
	}
	WaitForMultipleObjects(NUM_THREADS, hThread, TRUE, INFINITE);
	printf("Param value: %d\n", *(PINT)param);
}