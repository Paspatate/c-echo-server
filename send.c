#include <stdio.h>
#include <sys/socket.h> // socket API
#include <netinet/in.h> // IPV4 fonctionnalite
#include <arpa/inet.h> // conversion d'address

int main() {
	struct sockaddr_in target = {0};
	target.sin_family = AF_INET;
	target.sin_port = htons(8532);
	inet_aton("0.0.0.0", &target.sin_addr);
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

	char buff[300];
	while (1) {
		fgets(buff, 300, stdin);
		
		int byte_sent = sendto(socket_fd, buff, 300, 0, (struct sockaddr*)&target, sizeof(struct sockaddr_in));
		char buf_recv[350];
		int byte_recv = recv(socket_fd, buf_recv, 350, 0);
		printf("from server: %s\n", buf_recv);
	}
	return 0;
}
