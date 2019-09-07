# gcc sniff-raw.c -o sniffer
# sudo ./sniffer

gcc sniff-pcap.c -o sniffer -lpcap
sudo ./sniffer "$1"

# gcc sniff-raw.c -o sniffer
# sudo ./sniffer
