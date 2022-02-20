#ifndef __TEST_SOCKET_H__
#define __TEST_SOCKET_H__

#define VOS_OK 0
#define VOS_ERR 1
#define VOS_TRUE 1
#define VOS_FALSE 0

typedef void VOID;

typedef char CHAR;
typedef int INT32;

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;

#define SOCK_INFO(fmt...) do { \
    printf("INFO: [SOCK]" fmt);     \
    printf("\r\n");           \
} while(0)

#define SOCK_ERR(fmt...) do { \
    printf("ERROR: [SOCK]" fmt);     \
    printf("\r\n");           \
} while(0)

#define SOCK_PROCESS_TYPE_NAME_SERVER "server"
#define SOCK_PROCESS_TYPE_NAME_CLIENT "client"

#define SOCK_PROCESS_TYPE_SERVER 0
#define SOCK_PROCESS_TYPE_CLIENT 1

#define SOCK_DEFAULT_DST_ADDR "127.0.0.1"
#define SOCK_DEFAULT_DST_PORT 1500
#define SOCK_MSG_LEN 1024
#define SOCK_MAX_CLIENT_NUM 5

typedef struct {
    UINT16 family;
    UINT16 port;
    UINT32 addr;
    UINT8  resv[8];
} SOCK_ADDR_S;

typedef struct {
    UINT32 type;
    CHAR*  addr;
    UINT16 port;
} SOCK_PARA_S;

typedef struct {
    UINT16 sockId;
    UINT16 len;
    UINT8  data[SOCK_MSG_LEN + 1];
} SOCK_MSG_S;

#endif