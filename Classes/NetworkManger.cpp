#include "NetworkManger.h"

NetworkManger* NetworkManger::m_pInstance = NULL;

NetworkManger::NetworkManger(const string& url) :m_strBaseUrl(url)
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

void NetworkManger::SendRequest_AddDiamond(unsigned long long userID, int num, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_Bet(int roomID, unsigned long long userID, int num, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_CreateRoom(ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_CreateUser(ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_GetPoker(int roomID, unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_GetUserInfo(unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_JoinRoom(int roomID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_QiangZhuang(int roomID, unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_QuitRoom(int roomID, unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_Ready(int roomID, unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_SearchGains(unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SendRequest_ShowPoker(int roomID, unsigned long long userID, ccHttpRequestCallback callback)
{
	SendRequest(callback);
}

void NetworkManger::SetBaseURL(const string& url)
{
	m_strBaseUrl = url;
}

void NetworkManger::SendRequest(ccHttpRequestCallback callback, const char* requestData)
{
	HttpRequest* request = new HttpRequest();
	request->setUrl(m_strBaseUrl);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(callback);
	if (requestData != NULL)
	{
		request->setRequestData(requestData, strlen(requestData));
	}
	HttpClient::getInstance()->send(request);
	request->release();
}