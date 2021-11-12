#include <iostream>
#include <string>
using namespace std;

class Bicicleta
{
private:
	string producator;
	float greutate;
	int nrViteze;
	int* distante = nullptr;
	int nrExcursii = 0;
	//constantele se initializeaza fie la definire, fie in toti constructorii
	//constants should be initialised either when defined or in all constructors
	const int serie;
	//campurile statice apartin clasei, nu obiectelor (sunt comune pt toate obiectele)
	//static fields are class-related, not object-related (are common for all the objects)
	static string taraProductie;

public:

	/*Bicicleta() {
		producator = "Necunoscut";
		greutate = 3;
		nrViteze = 1;
	}*/

	//constructor cu parametri ce joaca si rol de constructor default
	//constructor with parameters that works also as a default constructor
	Bicicleta(string _producator = "Necunoscut", float _greutate = 3) : serie(1)
	{
		producator = _producator;
		greutate = _greutate;
		nrViteze = 1;
	}

	//initializare atribute in antet
	//attribute initialization in the constructor's header
	Bicicleta(string _producator, float _greutate, int nrViteze) : producator(_producator),
		greutate(_greutate), nrViteze(nrViteze), serie(2)
	{

	}

	//constantele se pot initializa doar in antetul constructorilor
	//constant fields can be initialised in the constructors' header only
	Bicicleta(int serie, string producator, int* distante, int nrExcursii) : serie(serie)
	{
		this->producator = producator;
		if (distante != nullptr && nrExcursii > 0) {
			this->distante = new int[nrExcursii];
			for (int i = 0; i < nrExcursii; i++)
			{
				this->distante[i] = distante[i];
			}
			this->nrExcursii = nrExcursii;
		}
	}

	//constructor de copiere
	//copy constructor
	Bicicleta(const Bicicleta& b) : serie(b.serie)
	{
		producator = b.producator;
		nrViteze = b.nrViteze;
		greutate = b.greutate;
		if (b.distante != nullptr && b.nrExcursii > 0) {
			this->distante = new int[b.nrExcursii];
			for (int i = 0; i < b.nrExcursii; i++)
			{
				this->distante[i] = b.distante[i];
			}
			this->nrExcursii = b.nrExcursii;
		}

	}

	//destructor
	~Bicicleta()
	{
		if (distante != nullptr) {
			delete[] distante;
			distante = nullptr;
		}

	}

	//getter
	string getProducator() {
		return producator;
	}

	//setter
	void setProducator(string _producator) {
		if (_producator.length() > 0)
		{
			producator = _producator;
		}
	}

	float getGreutate() {
		return greutate;
	}
	void setGreutate(float _greutate) {
		if (_greutate > 0)
		{
			greutate = _greutate;
		}
	}
	//getter-ul pentru vector trebuie sa returneze o copie
	//altfel se incalca incapsularea (se poate modifica campul privat)
	//the array getter should return a copy
	//otherwise the encapsulation is broken (we can change the private field)
	int* getDistante() {
		if (nrExcursii > 0 && distante != NULL)
		{
			int* copie = new int[nrExcursii];
			for (int i = 0; i < nrExcursii; i++) {
				copie[i] = distante[i];
			}
			return copie;
		}
		else {
			return NULL;
		}
	}

	//getter pentru numarul de elemente (de obicei se creeaza impreuna cu precedentul)
	//getter for the number of elements (usually created together with the previous one)
	int getNrExcursii() {
		return nrExcursii;
	}

	//setter-ul pentru array primeste atat noul vector, cat si noul numar de elemente
	//the setter for the array should receive the new array together with the new number of elements
	void setDistante(int* distante, int nrExcursii) {
		if (distante != NULL && nrExcursii > 0) {
			if (this->distante != NULL) {
				delete[] this->distante;
			}
			this->distante = new int[nrExcursii];
			this->nrExcursii = nrExcursii;
			for (int i = 0; i < nrExcursii; i++)
				this->distante[i] = distante[i];
		}
	}

	//getter per element (pentru a evita copia / alternativa la precedentul)
	//getter per element (to avoid the copy / an alternative to the previous one)
	int getDistante(int index) {
		if (index >= 0 && index < nrExcursii && distante != NULL) {
			return distante[index];
		}
		else
			return -1;
	}

	//metodele statice sunt fie getteri si setteri pentru campurile statice
	//fie metode ce prelucreaza mai multe obiecte simultan
	//ele nu primesc pointerul this
	//the static methods are either getters and setters for the static fields
	//or methods that process multiple objects simultaniously
	//they do not receive the this pointer
	static string getTaraProductie() {
		return taraProductie;
	}
	static void setTaraProductie(string taraProductie)
	{
		Bicicleta::taraProductie = taraProductie;
	}
	static long distantaTotala(Bicicleta* biciclete, int nrBiciclete) {
		long sumadistante = 0;
		if (nrBiciclete > 0 && biciclete != NULL) {
			for (int i = 0; i < nrBiciclete; i++) {
				if (biciclete[i].distante != NULL) {
					for (int j = 0; j < biciclete[i].nrExcursii; j++) {
						sumadistante += biciclete[i].distante[j];
					}
				}
			}
		}
		return sumadistante;
	}
};
//campurile statice se pot initializa doar in afara clasei
//static field should be initialised outside the class only
string Bicicleta::taraProductie = "Romania";

int main() {
	Bicicleta b1;
	Bicicleta b2("Pegas", 12);


	cout << b1.getProducator() << endl;
	b2.setProducator("RockRider");
	cout << b2.getProducator() << endl;
	cout << b2.getGreutate() << endl;

	//declararea unui vector de obiecte
	//va declansa apelul constructorului implicit
	//pentru fiecare obiect (element)
	//an array of objects will call the
	//default constructor for every element
	Bicicleta v[3];
	cout << v[0].getProducator() << endl;

	Bicicleta* pb;
	//alocare obiect in heap folosind ctor default
	//allocating an object in heap by using the defaul ctor
	pb = new Bicicleta();
	//object deallocation from heap
	//stergere obiect din heap
	delete pb;
	pb = nullptr;

	//alocare obiect in heap folosind ctor cu parametri
	//allocating an object in heap by using the ctor with parameters
	pb = new Bicicleta("B'twin", 14);
	cout << pb->getProducator() << endl;
	delete pb;
	pb = nullptr;

	Bicicleta b3("Pegas", 10, 18);
	int d[3] = { 5,2,7 };
	Bicicleta b4(123, "Romet", d, 3);
	d[0] = 99;

	//Apeluri explicite constructor de copiere
	//Explicit calls for the copy constructor
	Bicicleta b5 = b4;
	Bicicleta b6(b5);

	int* dist = b4.getDistante();
	dist[0] = 55;
	delete[] dist;

	int vector[] = { 3, 8, 14, 20 };
	b4.setDistante(vector, 4);
	int* r = b4.getDistante();
	for (int i = 0; i < b4.getNrExcursii(); i++) {
		cout << r[i] << endl;
		cout << b4.getDistante(i) << endl;
	}
	cout << b2.getTaraProductie() << endl;
	b4.setTaraProductie("Germania");
	cout << b2.getTaraProductie() << endl;
	cout << Bicicleta::getTaraProductie() << endl;
	Bicicleta biciclete[] = { b4, b5 };
	cout << Bicicleta::distantaTotala(biciclete, 2) << endl;
}