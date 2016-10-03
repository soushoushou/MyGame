#include "NetworkManger.h"
#include "TCPClient.h"
#include "TCPRequest.h"

NetworkManger* NetworkManger::m_pInstance = NULL;

NetworkManger::NetworkManger()
{
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
}



bool NetworkManger::SendRequest_CreateUser(const S_CreatePlayerReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_strAccountLen), 2);
	pIndex += 2;
	for (int i = 0; i <= requestData.m_account.length(); ++i)
	{
		(char)(*pIndex++) = requestData.m_account[i];
	}
	memcpy(pIndex, ((char*)&requestData.m_strRoleNameLen), 2);
	pIndex += 2;
	for (int i = 0; i <= requestData.m_roleName.length(); ++i)
	{
		(char)(*pIndex++) = requestData.m_roleName[i];
	}
	memcpy(pIndex, ((char*)&requestData.m_sex), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_yanZhengMa), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_yanZhengTime), 4);
	pIndex += 4;
	
	//发送
	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete [] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_CreateRoom(const S_CreateRoomReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, (char*)&requestData.m_wantBuy, 4);

	bool ret = false;
	
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;

	return ret;
}

bool NetworkManger::SendRequest_FaPai(const S_FaPaiReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_playerID), 8);

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_JoinRoom(const S_JoinRoomReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_roomID), 4);

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);
	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_QuitRoom(const S_QuitRoomReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_TanPai(const S_TanPaiReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest_YaZhu(const S_YaZhuReq& requestData, const TCPResponseCallback& responseCallback)
{
	//处理数据
	char* dataBuf = new char[requestData.m_packageLen];
	char* pIndex = dataBuf;
	memcpy(pIndex, &requestData, 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_key), 4);
	pIndex += 4;
	memcpy(pIndex, ((char*)&requestData.m_cmd), 2);
	pIndex += 2;
	memcpy(pIndex, ((char*)&requestData.m_beishu), 4);

	bool ret = false;
	ret = SendRequest((void*)(dataBuf), ntohs(requestData.m_packageLen), responseCallback);

	delete[] dataBuf;
	return ret;
}

bool NetworkManger::SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback)
{
	CTCPRequest *request = new CTCPRequest;
	request->retain();
	request->setRequestData((char*)requestData, size);
	request->setResponseCallback(responseCallback);
	bool ret = false;
	ret= m_tcpClient.sendTCPRequset(request);
	request->release();
	return ret;
}