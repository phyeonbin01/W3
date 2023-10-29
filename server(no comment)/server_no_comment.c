#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char** argv){
	int client_socket;
	int server_socket = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);		
	server_address.sin_port = htons(8080);

	int bind_server_socket = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (bind_server_socket == -1) {
		printf("bind fail\n");
	}

	int listen_server_socket = listen(server_socket, 5);
	if (listen_server_socket == -1) {
		printf("listen fail\n");
	}

	socklen_t client_address_size = sizeof(client_address);	
	client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size);
    if (client_socket == -1) {
		printf("accept fail\n");
	}

    char http_buff[10000] = {0};
    read(client_socket, http_buff, 10000);
    printf("%s", http_buff);

    char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nI'm Server!";
    write(client_socket, msg, 200);

	close(server_socket);
	close(client_socket);
	return 0;
}