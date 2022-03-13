///Tema 9

#include <iostream>
#include <typeinfo>
#include <string> /// permite folosirea datelor de tip 'string'
#include <vector>///permite folosirea stl-ului 'vector'
#include <set> ///permite folosirea stl-ului 'set'
#include <stdlib.h> ///permite executia functiei system(...)

using namespace std;

///la citirea datelor, utilizatorul este fortat sa introduca o noua valoare pentru variabila respectiva pana cand aloca una din categoria ceruta

class locuinta
{
    protected:
        string nume_client;
        float suprafata_utila;
        float discount;
        static int contor_locuinte;
        const int id_locuinta;
    public:
        locuinta();
        locuinta(const string, const float, const float);
        locuinta(const locuinta&);
        virtual ~locuinta();
        void set_nume_client(const string);
        string get_nume_client() const;
        void set_suprafata_utila(const float);
        float get_suprafata_utila()const;
        void set_discount(const float);
        float get_discount()const;
        const int get_id_locuinta()
        {
            return this->id_locuinta;
        }
        locuinta& operator=(const locuinta &l);
        virtual void citire(istream &in);
        friend istream& operator>>(istream &in, locuinta &l);
        virtual void afisare(ostream &out) const;
        friend ostream& operator<<(ostream &out, const locuinta &l);
        virtual float pret(){}; ///functie virtuala pura
        static int numar_locuinte()
        {
            return contor_locuinte;
        }
};

int locuinta::contor_locuinte=0; ///declararea variabilei statice

locuinta::locuinta():id_locuinta(++contor_locuinte)
{
    this->nume_client="";
    this->suprafata_utila=0;
    this->discount=0;
}

locuinta::locuinta(const string nume_client, const float suprafata_utila, const float discount):id_locuinta(++contor_locuinte)
{
    this->nume_client=nume_client;

    try
    {
        if(suprafata_utila<0)
            throw suprafata_utila;
    }
    catch(float su)
    {
        cout<<"Eroare in constructor, suprafata utila nu poate avea valoare negativa.\n";
        exit(EXIT_FAILURE);
    }
    this->suprafata_utila=suprafata_utila;

    try
    {
        if(discount<0)
            throw discount;
        if(discount>10)
            throw 1;
    }
    catch(float d)
    {
        cout<<"Eroare in constructor, discount-ul nu poate fi negativ.\n";
        exit(EXIT_FAILURE);
    }
    catch(int x)
    {
        cout<<"Eroare in constructor, discount-ul nu poate fi mai mare de 10%.\n";
        exit(EXIT_FAILURE);
    }
    this->discount=discount;
}

locuinta::locuinta(const locuinta &l):id_locuinta(contor_locuinte)
{
    this->nume_client=l.nume_client;
    this->suprafata_utila=l.suprafata_utila;
    this->discount=l.discount;
}

locuinta::~locuinta()
{
    this->nume_client="";
    this->suprafata_utila=0;
    this->discount=0;
    contor_locuinte--;
}

void locuinta::set_nume_client(const string nume_client)
{
    this->nume_client=nume_client;
}

string locuinta::get_nume_client() const
{
    return this->nume_client;
}

void locuinta::set_suprafata_utila(const float suprafata_utila)
{
    this->suprafata_utila=suprafata_utila;
}

float locuinta::get_suprafata_utila() const
{
    return this->suprafata_utila;
}

void locuinta::set_discount(const float discount)
{
    this->discount=discount;
}

float locuinta::get_discount() const
{
    return this->discount;
}

locuinta& locuinta::operator=(const locuinta &l)
{
    this->nume_client=l.nume_client;
    this->suprafata_utila=l.suprafata_utila;
    this->discount=l.discount;
}

