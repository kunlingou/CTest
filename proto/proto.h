#ifndef __PROTO_H__
#define __PROTO_H__

#include "types.h"

#define ETH_TYPE_IPV4 0x0800

typedef struct {
    UINT32 magic;
    UINT16 zone;
    UINT16 sigFigs;
    UINT16 snapLen;
    UINT16 linkType;
    UINT8 resv[12];
} PCAP_HEAD_S;

typedef struct {
    UINT32 time;
    UINT32 us;
    UINT32 capLen;
    UINT32 len;
} PCAP_PACKET_HEAD_S;


typedef struct {
    UINT8  dmac[6];
    UINT8  smac[6];
    UINT16 type;
} ETH_S;

typedef struct {
#if BYTE_ORDER == LITTLENDIAN
    UINT8  hLen : 4;
    UINT8  ver : 4;
#else
    UINT8  ver : 4;
    UINT8  hLen : 4;
#endif
    UINT8  tos;
    UINT16 tLen;
    UINT16 ipid;
    UINT16 frags;
    UINT8  ttl;
    UINT8  proto;
    UINT16 checksum;
    UINT32 saddr;
    UINT32 daddr;
} IP_S;

typedef struct {
    UINT16 sport;
    UINT16 dport;
    UINT16 len;
    UINT16 checksum;
} UDP_S;

typedef struct {

} SIP_S;

#endif