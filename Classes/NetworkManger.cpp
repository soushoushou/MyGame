#include "NetworkManger.h"


NetworkManger::NetworkManger(const string& url) :m_strBaseUrl(url)
{
}


NetworkManger::~NetworkManger()
{
}

void NetworkManger::SendRequest_AddDiamond(unsigned long long userID, int num, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_Bet(int roomID, unsigned long long userID, int num, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_CreateRoom(const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_CreateUser(const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_GetPoker(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_GetUserInfo(unsigned long long userID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_JoinRoom(int roomID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_QiangZhuang(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_QuitRoom(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_Ready(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_SearchGains(unsigned long long userID, const ccHttpRequestCallback& callback)
{

}

void NetworkManger::SendRequest_ShowPoker(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback)
{

}