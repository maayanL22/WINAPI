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


int main1()
{
	PVOID tid = NULL;
	/*
	struct MyStruct *my_struct =
		(MyStruct*)malloc(sizeof(MyStruct));
	my_struct->a = 3;
	my_struct->b = 4;
	my_struct->id = 1;
	LPVOID pstruct = my_struct;
	HANDLE hThread = CreateThread(
		NULL, //default security attributes
		0, //default stack size
		bla, //thread function
		pstruct, //thread param
		0, //default creation flags
		tid //return thread identifier
	);

	HANDLE hThread2 = CreateThread(
		NULL, //default security attributes
		0, //default stack size
		bla, //thread function
		pstruct, //thread param
		0, //default creation flags
		tid //return thread identifier
	);
	//printf(tid);
	//HANDLE threads[] = { hThread, hThread2 };
	//WaitForSingleObject(hThread, INFINITE);
	//WaitForMultipleObjects(2, threads, FALSE, INFINITE);
	*/
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