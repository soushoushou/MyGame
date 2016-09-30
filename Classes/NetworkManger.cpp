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

void NetworkManger::SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback)
{
	CTCPRequest *request = new CTCPRequest;
	request->retain();
	request->setRequestData((char*)requestData, size);
	request->setResponseCallback(responseCallback);
	CTCPClient::getInstance()->sendTCPRequset(request);
	request->release();
}