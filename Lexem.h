#include "language.h"
#include <string>
#include <fstream>

class lexems//анализатор
{private:
   class lex//лексема
    {
        public:
        lex() {}
        lex(int id1) {id=id1;}
        lex(int id1,variable a1) {id=id1;a=a1;}
        lex(int id1,int k1) {id=id1;k=k1;}
        int id;
        int k;
        variable a;

    };
    int i, n;
    lex * a_lex;//массив лексем
    bool true_program;//верна ли программа
    stack<variable> st_stack;//стек
    variable var_array[999] ;//массив переменных
    public:

    lexems() {i=0;n=0;a_lex=new lex[200];true_program=true;}
    lexems(int l) {i=0;n=0;a_lex=new lex[l];true_program=true;}
    ~lexems() {delete [] a_lex;}

    void read(char fname[])
    {

    cin>>fname;
    ifstream fin(fname);

    char c;
    //cin>>c;
    fin>>c;
    while (c!='.'&&!fin.eof())
    {
        if (c=='?') {lex l(1);a_lex[i]=l; i++;}else
        if (c=='+') {lex l(2);a_lex[i]=l; i++;}else
        if (c=='*') {lex l(3);a_lex[i]=l; i++;}else
        if (c=='-') {lex l(4);a_lex[i]=l; i++;}else
        if (c=='/') {lex l(5);a_lex[i]=l; i++;}else
        if (c=='%') {lex l(6);a_lex[i]=l; i++;}else
        if (c=='['||c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
            {
                bool t_p=true;
                variable a;
                fin.putback(c);
                try
                {
                fin>>a;
                }
                catch (set_int::xError)
                {
                    cout<<"error"<<endl;
                    lex l(17,c);true_program=false;a_lex[i]=l;i++;
                    t_p=false;
                }
                if (t_p){
                lex l(7,a);a_lex[i]=l;
                i++;}
            }else
        if (c=='!')
        {   char c1;
            fin>>c1;
            if (c1=='=') {lex l(8);a_lex[i]=l; i++;}
            else
            {lex l(9);a_lex[i]=l;  i++; fin.putback(c1);}

        }else
        if (c=='=')
        {
                char c1;
                fin>>c1;
            //cout<<"11111111111"<<endl;
                if (c1!='='){fin.putback(c1);lex l(17,i);true_program=false;a_lex[i]=l;i++;/* return;*/}
                else
                    {lex l(10);a_lex[i]=l;
                i++;}
        }else
        if (c=='i')
        {
            char c1;
            int k1;
            fin>>c1;
            if (c1!='j'){fin.putback(c1);}
            else{fin>>k1;
            lex l(11,k1);a_lex[i]=l;
            i++;}
        }else
        if (c=='a')
        {
            char c1;
            fin>>c1;
            if (c1=='c') {int k1;fin>>k1;lex l(18,k1);a_lex[i]=l;}else
            if (c1=='f') {lex l(20);a_lex[i]=l;}else
            {
                fin.putback(c1);
              lex l(17,c);true_program=false;a_lex[i]=l;i++;
            }
        i++;
        }else
        if (c=='m')
        {
            char c1;
            fin>>c1;
            if (c1=='c') {int k1;fin>>k1;lex l(19,k1);a_lex[i]=l;}else
            {
                fin.putback(c1);
              lex l(17,c);true_program=false;a_lex[i]=l;i++;
            }
        i++;
        }else

        if (c=='j')
        {
           char c1,c2,c3;
            fin>>c1>>c2>>c3;
            if (c1=='u'&&c2=='m'&&c3=='p')
            {
                fin>>c1;
                if (c1=='0'||c1=='1'||c1=='2'||c1=='3'||c1=='4'||c1=='5'||c1=='6'||c1=='7'||c1=='8'||c1=='9')
                {
                fin.putback(c1);
                int k1=0;
                fin>>k1;
                lex l(12,k1);a_lex[i]=l;
                }
                else
                {lex l(17,c);true_program=false;a_lex[i]=l;}                                                 //Сделать проще!
            }
            else
            {lex l(17,c);true_program=false;a_lex[i]=l;}
            i++;
        }else
        if (c=='>')
        {
            char c1;
            fin>>c1;
            if (c1=='x') {int k1;fin>>k1;lex l(13,k1);a_lex[i]=l;  }
            else
            {
                fin.putback(c1);
                lex l(14);a_lex[i]=l;
            }
            i++;
        }else
        if (c=='<')
        {
            char c1;
            fin>>c1;
            if (c1=='x') {int k1;fin>>k1;lex l(15,k1);a_lex[i]=l;  }
            else
            {
                fin.putback(c1);
                lex l(16);a_lex[i]=l;
            }
            i++;
        }
        else
        {
            lex l(17,c);true_program=false;a_lex[i]=l;i++;

        }

        fin>>c;
    }
    n=i;
    fin.close();
}

    void write()
    {
        cout<<"Список лексем:"<<endl;
        int j;
        for (j=0;j<n;j++)
        {
            if (a_lex[j].id==1) cout<<"lex_read"<<endl;else
            if (a_lex[j].id==2) cout<<"lex_sum"<<endl;else
            if (a_lex[j].id==3) cout<<"lex_mul"<<endl;else
            if (a_lex[j].id==4) cout<<"lex_sub"<<endl;else
            if (a_lex[j].id==5) cout<<"lex_div"<<endl;else
            if (a_lex[j].id==6) cout<<"lex_mod"<<endl;else
            if (a_lex[j].id==7) cout<<"lex_const_"<<a_lex[j].a<<endl;else
            if (a_lex[j].id==8) cout<<"lex_unwell"<<endl;else
            if (a_lex[j].id==9) cout<<"lex_write"<<endl;else
            if (a_lex[j].id==10) cout<<"lex_well"<<endl;else
            if (a_lex[j].id==11) cout<<"lex_ij_"<<a_lex[j].k<<endl;else
            if (a_lex[j].id==12) cout<<"lex_jump_"<<a_lex[j].k<<endl;else
            if (a_lex[j].id==13) cout<<"lex_in_var_"<<a_lex[j].k<<endl;else
            if (a_lex[j].id==14) cout<<"lex_more"<<endl;else
            if (a_lex[j].id==15) cout<<"lex_out_var_"<<a_lex[j].k<<endl;else
            if (a_lex[j].id==16) cout<<"lex_less"<<endl;else
            if (a_lex[j].id==17) {char c=a_lex[j].k;cout<<"lex_error_"<<c<<endl;}else
            if (a_lex[j].id==18) cout<<"lex_ac_"<<a_lex[j].k<<endl;else
            if (a_lex[j].id==19) cout<<"lex_mc_"<<a_lex[j].k<<endl;else
            if (a_lex[j].id==20) cout<<"lex_af"<<endl;
        }

    }

    void run()//интерпретатор
    {
        int j=0;
        cout<<"Выполнение программы:"<<endl;
        if (!true_program)
        {
            char c;
            cout<<"В программе содержаться ошибки, продолжить? y/n:"<<endl;
            cin>>c;
            if (c!='Y'&&c!='y') return;
        }
        while (j<n)
        {
            if (a_lex[j].id==1) {variable k;cout<<"Введите переменную:"<<endl;
                    try {cin>>k;} catch (set_int::xError)
                    {
                        cout<<"Ошибка ввода переменной"<<endl;
                        return;
                    }

                    st_stack.push(k);j++;}else
             if (a_lex[j].id==20)
            {
                variable a;
                a=st_stack.top();
                st_stack.pop();
                if (!a.is_int)
                    {
                        a.m.adding_the_first_missing();
                        st_stack.push(a);
                    }
                 j++;
            }else
            if (a_lex[j].id==19)
            {
                variable a;
                a=st_stack.top();
                st_stack.pop();
                if (!a.is_int)
                    {
                        variable c;
                        c.is_int=true;
                        c.k=a.m.multiplicity(a_lex[j].k);
                        st_stack.push(c);
                    }
                 j++;
            }else
            if (a_lex[j].id==18)
            {
                variable a;
                a=st_stack.top();
                st_stack.pop();
                if (!a.is_int)
                    if (a.m.size()>a_lex[j].k&&a_lex[j].k>=0)
                    {
                        variable c;
                        c.is_int=true;
                        c.k=a.m[a_lex[j].k];
                        st_stack.push(c);
                    }
                 j++;
            }else

            if (a_lex[j].id==2) { variable a,b;
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
    j++;
    }else
            if (a_lex[j].id==3) {
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
    j++;
    }
else
            if (a_lex[j].id==4) {
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
    j++;
    }else
            if (a_lex[j].id==5) {
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
    j++;
    }else
            if (a_lex[j].id==6) {
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
    j++;
    }else
            if (a_lex[j].id==7) {st_stack.push(a_lex[j].a); j++;}else
            if (a_lex[j].id==8)  {
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
        j++;
    }
else
            if (a_lex[j].id==9)  {
                if (st_stack.size()!=0){
                    cout<<st_stack.top();
                    st_stack.pop();
                        }
                j++;
                }else
            if (a_lex[j].id==10) {
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
        j++;
    }
else
            if (a_lex[j].id==11) {
        if (st_stack.size()!=0)
            if (st_stack.top().is_int&&st_stack.top().k!=0)
                {j=a_lex[j].k;st_stack.pop();}
            else
            j++;
    }else
            if (a_lex[j].id==12) {j=a_lex[j].k;}else
            if (a_lex[j].id==13) {var_array[a_lex[j].k]=st_stack.top();st_stack.pop();j++;}else
            if (a_lex[j].id==14)  {
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
        j++;
    }
else
            if (a_lex[j].id==15) {st_stack.push(var_array[a_lex[j].k]);j++;}else
            if (a_lex[j].id==16) {
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
        j++;
    }else
            if (a_lex[j].id==17) {char c=a_lex[j].k;cout<<"lex_error_"<<c<<endl;j++;}

        }

    }

};

