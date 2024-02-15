#include "socket_communication.h"

int32_t main()
{
    int32_t ret = SUCCESS;
    int socketFd = 0;  // socket handle
    int recvLen = 0;
    int newFd = 0;
    char buf[4096] = {0};
    struct sockaddr_in stLocalAddr = {0};    

    socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // establish socket
    if(socketFd < 0) {
        printf("Establish socket failed!\n");
        ret = FAIL;
        goto EXIT;
    }    

    stLocalAddr.sin_family = AF_INET;
    stLocalAddr.sin_port = htons(PORT);
    stLocalAddr.sin_addr.s_addr = inet_addr(ADDR);  // server ip
    if(bind(socketFd, (void *)&stLocalAddr, sizeof(stLocalAddr)) < 0) {
        printf("Bind socket failed!\n");
        ret = FAIL;
        goto EXIT;
    }

    if(listen(socketFd, MAX_PORT_NUM) < 0) {
        printf("Listening failed!\n");
        ret = FAIL;
        goto EXIT;
    }
    printf("SocketFD: %d\n", socketFd);
    
    struct sockaddr_in stRemoteAddr = {0};
    socklen_t socklen = 0;
    newFd = accept(socketFd, (void *)&stRemoteAddr, &socklen);
    if(newFd < 0)
    {
        printf("Accept failed!\n");
        ret = FAIL;
        goto EXIT;
    }
    printf("Accept successfully!\n");
    recvLen = recv(newFd, buf, sizeof(buf), 0);
    if(recvLen < 0) {
        printf("Receive failed!\n");
        ret = FAIL;
        goto EXIT;
    } else if (recvLen == 0) {
        ret = SUCCESS;
    } else {
        printf("buf: %s\n", buf);
        (void)memset(buf, 0, strlen(buf));
        send(newFd, "Accept successfully! Hello User!", sizeof("Accept successfully! Hello User!"), 0);
    }

EXIT:
    close(newFd);
    close(socketFd);
    return ret;
}