void locuinta::citire(istream &in)
{
    string nume_client, suprafata_utila, discount;
    int ok, i, m; ///ok va numara de cate ori apare caracterul caractere care nu sunt cifre intr-un string intr-un string; este bine sa apara maxim unul, ce ar trebui sa reprezint . pentru numerele float

    cout<<"Introduceti numele clientului: ";
    getline(in, nume_client);
    this->nume_client=nume_client;

    cout<<"Introduceti suprafata utila a locuintei (numarul de metri patrati): ";
    getline(in, suprafata_utila);

    while(true)
    {
      try
      {
        ok=0;
        for(i=0; i<suprafata_utila.size(); i++)
        {
            if(suprafata_utila[i]=='.')
                ok++;
            else
                if(!isdigit(suprafata_utila[i]))
                    ok=2;
            if(ok==2)
                break;
        }
        if(ok>1||(ok<2&&stof(suprafata_utila)<0))
            throw suprafata_utila;
        else
            break;
      }
      catch(string su)
      {
          cout<<"Eroare la introducerea valorii suprafetei utila, aceasta trebuie sa fie un numar real pozitiv.\n";
          cout<<"Introduceti suprafata utila a locuintei (numarul de metri patrati): ";
          getline(in, suprafata_utila);
      }
    }
    this->suprafata_utila=stof(suprafata_utila);
    ;
    cout<<"Introduceti discount-ul pretului locuintei(procentaj, valoare in intervalul [0, 10] ): ";
    getline(in, discount);
    while(true)
    {
      try
      {
        ok=0;
        for(i=0; i<discount.size(); i++)
        {
            if(discount[i]=='.')
                ok++;
            else
                if(!isdigit(discount[i]))
                    ok=2;
            if(ok==2)
                break;
        }
        if(ok>1||(ok<2&&(stof(discount)<0||stof(discount)>10)))
            throw discount;
        else
            break;
      }
      catch(string su)
      {
          cout<<"Eroare la introducerea valorii suprafetei utila, aceasta trebuie sa fie un numar real din intervalul [0, 10].\n";
          cout<<"Introduceti discount-ul locuintei locuintei (procentaj, valoarea in intervalul [0, 10]): ";
          getline(in, discount);
      }
    }
    this->discount=stof(discount);
}

istream& operator>>(istream &in, locuinta &l)
{
    l.citire(in);
    return in;
}

void locuinta::afisare(ostream &out) const
{
    out<<"Numele clientului: "<<this->get_nume_client()<<'\n';
    out<<"Suprafata utila a locuintei (numar metri patrati): "<<this->get_suprafata_utila()<<'\n';
    out<<"Discount-ul pretului locuintei: "<<this->get_discount()<<'\n';
}

ostream& operator<<(ostream &out, const locuinta &l)
{
    l.afisare(out);
    return out;
}


///----------------------------------------------------

class apartament: public locuinta
{
    private:
        int etaj;
        static float pret_mp;
    public:
        apartament();
        apartament(const string, const float, const float, const int);
        apartament(const apartament&);
        ~apartament();
        void set_etaj(const int);
        int get_etaj() const;
        static void set_pret_mp(const float);
        static float get_pret_mp();
        apartament& operator=(const apartament &a);
        void citire(istream &in);
        friend istream& operator>>(istream &in, apartament &a);
        void afisare(ostream &out) const;
        friend ostream& operator<<(ostream& out, const apartament &a);
        float pret() const;
};

float apartament::pret_mp=0;

apartament::apartament():locuinta()
{
    this->etaj=0;
}

apartament::apartament(const string nume_client,const float suprafata_utila, const float discount, const int etaj): locuinta(nume_client, suprafata_utila, discount)
{
    try
    {
        if(etaj<0)
            throw etaj;
    }
    catch(int e)
    {
        cout<<"Eroare in constructor, numarul etajului nu poate fi negativ.\n";
        exit(EXIT_FAILURE);
    }
    this->etaj=etaj;
}

apartament::apartament(const apartament &a):locuinta(a)
{
    this->etaj=a.etaj;
}

apartament::~apartament()
{
    this->etaj=0;
}

