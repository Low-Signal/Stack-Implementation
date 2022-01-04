#include <math.h>
#include <iostream>

#include "string.h"
#include "opnum.h"
#include "stack.h"
#include <vector>

using namespace std;
using namespace cop4530;

int main(int argc, char **argv)
{
   
   int retval = SYM_NULL;
   set_input(argc, argv);

    do {
       char * opnum = get_opnum(&retval);
       if (retval) {
          switch (retval)
          {
             case SYM_NAME: cout<<"ID: "; cout <<opnum<<endl; break;
             case SYM_INTEG: cout<<"Integer: ";cout <<opnum<<endl; break;
             case SYM_FLOAT: cout<<"Float: "; cout <<opnum<<endl; break;
             case SYM_ADD: cout<<"Op: "; cout <<opnum<<endl; break;
             case SYM_SUB: cout<<"Op: "; cout <<opnum<<endl; break;
             case SYM_MUL: cout<<"Op: "; cout <<opnum<<endl; break;
             case SYM_DIV: cout<<"Op: "; cout <<opnum<<endl; break;
             case SYM_OPEN: cout<<"left Par: "; cout <<opnum<<endl; break;
             case SYM_CLOSE: cout<<"Right Par: "; cout <<opnum<<endl; break;
             case SYM_INVAL: cout<<"Invalid: "; cout <<opnum<<endl; break;
             case SYM_NEWLINE: break;
             default: break; 
          }
       }
    } while (retval > SYM_NULL);
}
