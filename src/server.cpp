 //Program to conncect socket and esablish concurrency
#include "../include/func.h"

int main(){
      	 Server s;
         s.shmcreate();
	 s.shmattach();
	 s.createSocket();
	 s.concurrency();
	 s.shmdestroy();
}
