#include <iostream>
#include "math.h"

using namespace std;

class set_int
{
private:
	int n;//ВХЯКН ЩКЕЛЕМРНБ
	int * a;//ЛЮЯЯХБ
public:
    class xError {};
	set_int(){n=0;a=0;}
	set_int(int n1) {n=n1;a=new int[n];}
	set_int(const set_int & s)//конструктор копирования
            {
                n=s.n;
                a=new int[n];
                for (int i=0;i<n;i++)
                    a[i]=s.a[i];
            }
	~set_int(){delete [] a;}
	set_int& operator=(const set_int & s)//конструктор копирования
            {
                this->~set_int();
                new (this) set_int (s);
                return *this;
            }
	set_int operator+(const set_int & s) const//объедениние
        {
                 /* Объединением мультимножеств А и В называется мультимножество, со-
стоящее из всех элементов, которые присутствуют хотя бы в одном из муль-
тимножеств, и кратность каждого элемента равна максимальной кратности со-
ответствующих элементов в объединяемых мультимножествах*/

            set_int * k=new set_int(0);
            for (int i=0;i<n;i++)
            {
                //cout<<"i: "<<i<<" multiplicity(a[i]): "<<multiplicity(a[i])<<" s.multiplicity(a[i]): "<<s.multiplicity(a[i])<<" a[i]: "<<a[i]<<endl;
                if (multiplicity(a[i])>=s.multiplicity(a[i]))
                    *k=*k+a[i];
            }
            for (int i=0;i<s.n;i++)
            {
               // cout<<"i: "<<i<<" s.multiplicity(s.a[i]): "<<s.multiplicity(s.a[i])<<" multiplicity(s.a[i]): "<<multiplicity(s.a[i])<<" s.a[i]: "<<s.a[i]<<endl;
                if (s.multiplicity(s.a[i])>multiplicity(s.a[i]))
                *k=*k+s.a[i];
            }


            return *k;
            }
    set_int operator+(const int s) const
    {
            //cout<<"add "<<s<<endl;
           // set_int * k=new set_int(n+1);
           set_int k(n+1);
            for (int i=0;i<n;i++)
                k.a[i]=a[i];
            k.a[n]=s;
            return k;
    }

	set_int operator-(const set_int & s) const//разность
	{
	    /*                      разностью мультимножеств A и B называется мульти-
множество, состоящее из всех элементов мультимножества A, кратность кото-
рых превышает кратность соответствующих элементов в мультимножестве B, и
кратность каждого элемента равна разности кратностей соответствующих эле-
ментов в вычитаемых мультимножествах*/

	    //set_int * s1 = new set_int(0);
	    set_int s1(0);
	    for (int i=0;i<n;i++)
            if (multiplicity(a[i])>s.multiplicity(a[i])&&s1.multiplicity(a[i])==0)
                for (int j=0;j<multiplicity(a[i])-s.multiplicity(a[i]);j++)
                    s1=s1+a[i];
	    return s1;
	}
	set_int operator*(const set_int & s) const//пересечение
	{
                 /*Пересечением мультимножеств A и B называется мультимножество, со-
стоящее из всех элементов, которые одновременно присутствуют в каждом из
мультимножеств, и кратность каждого элемента равна минимальной кратности
соответствующих элементов в пересекаемых мультимножествах*/

            //set_int * s1=new set_int;
            set_int s1;
            bool k=false;
            int mp;
            for (int i=0;i<n;i++)
            {
                k=false;
                for (int j=0;j<s.n;j++)
                {
                if (s.a[j]==a[i])
                    {k=true;break;}
                }
                if (k&&s1.multiplicity(a[i])==0)
                {
                    if (s.multiplicity(a[i])>multiplicity(a[i]))
                        mp=multiplicity(a[i]);
                    else
                        mp=s.multiplicity(a[i]);
                for (int j=0; j<mp;j++)
                s1=s1+a[i];
                }
            }

            return s1;
            }

	set_int operator/(const set_int & s) const//симметрическая разность
	{
	          /*Симметрической разностью мультимножеств А и В называется мульти-
множество, состоящее из всех элементов обоих мультимножеств, кратности ко-
торых различны, и кратность каждого элемента равна модулю разности кратно-
стей соответствующих элементов в вычитаемых мультимножествах*/
            //set_int * s1=new  set_int(0);
            set_int s1(0);
            for (int i=0;i<n;i++)
                if (s.multiplicity(a[i])!=multiplicity(a[i])&&s1.multiplicity(a[i])==0)
                    for (int j=0;j*j<(s.multiplicity(a[i])-multiplicity(a[i]))*(s.multiplicity(a[i])-multiplicity(a[i]));j++)
                        s1=s1+a[i];
            for (int i=0;i<s.n;i++)
                if (s.multiplicity(s.a[i])!=multiplicity(s.a[i])&&s1.multiplicity(s.a[i])==0)
                    for (int j=0;j*j<(s.multiplicity(s.a[i])-multiplicity(s.a[i]))*(s.multiplicity(s.a[i])-multiplicity(s.a[i]));j++)
                        s1=s1+s.a[i];
            return s1;



	}

