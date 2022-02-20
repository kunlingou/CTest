#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "test_socket.h"


typedef struct {
    pthread_t pthread;
    INT32     sock;
} SOCK_ACCEPT_CONNECT_PARA_S;

VOID SOCK_InitPara(SOCK_PARA_S *pPara, int argc, char *argv[])
{
    argc--;
    argv++;

    if (argc > 0 && strcmp(SOCK_PROCESS_TYPE_NAME_CLIENT, argv[0]) == 0) {
        pPara->type                  = SOCK_PROCESS_TYPE_CLIENT;
    } else {
        pPara->type                  = SOCK_PROCESS_TYPE_SERVER;
    }
    
    if (argc > 1) {
        pPara->addr                  = argv[1];
    } else {
        pPara->addr                  = SOCK_DEFAULT_DST_ADDR;
    }

    if (argc > 2) {
        pPara->port                  = (UINT16)atol(argv[2]);
    } else {
        pPara->port                  = SOCK_DEFAULT_DST_PORT;
    }
}

UINT32 SOCK_Write(SOCK_MSG_S *pMsg)
{
    if (pMsg->len > SOCK_MSG_LEN) {
        return VOS_ERR;
    }

    pMsg->data[pMsg->len] = 0;
    INT32 len = write(pMsg->sockId, pMsg, sizeof(SOCK_MSG_S));

    if (len == -1) {
        SOCK_ERR("SEND FAIL[sock:%d len:%d]:%s", pMsg->sockId, pMsg->len, pMsg->data);
        return VOS_ERR;
    }
    return VOS_OK;
}

UINT32 SOCK_Read(UINT32 sock, SOCK_MSG_S *pMsg)
{

    INT32 len = read(sock, pMsg, sizeof(SOCK_MSG_S));

    if (len == -1) {
        SOCK_ERR("RECV[localsock:%d]:Fail", sock);
        return VOS_ERR;
    }

    if (len == 0) {
        pMsg->len                    =  0;
        pMsg->data[0]                = '\0';
    }

    return VOS_OK;
}

