#include <iostream>
//#include "subject_area.h"
#include <stack>
//#include "language.h"
#include "lexem-high.h"

using namespace std;

int main()
{
    cout<<"Enter file name "<<endl;
    char fname[80];
    cin>>fname;

    lexems l(300);
    l.read(fname);
    //l.run();
    l.write();

    return 0;
}