	int& operator[](int i)//доступ
	{
	    if (i<0||i>=n) throw "err";
	    return a[i];
	}
	int multiplicity(int elem) const //кратность элемента
	{
	    int k=0;
	    for (int i=0;i<n;i++)
            if (a[i]==elem)
                k++;
        return k;
	}
	void adding_the_first_missing()//добавление первого отсутствующего
	{
	    int n=1;
	    while (multiplicity(n)!=0)
            n++;
        *this=*this+n;

	}
	bool operator==(const set_int & s) const//ЯПЮБbМЕМХЕ
	{
	    for (int i=0;i<n;i++)
            if (multiplicity(a[i])!=s.multiplicity(a[i])) {return false;}

	    for (int i=0;i<s.n;i++)
            if (multiplicity(s.a[i])!=s.multiplicity(s.a[i])) {return false;}
        return true;
	}
	bool operator!=(const set_int & s) const
	{
	    if (*this==s) return false;
	    else return true;

	}
	friend ostream & operator<<(ostream& out,const set_int & s);//БШБНД
	friend istream & operator>>(istream& in,set_int & s);//ББНД


	class set_int_it//ХРЕПЮРНП
{
private:
		set_int * p;//ЛСКЭРХЛМНФЕЯРБН
		int i;//МНЛЕП ЩКЕЛЕМРЮ Б ЛЮЯЯХБЕ
public:
		set_int_it() {i=0;p=0;}
		set_int_it(set_int & x,int i1) {if (x.n<i1||i1<0) throw "err";    p=&x;i=i1;}
		set_int_it(const set_int_it & s)
		{
		    i=s.i;
		    p=s.p;
		}
		~set_int_it() {}
		set_int_it& operator++()// префексный (выч. до присваивания)
		{
		    //if (i<p->n-1)
                i++;
            return *this;
		}

		set_int_it& operator++(int s)
		{
		    //if (i<p->n-1)
		    set_int_it k=*this;
                i++;
            return k;

		}

		set_int_it& operator--()
		{
		    //if (i>0)
                i--;
            return *this;
		}

		set_int_it& operator--(int s)
		{
		    //if (i<p->n-1)
		    set_int_it k=*this;
                i--;
            return k;

		}

		set_int_it operator+(int i1)
		{
		    if (i+i1<p->n)
                i+=i1;
		    return *this;
		}
        set_int_it operator-(int i1)
        {
            if (i-i1>=0)
                i-=i1;
            return *this;
        }
        set_int_it operator=(const set_int_it&s)
        {
                this->~set_int_it();
                new (this) set_int_it (s);
                return *this;
        }
		bool operator==(const set_int_it &s) const
		{
		    if (p!=s.p) return false;
		    if (i!=s.i) return false;
		    return true;
		}
		bool operator!=(const set_int_it &s) const
		{
		    if (*this==s) return false;
		    else return true;
		}
		bool operator>(const set_int_it &s) const
		{
		    if (p!=s.p) return false;
		    if (i>s.i) return true;
		    return false;
		}
        bool operator<(const set_int_it &s) const
        {
            if (p!=s.p) return false;
		    if (i<s.i) return true;
		    return false;
        }
		int& operator*() {return p->a[i];}
        int&operator[](int i1) {if (i1<0||i1>=p->n) throw "err";return p->a[i1];}
};

	set_int_it begin()
	{
    set_int_it * it=new set_int_it(*this,0);
	return *it;
	}
	set_int_it end()
	{
    set_int_it * it=new set_int_it(*this,n);
	return *it;
	}


	void push_back(int i)//ГЮОХЯЮРЭ Б ЙНМЕЖ
	{
	    *this=*this+i;

	}
	int pop_back()
	{
	    n--;
	    return a[n];
	}

	bool empty() const {if (n==0) return true; return false;}
	int size() const {return n;}
};

ostream & operator<<(ostream& out,const set_int & s)
{
    out<<"[[";
    if (s.n==0) {cout<<"]]"<<endl;return out;}
    for (int i=0;i<s.n-1;i++)
        out<<s.a[i]<<", ";
        cout<<s.a[s.n-1];
    out<<"]]";
return out;
}

	istream & operator>>(istream& in,set_int & s)
	{
	    char c1,c;
	    in>>c1>>c;
	    if (c1!='['||c!='[') {throw set_int::xError();return in;}

	    set_int s1(0);
	    in>>c;
        if (c!=']') in.putback(c);
	    //set_int s2(1);
	    int k;
	    while (c!=']')
	    {

	        in>>k;
	        s1=s1+k;
	        in>>c;
	        if (c!=']'&&c!=',') {throw set_int::xError();return in;}
	    }
	    in>>c;
	    if (c!=']') {throw set_int::xError();return in;}
	    s=s1;

    return in;
	}


