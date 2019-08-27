/* 
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <openssl/md5.h>

/*for getting file size using stat()*/
#include<sys/stat.h>

/*for sendfile()*/
#include<sys/sendfile.h>

/*for O_RDONLY*/
#include<fcntl.h>

#define BUFSIZE 1024

/* 
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}

struct header{
	int sequence_number,length;
};

struct message{
	struct header h1;
	char buffer[BUFSIZE];
};

int main(int argc, char **argv) {
    int sockfd, portno, n,i;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
	struct stat obj;
    char *hostname;
    char buf[BUFSIZE],filename[20];
	int filehandle,status;

    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    /* get a message from the user */
    bzero(buf, BUFSIZE);
    printf("Please enter msg: ");
    fgets(buf, BUFSIZE, stdin);

    /* send the message to the server */
    serverlen = sizeof(serveraddr);
    n = sendto(sockfd, buf, strlen(buf), 0, &serveraddr, serverlen);
    if (n < 0) 
      error("ERROR in sendto");
    
    /* print the server's reply */
    n = recvfrom(sockfd, buf, strlen(buf), 0, &serveraddr, &serverlen);
    if (n < 0) 
      error("ERROR in recvfrom");
    printf("Echo from server: %s", buf);






	  printf("Enter filename to put to server: ");
          scanf("%s", filename);
	  filehandle = open(filename, O_RDONLY);
          if(filehandle == -1)
            {
              printf("No such file on the local directory\n\n");
              exit(0);
            }
          strcpy(buf, "put ");

	  strcat(buf, filename);
	  n = sendto(sockfd, buf, strlen(buf), 0, &serveraddr, serverlen);
      if (n < 0) 
          error("ERROR in sendto");

	  stat(filename, &obj);
	  int size = obj.st_size;

	  if(size<1000000)
		{
			printf("File is too small.\n\n");
			exit(0);
		}

	  n = sendto(sockfd, &size, sizeof(int), 0, &serveraddr, serverlen);
      if (n < 0) 
          error("ERROR in sendto");

	  /*sendfile(sock, filehandle, NULL, size);*/
	struct message M;
	int c1 = 0;
	FILE * fpIn = fopen(filename, "r");
	int remain_data=size;
	if(fpIn)
	{
        while(1)
        {
           ssize_t bytesRead = fread(M.buffer, 1, sizeof(M.buffer), fpIn);
           if (bytesRead <= 0) break;  // EOF
		   M.h1.sequence_number = c1;
		   M.h1.length = bytesRead;
           printf("Read %i bytes from file, sending them to network...\n", (int)bytesRead);
		   n = sendto(sockfd, M.buffer, bytesRead, 0, &serveraddr, serverlen);
		   if (n < 0) 
               error("ERROR in sendto");
		   
		   remain_data = remain_data - bytesRead;
		   printf("Bytes remaining is %d\n",remain_data);
		   usleep(1000);
           if (n != bytesRead)
           {
              perror("send");
              break;
           }
		   c1++;
        }
	}



	  n = recvfrom(sockfd, &status, sizeof(int), 0, &serveraddr, &serverlen);
	  if (n < 0) 
        error("ERROR in recvfrom");
	  if(status)
	    printf("File stored successfully\n");
	  else
	    printf("File failed to be stored to remote machine\n");

	unsigned char c[MD5_DIGEST_LENGTH];
	FILE *inFile = fopen (filename, "rb");
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[1024];

	if (inFile == NULL) {
		printf ("%s can't be opened.\n", filename);
		return 0;
	}

	MD5_Init (&mdContext);
	while ((bytes = fread (data, 1, 1024, inFile)) != 0)
		MD5_Update (&mdContext, data, bytes);
	MD5_Final (c,&mdContext);
	for(i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", c[i]);
	printf (" %s\n", filename);
	fclose (inFile);

	char buffer[1024] = {0};
	int valread = recvfrom(sockfd, buffer, 1024, 0, &serveraddr, &serverlen);;

	if(strcmp(buffer,c))
		printf("MD5 Not matched\n");
	else
		printf("MD5 Matched\n");
    return 0;
}
