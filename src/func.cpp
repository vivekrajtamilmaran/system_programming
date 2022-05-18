//Function to create bind and listen socket
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define ADDRSERV "127.0.0.1"
#define MAX 1024
#define PORT 8011
using namespace std;
#include "/home/cguser11/may17/include/func.h"
#define DIR "../keyfile"
//Function to create shared memory
void Server::shmcreate(){
	 key=ftok(DIR,65);
         shm_id = shmget(key,1,0666 | IPC_CREAT);
         if(shm_id == -1 ){
                perror("ERROR creating shared memory ");
                exit(EXIT_FAILURE);
         }
}
//Function to attach shared memory
void Server::shmattach(){
	count = (short * ) shmat(shm_id,(void*)0,0);
	*count = 0;
}
//Function to destroy shared memory
void Server::shmdestroy(){
//	shmdt(count);
        shmctl(shm_id,IPC_RMID,0);
}
//Function to increment shared memory count 
void Server::shmWrite(){
	(*count)++;
}
//function to create socket
void Server::func(){               

        slen=sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);

        servaddr.sin_family = AF_INET; //To use Internet addressing family
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORT);


        sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0){
                fputs("Socket creation has not been done",stderr);
                exit(EXIT_FAILURE);
        }
        ret=bind(sockfd, (struct sockaddr *)&servaddr, slen);
        if(ret < 0){
                fputs("Binding has not been done",stderr);
                exit(EXIT_FAILURE);
        }
        ret=listen(sockfd, 5);
        if(ret< 0){
                fputs("Socket is not Listening",stderr);
                exit(EXIT_FAILURE);
 	}      
}
//function to send and receive message in concurrency
void Server::concurrency(){
	while(1){

                connectfd=accept(sockfd,(struct sockaddr*)&servaddr,(socklen_t *)&slen);
                if(connectfd < 0){
                        fputs("Conncetion is not established",stderr);
                        exit(EXIT_FAILURE);
                }
		Server::shmWrite();
                pid = fork();
                if(pid==0){
			write(1,"No. of connections :",20);
			std::stringstream ss;
			ss << *count;
			std::string c;
			ss >> c;
			cout << c << endl;
                        close(sockfd);
                        while(1){
                                mlen = read(connectfd,cmsg,MAX);
				if(strcmp(cmsg,"bye\n")==0 || strcmp(cmsg,"Bye\n")==0){
					close(connectfd);
					cout << "Client said bye and left" << endl;
					exit(0);
				}
                                if(mlen==0){
                                        close(connectfd);
                                        cout << "Client connection Closed "<< endl;
                                        break;
                                }
                                mlen=write(1,"The message received from client :",35);
                                mlen=write(1,cmsg,strlen(cmsg));
				if(strcmp(cmsg,"bye\n")== 0){
                                        close(connectfd);
                                        cout << "Client connection Closed "<< endl;
                                        break;
			
				}
                                mlen=write(1,"\n",1);
        			memset(cmsg,0,MAX);
                                mlen=write(1,"Enter the message from server to client :",42);
                                mlen=read(0,cmsg,MAX);
                                mlen=write(connectfd,cmsg,strlen(cmsg));
                                cout << "Message sent from the server " << endl;
                        }
                                close(connectfd);
                                exit(EXIT_SUCCESS);
                }
                close(connectfd);
        }
}

