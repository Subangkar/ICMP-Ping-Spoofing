# ICMP Ping Spoofing Attack
Victim's source IP is spoofed to send a ping to server from Attacker.
As the source IP is spoofed server takes is as a original IP and hence ping reply is sent to victim instead of attacker who send the actual ping request.
Also a sniffer using pcap is built to sniff ICMP packets for verification.

Environments:
- Any Linux Based OS
- libpcap-dev for linux
- Qt4 support for GUI
- Python 2.7+ for GUI

Running the program:  
- To run from terminal,
First run the sniffer with
`./sniff.sh <net-interface-name>`  
Then run the spoofing program,  
`./spoof.sh <source-ip> <destination-ip> <payload>`  
Example:
    ```bash
    ./sniff.sh wlp2s0
    ./spoof.sh "1.2.3.4" "8.8.8.8" "spoofed ping"
    ```  

- To run spoofing using GUI:  
`python frontend.py`  

- To run using mininet  
A virtual topology with 4 hosts is created with mininet using `topology-mininet.py`.   
run `python topology-mininet.py` to create the mininet.
Must use python 2.
