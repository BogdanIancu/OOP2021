#include<iostream>
#include<string>
#include<fstream>
using namespace std;

namespace custom
{
	class string
	{

	};
};

class TV
{
protected:
	string producator;
private:
	int diagonala;
	int nrZile; // nr elemente duraraViz
	int* durataViz;

public:
	TV()
	{
		producator = "";
		diagonala = 0;
		nrZile = 0;
		durataViz = nullptr;
	}
	TV(string producator, int diagonala, int nrZile, int* durataViz)
	{
		this->producator = producator;
		this->diagonala = diagonala;
		if (nrZile > 0 && durataViz != nullptr)
		{
			this->nrZile = nrZile;
			this->durataViz = new int[nrZile];
			for (int i = 0; i < nrZile; i++)
			{
				this->durataViz[i] = durataViz[i];
			}
		}
	}

	~TV()
	{
		if (durataViz != nullptr)
		{
			delete[] durataViz;
			durataViz = nullptr;
		}
	}

	TV(const TV& t)
	{
		this->producator = t.producator;
		this->diagonala = t.diagonala;
		if (nrZile > 0 && durataViz != nullptr)
		{
			this->nrZile = t.nrZile;
			this->durataViz = new int[t.nrZile];
			for (int i = 0; i < t.nrZile; i++)
			{
				this->durataViz[i] = t.durataViz[i];
			}
		}
		else
		{
			this->nrZile = 0;
			this->durataViz = nullptr;
		}
	}
	TV& operator=(const TV& t)
	{
		if (durataViz != nullptr)
		{
			delete[] durataViz;
			durataViz = nullptr;
		}
		this->producator = t.producator;
		this->diagonala = t.diagonala;
		if (nrZile > 0 && durataViz != nullptr)
		{
			this->nrZile = t.nrZile;
			this->durataViz = new int[t.nrZile];
			for (int i = 0; i < t.nrZile; i++)
			{
				this->durataViz[i] = t.durataViz[i];
			}
		}
		else
		{
			this->nrZile = 0;
			this->durataViz = nullptr;
		}
		return *this;
	}
};

class SmartDevice
{
protected:
	string producator;
public:
	void turnOn()
	{
		cout << "The smart device is ON!" << endl;
	}
	virtual void turnOff()
	{
		cout << "The smart device is OFF!" << endl;
	}
};

class SmartTV : public TV, public SmartDevice
{
public:
	SmartTV()
	{

	}
	SmartTV(string producator, int diagonala) : SmartDevice(),
		TV(producator, diagonala, 0, nullptr)
	{

	}
	string getProducator()
	{
		return TV::producator;
	}
	void turnOn()
	{
		cout << "The smart tv is ON!" << endl;
	}
	void turnOff()
	{
		cout << "The smart tv is OFF!" << endl;
	}
};
class CharacterCounter
{
protected:
	string mesaj;
public:
	virtual void citeste()
	{
		cout << "Mesaj: ";
		cin >> ws;
		getline(cin, mesaj);
	}
	virtual void afiseaza()
	{
		cout << "Lungime: " << mesaj.length();
	}
};

class FileCharacterCounter : public CharacterCounter
{
public:
	void citeste() override
	{
		ifstream f("input.txt");
		f >> ws;
		getline(f, mesaj);
		f.close();
	}
	void afiseaza() override
	{
		ofstream f("output.txt");
		f << mesaj.length();
		f.close();
	}
};
int main()
{
	/*string f;
	custom::string s;*/

	TV t1;
	int v[3]{ 4,3,6 };
	TV t2("Samsung", 110, 3, v);

	SmartDevice s1;
	SmartTV sm1;
	sm1.turnOn();

	sm1.SmartDevice::turnOn();

	SmartDevice* p;
	p = &sm1;
	p->turnOff();

	CharacterCounter c1;
	FileCharacterCounter f1;
	CharacterCounter* pc;
	pc = &f1;
	pc->citeste();
	pc->afiseaza();
}