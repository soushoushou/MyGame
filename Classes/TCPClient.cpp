#include "TCPClient.h"
#include "NetworkManger.h"

CTCPClient::CTCPClient()
{
	m_fTimeEscaped = 0.0f;
	m_nInbufLen = 0;
	m_nOutbufLen = 0;
	m_nInbufStart = 0;
	m_flag = false;
	m_pRequest = nullptr;
	// 初始化
	m_bufInput = new unsigned char[INBUFSIZE];
	m_bufOutput = new unsigned char[OUTBUFSIZE];
	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
	m_sockClient = INVALID_SOCKET;

	//分离子线程
	thread t(&CTCPClient::NetworkThreadFunc, this);
	t.detach();
}

CTCPClient::~CTCPClient()
{
	Destroy();
	m_flag = true;
	while (m_flag)
	{
	}
	if (!m_bufInput)
	{
		delete[] m_bufInput;
		m_bufInput = 0;
	}
	if (!m_bufOutput)
	{
		delete[] m_bufOutput;
		m_bufOutput = 0;
	}
}

bool CTCPClient::isWantedCMD(short& cmd)
{
	if (cmd == PP_ZZ_DOUNIU_WECHAT_ORDER_ACK || cmd == PP_ZZ_DOUNIU_CREATE_ROOM_ACK || cmd == PP_ZZ_DOUNIU_GET_FOLEINFO_ACK ||
		cmd == PP_ZZ_DOUNIU_WECHAT_LOGIN_ACK || cmd == PP_ZZ_DOUNIU_ROLE_LOGIN_ACK || cmd == PP_ZZ_DOUNIU_JOIN_ROOM_ACK ||
		cmd == PP_ZZ_DOUNIU_TANPAI_ACK || cmd == PP_ZZ_DOUNIU_QUIT_ROOM_ACK ||
		cmd == PP_ZZ_DOUNIU_READY_ACK || cmd == PP_ZZ_DOUNIU_FAPAI_ACK ||
		cmd == PP_ZZ_DOUNIU_YAZHU_ACK || cmd == PP_ZZ_DOUNIU_TEXT_CHAT_ACK ||
		cmd == PP_ZZ_DOUNIU_VOICE_CHAT_ACK || cmd == PP_ZZ_DOUNIU_SHARE_INFO_NOTIFY ||
		cmd == PP_ZZ_DOUNIU_ONE_ROUND_START_NOTIFY || cmd == PP_ZZ_DOUNIU_MEMBER_INFO_NOTIFY ||
		cmd == PP_ZZ_DOUNIU_INVITE_CODE_ACK || cmd == PP_ZZ_DOUNIU_NOTICE_INFO_NOTIFY ||
		cmd == PP_ZZ_DOUNIU_SHARE_INFO_NOTIFY || cmd == PP_ZZ_DOUNIU_BUYDIAMOND_QUERY_ACK ||
		cmd == PP_ZZ_DOUNIU_ORDER_RESULT_ACK || cmd == PP_ZZ_DOUNIU_CHECK_UPDATE_ACK ||
		cmd == PP_ZZ_DOUNIU_ALL_ROUND_OVER_NOTIFY || cmd == PP_ZZ_DOUNIU_QIANGZHUANG_ACK ||
		cmd == PP_ZZ_DOUNIU_ONE_ROUND_SUM_NOTIFY || cmd == PP_ZZ_DOUNIU_ALL_ROUND_SUM_NOTIFY)
	{
		return true;
	}
	return false;
}

//bool CTCPClient::isRecvCompelete(int& nPackageLen)
//{
//	static bool b = false;
//	static unsigned int Len = 0;
//	if (!b)
//	{
//		if (m_nInbufLen >= 6)
//		{
//			short cmd = 0;
//			memcpy(&cmd, m_bufInput+m_nInbufStart+4, 2);
//			cmd = ntohs(cmd);
//			if (isWantedCMD(cmd))
//			{
//				int packageLen = 0;
//				memcpy(&packageLen, m_bufInput + m_nInbufStart, 4);
//				packageLen = ntohl(packageLen);
//				if (packageLen <= m_nInbufLen - m_nInbufStart)
//				{
//					b = false;
//					Len = 0;
//					nPackageLen = packageLen;
//					return true;
//				}
//				Len = packageLen;
//				b = true;
//			}
//		}
//	}
//	else
//	{
//		if (Len <= m_nInbufLen - m_nInbufStart)
//		{
//			b = false;
//			Len = 0;
//			nPackageLen = m_nInbufLen - m_nInbufStart;
//			return true;
//		}
//	}
//	return false;
//}


