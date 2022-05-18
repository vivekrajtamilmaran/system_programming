//Header file for tcp socket server  
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
class Server{
		struct sockaddr_in servaddr, cliaddr;
        	char cmsg[256];
		char smsg[256];
        	int sockfd, mlen , ret , slen ,connectfd;
        	socklen_t clen;
        	pid_t pid;
		key_t key;
        	int shm_id;
        	short* count;

	public: 

		void createSocket();	//function to create socket
		void shmcreate();	//function to create shared memory
		void shmattach();	//function to attach shared memory
		void shmdestroy();	//function to destroy shared memory
		void concurrency();	//function to make server work in concurrency
		void shmWrite();	//function to write the connections 
};
