#include<iostream>
#include<stdlib.h>
using namespace std;
#include <amp.h>
using namespace concurrency;


int main() {

	int size = 2;
	cout << "Enter Size  : " << endl;
	//cin >> size;
	int A[2 * 2], B[2 * 2], C[2 * 2];
	for (int i = 0; i < size * size; i++)
	{
		A[i] = (rand() % (size * 2)) + 1;
		B[i] = (rand() % (size * 2)) + 1;
		C[i] = 0;
	}

	array_view<int, 2> arrayA(size, size, A);

	array_view<int, 2> arrayB(size, size, B);

	array_view<int, 2> arrayC(size, size, C);

	parallel_for_each(arrayC.extent,
		[=](index<2> thid) restrict(amp) {
		int i = thid[0];
		int j = thid[1];
		for (int k = 0; k < size; k++)
			arrayC[thid] += arrayA(i, k) * arrayB(k, j);
	});
	arrayC.synchronize();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arrayA(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arrayB(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arrayC(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;

}
