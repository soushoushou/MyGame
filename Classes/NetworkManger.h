#pragma once
#include <string>
#include <map>
#include "network/HttpClient.h"
#include "TCPClient.h"
#include "TCPRequest.h"
USING_NS_CC;
using namespace network;
using namespace std;

//网络通信类
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	//发送请求--创建角色
	//callback = 回调
	void SendRequest_CreateUser(const S_CreatePlayerReq& requestData, const TCPResponseCallback& responseCallback);
	
private:
	static NetworkManger* m_pInstance;
	NetworkManger();
	void SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback);

};


