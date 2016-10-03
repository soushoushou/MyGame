#pragma once
#include <string>
#include <map>
#include "TCPClient.h"
#include "TCPRequest.h"
USING_NS_CC;
using namespace std;

//网络通信类
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	static void destroyInstance();

	//发送各种请求
	bool SendRequest_CreateUser(const S_CreatePlayerReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_CreateRoom(const S_CreateRoomReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_JoinRoom(const S_JoinRoomReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_QuitRoom(const S_QuitRoomReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_FaPai(const S_FaPaiReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_TanPai(const S_TanPaiReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData, const TCPResponseCallback& responseCallback);
	bool SendRequest_YaZhu(const S_YaZhuReq& requestData, const TCPResponseCallback& responseCallback);

private:
	static NetworkManger* m_pInstance;
	NetworkManger();
	bool SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback);
	CTCPClient m_tcpClient;

};


