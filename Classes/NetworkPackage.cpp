#include "NetworkPackage.h"

//8字节主机序转网络序
unsigned __int64 my_htonll(unsigned __int64 val) {
	return (((unsigned __int64)htonl(val)) << 32) + htonl(val >> 32);
}

//8字节网络序转主机序
unsigned __int64 my_ntohll(unsigned __int64 val) {
	return (((unsigned __int64)ntohl(val)) << 32) + ntohl(val >> 32);
}
