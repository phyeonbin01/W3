#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char** argv){
	int client_socket;
	int server_socket = socket(PF_INET, SOCK_STREAM, 0);	//PF_INET : IPv4,	SOCK_STREAM : TCP,	0 : SOCK_STREAM에 맞춰서 자동으로 프로토콜 선택(IPPROTO_TCP)
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);		//htonl()로 통신하는 두 컴퓨터의 바이트 순서를 빅엔디안으로 통일	INADDR_ANY : 현재 PC의 IP
	server_address.sin_port = htons(8080);

	//소켓 bind
	int bind_server_socket = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (bind_server_socket == -1) {
		printf("bind fail\n");
	}

	//listen
	int listen_server_socket = listen(server_socket, 5);		//대기 큐 5
	if (listen_server_socket == -1) {
		printf("listen fail\n");
	}

	//accept
	socklen_t client_address_size = sizeof(client_address);		//accept() 매개변수 자료형에 맞추기 위해 socklen_t로 선언. int형으로 할 시 warning
	client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size);
    if (client_socket == -1) {
		printf("accept fail\n");
	}

	//출력
    char http_buff[10000] = {0};
    read(client_socket, http_buff, 10000);
    printf("%s", http_buff);

    //전송
    char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nI'm Server!";
    write(client_socket, msg, 200);

	//종료
	close(server_socket);
	close(client_socket);
	return 0;
}