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
        lex(int id1,string a1) {id=id1;s=a1;}
        lex(int id1,int k1) {id=id1;k=k1;}
        int id;
        int k;
        variable a;
        string s;
    };

    int i, n;
    string sid;
    lex * a_lex;//массив лексем
    bool true_program,rem;//верна ли программа
public:
    lexems() {i=0;n=0;a_lex=new lex[200];true_program=true;rem=false;}
    lexems(int l) {i=0;n=0;a_lex=new lex[l];true_program=true;rem=false;}
    ~lexems() {delete [] a_lex;}

    void add_lex(int j)
    {
        if (!sid.empty())
      {
        add_word_lex();
      }
      lex l(j);a_lex[i]=l; i++;
    }

    void add_lex_t(int j)
    {
      lex l(j);a_lex[i]=l; i++;sid.clear();
    }

    void add_word_lex()
    {
        if (sid=="mc") add_lex_t(14);else
        if (sid=="af") add_lex_t(15);else
        if (sid=="ac") add_lex_t(16);else
        if (sid=="int") add_lex_t(17);else
        if (sid=="set_int") add_lex_t(18);else
        if (sid=="set") add_lex_t(19);else
        if (sid=="cout") add_lex_t(20);else
        if (sid=="cin") add_lex_t(21);else
        if (sid=="jump") add_lex_t(25);else
        if (sid=="while") add_lex_t(26);else
        if (sid=="for") add_lex_t(27);else
        if (sid=="to") add_lex_t(28);else
        if (sid=="do") add_lex_t(29);else
        if (sid=="begin") add_lex_t(32);else
        if (sid=="end") add_lex_t(33);else
        if (sid=="if") add_lex_t(37);else
        if (sid=="else") add_lex_t(38);else
        if (sid=="rem") {rem=true;sid.clear();}else
        {
            lex l(34,sid);a_lex[i]=l; i++;sid.clear();
        }
    }

    void read(char fname[])
    {
    ifstream fin(fname);
    char c;sid.clear();fin>>c;bool want_c=true;rem=false;
    while (!fin.eof())
    {
        want_c=true;
        while (rem&&c!='\n')
            fin.get(c);
        rem=false;
        if (c=='*') {add_lex(3);}else
        if (c=='-') {add_lex(2);}else
        if (c=='+') {add_lex(1);}else
        if (c=='/') {add_lex(4);}else
        if (c=='%') {add_lex(5);}else
        if (c==';') {add_lex(6);}else
        if (c==',') {add_lex(7);}else
        if (c=='<')
        {char c1;fin.get(c1);
            if (c1=='<')
                {add_lex(23);}
                else {want_c=false;c=c1;add_lex(8);}
        }else
        if (c=='>')
        {char c1;fin.get(c1);
            if (c1=='>')
                {add_lex(22);}
                else {want_c=false;c=c1;add_lex(9);}
        }else
        if (c=='=')
        {char c1;fin.get(c1);
            if (c1=='=')
                {add_lex(10);}
                else {want_c=false;c=c1;add_lex(30);}
        }else
        if (c=='!')
        {char c1;fin.get(c1);
            if (c1=='=')
                {add_lex(11);}
                else {want_c=false;c=c1;sid+="!";}
        }else
        if (c=='(') {add_lex(12);}else
        if (c==')') {add_lex(13);}else
        if ((c=='['||c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')&&sid.empty())
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
                    lex l(36,c);true_program=false;a_lex[i]=l;i++;
                    t_p=false;
                }
                if (t_p){
                lex l(35,a);a_lex[i]=l;
                i++;
                }
            }else
        if (isspace(c)&&!sid.empty())
        {
            add_word_lex();
        }
        else
        if (!isspace(c))
        sid+=c;

        if (want_c)
        fin.get(c);
    }
     if (!sid.empty())
      {
        add_word_lex();
      }
    n=i;
    fin.close();
}

void write()
    {
        cout<<"Lexem list:"<<endl;
        int j;
        for (j=0;j<n;j++)
        {
            if (a_lex[j].id==1) cout<<"lex_sum"<<endl;else
            if (a_lex[j].id==2) cout<<"lex_sub"<<endl;else
            if (a_lex[j].id==3) cout<<"lex_mul"<<endl;else
            if (a_lex[j].id==4) cout<<"lex_div"<<endl;else
            if (a_lex[j].id==5) cout<<"lex_mod"<<endl;else
            if (a_lex[j].id==6) cout<<"lex_semicolon"<<endl;else
            if (a_lex[j].id==7) cout<<"lex_comma"<<endl;else
            if (a_lex[j].id==8) cout<<"lex_less"<<endl;else
            if (a_lex[j].id==9) cout<<"lex_more"<<endl;else
            if (a_lex[j].id==10) cout<<"lex_well"<<endl;else
            if (a_lex[j].id==11) cout<<"lex_unmell"<<endl;else
            if (a_lex[j].id==12) cout<<"lex_open_braket"<<endl;else
            if (a_lex[j].id==13) cout<<"lex_close_braket"<<endl;else
            if (a_lex[j].id==14) cout<<"lex_multiplucity"<<endl;else
            if (a_lex[j].id==15) cout<<"lex_add_first"<<endl;else
            if (a_lex[j].id==16) cout<<"lex_access"<<endl;else
            if (a_lex[j].id==17) cout<<"lex_int"<<endl;else
            if (a_lex[j].id==18) cout<<"lex_set_int"<<endl;else
            if (a_lex[j].id==19) cout<<"lex_set"<<endl;else
            if (a_lex[j].id==20) cout<<"lex_cout"<<endl;else
            if (a_lex[j].id==21) cout<<"lex_cin"<<endl;else
            if (a_lex[j].id==22) cout<<"lex_double_more"<<endl;else
            if (a_lex[j].id==23) cout<<"lex_double_less"<<endl;else
            if (a_lex[j].id==24) cout<<"lex_colon"<<endl;else
            if (a_lex[j].id==25) cout<<"lex_jump"<<endl;else
            if (a_lex[j].id==26) cout<<"lex_while"<<endl;else
            if (a_lex[j].id==27) cout<<"lex_for"<<endl;else
            if (a_lex[j].id==28) cout<<"lex_to"<<endl;else
            if (a_lex[j].id==29) cout<<"lex_do"<<endl;else
            if (a_lex[j].id==30) cout<<"lex_assignment"<<endl;else
            if (a_lex[j].id==32) cout<<"lex_begin"<<endl;else
            if (a_lex[j].id==33) cout<<"lex_end"<<endl;else
            if (a_lex[j].id==34) cout<<"lex_id_<<"<<a_lex[j].s<<">>"<<endl;else
            if (a_lex[j].id==35) cout<<"lex_const_"<<a_lex[j].a<<endl;else
            if (a_lex[j].id==36) cout<<"lex_error"<<endl;else

            if (a_lex[j].id==37) cout<<"lex_if"<<endl;else
            if (a_lex[j].id==38) cout<<"lex_else"<<endl;

        }
    }
};
