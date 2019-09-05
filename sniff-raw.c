#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>


void got_packet(const u_char *packet, int packet_length) {
	struct ether_header *eth = (struct ether_header *) packet;

	if (ntohs(eth->ether_type) == ETHERTYPE_IP) {
		struct iphdr *ip = (struct iphdr *) (packet + sizeof(struct ether_header));
		if (ip->protocol == IPPROTO_ICMP) {
			struct icmphdr *icmp = (struct icmphdr *) (packet + sizeof(struct ether_header) + sizeof(struct iphdr));
			printf(" Protocol: ICMP\n");
			printf("     From: %s\n", inet_ntoa(*(struct in_addr *) &ip->saddr));
			printf("       To: %s\n", inet_ntoa(*(struct in_addr *) &ip->daddr));
			printf("     Type: ");

			if (icmp->type == ICMP_ECHO || icmp->type == ICMP_ECHOREPLY) {
				if (icmp->type == ICMP_ECHO) {
					printf("ping request\n");
				} else if (icmp->type == ICMP_ECHOREPLY) {
					printf("ping reply\n");
				}
				if (packet_length > (sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct icmphdr))) {
					printf("  Payload: ");
					puts((char *) packet +
					     (sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct icmphdr)));
				}
			}
			printf("\n");
		}
	}
}


int main() {
	int PACKET_LEN = 1024;
	u_char buffer[PACKET_LEN];
	struct sockaddr saddr;
	struct packet_mreq mr;

	// Create the raw socket
	int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));

	// Turn on the promiscuous mode.
	mr.mr_type = PACKET_MR_PROMISC;
	setsockopt(sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr));

	// Getting captured packets
	while (1) {
		int data_size = recvfrom(sock, buffer, PACKET_LEN, 0,
		                         &saddr, (socklen_t *) sizeof(saddr));
		if (data_size)
			got_packet(buffer, data_size);
	}

	close(sock);
	return 0;
}
