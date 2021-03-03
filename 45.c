#include <Windows.h>

#include <Windows.h>
#include <stdio.h>

struct MyStruct
{
	INT a;
	INT b;
	INT id;
} typedef MyStruct;

DWORD WINAPI bla(LPVOID lparam) {
	struct MyStruct *nums = (MyStruct*)lparam;
	INT count = nums->a + nums->b;
	for (INT i = 1; i <= count; i++) {
		printf("Thread: %d ", nums->id);
		printf("var: %d\n", i);
	}
	Sleep(10000);
	return 1;
}


int main()
{
	PVOID tid = NULL;

	HANDLE threads[4] = {NULL, NULL, NULL, NULL};
	struct MyStruct* structs[4] = { NULL, NULL, NULL, NULL };
	LPVOID pstructs[4];
	for (int i = 0; i < 4; i++) {
		structs[i] = (MyStruct*)malloc(sizeof(MyStruct));
		structs[i]->a = (i + 1) * 2;
		structs[i]->b = 4;
		structs[i]->id = i + 1;
		pstructs[i] = structs[i];
		threads[i]= CreateThread(
			NULL, //default security attributes
			0, //default stack size
			bla, //thread function
			structs[i], //thread param
			0, //default creation flags
			tid //return thread identifier
		);
	}
	WaitForMultipleObjects(4, threads, FALSE, INFINITE);
}
