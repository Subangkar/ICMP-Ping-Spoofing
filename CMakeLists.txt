cmake_minimum_required(VERSION 3.5)
project(ping_spoof C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ping_spoof
        checksum.c
        icmp_ping.c
        icmp_ping.h
        raw_socket.c)

add_executable(raw-sniffer
        #        sniff-raw-icmp.c
        sniff-raw.c
        )

add_executable(pacp-sniffer sniff-pcap.c)
target_link_libraries(pacp-sniffer pcap)
