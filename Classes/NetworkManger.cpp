#include "NetworkManger.h"
#include "TCPClient.h"
#include "TCPRequest.h"

NetworkManger* NetworkManger::m_pInstance = NULL;

NetworkManger::NetworkManger() :m_tcpClient(nullptr)
{
	m_tcpClient = new CTCPClient;

}


NetworkManger* NetworkManger::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new NetworkManger;
	}
	return m_pInstance;
}

void NetworkManger::destroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
	}
}


NetworkManger::~NetworkManger()
{
	if (nullptr != m_tcpClient)
	{
		delete m_tcpClient;
	}
}



//bool NetworkManger::SendRequest_CreateUser(const S_CreatePlayerReq& requestData)
//{
//	//¥¶¿Ì ˝æ›
//	char* dataBuf = new char[ntohs(requestData.m_packageLen)];
//	char* pIndex = dataBuf;
//	memcpy(pIndex, &requestData.m_cmd, 2);
//	pIndex += 2;
//	memcpy(pIndex, ((char*)&requestData.m_packageLen), 2);
//	pIndex += 2;
//	short len = requestData.m_strAccountLen;
//	memcpy(pIndex, ((char*)&len), 2);
//	len = ntohs(len);
//	pIndex += 2;
//	memcpy(pIndex, requestData.m_account.c_str(), len);
//	pIndex += len;
//	memcpy(pIndex, ((char*)&requestData.m_strRoleNameLen), 2);
//	len = ntohs(requestData.m_strRoleNameLen);
//	pIndex += 2;
//	memcpy(pIndex, requestData.m_roleName.c_str(), len);
//	pIndex += len;
//	memcpy(pIndex, ((char*)&requestData.m_sex), 4);
//	pIndex += 4;
//	memcpy(pIndex, ((char*)&requestData.m_yanZhengMa), 4);
//	pIndex += 4;
//	memcpy(pIndex, ((char*)&requestData.m_yanZhengTime), 4);
//	pIndex += 4;
//	
//	//∑¢ÀÕ
//	bool ret = false;
//	ret = _SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));
//
//	delete [] dataBuf;
//	return ret;
//}

bool NetworkManger::SendRequest(const S_ZZ_WechatLoginReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_strCodeLen), 2);
	pIndex += 2;
	short len = ntohs(requestData.m_strCodeLen);
	memcpy(pIndex, requestData.m_wechatCode.c_str(), len);
	pIndex += len;
	memcpy(pIndex, ((char*)&requestData.m_statusCode), 4);
	pIndex += 4;
	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_CreateRoomReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_playerID), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_mode), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_round), 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_WechatOrderReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, (char*)&requestData.m_diamondNum, 4);
	bool ret = false;
	
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;

	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_FaPaiReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;	
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_GetPlayerInfoReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_playerID), 4);

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_JoinRoomReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_roomID), 4);

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));
	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_QiangZhuangReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, (char*)&requestData.m_isQiang, 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_QuitRoomReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_ReadyPlayReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_SearchZhanjiReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

//bool NetworkManger::SendRequest_SuanNiu(const S_SuanNiuReq& requestData)
//{
//	//¥¶¿Ì ˝æ›
//	char* dataBuf = new char[ntohs(requestData.m_packageLen)];
//	char* pIndex = dataBuf;
//	memcpy(pIndex, &requestData.m_cmd, 2);
//	pIndex += 2;
//	memcpy(pIndex, ((char*)&requestData.m_packageLen), 2);
//	pIndex += 2;
//
//	bool ret = false;
//	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen));
//
//	delete[] dataBuf;
//	return ret;
//}

bool NetworkManger::SendRequest(const S_ZZ_SuanNiuTanPaiReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_YaZhuReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_beishu), 4);

	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}
bool NetworkManger::SendRequest(const S_ZZ_VoiceChatReq& requestData)
{
	//¥¶¿Ì ˝æ›
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_voiceSize), 4);
	pIndex += 4;
	int size = ntohl(requestData.m_voiceSize);
	memcpy(pIndex, ((char*)requestData.m_voiceBuf), size);
	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_RoleLoginReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_statusCode), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_platformTpye), 4);
	pIndex += 4;
	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_ReconnectReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_statusCode), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_roomID), 4);
	pIndex += 4;
	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}


bool NetworkManger::SendRequest(const S_ZZ_QuickChatReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_quickChatSeq), 4);
	pIndex += 4;
	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_InviteReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_inviteCode), 4);
	pIndex += 4;
	bool ret = false;
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_TextChatReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_textLen), 2);
	pIndex += 2;
	bool ret = false;
	memcpy(pIndex, requestData.m_strText.c_str(), ntohs(requestData.m_textLen));
	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_KeepaliveReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_playerID, 4);

	bool ret = false;

	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(const S_ZZ_CheckUpdateReq& requestData)
{
	char* dataBuf = new char[ntohl(requestData.m_packageLen)];
	char* pIndex = dataBuf;
	memcpy(pIndex, ((char*)&requestData.m_packageLen), 4);
	pIndex += 4;
	memcpy(pIndex, &requestData.m_cmd, 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_versionLen, 2);
	pIndex += 2;
	memcpy(pIndex, requestData.m_strVersion.c_str(), ntohs(requestData.m_versionLen));

	bool ret = false;

	ret = _SendRequest((void*)(dataBuf), ntohl(requestData.m_packageLen));

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::_SendRequest(void* requestData, int size)
{
	CTCPRequest *request = new CTCPRequest;
	request->setRequestData((char*)requestData, size);
	bool ret = false;
	ret= m_tcpClient->sendTCPRequset(request);
	delete request;
	return ret;
}

void NetworkManger::shutDownNetwork()
{
	if (m_tcpClient != nullptr)
	{
		m_tcpClient->Destroy();
		m_tcpClient = nullptr;
	}
}

void NetworkManger::startNetwork()
{
	if (m_tcpClient == nullptr)
	{
		m_tcpClient = new CTCPClient;
	}
}

bool  NetworkManger::CACKResponseQueue::isEmpty()
{
	return m_queue.empty();
}

S_ACKResponse* NetworkManger::CACKResponseQueue::getFrontFromQueue()
{
	if (m_queue.empty())
	{
		return nullptr;
	}
	return m_queue.front();
}

void NetworkManger::CACKResponseQueue::pushACKResponse(void* responseData, int size)
{
	S_ACKResponse *s = new S_ACKResponse(responseData, size);
	m_queue.push_back(s);
}

void NetworkManger::CACKResponseQueue::popACKResponse()
{
	if (!m_queue.empty())
	{
		delete m_queue.front();
		m_queue.pop_front();
	}
}

bool NetworkManger::ackQueueIsEmpty()
{
	return m_ackQueue.isEmpty();
}

void NetworkManger::pushACKQueue(void* data, int size)
{
	m_ackQueue.pushACKResponse(data, size);
}

void NetworkManger::popACKQueue()
{
	m_ackQueue.popACKResponse();
}

short NetworkManger::getQueueFrontACKCmd()
{
	short cmd = 0;
	S_ACKResponse *s = m_ackQueue.getFrontFromQueue();
	memcpy(&cmd, s->m_buf+4, 2);
	short tt = ntohs(cmd);
	return tt;
}

void* NetworkManger::getQueueFrontACKBinaryData()
{
	return m_ackQueue.getFrontFromQueue()->m_buf;
}