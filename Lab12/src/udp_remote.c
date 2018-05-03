#include "udp_remote.h"

io_t in, out;

int recv_sock, send_sock;
int addr_len, bytes_read, bytes_sent;
char recv_data[2048];
char send_data[2048];
struct sockaddr_in server_addr, client_addr;
int no_net, UDP_verbose;

void binarize_io(io_t* io)
{
	if (io->b0) io->b0 = 1;
	if (io->b1) io->b1 = 1;
	if (io->b2) io->b2 = 1;
	if (io->b3) io->b3 = 1;
	if (io->b4) io->b4 = 1;
	if (io->b5) io->b5 = 1;
	if (io->b6) io->b6 = 1;
	if (io->b7) io->b7 = 1;
}

void perror_and_clean(const char* s)
{
  #ifdef WIN32
	WSACleanup();
  #endif
	perror(s);
}

void UDP_remote_init(void)
{
  #ifdef WIN32
	// Initialize Winsock
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (res != 0) {
	    printf("WSAStartup failed: %d\n", res);
	    exit(2);
	    //return 1;
	}
  #endif

	if ((recv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror_and_clean("Socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9810);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	if (bind(recv_sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1){
		perror_and_clean("Bind");
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);

	if (UDP_verbose) {
		printf("\nUDPServer Waiting for client on port 9810");
		fflush(stdout);
	}

    send_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (send_sock == INVALID_SOCKET) {
		perror_and_clean("Send Socket");
		exit(1);
    }
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9811);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

int recvfromTimeOutUDP(SOCKET socket, long sec, long usec)
{
    // Setup timeval variable
    struct timeval timeout;
    struct fd_set fds;

    timeout.tv_sec = sec;
    timeout.tv_usec = usec;

    // Setup fd_set structure
    FD_ZERO(&fds);
    FD_SET(socket, &fds);

    // Return value:
    // -1: error occurred
    // 0: timed out
    // > 0: data ready to be read

    return select(0, &fds, 0, 0, &timeout);
}


void UDP_remote_read_timeout(long usec)
{
    if (recvfromTimeOutUDP(recv_sock, 0, usec) == 0 ){
		if (UDP_verbose) {
			printf(".");
			fflush(stdout);
		}
		no_net++;
    } else {
    	no_net = 0;
		bytes_read = recvfrom(recv_sock, recv_data, 1024, 0, (struct sockaddr *)&client_addr, &addr_len);
 	    recv_data[bytes_read] = '\0';
 	    in.b0 = recv_data[0] - '0';
 	    in.b1 = recv_data[1] - '0';
 	    in.b2 = recv_data[2] - '0';
 	    in.b3 = recv_data[3] - '0';
 	    in.b4 = recv_data[4] - '0';
 	    in.b5 = recv_data[5] - '0';
 	    in.b6 = recv_data[6] - '0';
 	    in.b7 = recv_data[7] - '0';

		if (UDP_verbose) {
		    printf("\n(%s , %d) said : ",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	    	printf("%s", recv_data);
	    	fflush(stdout);
		}
    }
	
}

void UDP_remote_write(void)
{
  	no_net = 0;
    if (no_net != 0) return;
    
	client_addr.sin_port = htons(9811);
	
	binarize_io(&out);
	send_data[0] = '0' + out.b0;
	send_data[1] = '0' + out.b1;
	send_data[2] = '0' + out.b2;
	send_data[3] = '0' + out.b3;
	send_data[4] = '0' + out.b4;
	send_data[5] = '0' + out.b5;
	send_data[6] = '0' + out.b6;
	send_data[7] = '0' + out.b7;
	//send_data[8] = 0;
	bytes_sent = sendto(send_sock, send_data, 8, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));	

	if (UDP_verbose) {
		if (bytes_sent == SOCKET_ERROR){
    		printf("\nSent Failed\n");
		} else {
    		printf("(%d)", bytes_sent);
		}
	}

}


