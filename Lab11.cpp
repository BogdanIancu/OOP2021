#include<iostream>
#include<string>
using namespace std;

//interfata (interface)
class Afisabil
{
public:
	virtual void afiseaza() = 0;
};

ostream& operator<<(ostream& out, Afisabil& a)
{
	a.afiseaza();
	return out;
}

//clasa abstracta (abstract class)
class Persoana
{
private:
	string nume;
	int varsta;
public:
	Persoana()
	{
		nume = "nec";
		varsta = 1;
	}

	Persoana(string nume, int varsta)
	{
		this->nume = nume;
		this->varsta = varsta;
	}

	virtual float venit() = 0;

};

class Student : public Persoana, public Afisabil
{
private:
	float bursa;

public:
	Student()
	{
		bursa = 0;
	}
	Student(string nume, int varsta, float bursa) :Persoana(nume, varsta)
	{
		this->bursa = bursa;
	}

	virtual float venit()
	{
		return bursa;
	}

	void afiseaza() override
	{
		cout << "Bursa este " << bursa << endl;
	}

};

class Angajat : public Persoana
{
private:
	float salariu;

public:
	Angajat()
	{
		salariu = 0;
	}

	Angajat(string nume, int varsta, float salariu) :Persoana(nume, varsta)
	{
		this->salariu = salariu;
	}

	float venit() override
	{
		return salariu * 0.6;
	}
};


template<class T>
T aduna(T a, T b)
{
	return a + b;
}

template<typename T = int>
class Vector
{
private:
	T* elemente;
	int dimensiune;
public:
	Vector()
	{
		elemente = new T[1];
		dimensiune = 1;
	}
	Vector(unsigned int dimensiune)
	{
		this->elemente = new T[dimensiune];
		this->dimensiune = dimensiune;
	}

	Vector(const Vector& v)
	{
		this->elemente = new T[v.dimensiune];
		this->dimensiune = v.dimensiune;
		for (int i = 0; i < dimensiune; i++)
		{
			this->elemente[i] = v.elemente[i];
		}
	}
	Vector& operator=(const Vector& v)
	{
		if (this != &v)
		{
			delete[] this->elemente;
			this->elemente = new T[v.dimensiune];
			this->dimensiune = v.dimensiune;
			for (int i = 0; i < dimensiune; i++)
			{
				this->elemente[i] = v.elemente[i];
			}
		}
		return *this;
	}
	~Vector()
	{
		delete[] this->elemente;
	}

	unsigned int getDimensiune()
	{
		return dimensiune;
	}

	T& operator[](int index)
	{
		if ((index >= 0) && (index < dimensiune))
		{
			return elemente[index];
		}
		else
			throw exception("Index invalid");
	}
};

int main()
{
	Student s1("Ion", 20, 1200);
	//cout << s1.Persoana::venit() << endl;
	cout << s1.venit() << endl;


	Persoana* p;
	//Persoana p1("Andrei", 20);

	Angajat a1("Gabrel", 69, 5800);

	//p = &p1;
	p = &s1;
	p = &a1;
	cout << p->venit() << endl;

	Afisabil* pa;
	pa = &s1;
	pa->afiseaza();

	cout << s1;

	cout << aduna<int>(2, 3) << endl;
	cout << aduna<float>(2.5, 3.5) << endl;

	//aduna(s1, s1);
	Vector<int>v1;
	v1[0] = 99;
	cout << v1[0] << endl;
	Vector<float>v2(3);
	v2[0] = 9;
	v2[1] = 2.5;
	v2[2] = 1.2;
	for (int i = 0; i < v2.getDimensiune(); i++)
	{
		cout << v2[i] << endl;
	}
	Vector<Student>v3(2);
	v3[0] = s1;
	v3[1] = s1;
	for (int i = 0; i < v3.getDimensiune(); i++)
	{
		cout << v3[i] << endl;
	}
	//vector de int datorita valorii default pentru T
	//int vector due to the default value for T
	Vector<> v4;

	//p = new Student();
	//delete p;
}