//
// Created by Subangkar on 07-Aug-19.
//

#include <stdint.h>

uint16_t in_checksum(uint16_t *buf, uint32_t length) {
	uint16_t *w = buf;
	uint32_t nleft = length;
	uint32_t sum = 0;
	uint16_t temp = 0;

	/*
	* The algorithm uses a 32 bit accumulator (sum), adds
	* sequential 16 bit words to it, and at the end, folds back all
	* the carry bits from the top 16 bits into the lower 16 bits.
	*/
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	/* treat the odd byte at the end, if any */
	if (nleft == 1) {
		*(uint8_t *) (&temp) = *(uint8_t *) w;
		sum += temp;
	}

	/* add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff); // add hi 16 to low 16
	sum += (sum >> 16);                 // add carry
	return (uint16_t) (~sum);
}

