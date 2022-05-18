//Header file for tcp socket 

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

		void func();
		void shmcreate();
		void shmattach();
		void sharememInc();
		void shmdestroy();
		void concurrency();
		void shmWrite();
};
