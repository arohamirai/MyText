#include <iostream>
#include <stdio.h>

using namespace std; 
extern "C"  int add(int ,int );
int main(int arg,char **argv)
{

printf("add a and b=%d\n",add(3,4));
return 0;

}