UINT32 SOCK_AcceptConnectionRecvResquest(SOCK_ACCEPT_CONNECT_PARA_S *pPara, SOCK_MSG_S *pMsg)
{
    for (UINT32 i = 0; i < 10; i++) {

        sleep(1);

        if (SOCK_Read(pPara->sock, pMsg) == VOS_OK) {
            SOCK_INFO("RECV[thread:%lu localsock:%d sock:%d len:%d]:%s", pPara->pthread, pPara->sock, pMsg->sockId, pMsg->len, pMsg->data);
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

UINT32 SOCK_AcceptConnectionSendResponse(SOCK_ACCEPT_CONNECT_PARA_S *pPara, SOCK_MSG_S *pResquest)
{
    SOCK_MSG_S sendMsg;
    sendMsg.sockId           = pPara->sock;
    INT32 len;
    for (UINT32 i = 0; i < 50; i++) {
        len = sprintf(sendMsg.data, "this is Response Message(%u).", i);
        if (len < 0) {
            SOCK_ERR("Response sprintf Fail");
            continue;
        }
        sendMsg.len          = len;
        if (SOCK_Write(&sendMsg) == VOS_OK) {
            SOCK_INFO("SEND[thread:%lu sock:%d len:%d]:%s", pPara->pthread, sendMsg.sockId, sendMsg.len, sendMsg.data);
        }

        usleep(100000); // 1s写10次
    }
}

VOID SOCK_AcceptConnection(SOCK_ACCEPT_CONNECT_PARA_S *pPara)
{
    SOCK_MSG_S recvMsg;

    if (SOCK_AcceptConnectionRecvResquest(pPara, &recvMsg) != VOS_OK) {
        return;
    }

    SOCK_AcceptConnectionSendResponse(pPara, &recvMsg);

    INT32 ret = close(pPara->sock);
    SOCK_INFO("CLSE[sock:%d ret:%d]", pPara->sock, ret);
}

VOID *SOCK_AcceptConnectionThread(VOID *pArg)
{

    SOCK_ACCEPT_CONNECT_PARA_S *pPara = (SOCK_ACCEPT_CONNECT_PARA_S*)pArg;

    SOCK_INFO("SOCK_AcceptConnectionThread In: pthread(%lu) self_thread(%lu) localSock(%u)", pPara->pthread, pthread_self(), pPara->sock);

    pthread_detach(pPara->pthread); 

    SOCK_AcceptConnection(pPara);

    SOCK_INFO("SOCK_AcceptConnectionThread Out: pthread(%lu) localSock(%u)", pPara->pthread, pPara->sock);

    pPara->pthread = 0;

    pthread_exit(NULL);
}

SOCK_ACCEPT_CONNECT_PARA_S *SOCK_GetFreeConnetPara(SOCK_ACCEPT_CONNECT_PARA_S pPara[], UINT32 size)
{
    for (UINT32 i = 0; i < size; i++) {
        if (pPara[i].pthread == 0) {
            return pPara + i;
        }
    }
    return NULL;
}

UINT32 SOCK_MainServer(SOCK_PARA_S *pPara)
{
    INT32 ret, len;

    // socket

    INT32 sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        SOCK_ERR("socket Fail!");
        return VOS_ERR;
    }
    SOCK_INFO("socket(%d) create ok", sock);

    // bind

    SOCK_ADDR_S addr;
    addr.family                      = AF_INET;
    addr.port                        = htons(pPara->port);
    addr.addr                        = inet_addr(pPara->addr);

    ret = bind(sock, (struct sockaddr *)&addr, sizeof(SOCK_ADDR_S));
    if (ret < 0) {
        SOCK_ERR("socket bind Err(%d)!", ret);
        return VOS_ERR;
    }

    // listen

    ret = listen(sock, 5);
    if (ret != VOS_OK) {
        SOCK_ERR("socket listen Err(%d)!", ret);
        return VOS_ERR;
    }

    SOCK_INFO("socket accept ...");

    // accept

    INT32       clientSock;
    SOCK_ADDR_S clientAddr;
    UINT32      clientAddrLen        = sizeof(SOCK_ADDR_S); // 注意：这里得是有效值

    SOCK_ACCEPT_CONNECT_PARA_S paras[SOCK_MAX_CLIENT_NUM] = {0};

    while (VOS_TRUE) {
        clientSock = accept(sock, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSock == -1) {
            SOCK_ERR("socket accept Fail(%d)", clientSock);
            continue;
        }

        SOCK_INFO("socket accept Succ(%d)", clientSock);

        SOCK_ACCEPT_CONNECT_PARA_S *pPara = SOCK_GetFreeConnetPara(paras, SOCK_MAX_CLIENT_NUM);

        if (pPara == NULL) {
            close(clientSock);
            SOCK_ERR("socket Cur Thread is Over MaxNum(%u)", SOCK_MAX_CLIENT_NUM);
            continue;
        }

        pPara->sock                  = clientSock;
        ret = pthread_create(&pPara->pthread, NULL, SOCK_AcceptConnectionThread, pPara);

        if (ret != VOS_OK) {
            close(clientSock);
            SOCK_ERR("socket create thread SOCK_AcceptConnection Fail(%d)", ret);
            continue;
        }

        SOCK_INFO("socket create thread SOCK_AcceptConnection Succ pthread(%lu)", pPara->pthread);
    }

    // close

    close(sock);

    return VOS_OK;
}

UINT32 SOCK_MainClient(SOCK_PARA_S *pPara)
{
    INT32 ret, len;

    // socket

    INT32 sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        SOCK_ERR("socket Fail!");
        return VOS_ERR;
    }
    SOCK_INFO("socket(%d) create ok", sock);

    // connet

    SOCK_ADDR_S addr;
    addr.family                      = AF_INET;
    addr.port                        = htons(pPara->port);
    addr.addr                        = inet_addr(pPara->addr);

    ret = connect(sock, (struct sockaddr *)&addr, sizeof(SOCK_ADDR_S));
    if (ret == -1) {
        SOCK_ERR("socket connet Fail(%d)!", ret);
        return VOS_ERR;
    }

    SOCK_INFO("socket connet Succ(%d)!", ret);

    // write

    CHAR msgData[] = "this is Request Message.";

    SOCK_MSG_S sendMsg;
    sendMsg.sockId                       = sock;
    sendMsg.len                          = strlen(msgData);
    memcpy(sendMsg.data, msgData, sendMsg.len);

    if (SOCK_Write(&sendMsg) != VOS_OK) {
        return VOS_ERR;
    }

    SOCK_INFO("SEND[thread:%lu sock:%d len:%d]:%s", pthread_self(), sendMsg.sockId, sendMsg.len, sendMsg.data);

    // recv

    SOCK_MSG_S recvMsg = {0};

    while (VOS_TRUE) {

        sleep(1);

        if (SOCK_Read(sock, &recvMsg) != VOS_OK) {
            continue;
        }

        if (recvMsg.len == 0) {
            break;
        }

        SOCK_INFO("RECV[thread:%lu localsock:%d sock:%d len:%d]:%s", pthread_self(), sock, recvMsg.sockId, recvMsg.len, recvMsg.data);
    }

    // close

    close(sock);

    return VOS_ERR;
}

int main(int argc, char *argv[])
{
    SOCK_PARA_S para;
    SOCK_InitPara(&para, argc, argv);

    SOCK_INFO("test socket start");

    if (para.type == SOCK_PROCESS_TYPE_SERVER) {
        (VOID)SOCK_MainServer(&para);
    } else {
        (VOID)SOCK_MainClient(&para);
    }

    SOCK_INFO("test socket end");

    return VOS_OK;
}