#include <stdio.h>
#include <time.h>

#include "proto.h"

#define writeLog(fmt...) do { \
    printf("ERR: " fmt);     \
    printf("\r\n");           \
} while(0)

UINT8 *getSipHdFromPcap(CHAR *fileName, UINT8 *dataPtr, UINT32 dataLen)
{
    FILE *file = fopen(fileName, "rb");

    if (file == NULL) {
        writeLog("open file is err fileName = %s", fileName);
        return NULL;
    }

    size_t len = 0;
    UINT32 offset = 0;

    do {
        len = fread(dataPtr + offset, 1, 1, file);
        offset += len;
    } while (len == 1);

    ETH_S *macHd = (ETH_S*)(dataPtr + sizeof(PCAP_HEAD_S) + sizeof(PCAP_PACKET_HEAD_S));

    if (ntohs(macHd->type) != ETH_TYPE_IPV4) {
        writeLog("eth type is err %x", macHd->type);
        return NULL;
    }

    IP_S *ipHd = (IP_S*)(macHd + 1);

    if (ipHd->ver != 4) {
        writeLog("ip ver is err %u", ipHd->ver);
        return NULL;
    }

    UINT8 *sipHd = (UINT8 *)ipHd + sizeof(IP_S) + sizeof(UDP_S);

    return sipHd;
}

#define SIP_CLRF(ptr) ((*(UINT8*)(ptr) <= 0x0d) && ((ntohs(*(UINT16*)((UINT8*)(ptr) - 1)) == 0x0d0a) || (ntohs(*(UINT16*)((UINT8*)(ptr))) == 0x0d0a)))
#define SIP_CLRF_OFFSET(ptr) ((*(UINT8*)(ptr) == 0x0d) ? 2 : 1)

#define ntohll(val) ((((UINT64)(ntohl((UINT32)((val) & 0x00000000FFFFFFFF)))) << 32) | (UINT64)(ntohl((UINT32)((val) >> 32))))

#define SIP_HEAD_CSEQ(ptr)  (((ntohll(*(UINT64*)(ptr)) >> 16) & 0x0000435365713a20) == 0x0000435365713a20)
#define SIP_HEAD_CSEQ_LEN 6
#define SIP_BLANK 0x20

#define SIP_RESPONSE(ptr) ((*(UINT8*)(ptr) == 0x53) && (ntohll(*(UINT64*)(ptr)) == 0x5349502f322e3020))
#define SIP_RESPONSE_CODE_OFFSET 8

#define SIP_CSEQ_INVITE(ptr)  (((ntohll(*(UINT64*)(ptr)) >> 16) & 0x0000494e56495445) == 0x0000494e56495445)

#define SIP_CSEQ_INVITE2(ptr)  ((((*(UINT64*)(ptr))) & 0x0000455449564e49) == 0x0000455449564e49)

int str2int(CHAR *str, int* intlen)
{
    int val = 0;
    int len = 0;

    while (*str >= '0' && *str <= '9') {
        len++;
        val = val * 10 + (*str - '0');
        str++;
    }

    if (intlen != NULL) {
        *intlen = len;
    }

    return val;
}

typedef enum {
    E_SIP_MSGTYPE_REQUEST = 1,
    E_SIP_MSGTYPE_RESPONSE,
    E_SIP_MSGTYPE_BUTT
} E_SIP_MSGTYPE;

typedef enum {
    E_SIP_METHOD_INVITE = 1,
    E_SIP_METHOD_BUTT
} E_SIP_METHOD;

typedef struct {
    UINT32 msgType;
    UINT32 method;
    UINT32 seq;
    UINT32 statusCode;
} SIP_INFO_S;

CHAR *g_sipMsgTypeStr[E_SIP_MSGTYPE_BUTT] = {
    "UNKNOWN",
    "REQUEST",
    "RESPONSE"
};

CHAR *g_sipMethodStr[E_SIP_METHOD_BUTT] = {
    "UNKNOWN",
    "INVITE"
};

int main1()
{

    UINT32 dataLen = 1200;
    UINT8 *dataPtr = malloc(dataLen);

    memset(dataPtr, 0, dataLen);

    UINT8 *sipHd = getSipHdFromPcap("./sip_init_response.pcap", dataPtr, dataLen);

    if (sipHd == NULL) {
        writeLog("getSipHdFromPcap err!");
    } else {
        writeLog("sip: %s", (CHAR*)sipHd);
    }

    SIP_INFO_S sipInfo = {0};

    if (*sipHd == 0x49 && ntohl(*(UINT32*)sipHd) == 0x494e5649) {
        writeLog("SIP INVITE Request!");
        sipInfo.msgType = E_SIP_MSGTYPE_REQUEST;
        sipInfo.method = E_SIP_METHOD_INVITE;
    } else if (SIP_RESPONSE(sipHd)) {
        writeLog("SIP INVITE Response!");
        sipInfo.msgType = E_SIP_MSGTYPE_RESPONSE;
        sipInfo.statusCode = str2int(sipHd + SIP_RESPONSE_CODE_OFFSET, NULL);
    } else {
        writeLog("UNKNOWN MSG!");
    }

    UINT8 *reqHd = sipHd;

    while(*reqHd != '\0') {
        
        if (SIP_CLRF(reqHd)) {
            
            UINT8 *sipLine = reqHd + SIP_CLRF_OFFSET(reqHd);

            if (SIP_HEAD_CSEQ(sipLine)) {

                UINT32 seqLen = 0;

                sipInfo.seq = str2int(sipLine + SIP_HEAD_CSEQ_LEN, &seqLen);

                if (sipInfo.msgType == E_SIP_MSGTYPE_RESPONSE) {
                    if (SIP_CSEQ_INVITE(sipLine + SIP_HEAD_CSEQ_LEN + seqLen + 1)) {
                        sipInfo.method = E_SIP_METHOD_INVITE;
                    }
                }
            }
        }

        reqHd += 2;
    }

    writeLog("SIP msgType = %s, method = %s, seqNum = %u, statusCode = %u!", g_sipMsgTypeStr[sipInfo.msgType], g_sipMethodStr[sipInfo.method], sipInfo.seq, sipInfo.statusCode);

    return 0;
}

int main2()
{
    CHAR *str = "INVITE sip:test@10.0.2.15:5060 SIP/2.0";

    UINT32 tryTimes = 1000000000;

    UINT32 cnt = 0;

    clock_t start_t;

    usleep(1000000);

    cnt = 0;
    start_t = clock();

    for (UINT32 i = 0; i < tryTimes; i++) {
        if (strncmp("INVITE", str, 6) == 0) {
            cnt++;
        }
    }

    writeLog("SIP strncmp cost %ld time, cnt = %u!", clock() - start_t, cnt);

    usleep(1000000);

    cnt = 0;
    start_t = clock();

    for (UINT32 i = 0; i < tryTimes; i++) {
        if (SIP_CSEQ_INVITE(str)) {
            cnt++;
        }
    }

    writeLog("SIP uint64 notohll cost %ld time, cnt = %u!", clock() - start_t, cnt);

    usleep(1000000);

    cnt = 0;
    start_t = clock();

    for (UINT32 i = 0; i < tryTimes; i++) {
        if (SIP_CSEQ_INVITE2(str)) {
            cnt++;
        }
    }

    writeLog("SIP uint64 no ntohll cost %ld time, cnt = %u!", clock() - start_t, cnt);
}

int main()
{
    return main2();
}