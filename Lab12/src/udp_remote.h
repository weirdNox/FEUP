#ifndef UDP_REMOTE_H_
#define UDP_REMOTE_H_

#include <sys/types.h>
#ifdef WIN32
  #include <winsock2.h>
  #include <winsock.h>
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    byte b0, b1, b2, b3, b4, b5, b6, b7; 
} io_t;

extern io_t in, out;
extern int sock, send_sock;
extern int addr_len, bytes_read, bytes_sent;
extern char recv_data[2048];
extern char send_data[2048];
extern struct sockaddr_in server_addr, client_addr;
extern int no_net, UDP_verbose;

void binarize_io(io_t* io);

void perror_and_clean(const char* s);
void UDP_remote_init(void);
void UDP_remote_read_timeout(long usec);
void UDP_remote_write(void);

//int recvfromTimeOutUDP(SOCKET socket, long sec, long usec);

#endif /* UDP_REMOTE_H_ */
