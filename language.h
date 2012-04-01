#include <iostream>
#include "subject_area.h"
#include <stack>
#include "math.h"

using namespace std;

class variable
{
    public:
    int k;
    set_int m;
    bool is_int;
    friend istream&operator>>(istream&in,variable&s);
    friend ostream&operator<<(ostream&out,variable s);
   // friend ifsteram&operator>>(ifstream&in,variable&s);
};

ostream&operator<<(ostream&out,variable s)
{
    if (s.is_int)
        out<<s.k;
    else
        out<<s.m;
        out<<endl;
    return out;
}

/*friend ifsteram&operator>>(ifstream&in,variable&s)
{
    char c;
    in>>c;
    if (c=='[')
    {
        in.putback(c);
        in>>s.m;
        s.is_int=false;
    }
    else
    {
        in.putback(c);
        in>>s.k;
        s.is_int=true;
    }
    return in;
}*/

istream&operator>>(istream&in,variable&s)
{

    char c;
    in>>c;
    if (c=='[')
    {
        in.putback(c);
        in>>s.m;
        s.is_int=false;
    }
    else
    if (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
    {
        in.putback(c);
        in>>s.k;
        s.is_int=true;
    }
    else
    throw set_int::xError();
    return in;
}

class operation
{
    public:
    string s;//название
    int i;//число операндов
    int t;//тип возвращаемого значения 0

 virtual void ret() {cout<<"oper";}
 //void add_st(variable k) {st_stack.push(k);}
};

stack<variable> st_stack;//стек
variable var_array[200] ;//массив переменных
operation **op_array=new operation*[200];//массив команд
int num_command=0;//номер исполняемой команды
int count_command=0;//число команд

void start()
{
    while (num_command<count_command)
    {
        //cout<<op_array[num_command]->s<<endl;
        op_array[num_command]->ret();
    }
}



class o_read:public operation
{

     public:
    o_read() {i=0;s="?";}
    ~o_read() {}
    void ret() {variable k;cin>>k;st_stack.push(k);num_command++;}
};

class o_write:public operation
{
    public:
    o_write() {i=0;s="!";}
    ~o_write() {}
    void ret()
    {
        if (st_stack.size()!=0){
        cout<<st_stack.top();
                st_stack.pop();
        }
        num_command++;
    }

};

class o_sum:public operation
{
    public:
    o_sum()  {s="+";}
    ~o_sum() {}
    void ret() {
    variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    //cout<<"a: "<<a<<"b: "<<b<<endl;
    variable c;
    if (a.is_int)
        {if (b.is_int)
            {c.k=a.k+b.k;c.is_int=true;}
        else
            {c.m=b.m+a.k;c.is_int=false;}}
    else
        {if (b.is_int)
            {c.m=a.m+b.k;c.is_int=false;}
            else
            {c.m=a.m+b.m;c.is_int=false;}
            }
    st_stack.push(c);
    num_command++;
    }

};

class o_mul:public operation
{
    public:
    o_mul() {s="*";}
    ~o_mul() {}
    void ret()
    {
               variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
   // cout<<"a: "<<a<<"b: "<<b<<endl;
    variable c;
    if (a.is_int&&b.is_int)
        {c.k=a.k*b.k;c.is_int=true;}
    else
    if ((!a.is_int)&&(!b.is_int))
        {c.m=a.m*b.m;c.is_int=false;}
    else return;

    st_stack.push(c);
    num_command++;
    }

};

class in_var:public operation
{
    public:
    int n;
    in_var(int n1) {n=n1;s=">x";}
    ~in_var() {}
    void ret() {var_array[n]=st_stack.top();st_stack.pop();num_command++;}

};

class out_var:public operation
{
    public:
    int n;
    out_var(int n1) {n=n1;s="<x";}
    ~out_var() {}
    void ret() {st_stack.push(var_array[n]);num_command++;}

};



class jump:public operation
{
    public:
    int n;
    jump(int n1) {n=n1;s="jump";}
    ~jump() {}
    void ret() {num_command=n;}
};

class ij:public operation
{
    public:
    int n;
    ij(int n1) {n=n1;s="ij";}
    ~ij() {}
    void ret()
    {
        if (st_stack.size()!=0)
            if (st_stack.top().is_int&&st_stack.top().k!=0)
                {num_command=n;st_stack.pop();}
            else
            num_command++;
    }

};

class well:public operation
{
    public:
    well() {s="==";}
    ~well() {}
    void ret()
    {
        variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    variable c;c.is_int=true;
    if ((a.is_int&&b.is_int&&b.k==a.k)||((!a.is_int)&&(!b.is_int)&&b.m==a.m))
       { c.k=1;}
        else
        {c.k=0;}
        st_stack.push(c);
        num_command++;
    }

};

class o_mod:public operation
{
    public:
    o_mod() {s="/";}
    ~o_mod() {}
    void ret()
    {
     variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    variable c;
    if (a.is_int&&b.is_int)
    {
        c.k=b.k%a.k;
        c.is_int=true;
    }
    else return ;
    st_stack.push(c);
    num_command++;
    }
};

class o_div:public operation
{
    public:
    o_div() {s="/";}
    ~o_div() {}
    void ret()
    {
     variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    variable c;
    if (a.is_int&&b.is_int)
    {
        c.k=b.k/a.k;
        c.is_int=true;
    }
    else
    if ((!a.is_int)&&(!b.is_int))
    {
        c.m=b.m/a.m;
        c.is_int=false;
    }
    else return ;
    st_stack.push(c);
    num_command++;
    }
};

class o_sub:public operation
{
    public:
    o_sub() {s="-";}
    ~o_sub() {}
    void ret()
    {
     variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    //cout<<"a: "<<a<<"b: "<<b<<endl;
    variable c;
    if (a.is_int&&b.is_int)
    {
        c.k=b.k-a.k;
        c.is_int=true;
    }
    else
    if ((!a.is_int)&&(!b.is_int))
    {
        c.m=b.m-a.m;
        c.is_int=false;
    }
    else return ;
    st_stack.push(c);
    num_command++;
    }
};

class o_less:public operation
{
    public:
    o_less() {s="<";}
    ~o_less() {}
    void ret()
    {
        variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    variable c;     c.is_int=true;
    if (a.is_int&&b.is_int&&b.k<a.k)
       { c.k=1;}
        else
        {c.k=0;}
        st_stack.push(c);
        num_command++;
    }

};

class more:public operation
{
    public:
    more() {s=">";}
    ~more() {}
    void ret()
    {
        variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    variable c;c.is_int=true;
    if (a.is_int&&b.is_int&&b.k>a.k)
       { c.k=1;}
        else
        {c.k=0;}
        st_stack.push(c);
        num_command++;
    }

};

class unwell:public operation
{
    public:
    unwell() {s="!=";}
    ~unwell() {}
    void ret()
    {
        variable a,b;
    if (st_stack.size()!=0){
        a=st_stack.top();
        st_stack.pop();
    }
    else return;
    if (st_stack.size()!=0){
        b=st_stack.top();
        st_stack.pop();
    }
    else return;
    variable c;c.is_int=true;
    if ((a.is_int&&b.is_int&&b.k==a.k)||((!a.is_int)&&(!b.is_int)&&b.m==a.m))
       { c.k=0;}
        else
        {c.k=1;}
        st_stack.push(c);
        num_command++;
    }

};

class to_stack:public operation
{
    public:
    variable var;
    to_stack(variable var1) {var=var1;}
    ~to_stack() {}
    void ret() {st_stack.push(var); num_command++;}

};



void input()
{
    cout<<"Введите программу в ОПЗ: "<<endl;
int i=0;
    char c;
    cin>>c;
    while (c!='.')
    {
        if (c=='?') {op_array[i]=new o_read;i++;}
        if (c=='+') {op_array[i]=new o_sum;i++;}
        if (c=='*') {op_array[i]=new o_mul;i++;}
        if (c=='-') {op_array[i]=new o_sub;i++;}
        if (c=='/') {op_array[i]=new o_div;i++;}
        if (c=='%') {op_array[i]=new o_mod;i++;}
        if (c=='['||c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
            {
                variable a;
                cin.putback(c);
                cin>>a;
                op_array[i]=new to_stack(a);
                i++;
            }
        if (c=='!')
        {   char c1;
            cin>>c1;
            if (c1=='=') {op_array[i]=new unwell;i++;}
            else
            {op_array[i]=new o_write;i++;cin.putback(c1);}

        }
        if (c=='=')
        {
                char c1;
                cin>>c1;
                if (c1!='='){cin.putback(c1);/* return;*/}
                else
                    {op_array[i]=new well;
                i++;}
        }
        if (c=='i')
        {
            char c1;
            int k1;
            cin>>c1;
            if (c1!='j'){cin.putback(c1);}
            else{cin>>k1;
            op_array[i]=new ij(k1);
            i++;}
        }
        if (c=='j')
        {
            char c1,c2,c3;
            cin>>c1;
            if (c1!='u'){cin.putback(c1); }
            cin>>c2;
            if (c2!='m'){cin.putback(c1);cin.putback(c2);}
            cin>>c3;
            if (c3!='p'){cin.putback(c1);cin.putback(c2);cin.putback(c3);}
            int k1;
            cin>>k1;
            op_array[i]=new jump(k1);
            i++;
        }
        if (c=='>')
        {
            char c1;
            cin>>c1;
            if (c1=='x') {int k1;cin>>k1;op_array[i]=new in_var(k1);}
            else
            {
                cin.putback(c1);
                op_array[i]=new more;
            }
            i++;
        }
        if (c=='<')
        {
            char c1;
            cin>>c1;
            if (c1=='x') {int k1;cin>>k1;op_array[i]=new out_var(k1);}
            else
            {
                cin.putback(c1);
                op_array[i]=new o_less;
            }
            i++;
        }


        cin>>c;
    }
    count_command=i;
}


