#include "socket_communication.h"

int32_t main()
{
    int32_t ret = SUCCESS;
    int socketFd = 0; // socket handle
    unsigned int remoteAddr = 0;
    struct sockaddr_in stRemoteAddr = {0};
    socklen_t socklen = 0;
    char buf[4096] = {0};

    socketFd = socket(AF_INET, SOCK_STREAM, 0); // establish socket
    if (socketFd < 0) {
        printf("Establish socket failed!\n");
        ret = FAIL;
        goto EXIT;
    }    

    stRemoteAddr.sin_family = AF_INET;
    stRemoteAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, ADDR, &remoteAddr);
    stRemoteAddr.sin_addr.s_addr = remoteAddr;

    if (connect(socketFd, (void *)&stRemoteAddr, sizeof(stRemoteAddr)) < 0) {
        printf("Connect failed!\n");
        ret = FAIL;
        goto EXIT;
    }
    printf("Connect successfully!\n");
    send(socketFd, "Hello Server!", sizeof("Hello Server!"), 0);
    recv(socketFd, buf, sizeof(buf), 0);
    printf("Received:%s\n", buf);

EXIT:
    close(socketFd);
    return ret;
}
