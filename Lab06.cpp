#include <iostream>
#include <string>
using namespace std;

//functions can return a reference
//only when the value that they return
//is global to the function (NOT local)
long s = 0;
long& suma(int x, int y)
{
	s = x + y;
	return s;
}

class Masina
{
private:
	char* producator;
	string model;
	int viteza;
	const int serieSasiu;
public:
	Masina() :serieSasiu(0)
	{
		producator = nullptr;
		model = "";
		viteza = 0;
	}

	Masina(int viteza) :serieSasiu(1)
	{
		this->viteza = viteza;
		producator = nullptr;
		model = "";
	}

	Masina(const char* producator, string model, int viteza) :serieSasiu(2)
	{
		this->model = model;
		this->viteza = viteza;
		if (producator != nullptr) {
			this->producator = new char[strlen(producator) + 1];
			strcpy_s(this->producator, strlen(producator) + 1, producator);
		}
		else {
			this->producator = nullptr;
		}
	}

	Masina(const Masina& m) :serieSasiu(m.serieSasiu)
	{
		model = m.model;
		viteza = m.viteza;
		if (m.producator != nullptr)
		{
			producator = new char[strlen(m.producator) + 1];
			strcpy_s(producator, strlen(m.producator) + 1, m.producator);
		}
		else {
			producator = nullptr;
		}
	}

	~Masina()
	{
		if (producator != nullptr) {
			delete[] producator;
			producator = nullptr;
		}

	}

	//equals operator
	Masina& operator=(const Masina& m)
	{
		if (this != &m) {
			if (producator != nullptr) {
				delete[] producator;
				producator = nullptr;
			}

			model = m.model;
			viteza = m.viteza;
			if (m.producator != nullptr)
			{
				producator = new char[strlen(m.producator) + 1];
				strcpy_s(producator, strlen(m.producator) + 1, m.producator);
			}
		}
		return *this;

	}

	int getViteza()
	{
		return viteza;
	}

	void setViteza(int viteza)
	{
		if (viteza > 0) {
			this->viteza = viteza;
		}
	}

	char* getProducator() {
		if (producator != nullptr) {
			char* copie = new char[strlen(producator) + 1];
			strcpy_s(copie, strlen(producator) + 1, producator);
			return copie;
		}
		else {
			return nullptr;
		}
	}

	void setProducator(const char* producator) {

		if (producator != nullptr) {
			if (this->producator != nullptr) {
				delete[] this->producator;
			}
			this->producator = new char[strlen(producator) + 1];
			strcpy_s(this->producator, strlen(producator) + 1, producator);
		}

	}
};

int main()
{
	Masina m1;
	Masina m2("Dacia", "Spring", 90);
	m1.setViteza(30);
	cout << m1.getViteza() << endl;
	m1.setProducator("Tesla");
	cout << m1.getProducator() << endl;
	char* prod = m2.getProducator();
	cout << prod << endl;
	delete[] prod;

	Masina m3(m2); //explicit call copy constructor
	Masina m4 = m2; //explicit call copy constructor

	Masina m5(50);
	Masina m6 = 40; //same as above (constructors with one parameter can be called with = also)

	m6 = m2; //equals operator call
	m6.operator=(m2); //the call from above is transformed into this one

	int x = 1, y = 2;
	int z = y = x; //the equals operator can be called chained

	m1 = m2 = m3;
	m1.operator=(m2.operator=(m3));

	m3 = m3; //the first if from the equals operator avoids auto-assignation
}