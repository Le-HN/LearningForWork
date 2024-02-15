gcc -g socket_com_server.c -o sktsrv -I ../public -lpublic -lpthread -L ../lib -Wl,-rpath ../lib
gcc -g socket_com_client.c -o sktclt -I ../public -lpublic -lpthread -L ../lib -Wl,-rpath ../lib 
