 //Program to conncect socket and esablish concurrency
#include "../include/func.h"

int main(){
      	 Server s;			//creating a object server
	 s.shmcreate();      		//calling the  function to create shared memory
	 s.shmattach();			//calling the function to attach shared memory
	 s.createSocket();		//calling the function to create socket
	 s.concurrency();		//calling the function to make socket work in concurrency
	 s.shmdestroy();		//calling the function to destroy the shared memory
}
