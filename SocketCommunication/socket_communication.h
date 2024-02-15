#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "public.h"

#define PORT 23		    // socket num
#define MAX_PORT_NUM 5  // max listening num
#define ADDR "127.0.0.1"
