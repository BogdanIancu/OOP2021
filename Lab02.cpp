#include <iostream>
#include <string>
using namespace std;

//passing by value
void interschimba(int x, int y)
{
	int aux;
	aux = x;
	x = y;
	y = aux;

}

//passing by address
void interschimba2(int* x, int* y)
{
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;

}

//passing by reference
void interschimba3(int& x, int& y)
{
	int aux;
	aux = x;
	x = y;
	y = aux;

}

int main()
{
	int m[2][3];
	//computing the number of lines
	cout << sizeof(m) / sizeof(m[0]) << endl;
	//computing the number of columns
	cout << sizeof(m[0]) / sizeof(m[0][0]) << endl;

	int** z = new int* [2];
	for (int i = 0; i < 2; i++) {

		z[i] = new int[3];
	}

	z[1][2] = 55;

	cout << *(*(z + 1) + 2) << endl;

	//the deallocation is always done in the
	//reverse order of the allocation
	for (int i = 0; i < 2; i++) {

		delete[] z[i];
	}
	delete[] z;
	z = nullptr;

	const char* s = "cuvant";
	//not possible because s is a pointer to a constant char
	//s[0] = 'C';

	char t[10];
	strcpy_s(t, "ceva");
	cout << t << endl;
	cout << strlen(t) << endl;

	char* w = new char[strlen(t) + 1];
	strcpy_s(w, strlen(t) + 1, t);
	cout << w << endl;

	//a shallow copy!
	//char* y = w;
	cout << strcmp(t, w) << endl;

	string s1 = "cuvant";
	string s2 = s1;
	string s3 = s1 + "!!!";
	cout << s3 << endl;
	//number of letters
	cout << s1.length() << endl;
	cout << s1.size() << endl;
	//transforming from char* to string
	string s4 = w;
	cout << s4 << endl;
	//transforming from string to char*
	const char* q = s3.c_str();
	delete[] w;

	int x = 7;
	int y = 5;

	interschimba(x, y);
	cout << x << " " << y << endl;

	interschimba2(&x, &y);
	cout << x << " " << y << endl;

	//r is a reference that saves the address of x
	int& r = x;
	cout << r << endl;

	interschimba3(x, y);
	cout << x << " " << y << endl;

	cout << r << endl;

}