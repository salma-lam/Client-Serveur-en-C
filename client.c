#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc , char *argv[]) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;

    if (argc < 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }
    
    printf("Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0) {
        printf("connect error");
        return 1;
    }
    printf("Connected.\n");

    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR) {
        printf("recv failed");
    }
    server_reply[recv_size] = '\0';
    printf("Server reply:\n%s", server_reply);

    closesocket(s);
    WSACleanup();

    return 0;
}
