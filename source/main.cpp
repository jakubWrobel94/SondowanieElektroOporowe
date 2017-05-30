#include <iostream>
#include<vector>
#include<math.h>
#include"RozkladOpornosci.h"
#include <cstdlib>
using namespace std;


void interface(); //funkcja obslugujaca interfejs
int main()
{
    cout<< "Program wyliczajacy teoretyczna wartosc \nopornosci pozornej w profilowaniu elektro-oporowym "<<endl;
    interface();



}

void interface()
{
    double a;
    double h;
    double dx;
    double b;
    double ro1;
    double ro2;
    double I;
    cout<< "Podaj promien kuli [m] : ";

    cin >>a;
    cout <<endl<<"Podaj glebokosc zalegania kuli [m]: ";

    cin>>h;
    cout<<endl<<"Podaj krok pomiarowy [m]: ";

    cin>>dx;
    cout<<endl<<"Podaj rozuniecie elektrod w ukladzie Wenner'a [m]: ";

    cin>>b;
    cout<<endl<<"Podaj opornosc osrodka [Omm] : ";

    cin>>ro1;
    cout<<endl<<"Nacisnij 1 jesli chcesz podac opornosc kuli, jesli chcesz aby byla nieskonczona nacisnij 0 [1/0] : ";
    int i;
    cin>>i;

    if(i==1) {
    cout<<endl<<"Podaj opornosc kuli [Omm] : ";
    cin>>ro2;
    } else ro2=-99;

    cout<<endl<<"Podaj natezenie pradu [A] : ";
    cin>>I;

    RozkladOpornosci *pnt= new RozkladOpornosci(a,h,dx,b,ro1,ro2,I);

    cout<<endl<<"Chcesz zapisac wynik ?? [t/n] ";
    char odp;
    cin>>odp;
    if(odp== 't' || odp == 'T')
    {
        cout <<endl<<"Podaj nazwe pliku (pamietaj o koncowce .txt) : ";
        string filename;
        cin>>filename;
        pnt->zapisDoPliku(filename.c_str());
    }
    cout<<endl<<"Wyswietlic wynik na konsoli ? [t/n]";
    cin>>odp;
    if(odp== 't' || odp == 'T')
    {
        pnt->wypisz_V();
    }



     cout<<endl<<"Wyjscie z programu : 1";
     cout<<endl<<"Kolejne obliczenia : 2"<<endl;
    int i2;
    cin>>i2;
     switch(i2){
     case 1 :
        return;
     case 2:
        system("cls");
        delete pnt;
        interface();
     }

}

