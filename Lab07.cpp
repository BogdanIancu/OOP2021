#include <iostream>
#include <string>
using namespace std;

class Roata
{
private:
	int dimensiune;
	int nrSuruburi;
};

class Masina
{
private:
	//innert class (clasa imbricata/interna)
	class Motor
	{
	private:
		int putere;
		string producator;
	};
	char* producator;
	string model;
	int viteza;
	const int serieSasiu;
	//1:1 composition (relatie de compozitie de tip 1:1)
	Motor motor;
	//1:M composition (relatie de compozitie de tip 1:M)
	Roata roti[4];

public:
	Masina() : serieSasiu(0)
	{
		producator = nullptr;
		model = "";
		viteza = 0;
	}

	Masina(const char* _producator, string _model, int _viteza) :serieSasiu(1)
	{
		model = _model;
		viteza = _viteza;

		if (_producator != nullptr)
		{
			delete[] producator;
			producator = new char[strlen(_producator) + 1];
			strcpy_s(producator, strlen(_producator) + 1, _producator);
		}
		else
		{
			producator = nullptr;
		}
	}

	Masina(int _viteza) :serieSasiu(2)
	{
		this->producator = nullptr;
		this->model = "";
		viteza = _viteza;
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
		else
		{

			producator = nullptr;
		}
	}

	~Masina()
	{
		if (producator != nullptr)
		{
			delete[] producator;
			producator = nullptr;
		}
	}

	int getViteza()
	{
		return viteza;
	}

	void setViteza(int _viteza)
	{
		if (_viteza >= 0)
		{
			viteza = _viteza;
		}
	}

	char* getProducator()
	{
		if (producator != nullptr)
		{
			char* cop = new char[strlen(producator) + 1];
			strcpy_s(cop, strlen(producator) + 1, producator);
			return cop;
		}
		return nullptr;
	}

	void setProducator(const char* _producator)
	{
		if (_producator != nullptr)
		{
			if (producator != nullptr)
			{
				delete[] producator;
			}
			producator = new char[strlen(_producator) + 1];
			strcpy_s(producator, strlen(_producator) + 1, _producator);

		}
	}

	Masina& operator=(const Masina& m)
	{
		if (this != &m) {
			if (producator != nullptr)
			{
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

	//unary operator overloaded through a method
	//supraincarcare operator unar prin metoda
	bool operator!()
	{
		bool ok = this->viteza > 0 ? true : false;
		return ok;
	}

	//pre-incrementation
	Masina operator++()
	{
		this->viteza++;
		return *this;
	}

	//post-incrementation
	Masina operator++(int i)
	{
		Masina copie = *this;
		this->viteza++;
		return copie;
	}

	//binary operator overloaded through a method
	//supraincarcare operator binar prin metoda
	Masina operator+(const Masina& m)
	{
		Masina copie = *this;
		copie.viteza = copie.viteza + m.viteza;
		return copie;
	}

	//binary operator overloaded through a method
	//supraincarcare operator binar prin metoda
	Masina operator+(int x)
	{
		Masina copie = *this;
		copie.viteza = copie.viteza + x;
		return copie;
	}

	//friend functions can access the non-public members
	//functiile friend pot accesa membrii non-publici
	friend Masina operator+(int x, Masina m);
	friend ostream& operator<<(ostream& out, Masina m);

	//friend methods can be declared like this
	//but will still be global
	//functiile friend pot avea tot corpul in clasa
	//dar asta nu le face metode (vor fi tot functii globale)
	friend istream& operator>>(istream& in, Masina& m)
	{
		string buffer;
		cout << "Producator: ";

		in >> buffer;
		m.setProducator(buffer.c_str());

		cout << "Model: ";
		in >> m.model;

		cout << "Viteza: ";
		in >> m.viteza;

		return in;
	}
};

//the reading or writing operators (<< and >>)
//can be overloaded by global functions only
//operatorii de citire si scriere (<< si >>)
//pot fi supraincarcati doar prin functii globale
ostream& operator<<(ostream& out, Masina m)
{
	if (m.producator != NULL)
	{
		out << "Producator: " << m.producator << endl;
	}
	else
	{
		out << "Producator: " << endl;
	}
	out << "Modelul: " << m.model << endl;
	out << "Viteza: " << m.viteza << endl;

	return out;
}

//binary operator overloaded through a global function
//operator binar supraincarcat prin functie globala
Masina operator+(int x, Masina m)
{
	m.viteza = m.viteza + x;
	return m;
}

/*bool operator!(Masina m)
{
	return m.getViteza() > 0;
}*/

int main()
{
	Masina m1;
	Masina m2("Dacia", "Spring", 90);

	m1.setViteza(30);
	cout << m1.getViteza() << endl;
	cout << m2.getProducator() << endl;

	m1.setProducator("Renault");
	char* prod = m1.getProducator();
	cout << prod << endl;
	delete[] prod;
	//orice constructor cu parametru poate fi apelat si cu egal
	Masina m3(m2);
	Masina m4 = m2;

	Masina m5(40);
	Masina m6 = 60;
	m6 = m3;

	int x = 1, y = 2, z = 3;
	x = y = z;

	m6 = m3 = m2;
	m6.operator=(m3.operator=(m2));

	//! operator call
	//apel operator !
	if (!m2)
	{
		cout << "Masina se deplaseaza.";
	}
	else
	{
		cout << "Masina nu se deplaseaza.";
	}

	//pre-increment
	m6 = ++m2;
	//post-increment
	m6 = m2++;

	//+ operator which adds two cars
	Masina m7 = m2 + m3;
	//+ operator which adds cars and ints
	m7 = m3 + 10;
	//+ operator which adds ints and cars
	Masina m8 = 10 + m3;

	//console writing operator
	cout << m8;

	Masina m9;

	//console reading operator
	cin >> m9;
	cout << m9;
}



