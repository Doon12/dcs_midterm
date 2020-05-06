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
	int listenfd, connfd, filefd, len;
	struct sockaddr_in cliaddr, servaddr;
	socklen_t clilen;
	char recv_msg[BUFSIZE];
	char send_msg[BUFSIZE];
	file_segment segment;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		error("socket() error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
		error("bind() error");

	if (listen(listenfd, 5) == -1)
		error("listen() error");

	if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) == -1)
		error("accept() error");

	/* Phase 2 : Create Player */
	char _name[] = "Player1";
	int _hp = 60;
	int _strength = 50;
	int _portion_count = 70;
	Player* myPlayer = initPlayer(_name, _hp, _strength, _portion_count);
	
	while(1){
	  // clear player_msg
		send_msg[0] = '\0';
		recv_msg[0] = '\0';

		len = read(connfd, recv_msg, sizeof(recv_msg));

		printf("MSG TYPE Received: %s\n", recv_msg);

		switch (atoi(recv_msg)) {
			case MSG_NAME:
				sprintf(send_msg, "player's name is : %s", getName(myPlayer));
				break;
			case MSG_HP:
				sprintf(send_msg, "player's hp is : %d", getHp(myPlayer));
				break;
			case MSG_STRENGTH:
				sprintf(send_msg, "player's strength is : %d", getStrength(myPlayer));
				break;
			case MSG_PORTION_COUNT:
				sprintf(send_msg, "player's portion count is : %d", getPortionCount(myPlayer));
				break;
			default:
				printf("no such message and exit\n");
				break;
		}

		if (strcmp(recv_msg, "4") == 0)
		{
			printf("get Termination msg and quit\n");
			break;
		}

		write(connfd, send_msg, strlen(send_msg)+1);
	}

	destroyPlayer(myPlayer);

	close(connfd);
	close(listenfd);
	return 0;
}
