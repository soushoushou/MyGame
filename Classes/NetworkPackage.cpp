#include "NetworkPackage.h"

//8字节主机序转网络序
unsigned long long my_htonll(unsigned long long val) {
	return (((unsigned long long)htonl(val)) << 32) + htonl(val >> 32);
}

//8字节网络序转主机序
unsigned long long my_ntohll(unsigned long long val) {
	return (((unsigned long long)ntohl(val)) << 32) + ntohl(val >> 32);
}