void apartament::set_etaj(const int etaj)
{
   this->etaj=etaj;
}

int apartament::get_etaj() const
{
    return this->etaj;
}

void apartament::set_pret_mp(const float pmp)
{
    pret_mp=pmp;
}

float apartament::get_pret_mp()
{
    return pret_mp;
}

apartament& apartament::operator=(const apartament &a)
{
    locuinta::operator=(a); ///apelarea supraincarcarii operator= din clasa baza
    this->etaj=a.etaj;
    ///completarea supraincarcarii operator= pentru clasa derivata in care ne aflam
}

void apartament::citire(istream&in)
{
    locuinta::citire(in); ///apelarea metodei citire din clasa baza
    string etaj;
    int i;
    cout<<"Introduceti numarul etajului: ";
    getline(in, etaj);
    while(true)
    {
      try
      {
        for(i=0; i<etaj.size(); i++)
            if(!isdigit(etaj[i]))
                 break;
        if(i!=etaj.size()||(i==etaj.size()&&stoi(etaj)<0))
            throw etaj;
        else
            break;
      }
      catch(string et)
      {
          cout<<"Eroare la introducerea numarului etajului, acesta trebuie sa fie un numar natural.\n";
          cout<<"Introduceti numarul etajului: ";
          getline(in, etaj);
      }
    }
    this->etaj=stoi(etaj);
    ///completarea citirii pentru clasa derivata in care ne aflam
}

istream& operator>>(istream& in, apartament &a)
{
    a.citire(in);
    return in;
}

void apartament::afisare(ostream &out) const
{
    locuinta::afisare(out); ///apelarea metodei afisare din clasa baza
    out<<"Numarul etajului apartamentului: "<<this->get_etaj()<<'\n';
    ///completarea afisarii pentru clasa derivata in care ne aflam
}

ostream& operator<<(ostream& out, const apartament &a)
{
    a.afisare(out);
    return out;
}

float apartament::pret() const
{
    float pf;
    pf=this->get_suprafata_utila()*apartament::get_pret_mp();
    pf=pf-(float)(this->get_discount()/100)*pf;
    return pf;
}


///----------------------------------------------------

class casa:public locuinta
{
    private:
        float nr_mp_curte;
        int nr_etaje;
        vector <float> su_etaj; ///stl vector
        static float pret_mp;
    public:
        casa();
        casa( const string, const float, const float, const float, const int, const vector<float>);
        casa(const casa&);
        ~casa();
        void set_nr_mp_curte(const float);
        float get_nr_mp_curte() const;
        void set_nr_etaje(const int);
        int get_nr_etaje() const;
        void set_su_etaj(const vector<float>);
        vector <float> get_su_etaj() const;
        static void set_pret_mp(const float pmp);
        static float get_pret_mp();
        casa& operator=(const casa &c);
        void citire(istream &in);
        friend istream& operator>>(istream &in, casa &c);
        void afisare(ostream &out) const;
        friend ostream& operator<<(ostream &out, const casa &c);
        float pret() const;
};

float casa::pret_mp=0;

casa::casa():locuinta()
{
    this->nr_mp_curte=0;
    this->nr_etaje=0;
    //for(int i=0; i<=nr_etaje; i++)
    this->su_etaj.push_back(0);
}

