#include "RozkladOpornosci.h"
#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
RozkladOpornosci::RozkladOpornosci(double   a,double   h,double   dx,double   b, double   ro1,double   ro2,double   I)
{
    set_a(a);
    set_h(h);
    set_dx(dx);
    set_b(b);
    set_ro1(ro1);
    set_ro2(ro2);
    set_I(I);
    calcAll();
}

RozkladOpornosci::RozkladOpornosci(double  a, double  h, double  dx, double  b, double  ro1, string ro2, double  I)
{
        set_a(a);
    set_h(h);
    set_dx(dx);
    set_b(b);
    set_ro1(ro1);
    set_ro2(-99);
    set_I(I);
    calcAll();
}
RozkladOpornosci::~RozkladOpornosci()
{
    //dtor
}

void RozkladOpornosci::set_b(double   b)
{
        _b=b;
}

void RozkladOpornosci::set_dx(double   dx)
{
    _dx=dx;
}

void RozkladOpornosci::set_h(double   h)
{
    _h=h;
}

void RozkladOpornosci::set_a(double   a)
{
    _a=a;

}

void RozkladOpornosci::set_I(double   I)
{


    _I=I;
}
void RozkladOpornosci::set_ro1(double   ro1)
{
        _ro1=ro1;
}

void RozkladOpornosci::set_ro2(double   ro2)
{
  _ro2=ro2;
}
void RozkladOpornosci::rememberRoApp(double   x)
{
    _ro_app.push_back(x);
}

void RozkladOpornosci::rememberV_MN(double   x)
{
    _V_MN.push_back(x);
}

double   RozkladOpornosci::calcCos(double   r, double   d, double   c)
{
    double  a=(r*r)+(d*d)-(c*c);
    double  b=2*r*d;
    return(a/b);
}

double   RozkladOpornosci::calcBn(double   d, double   n)
{
    double   bn1=(_ro1*_I)/(2.0*M_PI);
    double  bn2,bn3;
    if(_ro2==0)
    {
        bn2=-1;
        bn3=1;
    } else if(_ro2==-99)
    {
        bn2=n;
        bn3=n+1;
    } else {
        bn2=n*(_ro2-_ro1);
        bn3=1/(n*_ro1+((n+1)*_ro2));
        }
    double   bn4=pow(_a,2.0*n+1)/pow(d,n+1);
    double  bn=bn1*bn2*bn3*bn4;
    return bn;
}

vector <double  >RozkladOpornosci::calcP(double   &x, double   iterations)
{
    vector <double  > P;
    P.push_back(1);
    P.push_back(x);
    for(double   i=1;i<iterations;i++)
    {

        P.push_back(((2*i+1)/(i+1))*x*P[i]-(i/(i+1))*P[i-1]);
    }
    return P;
}

double   RozkladOpornosci::calcD_R( double   db,double   n)
{
        return sqrt(pow(10.0*_a-(_dx*n-_b*db),2.0)+pow(_h+_a,2));
}

double   RozkladOpornosci::calcVInPoint(double   r, double   d, double   &teta, double R,double   n)
{
	vector <double  > P=calcP(teta,n);
	double   v2=0;
	for(double   i=0;i<n;i++)
            {
                v2+=calcBn(d,i)*pow(r,-(i+1))*P[i];
            }
            double   v1=(_I*_ro1)/(2.0*M_PI*R);
         return  v1+v2;
}

double  RozkladOpornosci::calcV(double dd,double dr,double n) // dd- przesuniecie elektordy pradowej wzgl srodka ukladu, dr - elektrody zbiorczej
{
    double   d=calcD_R(dd,n);
    double   r=calcD_R(dr,n);
    double b=fabs(dd-dr)*_b;
    double   teta=calcCos(d,r,b);
    double   V=calcVInPoint(r,d,teta,b,100);
    return V;
}
double   RozkladOpornosci::calcV_MN(double   n) // n jest potrzebne przy n*_dx czyli okreslamy punkt pomiarowy po profilu
{
    double   V_AM=calcV(1.5,0.5,n);
    _V_AM.push_back(V_AM);

    double   V_BN=calcV(-1.5,-0.5,n);
    _V_BN.push_back(V_BN);

    double   V_BM=calcV(-1.5,0.5,n);
    _V_BM.push_back(V_BM);
    double   V_AN=calcV(-0.5,1.5,n);
    _V_AN.push_back(V_AN);

    double   V_M=V_AM-V_BM;

    double   V_N=V_AN-V_BN;
    return V_M-V_N;
}

void RozkladOpornosci::calcAll()
{
    double   n=(20*_a)/_dx;
    for(double   i=0;i<n;i++)
    {
        double   x=calcV_MN(i);
        double   op=2*M_PI*_b*(x/_I);

        rememberRoApp(op);
        rememberV_MN(x);
    }

}

void RozkladOpornosci::wypisz_V()
{
    double   n=(20*_a)/_dx;

    for(double   i=0;i<n;i++)
    {
        cout<<i*_dx<<"      "<<_V_MN[i]<<"       "<<_ro_app[i]<<endl;
    }

}

void RozkladOpornosci::zapisDoPliku(const char *filename)
{
    ofstream plik;
    plik.open(filename);
    if(plik.good())
    {
        for(double   i=0;i<_V_MN.size();i++)
        {
            plik<<i*_dx<<" "<<_ro_app[i]<<endl;
        }
        plik.close();
    }
}









