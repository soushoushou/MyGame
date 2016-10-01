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


NetworkManger::~NetworkManger()
{
}



void NetworkManger::SendRequest_CreateUser(const S_CreatePlayerReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData),sizeof(requestData),responseCallback);
}

void NetworkManger::SendRequest_CreateRoom(const S_CreateRoomReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_FaPai(const S_FaPaiReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_JoinRoom(const S_JoinRoomReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_QuitRoom(const S_QuitRoomReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_TanPai(const S_TanPaiReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest_YaZhu(const S_YaZhuReq& requestData, const TCPResponseCallback& responseCallback)
{
	SendRequest((void*)(&requestData), sizeof(requestData), responseCallback);
}

void NetworkManger::SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback)
{
	CTCPRequest *request = new CTCPRequest;
	request->retain();
	request->setRequestData((char*)requestData, size);
	request->setResponseCallback(responseCallback);
	CTCPClient::getInstance()->sendTCPRequset(request);
	request->release();
}