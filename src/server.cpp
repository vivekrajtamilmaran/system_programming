 //Program to conncect socket and esablish concurrency
#include "/home/cguser11/may17/include/func.h"

int main(){
      	 Server s;
         s.shmcreate();
	 s.shmattach();
	 s.func();
	 s.concurrency();
	 s.shmdestroy();
}
