#ifndef ROZKLADOPORNOSCI_H
#define ROZKLADOPORNOSCI_H
#include<vector>
#include<string>

using namespace std;
class RozkladOpornosci
{
    public:

        ///--------KONSTRUKTORY ----------
        RozkladOpornosci(double   a,double   h,double   dx,double   b, double   ro1,double   ro2,double   I);
        RozkladOpornosci(double   a,double   h,double   dx,double   b, double   ro1,string  ro2,double   I);
        virtual ~RozkladOpornosci();

        ///---------SETTERY---------------


        void set_a(double   a);
        void set_h(double   h);
        void set_dx(double   dx);
        void set_b(double   b);
        void set_ro1(double   ro1);
        void set_ro2(double   ro2);
        void set_I(double   I);

        ///----------GEOMETRIA-------------

        double   calcD_R( double   db,double   n); // oblicza D lub R - dx wartosc przesuniecia - bedzie zmieniana w iteracjach,
                                                            // db - przesuniecie elktrody wzgl. punktu pomiarowego
        ///------------OBLCZENIA ----------

        vector <double  > calcP(double   &x,double   iterations);// funkcja obliczajaca wsp Legendre'a

        double   calcBn(double   d,double   n); //funkcja obliczajaca wspolczynniki B n-tego stopnia
        double   calcVInPoint(double   r,double   d,double   &teta, double R, double   n); //oblicza V w punkcie w zal. od r,d, teta; n - liczba skladnikow w sumie
        double   calcCos(double   r,double   d,double   c); //funkcja obliczajaca cosinus z tw. cosinusow
        double   calcV_MN(double   n); //funkcja obliczajaca roznice potencjalow na elektordach VM i VN,
                                                // w srodku oblicza 4 potencjaly i dodaje je do siebie
        double  calcV(double dd,double dr,double n); // oblicza potencjaly dla pary elektrod,
                                                    //dd- przesuniecie lektrody pradowej wzgl punktu pomiaru
                                                    //dr - przesuniecie elektordy pomiarowej wzgl punktu pomiaru

        void calcAll(); //funkcja zbiorcza obliczajaca wszystko

        ///---------POMOCNICZE-----------
        void wypisz_V(); // wypisuje wartosci potencalow i opornosci na ekran konsoli
        void zapisDoPliku(const char *); //zapisuje wartosci x i opornosci pozornych
        void rememberRoApp(double   x);
        void rememberV_MN(double   x);

    private:
        double   _a; //prom kuli
        double   _h; //glebokosc zalegania
        double   _dx; //krok pomiarowy
        double   _b;  //odleglosc miedzy elektrodami
        double   _ro1;//opornosc osrodka
        double   _ro2;//opornosc kuli
        double   _I;  //natezenie pradu

        /// --------WEKTORY PRZTRZYMUJ¥CE POSZCZEGÓLNE WARNOŒCI ------------
        vector<double  > _ro_app;
        vector<double  > _V_MN;
        vector<double  > _V_AM;
        vector<double  > _V_BM;
        vector<double  > _V_AN;
        vector<double  > _V_BN;
};

#endif // ROZKLADOPORNOSCI_H
