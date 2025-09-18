#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	struct sockaddr_in destination = {0};
	destination.sin_family = AF_INET;
	destination.sin_port = htons(8532);
	inet_aton("0.0.0.0", &destination.sin_addr);
	printf("%d\n", ntohs(destination.sin_port));

	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	int err_bind = bind(sock, (struct sockaddr*)&destination, sizeof(struct sockaddr));
	if (err_bind == -1) {
		printf("cannot bind");
	}
	
	printf("listening\n");
	char buf[350];
	while(1) {
		struct sockaddr_in source = {0};
		socklen_t source_len = sizeof(struct sockaddr_in);
		recvfrom(sock, buf, 350, 0, (struct sockaddr*)&source, &source_len);
		printf("%s\n", buf);

		if (source_len == sizeof(struct sockaddr_in)) {
			sendto(sock, buf, 350, 0, (struct sockaddr*)&source, source_len);
			printf("sending data to %s\n", inet_ntoa(source.sin_addr));
		} else {
			printf("not sending data\n");
		}
	}
	return 0;
}