void CTCPClient::NetworkThreadFunc()
{
	m_requestMutex.lock();
	if (!Create(g_mdzzStrServerName.c_str(), g_mdzzServerPort, BLOCKSECONDS, true))
	{
		log("connect server error!");
		m_requestMutex.unlock();
		return;
	}
	m_requestMutex.unlock();
	while (1)
	{
		m_requestMutex.lock();
		if (m_sockClient != INVALID_SOCKET)
		{
			if (ReceiveMsg())
			{
				
				bool ishasnext = true;
				while (ishasnext)
				{
					int packageLen = 0;
					memcpy(&packageLen, m_bufInput + m_nInbufStart, 4);
					packageLen = ntohl(packageLen);

					short cmd = 0;
					memcpy(&cmd, m_bufInput + m_nInbufStart + 4, 2);
					cmd = ntohs(cmd);

					if (!isWantedCMD(cmd)){
						break;
					}

					if (m_nInbufStart + packageLen > m_nInbufLen){
						break;
					}

					//往消息队列添加ack
					NetworkManger::getInstance()->pushACKQueue(m_bufInput+m_nInbufStart, packageLen);
					
					if (m_nInbufStart + packageLen == m_nInbufLen)
					{
						m_nInbufLen = 0;
						m_nInbufStart = 0;
						m_pRequest = nullptr;
						break;
					}
					else
						m_nInbufStart += packageLen;
				}
			}
			else
			{
#ifdef WIN32
				int err = WSAGetLastError();
				//if (err == 10053 || err == 0)
				//{
				//	log("will reconnecting server!");
				//	ReconnectServer();
				//}
#else
				int err = errno;
				//if (err == 60 || err == 0)
				//{
				//	log("will reconnecting server!");
				//	ReconnectServer();
				//}
#endif
				log("errno = %d", err);
			}
		}
		if (m_sockClient == INVALID_SOCKET)
		{
			m_requestMutex.unlock();
			m_flag = false;
			return;
		}
		m_requestMutex.unlock();
#ifdef _WIN32
		Sleep(30);
#else
		usleep(30*1000); // takes microseconds
#endif
	}
}

bool CTCPClient::sendTCPRequset(CTCPRequest* request)
{
	if (request == nullptr)
	{
		log("request is null in sendTCPRequest()!");
		return false;
	}
	if (!SendMsg(request->getRequestData(),request->getRequestDataLen()))
	{
		log("send msg error in sendTCPRequest()!");
		return false;
	}
	m_pRequest = request;
	return true;
}

void CTCPClient::closeSocket()
{
#ifdef WIN32
	closesocket(m_sockClient);
	WSACleanup();
#else
	close(m_sockClient);
#endif
}

bool CTCPClient::Create(const char* pszServerIP, int nServerPort, int nBlockSec, bool bKeepAlive /*= FALSE*/)
{
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;


#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if (ret != 0) {
		return false;
	}