casa::casa( const string nume_client, const float suprafata_utila, const float discount, const float nr_mp_curte, const int nr_etaje, const vector <float> su_etaj):locuinta(nume_client, suprafata_utila, discount)
{
    try
    {
        if(nr_mp_curte<0)
            throw nr_mp_curte;
    }
    catch(float nmpc)
    {
        cout<<"Eroare in constructor, numarul de metri patrati al unei curti nu poate fi negativ.\n";
        exit(EXIT_FAILURE);
    }
    this->nr_mp_curte=nr_mp_curte;

    try
    {
        if(nr_etaje<0)
            throw nr_etaje;
    }
    catch(int ne)
    {
        cout<<"Eroare in constructor, numarul de etaje nu poate fi negativ.\n";
        exit(EXIT_FAILURE);
    }
    this->nr_etaje=nr_etaje;

    this->su_etaj.clear();
    vector<float>::const_iterator i;
    for(i=su_etaj.begin(); i!=su_etaj.end(); ++i)
    {
        try
        {
            if(*i<0)
                throw 1;
        }
        catch (int val)
        {
            cout<<"Eroare in constructor, suprafata unui etaj nu poate fi negativa.\n";
            exit(EXIT_FAILURE);
        }
        this->su_etaj.push_back(*i);
    }
}

casa::casa(const casa& c):locuinta(c)
{
    this->nr_mp_curte=c.nr_mp_curte;
    this->nr_etaje=c.nr_etaje;

    this->su_etaj.clear();
    vector <float>::const_iterator i;
    for(i=c.su_etaj.begin(); i!=c.su_etaj.end(); ++i)
        this->su_etaj.push_back(*i);
}
casa::~casa()
{
    this->nr_mp_curte=0;
    this->nr_etaje=0;

    this->su_etaj.clear();
}

void casa::set_nr_mp_curte(const float nr_mp_curte)
{
    this->nr_mp_curte=nr_mp_curte;
}

float casa::get_nr_mp_curte() const
{
    return this->nr_mp_curte;
}

void casa::set_nr_etaje(const int nr_etaje)
{
    this->nr_etaje=nr_etaje;
}

int casa::get_nr_etaje() const
{
    return this->nr_etaje;
}

void casa::set_su_etaj(const vector<float> su_etaj)
{
    this->su_etaj.clear();
    vector <float>::const_iterator i;
    for(i=su_etaj.begin(); i!=su_etaj.end(); ++i)
        this->su_etaj.push_back(*i);
}

vector<float> casa::get_su_etaj() const
{
    return this->su_etaj;
}

void casa::set_pret_mp(const float pmp)
{
    pret_mp=pmp;
}

float casa::get_pret_mp()
{
    return pret_mp;
}

casa& casa::operator=(const casa &c)
{
    locuinta::operator=(c);
    this->nr_mp_curte=c.nr_mp_curte;
    this->nr_etaje=c.nr_etaje;

    this->su_etaj.clear();
    vector <float>::const_iterator i;
    for(i=c.su_etaj.begin(); i!=c.su_etaj.end(); ++i)
        this->su_etaj.push_back(*i);
}

