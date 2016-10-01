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

	//发送各种请求
	void SendRequest_CreateUser(const S_CreatePlayerReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_CreateRoom(const S_CreateRoomReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_JoinRoom(const S_JoinRoomReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_QuitRoom(const S_QuitRoomReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_FaPai(const S_FaPaiReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_TanPai(const S_TanPaiReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData, const TCPResponseCallback& responseCallback);
	void SendRequest_YaZhu(const S_YaZhuReq& requestData, const TCPResponseCallback& responseCallback);

private:
	static NetworkManger* m_pInstance;
	NetworkManger();
	void SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback);

};


