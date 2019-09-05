#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "icmp_ping.h"


int main(int argc, char const *argv[]) {

	if (argc < 3) PRINT_ERROR("usage <source-ip> <destination-ip>")

	struct iphdr *ip;
	ip = create_ping_ip_packet(argv[1], argv[2], "ping spoofing test");
	send_raw_ip_packet(ip);
	return 0;
}

void set_icmp_ping_header(struct icmphdr *icmp, uint16_t payload_length) {
	icmp->type = ICMP_ECHO;
	icmp->checksum = in_checksum((uint16_t *) icmp, sizeof(struct icmphdr) + payload_length);
}

void set_ip_icmp_header(struct iphdr *ip, const char *src, const char *dest, uint16_t payload_length) {
	ip->version = 4;
	ip->ihl = 5;
	ip->ttl = 20;
	ip->saddr = inet_addr(src);
	ip->daddr = inet_addr(dest);
	ip->protocol = IPPROTO_ICMP;
	ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr) + payload_length);// ip payload length
}

struct iphdr *create_ping_ip_packet(const char *src, const char *dest, const char *payload) {
	static uint8_t *buffer = NULL;

	const size_t payload_length = strlen(payload);
	const size_t buffer_length = sizeof(struct iphdr) + sizeof(struct icmphdr) + payload_length;

	if (buffer) free(buffer);
	buffer = malloc(buffer_length);
	memset(buffer, 0, buffer_length);

	memcpy(buffer + sizeof(struct iphdr) + sizeof(struct icmphdr), payload, payload_length);
	set_icmp_ping_header((struct icmphdr *) (buffer + sizeof(struct iphdr)), payload_length);
	set_ip_icmp_header((struct iphdr *) buffer, src, dest, payload_length);

	return (struct iphdr *) buffer;
}