void casa::citire(istream &in)
{
    locuinta::citire(in);
    string nr_mp_curte, nr_etaje, suprafata_per_etaj;
    int ok, i, j; ///ok va numara de cate ori apare caracterul caractere care nu sunt cifre intr-un string intr-un string; este bine sa apara maxim unul, ce ar trebui sa reprezint . pentru numerele float

    cout<<"Introduceti numarul de metri patrati al curtii: ";
    getline(in, nr_mp_curte);
    while(true)
    {
      try
      {
        ok=0;
        for(i=0; i<nr_mp_curte.size(); i++)
        {
            if(nr_mp_curte[i]=='.')
                ok++;
            else
                if(!isdigit(nr_mp_curte[i]))
                    ok=2;
            if(ok==2)
                break;
        }
        if(ok>1||(ok==2&&stof(nr_mp_curte)<0))
            throw nr_mp_curte;
        else
            break;
      }
      catch(string nmpc)
      {
          cout<<"Eroare la introducerea valorii pentru numarul patrat de metri al curtii, aceasta trebuie sa fie un numar real pozitiv.\n";
          cout<<"Introduceti numarul de metri patrati al curtii: ";
          getline(in, nr_mp_curte);
      }
    }
    this->nr_mp_curte=stof(nr_mp_curte);

    cout<<"Introduceti numarul de etaje al casei: ";
    getline(in, nr_etaje);
    while(true)
    {
      try
      {
        for(i=0; i<nr_etaje.size(); i++)
            if(!isdigit(nr_etaje[i]))
                 break;
        if(i!=nr_etaje.size()||(i==nr_etaje.size()&&stoi(nr_etaje)<0))
            throw nr_etaje;
        else
            break;
      }
      catch(string ne)
      {
          cout<<"Eroare la introducerea numarului de etaje, acesta trebuie sa fie un numar natural.\n";
          cout<<"Introduceti numarul de etaje al casei: ";
          getline(in, nr_etaje);
      }
    }
    this->nr_etaje=stoi(nr_etaje);

    for(j=1; j<=this->nr_etaje; j++)
    {
        cout<<"Introduceti suprafata utila a etajului cu numarul "<<j<<" (numar metri patrati): ";
        getline(in, suprafata_per_etaj);
        while(true)
        {
           try
           {
             ok=0;
             for(i=0; i<suprafata_per_etaj.size(); i++)
             {
                if(suprafata_per_etaj[i]=='.')
                    ok++;
                else
                    if(!isdigit(suprafata_per_etaj[i]))
                       ok=2;
                if(ok==2)
                    break;
             }
             if(ok>1||(ok<2&&stof(suprafata_per_etaj)<0))
                  throw suprafata_per_etaj;
             else
                  break;
           }
           catch(string se)
           {
               cout<<"Eroare la introducerea valorii pentru suprafata etajului cu numarul "<<j<<", aceasta trebuie sa fie un numar real pozitiv.\n";
               cout<<"Introduceti suprafata utila a etajului cu numarul "<<j<<" (numar metri patrati): ";
               getline(in, suprafata_per_etaj);
           }
        }
        this->su_etaj.push_back(stof(suprafata_per_etaj));
    }
}

istream& operator>>(istream &in, casa &c)
{
    c.citire(in);
    return in;
}

void casa::afisare(ostream &out) const
{
    locuinta::afisare(out);
    out<<"Numarul de metri patrati ai curtii: "<<this->get_nr_mp_curte()<<'\n';
    out<<"Numarul de etaje al casei: "<<this->get_nr_etaje()<<'\n';
    int i;
    for(i=1; i<=this->nr_etaje; i++)
        cout<<"Suprafata utila a etajului "<<i<<" este: "<<this->su_etaj[i]<<'\n';
}

ostream& operator<<(ostream &out, const casa &c)
{
    c.afisare(out);
    return out;
}

float casa::pret() const
{
    float pf=0;
    int i;
    for(i=1; i<=this->get_nr_etaje(); i++)
        pf=pf+this->su_etaj[i]*casa::get_pret_mp();
    pf=pf-(float)(this->get_discount()/100)*pf;
    pf=pf+this->get_nr_mp_curte()*casa::get_pret_mp();
    return pf;
}


///----------------------------------------------------


template <class t> class Gestiune
{
    t *v;
    int nr;
public:
    Gestiune(t *p=NULL, int n=0)
    {
        nr=n;
        v=new t[n];
        for(int i=0;i<n;i++)
        {
            v[i]=p[i];
        }
    }
    Gestiune(Gestiune &a)
    {
        nr=a.nr;
        v=new t[nr];
        for(int i=0;i<nr;i++)
        {
            v[i]=a.v[i];
        }
    }
    ~Gestiune()
    {
        delete [] v;
    }

    int get_nr() {return nr;}
    t get_v(int i) {return v[i];}

    friend istream& operator >>(istream &in, Gestiune <t> &g)
    {
        cout<<"Introduceti numarul de persoane implicate: ";
        string sir;
        int j;
        getline(in, sir);
        while(true)
        {
          try
          {
            for(j=0; j<sir.size(); j++)
              if(!isdigit(sir[j]))
                   break;
            if(j!=sir.size()||(j==sir.size()&&stoi(sir)<0))
              throw sir;
            else
              break;
          }
          catch(string p)
          {
            cout<<"Eroare la introducerea numarului de persoane implicate, aceasta trebuie sa fie un numar natural.\n";
            cout<<"Introduceti numarul de persoane implicate: ";
            getline(cin, sir);
          }
        }
        g.nr=stoi(sir);


        g.v=new t[g.nr];
        cout<<"Introduceti obiectele: \n";
        for(int i=0;i<g.nr;i++){
           in>>g.v[i];
           cout<<"\n";
        }
        return in;
    }

    friend ostream& operator <<(ostream &out, Gestiune<t> &g)
    {
        out<<"In firma de gestiune se gasesc urmatoarele "<<g.nr<<" persoane implicate:"<<"\n";
        for(int i=0;i<g.nr;i++)
            out<<g.v[i]<<"\n";
        return out;
    }

    t& operator+=(const t &nou)
    {
        this->nr++;
        this->v[nr]=new t;
        this->v[nr]=nou;
    }
};


