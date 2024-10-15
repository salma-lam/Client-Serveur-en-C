#include <stdio.h>
#include <winsock2.h>
#include <dirent.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char *message, client_reply[2000];

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

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    if(bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }
    printf("Bind done.\n");

    listen(s , 3);
    printf("Waiting for incoming connections...\n");
    
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        printf("accept failed with error code : %d" , WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }
    printf("Connection accepted.\n");

    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL) {
        printf("Could not open current directory");
        return 0;
    }
    
    char file_list[2000] = "";
    while ((de = readdir(dr)) != NULL) {
        strcat(file_list, de->d_name);
        strcat(file_list, "\n");
    }
    closedir(dr);

    send(new_socket, file_list, strlen(file_list), 0);
    
    closesocket(new_socket);
    closesocket(s);
    WSACleanup();

    return 0;
}
