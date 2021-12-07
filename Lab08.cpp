#include <iostream>
#include <string>
using namespace std;

//var globala pt operatorul index
//global variable to be used by the index operator
int valoareInvalida = -1;

class Bicicleta
{
private:
	string producator;
	float greutate;
	int nrViteze;
	int* distante = nullptr;
	int nrExcursii = 0;
	const int serie;

	static string taraProductie;

public:
	Bicicleta(string _producator = "Necunoscut", float _greutate = 3) : serie(1)
	{
		producator = _producator;
		greutate = _greutate;
		nrViteze = 1;
	}

	Bicicleta(string _producator, float _greutate, int nrViteze) : producator(_producator),
		greutate(_greutate), nrViteze(nrViteze), serie(2)
	{

	}

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

	~Bicicleta()
	{
		if (distante != nullptr) {
			delete[] distante;
			distante = nullptr;
		}
	}

	Bicicleta operator=(const Bicicleta& b) {
		if (distante != nullptr) {
			delete[] distante;
			distante = nullptr;
		}

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
		return *this;
	}

	string getProducator() {
		return producator;
	}

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

	int getNrExcursii() {
		return nrExcursii;
	}

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

	int getDistante(int index) {
		if (index >= 0 && index < nrExcursii && distante != NULL) {
			return distante[index];
		}
		else
			return -1;
	}

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

	//index operator
	int& operator[](int index) {
		if (index >= 0 && index < nrExcursii) {
			return distante[index];
		}
		else {
			return valoareInvalida;
		}
	}

	//explicit cast operator
	explicit operator float() {
		return greutate;
	}

	//function operator
	void operator()(float f) {
		greutate = greutate - f < 0 ? greutate - f : greutate;
	}

	bool operator<(Bicicleta b) {
		return nrViteze < b.nrViteze;
	}

	friend ostream& operator<<(ostream& out, Bicicleta b);
	friend istream& operator>>(istream& in, Bicicleta& b);

};
string Bicicleta::taraProductie = "Romania";

ostream& operator<<(ostream& out, Bicicleta b) {
	out << "serie " << b.serie << endl;
	out << "producator: " << b.producator << endl;
	out << "nr viteze " << b.nrViteze << endl;
	out << "nr excursii" << b.nrExcursii << endl;
	out << "distante";
	for (int i = 0; i < b.nrExcursii; i++) {
		out << b.distante[i] << " ";
	}
	return out;
}

istream& operator>>(istream& in, Bicicleta& b) {
	cout << "producator";
	in >> b.producator;
	cout << "greutate";
	float g;
	in >> g;
	b.setGreutate(g);
	int nr;
	cout << "nr el";
	in >> nr;
	int* v = new int[nr];
	for (int i = 0; i < nr; i++) {
		cout << "distanta[" << i << "]=";
		in >> v[i];
	}
	b.setDistante(v, nr);
	delete[]v;
	return in;
}

//public inheritance
class BicicletaElectrica : public Bicicleta {
private:
	int autonomie;
	char* producatorMotor;
public:
	BicicletaElectrica() {
		autonomie = 0;
		producatorMotor = NULL;
	}

	BicicletaElectrica(int serie, string producator, int nrExcursii, int* distante, int autonomie, const char* producatorMotor) :Bicicleta(serie, producator, distante, nrExcursii) {
		this->autonomie = autonomie;
		if (producatorMotor != NULL) {
			this->producatorMotor = new char[strlen(producatorMotor) + 1];
			strcpy_s(this->producatorMotor, strlen(producatorMotor) + 1, producatorMotor);
		}
		else
		{
			this->producatorMotor = NULL;
		}
	}

	BicicletaElectrica(const BicicletaElectrica& be) :Bicicleta(be)
	{
		this->autonomie = be.autonomie;
		if (be.producatorMotor != NULL) {
			this->producatorMotor = new char[strlen(be.producatorMotor) + 1];
			strcpy_s(this->producatorMotor, strlen(be.producatorMotor) + 1, be.producatorMotor);
		}
		else {
			this->producatorMotor = NULL;
		}
	}

	~BicicletaElectrica() {
		delete[] producatorMotor;
	}

	BicicletaElectrica& operator=(const BicicletaElectrica& be) {
		Bicicleta::operator=(be);
		delete[] producatorMotor;
		this->autonomie = be.autonomie;
		if (be.producatorMotor != NULL) {
			this->producatorMotor = new char[strlen(be.producatorMotor) + 1];
			strcpy_s(this->producatorMotor, strlen(be.producatorMotor) + 1, be.producatorMotor);
		}
		return *this;
	}
};

int main() {
	Bicicleta b1;
	Bicicleta b2("Pegas", 12);


	cout << b1.getProducator() << endl;
	b2.setProducator("RockRider");
	cout << b2.getProducator() << endl;
	cout << b2.getGreutate() << endl;

	Bicicleta v[3];
	cout << v[0].getProducator() << endl;

	Bicicleta* pb;
	pb = new Bicicleta();
	delete pb;
	pb = nullptr;

	pb = new Bicicleta("B'twin", 14);
	cout << pb->getProducator() << endl;
	delete pb;
	pb = nullptr;

	Bicicleta b3("Pegas", 10, 18);
	int d[3] = { 5,2,7 };
	Bicicleta b4(123, "Romet", d, 3);
	d[0] = 99;

	Bicicleta b5 = b4;
	Bicicleta b6(b5);

	int* dist = b4.getDistante();
	dist[0] = 55;
	delete[] dist;
	//index operator call
	b4[1] = 10;
	cout << b4[1] << endl;

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

	//explicit cast
	float x = (float)b2;
	cout << x;
	//op <
	cout << (b1 < b3) << endl;
	Bicicleta b7;
	//cin >> b7;
	//cout << b7;

	BicicletaElectrica be1;
	BicicletaElectrica be2(456, "Pegas", 4, vector, 50, "Bosch");
	Bicicleta b8 = be2;

	BicicletaElectrica be3 = be1;
	be3 = be2;
}