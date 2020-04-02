#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
/*
Scurt preview:
Clasa de baza este proces,din care am derivat 2 clase: procesCivil respectiv procesPenal,fiecare cu datele respective.
Am urmat exemplul din lab pt a face meniul interactiv
Am folosit functii virtuale pt a putea face metode in clasele derivate si cu ajutorul acestora am modificat taxa de timbru si stadiul



*/
class proces
{
protected:
    int nrProces;
    string reclamant;
    string reclamat;


public:
  proces(int,string,string);


    virtual ~proces();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    virtual void calc_timbru(){};
    virtual void mod_stadiu(){};
    virtual double get_timbru(){};
    friend istream &operator>>(istream&, proces&);
    friend ostream &operator<<(ostream&, proces&);



};
proces::proces(int nr=0,string p1="",string p2="")
   {
    if(nr<0)
    {
        cout<<"Introduceti un numar de proces valid\n";
        exit(EXIT_FAILURE);
    }
     nrProces=nr;
   reclamant=p1;
   reclamat=p2;

   }
void proces::citire(istream &in)
{
    string aux,aux2;
    int a;
    cout<<"Numarul procesului= ";
    in>>a;
    in.get();
    cout<<"Nume reclamant= ";
   getline(in,aux);
   cout<<"Numele reclamatului= ";
   getline(in,aux2);
   reclamant=aux;
   reclamat=aux2;
   if(a>0)
    nrProces=a;
   else
   {cout<<"Introduceti un nr de proces valid\n";
   exit(EXIT_FAILURE);
   }
}
proces::~proces()
{
    nrProces=0;
   reclamant="";
   reclamat="";

}

void proces::afisare(ostream &out)
{
    out<<"Nr proces= "<<nrProces<<"\n";
    out<<"Reclamant= "<<reclamant<<"\n";
    out<<"Reclamat= "<<reclamat<<"\n";

}
istream& operator>>(istream& in,proces &p)
{
    p.citire(in);
    return in;
}
ostream & operator<<(ostream& out,proces &p)
{
    p.afisare(out);
    return out;
}

class procesCivil: public proces
{
protected:
    double dauneMorale;
    double dauneMateriale;
    int nrMartori;
    bool stadiu;
    double taxa_timbru;

public:
    ~procesCivil();
    procesCivil(int,string,string,double,double,int,bool,double);
    void citire(istream &in);
    void afisare(ostream &out);
    double get_dauneMorale();
    double get_dauneMateriale();
    double get_timbru();
    void calc_timbru();
    void mod_stadiu();
    friend istream &operator>>(istream &in,procesCivil &p);
    friend ostream &operator<<(ostream &out,procesCivil &p);
};
procesCivil::procesCivil(int a=0,string p1="",string p2="",double a2=0,double a3=0,int a4=0,bool a5=0,double a6=0)
{
    proces(a,p1,p2);
    dauneMorale=a2;
    dauneMateriale=a3;
    nrMartori=a4;
    stadiu=a5;
    taxa_timbru=a6;
}
procesCivil::~procesCivil()
{
dauneMateriale=dauneMorale=0;
nrMartori=0;
stadiu=0;
taxa_timbru=0;

}
double procesCivil::get_dauneMorale()
{
    return dauneMorale;
}
double procesCivil::get_dauneMateriale()
{
    return dauneMateriale;
}
double procesCivil::get_timbru()
{
    return taxa_timbru;
}
void procesCivil::citire(istream &in)
{
    proces::citire(in);
    cout<<"Daune morale= ";
    in>>dauneMorale;
    cout<<"Daune materiale= ";
    in>>dauneMateriale;
    cout<<"Nr martori= ";
    in>>nrMartori;
    if(nrMartori>5)
    {
        cout<<"Stadiul a fost transformat in 1\n";
        stadiu=1;
    }
    else
        {
            cout<<"Stadiul a fost transformat in 0\n";
            stadiu=0;
        }
}
void procesCivil::afisare(ostream &out)
{
    proces::afisare(out);
    out<<"Daune morale: "<<dauneMorale<<"\n";
    out<<"Daune materiale: "<<dauneMateriale<<"\n";
    out<<"Nr martori: "<<nrMartori<<"\n";
    out<<"Stadiu: "<<stadiu<<"\n";
    out<<"Taxa_timbru= "<<taxa_timbru<<"\n";
}
void procesCivil::mod_stadiu()
{
    stadiu=!stadiu;
}

