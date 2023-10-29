#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv){
    struct sockaddr_in server_address;
    int client_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (client_sock == -1){
        printf("socket wasn't made\n");
    }

    server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");		
	server_address.sin_port = htons(8080);

    socklen_t serv_addr_size = sizeof(server_address);
    int connect_serv_addr = connect(client_sock, (struct sockaddr *)&server_address, serv_addr_size);
    if (connect_serv_addr == -1){
        printf("connect fail\n");
    }

    char *msg = "I'm Client!";
    write(client_sock, msg, 20);

    char http_buff[10000] = {0};
    read(client_sock, http_buff, 10000);
    printf("result : \n%s", http_buff);

    close(client_sock);
    return 0;
}