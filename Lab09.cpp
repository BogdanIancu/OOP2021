#include <iostream>
#include <string>
#include<fstream>
using namespace std;

int valoareInvalida = -1;

//custom exception
class invalid_index_exception :public exception
{
};

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

	Bicicleta operator=(const Bicicleta& b)
	{
		if (this != &b)
		{
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

	int& operator[](int index)
	{
		if (index >= 0 && index < nrExcursii && distante != nullptr)
		{
			return distante[index];
		}
		else
		{
			//return valoareInvalida;
			//throw exception("mesaj invalid");
			throw invalid_index_exception();
		}
	}

	explicit operator float()
	{
		return greutate;
	}

	void operator()(float f)
	{
		if (greutate - f > 0)
		{
			greutate -= f;
		}
	}

	bool operator<(Bicicleta b)
	{
		return greutate < b.greutate;
	}

	void operator+=(string s)
	{
		producator += s;
	}

	//writing info into a binary file
	void serializare()
	{
		ofstream f("bicicleta.bin", ios::binary);
		int length = producator.length();
		f.write((char*)&length, sizeof(length));
		f.write(producator.c_str(), length + 1);
		f.write((char*)&greutate, sizeof(greutate));
		f.write((char*)&nrViteze, sizeof(nrViteze));
		f.write((char*)&nrExcursii, sizeof(nrExcursii));

		if (distante != NULL)
		{
			for (int i = 0; i < nrExcursii; i++)
			{
				f.write((char*)&distante[i], sizeof(distante[i]));
			}
		}
		f.close();
	}

	//reading info from a bianry file
	void deserializare()
	{
		ifstream f("bicicleta.bin", ios::binary);
		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* buffer = new char[length + 1];
		f.read(buffer, length + 1);
		producator = buffer;
		delete[] buffer;
		f.read((char*)&greutate, sizeof(greutate));
		f.read((char*)&nrViteze, sizeof(nrViteze));
		f.read((char*)&nrExcursii, sizeof(nrExcursii));

		delete[] distante;
		distante = new int[nrExcursii];
		for (int i = 0; i < nrExcursii; i++)
		{
			f.read((char*)&distante[i], sizeof(distante[i]));
		}

		f.close();
	}

	friend ostream& operator<<(ostream& out, Bicicleta b);
	friend istream& operator>>(istream& in, Bicicleta& b);

	friend ofstream& operator<<(ofstream& f, Bicicleta b);
	friend ifstream& operator>>(ifstream& f, Bicicleta& b);
};
string Bicicleta::taraProductie = "Romania";

//writing info into a text file
ofstream& operator<<(ofstream& f, Bicicleta b)
{
	if (f.is_open())
	{
		f << "" << b.producator << endl;
		f << b.greutate << endl;
		f << b.nrViteze << endl;
		f << b.nrExcursii << endl;

		for (int i = 0; i < b.nrExcursii; i++)
		{
			f << b.distante[i] << endl;
		}
	}
	return f;
}

//reading info from a text file
ifstream& operator>>(ifstream& f, Bicicleta& b)
{
	if (f.is_open())
	{
		//readinf a string that contains spaces
		f >> ws;
		getline(f, b.producator);
		f >> b.greutate;
		f >> b.nrViteze;
		f >> b.nrExcursii;
		delete[] b.distante;
		b.distante = new int[b.nrExcursii];
		for (int i = 0; i < b.nrExcursii; i++)
		{
			f >> b.distante[i];
		}
	}
	return f;
}

ostream& operator<<(ostream& out, Bicicleta b)
{
	out << "serie: " << b.serie << endl;
	out << "producator: " << b.producator << endl;
	out << "greutate: " << b.greutate << endl;
	out << "nr viteze: " << b.nrViteze << endl;
	out << "nr excursii: " << b.nrExcursii << endl;
	out << "distante: ";
	for (int i = 0; i < b.nrExcursii; i++)
	{
		out << b.distante[i] << " ";
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, Bicicleta& b)
{
	cout << "producator: ";
	//in >> b.producator;
	in >> ws;
	getline(in, b.producator);
	cout << "greutate: ";
	float g = 0;
	in >> g;
	b.setGreutate(g);
	cout << "nr viteze: ";
	in >> b.nrViteze;
	int nr;
	cout << "nr excursii: ";
	in >> nr;
	int* vector = new int[nr];
	for (int i = 0; i < nr; i++)
	{
		cout << "distanta[" << i << "]: ";
		in >> vector[i];
	}
	b.setDistante(vector, nr);
	delete[]vector;
	vector = nullptr;
	return in;
}


class BicicletaElectrica : public Bicicleta
{
private:
	int autonomie;
	char* producatorMotor;
public:
	BicicletaElectrica()
	{
		autonomie = 0;
		producatorMotor = nullptr;
	}
	BicicletaElectrica(int serie, string producator, int* distante, int nrExcursii, int autonomie, const char* producatorMotor) :Bicicleta(serie, producator, distante, nrExcursii)
	{
		this->autonomie = autonomie;
		if (producatorMotor != nullptr)
		{
			this->producatorMotor = new char[strlen(producatorMotor) + 1];
			strcpy_s(this->producatorMotor, strlen(producatorMotor) + 1, producatorMotor);
		}
		else
		{
			this->producatorMotor = nullptr;
		}
	}
	BicicletaElectrica(const BicicletaElectrica& be) : Bicicleta(be)
	{
		this->autonomie = be.autonomie;
		if (be.producatorMotor != nullptr)
		{
			this->producatorMotor = new char[strlen(be.producatorMotor) + 1];
			strcpy_s(this->producatorMotor, strlen(be.producatorMotor) + 1, be.producatorMotor);
		}
		else
		{
			this->producatorMotor = nullptr;
		}
	}
	~BicicletaElectrica()
	{
		if (producatorMotor != nullptr)
		{
			delete[]producatorMotor;
		}
		producatorMotor = nullptr;

	}
	BicicletaElectrica operator=(const BicicletaElectrica& be)
	{
		if (this != &be)
		{
			Bicicleta::operator=(be);
			if (producatorMotor != nullptr)
			{
				delete[]producatorMotor;
			}
			this->autonomie = be.autonomie;
			if (be.producatorMotor != nullptr)
			{
				this->producatorMotor = new char[strlen(be.producatorMotor) + 1];
				strcpy_s(this->producatorMotor, strlen(be.producatorMotor) + 1, be.producatorMotor);
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, BicicletaElectrica be);
	friend istream& operator>>(istream& in, BicicletaElectrica& be);

};

ostream& operator<<(ostream& out, BicicletaElectrica be)
{
	out << (Bicicleta)be;
	out << "autonomie: ";
	out << be.autonomie << endl;
	out << "producator motor: " << be.producatorMotor << endl;
	return out;
}
istream& operator>>(istream& in, BicicletaElectrica& be)
{
	in >> (Bicicleta&)be;
	cout << "autonomie: ";
	in >> be.autonomie;
	char aux[50];
	cout << "Producator mototr: ";
	//readinf a char array that contains spaces
	in >> ws;
	in.getline(aux, 49);
	delete[]be.producatorMotor;
	be.producatorMotor = new char[strlen(aux) + 1];
	strcpy_s(be.producatorMotor, strlen(aux) + 1, aux);
	return in;
}

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

	b3 = b4;

	cout << b4[1] << endl;
	b4[0] = 99;
	cout << b4[0] << endl;

	b2(2);

	float f = (float)b2;
	cout << f << endl;

	cout << (b4 < b2) << endl;

	b3 += " Romania ";
	cout << b3.getProducator() << endl;

	cout << b3;

	//Bicicleta b7;
	//cin >> b7;
	//cout << b7;

	BicicletaElectrica be1;
	BicicletaElectrica be2(55, "Pegas", d, 3, 50, "Bosch");
	Bicicleta b8 = be1; //upcasting (casting implicit)

	BicicletaElectrica be3 = be2;

	be1 = be2;

	//cout << be2;

	//cin >> be1;

	//handling exceptions with a try-catch block
	try
	{
		b4[-1];

	}
	catch (invalid_index_exception& e)
	{
		cout << "index invalid";
	}
	catch (exception& e)
	{
		cout << "eroare: " << e.what();
	}
	catch (...) {
		cout << "eroare generica";
	}

	ofstream g("fisier.txt");
	g << b4;
	g.close();

	Bicicleta b10;

	ifstream h;
	h.open("fisier.txt");
	h >> b10;
	h.close();

	b4.serializare();

	Bicicleta b11;

	b11.deserializare();
}