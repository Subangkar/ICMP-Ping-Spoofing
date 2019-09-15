//
// Created by Subangkar on 07-Aug-19.
//

#ifndef RAW_PING_ICMP_PING_H
#define RAW_PING_ICMP_PING_H

#define PRINT_LINE(msg) {\
    printf(msg);\
    printf("\n");\
}

#define PRINT_ERROR(msg) {\
    PRINT_LINE(msg);\
    exit(0);\
}

/*************************************************************
  Given an IP packet, send it out using a raw socket.
**************************************************************/
void send_raw_ip_packet(struct iphdr *ip);

uint16_t in_checksum(uint16_t *buf, uint32_t length);

/*********************************************************
    Fill in the ICMP header for a ping request.
********************************************************/
void set_icmp_ping_header(struct icmphdr *icmp, uint16_t payload_length);

/*********************************************************
    Fill in the IP header for a ICMP payload.
********************************************************/
void set_ip_icmp_header(struct iphdr *ip, const char *src, const char *dest, uint16_t payload_length);

/*********************************************************
    Create an IP packet with payload for ping request.
********************************************************/
struct iphdr *create_ping_ip_packet(const char *src, const char *dest, const char *payload);


#endif //RAW_PING_ICMP_PING_H