#endif

	// 检查参数
	if (pszServerIP == 0 || strlen(pszServerIP) > 15) {
		//如果不是IP，则解析域名
		hostent *h = gethostbyname(pszServerIP);
		if (h == nullptr)
		{
			hasError();
			return false;
		}
		pszServerIP = inet_ntoa(*(struct in_addr*)h->h_addr_list[0]);

	}

	// 创建主套接字
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sockClient == INVALID_SOCKET) {
		closeSocket();
		return false;
	}

	// 设置SOCKET为KEEPALIVE
	if (bKeepAlive)
	{
		int		optval = 1;
		if (setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)))
		{
			closeSocket();
			return false;
		}
	}


	unsigned long serveraddr = inet_addr(pszServerIP);
	if (serveraddr == INADDR_NONE)	// 检查IP地址格式错误
	{
		closeSocket();
		return false;
	}

	sockaddr_in	addr_in;
	memset((void *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nServerPort);
	addr_in.sin_addr.s_addr = serveraddr;

	if (connect(m_sockClient, (sockaddr *)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
		if (hasError()) {
			closeSocket();
			return false;
		}
		else	// WSAWOLDBLOCK
		{
#ifdef WIN32
			DWORD nMode = 1;
			int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
			if (nRes == SOCKET_ERROR) {
				closeSocket();
				return false;
			}
#else
			// 设置为非阻塞方式
			fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
#endif
			timeval timeout;
			timeout.tv_sec = nBlockSec;
			timeout.tv_usec = 0;
			fd_set writeset, exceptset;
			FD_ZERO(&writeset);
			FD_ZERO(&exceptset);
			FD_SET(m_sockClient, &writeset);
			FD_SET(m_sockClient, &exceptset);

			int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
			if (ret == 0 || ret < 0) {
				closeSocket();
				return false;
			}
			else	// ret > 0
			{
				ret = FD_ISSET(m_sockClient, &exceptset);
				if (ret)		// or (!FD_ISSET(m_sockClient, &writeset)
				{
					closeSocket();
					return false;
				}
			}
		}
	}
	return true;
}

bool CTCPClient::SendMsg(void* pBuf, int nSize)
{
	if (pBuf == 0 || nSize <= 0) {
		return false;
	}

	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	if (m_nOutbufLen+nSize > OUTBUFSIZE)
	{
		return false;
	}
	m_nOutbufLen += nSize;
	memcpy(m_bufOutput, pBuf, m_nOutbufLen);
	Flush();
	m_nOutbufLen = 0;
	return true;
}

bool CTCPClient::ReceiveMsg()
{
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	int rcvLen = recvFromSock();
 	if (rcvLen <= 0)
	{
		return false;
	}
	m_nInbufLen += rcvLen;
	return true;
}

bool CTCPClient::isConnected()
{
	if (m_sockClient == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool CTCPClient::hasError()
{
#ifdef WIN32
	int err = WSAGetLastError();
	if (err != WSAEWOULDBLOCK) {
#else
	int err = errno;
	if (err != EINPROGRESS && err != EAGAIN) {
#endif
		return true;
	}

	return false;
}

// 从网络中读取尽可能多的数据，实际向服务器请求数据的地方
int CTCPClient::recvFromSock(void)
{
	if (m_nInbufLen >= INBUFSIZE || m_sockClient == INVALID_SOCKET) {
		return 0 ;
	}
	const int size = INBUFSIZE - m_nInbufLen;
	int inlen = recv(m_sockClient, (char*)m_bufInput + m_nInbufLen, size, 0);
	if (inlen <= 0)
	{
		if (hasError()) {
			return 0;
		}
	}

	return inlen;
}

bool CTCPClient::Flush(void)		// 如果 OUTBUF > SENDBUF 则需要多次SEND（）
{
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	if (m_nOutbufLen <= 0) {
		return false;
	}

	// 发送一段数据
	int	outsize = 0;
	while (outsize < m_nOutbufLen)
	{
		outsize += send(m_sockClient, (char*)m_bufOutput+outsize, m_nOutbufLen-outsize, 0);
		if (outsize <= 0)
		{
			int err = hasError();
#ifdef WIN32
			if (err == 10053)
			{
				log("will reconnecting server!");

			}
#else
			if (err == 60)
			{
				log("will reconnecting server!");
			}
#endif
			//ReconnectServer();
			return false;
		}
	}


	return true;
}

void CTCPClient::ReconnectFunc()
{
	Destroy();
	m_flag = true;
	while (m_flag);
	thread t(&CTCPClient::NetworkThreadFunc, this);
	t.detach();
}


void CTCPClient::ReconnectServer()
{
	//分离子线程
	thread t(&CTCPClient::ReconnectFunc, this);
	t.detach();
}

bool CTCPClient::Check(void)
{
	// 检查状态
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	char buf[1];
	int	ret = recv(m_sockClient, buf, 1, MSG_PEEK);
	if (ret == 0) {
		return false;
	}
	else if (ret < 0) {
		if (hasError()) {
			return false;
		}
		else {	// 阻塞
			return true;
		}
	}
	else {	// 有数据
		return true;
	}

	return true;
}

void CTCPClient::Destroy(void)
{
	closeSocket();

	m_sockClient = INVALID_SOCKET;
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;

	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
}

