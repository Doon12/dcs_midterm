#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "player.h"

#define	BUFSIZE	256

typedef struct file_segment {
		int len;
		char buf[BUFSIZE];
} file_segment;

void error (char* msg) {
		perror(msg);
		exit(1);
}

int main(int argc, char* argv[]) {
		int sockfd, filefd, len;
		struct sockaddr_in servaddr;
		char send_buf[1];
		char recv_buf[BUFSIZE];

		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			error("socket() error");

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = inet_addr(argv[1]);
		servaddr.sin_port = htons(atoi(argv[2]));

		if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
				error ("connect() error");
		}

		while (1) {
				printf("0: get NAME, 1: get HP, 2: get STRENGTH, 3: get PORTION_COUNT, 4: TERMINATE \n");
				scanf("%s", send_buf);
				write(sockfd, send_buf, strlen(send_buf));
				if (atoi(send_buf) == MSG_TERMINATE)
					{
						printf("TERMINATE COMMUNICATION\n");
						break;
					}
				len = read(sockfd, recv_buf, sizeof(recv_buf));
				printf("Echo from Server: %s\n", recv_buf);
		}

		close(sockfd);
		return 0;
}
