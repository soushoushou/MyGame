#pragma once

#include <cocos2d.h>
#include <thread>
#include "NetworkPackage.h"
#include "TCPRequest.h"
USING_NS_CC;
#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif

#ifndef CHECKF
#define CHECKF(x) \
	do \
				{ \
	if (!(x)) { \
		log("%s%s%s%s","CHECKF", #x, __FILE__, __LINE__); \
	return 0; \
					} \
				} while (0)
#endif

const string g_strServerIP = "120.24.180.25"/*"127.0.0.1"*/;
const int g_nServerPort = 333/*9999*/;
#define _MAX_MSGSIZE (1000 * 1024)		// 暂定一个消息最大为16k
#define BLOCKSECONDS	30			// 读取函数阻塞时间
#define INBUFSIZE	(1000*1024)		//	具体尺寸根据剖面报告调整  接收数据的缓存
#define OUTBUFSIZE	(1000*1024)		// 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一次

class CTCPClient {
public:
	CTCPClient(void);
	~CTCPClient();

	bool sendTCPRequset(CTCPRequest* request);
	bool	Create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	void	Destroy(void);
	bool isConnected();
private:
	void   ReconnectServer();
	void	NetworkThreadFunc();					//处理网络IO的线程函数
	void	ReconnectFunc();						//重连线程函数
	bool	Flush(void);
	bool	Check(void);
	bool	isWantedCMD(unsigned short& cmd);
	bool	isRecvCompelete(unsigned int& nPackageLen);
	SOCKET	GetSocket(void) const { return m_sockClient; }
	bool	ReceiveMsg();
	bool	SendMsg(void* pBuf, int nSize);
	int	recvFromSock(void);		// 从网络中读取尽可能多的数据
	bool    hasError();			// 是否发生错误，注意，异步模式未完成非错误
	void    closeSocket();

	SOCKET	m_sockClient;

	// 发送数据缓冲
	unsigned char	*m_bufOutput;	// 可优化为指针数组
	int		m_nOutbufLen;

	unsigned char	*m_bufInput;
	int		m_nInbufLen;
	unsigned int		m_nInbufStart;				//包头

	CTCPRequest* m_pRequest;
	mutex m_requestMutex;
	bool m_flag;
};
