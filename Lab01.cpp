#include <iostream>
using namespace std;

int main() {
	//the pointers should be explicitly intiliased
	//otherwise their value might be random or CCCC CCCC
	int* p = nullptr;
	int x = 5;
	//the & operator extract the address of a variable (of any type)
	p = &x;
	//this is the address of x
	cout << "p: " << p << endl;
	//the * operator extracts the value from that address
	cout << "*p: " << *p << endl;
	cout << "&p: " << &p << endl;
	//the address of an int* pointer is of type int**
	int** q = &p;
	//*q in this case gives us a value of type int*
	cout << "*q: " << *q << endl;
	//**q gives us a value of type int
	cout << "**q: " << **q << endl;
	//jumps in memory to the next int (+4)
	p++;
	cout << "p++: " << p << endl;
	//jumps in memory after 3 ints (+12 bytes = 3 * 4)
	int* r = p + 3;
	cout << "r: " << r << endl;
	//we can substract pointers of the same type
	//the result is the number of variables of that type
	//that can fit between the two addresses
	cout << "r-p: " << r - p << endl;
	cout << "p-r: " << p - r << endl;

	//statically allocated array
	//its size is mandatory to be a constant
	const int size = 5;
	float v[size];
	v[1] = 99;
	//we can compute the size of a statically allocated array
	cout << sizeof(v) / sizeof(v[0]) << endl;
	//the name of a statically allocated array is a pointer
	//to the first element
	cout << v << endl;
	//v[1] is equivalent to this:
	cout << *(v + 1) << endl;

	float a = 4.5;
	//(int) is called a casting operation
	//it transforms a from int to float
	int b = (int)a;

	//dinamically allocated array with malloc
	//its size can be a variable
	int length = 5;
	float* w = (float*)malloc(length * sizeof(float));
	if (w != nullptr) {
		for (int i = 0; i < length; i++) {
			w[i] = i + 1;
		}
		for (int i = 0; i < length; i++) {
			cout << *(w + i) << endl;
		}
	}
	//each allocation should be followed at the end
	//by a deallocation
	free(w);
	//this line avoids dangling pointers
	w = nullptr;

	//allocating and deleting a single float
	//with new and delete
	float* y = new float();
	*y = 99;
	cout << *y << endl;
	delete y;
	y = nullptr;

	//allocating and deleting a float array
	float* z = new float[length];
	for (int i = 0; i < length; i++) {
		z[i] = i + 1;
	}
	cout << z[2] << endl;
	delete[] z;
	//this line avoids dangling pointers
	z = nullptr;
}