void procesCivil::calc_timbru()
{
   taxa_timbru=get_dauneMateriale()+get_dauneMorale();
taxa_timbru=double(1)/double(10)*taxa_timbru;


}
class procesPenal: public proces
{
protected:
    int dovezi;
    bool stadiu;
public:
   procesPenal(int,string,string,int,bool);
   ~procesPenal();
   void citire(istream &in);
   void afisare(ostream &out);
   void mod_stadiu();
   friend istream& operator>>(istream &,procesPenal&);
   friend ostream& operator<<(ostream &,procesPenal&);
};
void procesPenal::mod_stadiu()
{
    stadiu=!stadiu;
}
procesPenal::procesPenal(int a=0,string p1="",string p2="",int a1=0,bool a2=0)
{
    proces(a,p1,p2);
    dovezi=a1;
    stadiu=a2;
}
procesPenal::~procesPenal()
{
    dovezi=0;
    stadiu=0;
}
void procesPenal::citire(istream &in)
{
    proces::citire(in);
    cout<<"Dovezi= ";
    in>>dovezi;
    if(dovezi>25)
    {
        cout<<"Stadiul a fost transformat in 1\n";
        stadiu=1;
    }
    else
    {
        cout<<"Stadiul a fost transformat in 0\n";
        stadiu=0;
    }
}
void procesPenal::afisare(ostream &out)
{
    proces::afisare(out);
    out<<"Dovezi: "<<dovezi<<"\n";
    out<<"Stadiu: "<<stadiu<<"\n";

}

void tip(proces *&p,int &i,double &maxim,int &k,bool &indicator)
{
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul procesului(civil/penal) "<<i+1<<" :";
    cin>>s;
    if(s=="civil")
    {
        p=new procesCivil;
        cin>>*p;
        p->calc_timbru();
        indicator=1;
        if(p->get_timbru()>maxim)
            {
                maxim=p->get_timbru();
                k=i+1;
            }

        i++;
    cout<<"Vreti sa modificati stadiul?(1/0)\n";
    bool a;
    cin>>a;
    if(a==1)
    {
        p->mod_stadiu();
        cout<<"Stagiul a fost modificat cu succes!";
    }


    }
    else
        if(s=="penal")
    {
        p=new procesPenal;
        cin>>*p;
        cout<<"Vreti sa modificati stadiul?(1/0)\n";
        i++;
        bool a;
        cin>>a;
        if(a==1)
            {
            p->mod_stadiu();
            cout<<"Stadiul a fost transformat cu succes";
            }
    }
    else
    {
        cout<<"Proces invalid, alegeti dintre civil sau penal\n";
    }

}
int main()
{
    double maxim=-1;
    int k=1;
    bool indicator=0;
    cout<<"\t PASCU CRISTIAN VLAD GRUPA 211 PROIECT 2 TEMA 14\n\n";
proces **v;
int n=-1;
while(n<=0)
{
    cout<<"Dati numarul de procese: ";
    cin>>n;
    if(n<=0)
    cout<<"Introduceti un numar pozitiv de procese\n";
}
v=new proces*[n];
for(int i=0;i<n;)
{
    tip(v[i],i,maxim,k,indicator);
}
cout<<"\n\n";
cout<<"Afisare:\n";
for(int i=0;i<n;i++)
        cout<<*v[i]<<"\n\n";
 cout<<"\n";
 if(indicator==1)
 cout<<"Procesul civil cu taxa de timbru cel mai mare are numarul "<<k<< " iar taxa este "<<maxim<<"\n";
 else
    cout<<"Nu exista procese civile\n";


    return 0;
}
