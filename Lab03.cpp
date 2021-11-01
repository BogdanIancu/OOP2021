#include <iostream>
#include <string>
using namespace std;

//enum is used when we want to have
//only one value from a few possible ones
enum CuloareOchi
{
    albastri, verzi, caprui, negri = 5

};

//union overlaps the field in memory
union IdUnic
{
    short idScurt;
    int idMediu;
    long long idLung;


};

//struct was the first form
//of abstraction from C
struct Persoana {
    string nume;
    string prenume;
    int varsta;
};

int x = 5;
void f() {
    //local variables
    //shadow global variables with the same name
    int x = 2;
    cout << x;
}

//classes are the
//foundation of OOP
class Student {
public:
    //attributes
    string nume;
    string prenume;

    //constructors
    Student() {
        nume = "necunoscut";
        prenume = "necunoscut";
        varsta = 18;
        esteLaBuget = false;
    }
    Student(string nume, string _prenume) {
        this->nume = nume;
        prenume = _prenume;
        varsta = 18;
        esteLaBuget = false;
    }
    //destructor
    ~Student() {
        cout << "s-a apelat destructorul" << endl;
    }
    //method
    void repartizeazaBuget()
    {
        esteLaBuget = true;

    }
private:
    int varsta;
    bool esteLaBuget = false;
};

int main()
{
    Persoana persoana1;
    persoana1.nume = "Alexandru";
    persoana1.varsta = 21;
    Persoana persoana2;
    persoana2.nume = "Maria";

    CuloareOchi culoare;
    culoare = albastri;
    cout << culoare << endl;
    culoare = CuloareOchi::negri;

    cout << sizeof(IdUnic) << endl;
    IdUnic id;
    id.idLung = 100;
    cout << id.idScurt << endl;

    //student1 is an object
    Student student1;
    student1.nume = "Ionel";
    student1.repartizeazaBuget();
    Student student2("Ionescu", "Mihai");
    f();
    cout << student2.nume;
    //when declaring an array of objects
    //the default constructor is called
    //for every one of them (for every element)
    Student v[5];
    //pointer to object (to Student)
    Student* ps;
    ps = &student2;
    //The next two lines are equivalent
    cout << (*ps).nume << endl;
    cout << ps->nume << endl;
}
