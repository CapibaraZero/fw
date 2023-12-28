// TODO: Switch to something more reliable that millis(). 
#define PCAP_FILE(type) String(String(String("/") + type + String("/")) + millis() + String(".pcap"))