///----------------------------------------------------


template <> class Gestiune <casa>
{
    casa* c;
    int nr_case;
    float venit_total;
public:
    Gestiune(casa *x=NULL, int n=0)
    {
        this->venit_total=0;
        this->nr_case=n;
        this->c=new casa[n];
        for(int i=0;i<n;i++)
        {
            c[i]=x[i];
            this->venit_total=this->venit_total+c[i].pret();
        }
    }
    Gestiune(Gestiune &a)
    {
        this->nr_case=a.nr_case;
        this->venit_total=0;
        //delete [] this->c;
        this->c=new casa[this->nr_case];
        for(int i=0;i<nr_case;i++)
        {
            c[i]=a.c[i];
            this->venit_total=this->venit_total+c[i].pret();
        }
    }
    ~Gestiune()
    {
        delete [] c;
    }

    int get_nr_case() {return nr_case;}
    casa get_c(int i) {return c[i];}

    friend istream& operator >>(istream &in, Gestiune <casa> &g)
    {
        cout<<"Introduceti numarul de persoane implicate: ";
        string sir;
        int j;
        getline(in, sir);
        while(true)
        {
          try
          {
            for(j=0; j<sir.size(); j++)
              if(!isdigit(sir[j]))
                   break;
            if(j!=sir.size()||(j==sir.size()&&stoi(sir)<0))
              throw sir;
            else
              break;
          }
          catch(string p)
          {
            cout<<"Eroare la introducerea numarului de persoane implicate, aceasta trebuie sa fie un numar natural.\n";
            cout<<"Introduceti numarul de persoane implicate: ";
            getline(cin, sir);
          }
        }
        g.nr_case=stoi(sir);

        g.c=new casa[g.nr_case];
        cout<<"Introduceti obiectele\n";
        for(int i=0;i<g.nr_case;i++)
        {
            in>>g.c[i];
            g.venit_total+=g.c[i].pret();
           cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, Gestiune<casa> &g)
    {
        out<<"In firma de gestiune sunt "<<g.nr_case<<" case date in chirie.\n";
        for(int i=0;i<g.nr_case;i++)
            out<<g.c[i]<<"\n";
        out<<"Pe luna, acestea aduc firmei un venit total "<<g.venit_total<<" de lei.\n\n";
        return out;
    }
};


///----------------------------------------------------


void menu()
{
    int option, ok, j; ///ok va numara de cate ori apare caracterul caractere care nu sunt cifre intr-un string intr-un string; este bine sa apara maxim unul, ce ar trebui sa reprezint . pentru numerele float

    string op, p1, p2;

    cout<<"Introduceti valoarea pretului pe metru patrat pentru locuintele de tip aparatament: ";
    getline(cin, p1);
    while(true)
    {
      try
      {
        ok=0;
        for(j=0; j<p1.size(); j++)
        {
            if(p1[j]=='.')
                ok++;
            else
                if(!isdigit(p1[j]))
                    ok=2;
            if(ok==2)
                break;
        }
        if(ok>1||(ok==2&&stof(p1)<0))
            throw p1;
        else
            break;
      }
      catch(string p)
      {
          cout<<"Eroare la introducerea valorii pentru pretul per metru patrat al unui apartament, aceasta trebuie sa fie un numar real pozitiv.\n";
          cout<<"Introduceti valoarea pretului pe metru patrat pentru locuintele de tip aparatament: ";
          getline(cin, p1);
      }
    }
    apartament::set_pret_mp(stof(p1));

    cout<<"Introduceti valoarea pretului pe metru patrat pentru locuintele de tip casa: ";
    getline(cin, p2);
    while(true)
    {
      try
      {
        ok=0;
        for(j=0; j<p2.size(); j++)
        {
            if(p2[j]=='.')
                ok++;
            else
                if(!isdigit(p2[j]))
                    ok=2;
            if(ok==2)
                break;
        }
        if(ok>1||(ok==2&&stof(p2)<0))
            throw p2;
        else
            break;
      }
      catch(string p)
      {
          cout<<"Eroare la introducerea valorii pentru pretul per metru patrat al unei case, aceasta trebuie sa fie un numar real pozitiv.\n";
          cout<<"Introduceti valoarea pretului pe metru patrat pentru locuintele de tip casa: ";
          getline(cin, p2);
      }
    }
    casa::set_pret_mp(stof(p2));


    int n;
    set<pair<locuinta*, string>> proprietati;

    do{
        cout<<"\n Roman Iulian-Robert, grupa 141. Proiect: Proprietati - 9 \n\n";
        cout<<"\tMENIU : \n";
        cout<<"0 - Terminare program.\n";
        cout<<"1 - Citire si memorare n locuinte.\n";
        cout<<"2 - Afisare n locuinte memorate ulterior.\n";
        cout<<"3 - Gestiune - Template: Apartament. \n";
        cout<<"4 - Gestiune - Template:Casa - specializare \n";
        cout<<"5 - Veniturile totale de pe un anumit tip de proprietate \n";
        cout<<"6 - Stergeti cele n locuinte memorate anterior si apelati din nou prima optiune pentru a putea folosi optiunea 2 pe un set diferit de locuinte.\n\n";
        cout<<'\n';

        cout<<'\n'<<"Optiunea dvs. : ";
        getline(cin, op);
        while(true)
        {
          try
          {
            for(j=0; j<op.size(); j++)
              if(!isdigit(op[j]))
                   break;
            if(j!=op.size()||(j==op.size()&&stoi(op)<0))
              throw op;
            else
              break;
          }
          catch(string p)
          {
            cout<<"Eroare la introducerea valorii pentru optiune, aceasta trebuie sa fie un numar natural.\n";
            cout<<'\n'<<"Optiunea dvs. : ";
            getline(cin, op);
          }
        }
        option=stoi(op);
        cout<<endl;

        switch(option)
        {
            case 0:
            {
                cout<<"\nTerminare program...\n\n";
                break;
            }
            case 1:
            {

                cout<<"Introduceti numarul de locuinte pe care vreti sa-l memorati: ";
                string nr;
                getline(cin, nr);
                while(true)
                {
                  try
                  {
                    for(j=0; j<nr.size(); j++)
                      if(!isdigit(nr[j]))
                        break;
                    if(j!=nr.size()||(j==nr.size()&&stoi(nr)<0))
                      throw nr;
                    else
                      break;
                  }
                  catch(string p)
                  {
                    cout<<"Eroare la introducerea valorii pentru numarul de locuinte, aceasta trebuie sa fie un numar natural.\n";
                    cout<<"Introduceti numarul de locuinte pe care vreti sa-l memorati: ";
                    getline(cin, nr);
                  }
                }
                n=stoi(nr);

                int i;
                locuinta *l;
                string s;
                for(i=1; i<=n; i++)
                {
                    cout<<'\n';
                    cout<<"Introduceti tipul locuintei(apartament/casa): ";
                    getline(cin, s);
                    while(true)
                    {
                      try
                      {
                          if(s=="apartament")
                          {
                              //cin.get();
                              l=new apartament();
                              cout<<"Pentru locuinta citita cu numarul "<<i<<" de tip apartament: "<<'\n';
                              cin>>static_cast<apartament&>(*(l));
                              proprietati.insert(make_pair(&*l, s));
                              break;
                          }
                          else
                          {
                              if(s=="casa")
                              {
                                  //cin.get();
                                  l=new casa();
                                  cout<<"Pentru locuinta citita cu numarul "<<i<<" de tipul casa:" <<'\n';
                                  cin>>static_cast<casa&>(*(l));
                                  proprietati.insert(make_pair(&*l, s));
                                  break;
                              }
                              else
                                  throw s;

                        }
                      }
                      catch(string sir)
                      {
                          cout<<"Eroare la alegerea tipului de locuinta, este necesar sa introduceti unul dintre cuvintele 'apartament' si 'casa'.\n";
                          cout<<"Introduceti tipul locuintei(apartament/casa): ";
                          getline(cin, s);
                      }
                    }
                }
                cout<<'\n';
                break;
            }

            case 2:
            {
                set<pair<locuinta*, string>>::iterator i;
                for(i=proprietati.begin(); i!=proprietati.end(); ++i)
                {
                    cout<<(*i).second<<":"<<'\n';
                    cout<<*((*i).first)<<'\n'<<'\n';
                }
                break;
            }

            case 3:
            {
                Gestiune <apartament> ap;
                cin>>ap;
                cout<<ap;
                break;
            }

            case 4:
            {
                Gestiune <casa> ca;
                cin>>ca;
                cout<<ca;
                break;
            }

            case 5:
            {
                string s;
                float profit=0;
                cout<<"Introduceti tipul de locuinta (apartament/casa): ";
                getline(cin, s);
                while(true)
                {
                  try
                  {
                    if(s=="apartament")
                    {
                        apartament *ap;
                        set<pair<locuinta*, string>>::iterator i;
                        for(i=proprietati.begin(); i!=proprietati.end(); ++i)
                        {
                            if((*i).second==s)
                             {
                                 ap=dynamic_cast<apartament*>((*i).first);
                                 profit+=ap->pret();
                             }
                        }
                        cout<<"Profitul generat de toate locuintele de tip apartament este: "<<profit<<'\n';
                        break;
                    }
                    else
                    {
                        if(s=="casa")
                        {
                            casa *ca;
                            set<pair<locuinta*, string>>::iterator i;
                            for(i=proprietati.begin(); i!=proprietati.end(); ++i)
                            {
                                if((*i).second==s)
                                {
                                     ca=dynamic_cast<casa*>((*i).first);
                                     profit+=ca->pret();
                                }
                            }
                            cout<<"Profitul generat de toate locuintele de tip casa este: "<<profit<<'\n';
                            break;
                        }
                        else
                            throw s;
                    }
                  }
                  catch(string sir)
                  {
                      cout<<"Eroare la alegerea tipului de locuinta, este necesar sa introduceti unul dintre cuvintele 'apartament' si 'casa'.\n";
                      cout<<"Introduceti tipul locuintei(apartament/casa): ";
                    getline(cin, s);
                  }
                }
                break;
            }

            case 6:
            {
                proprietati.clear();
                cout<<"Cele "<<n<<"locuinte citite anterior au fost sterse din memorie.\n\n";
                break;
            }

            default:
            {
                cout<<"Comanda inexistenta"<<'\n';
                break;
            }
        }

        system("pause");
        system("cls");
    }
    while(option!=0);
}


///----------------------------------------------------


int main ()
{
    menu();
  return 0;
}


///id-ul unui obiect nu este neaparat unic
