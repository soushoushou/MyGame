#pragma once
#include <string>
#include <map>
#include "network/HttpClient.h"
USING_NS_CC;
using namespace network;
using namespace std;

//网络通信类
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	void SetBaseURL(const string& url);
	//发送请求--创建角色
	//callback = 回调
	void SendRequest_CreateUser(ccHttpRequestCallback callback);
	//发送请求--获取角色信息
	//userID=用户id
	//callback=回调
	void SendRequest_GetUserInfo(unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--创建房间
	//callback=回调
	void SendRequest_CreateRoom(ccHttpRequestCallback callback);
	//发送请求--加入房间
	//roomID=房间ID
	//callback=回调
	void SendRequest_JoinRoom(int roomID, ccHttpRequestCallback callback);
	//发送请求--战绩查询
	//userID=用户ID
	//callback=回调
	void SendRequest_SearchGains(unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--退出房间
	//roomID=房间ID
	//userID=用户ID
	//callback=回调
	void SendRequest_QuitRoom(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--准备
	//roomID=房间ID
	//userID=用户ID
	//callback=回调
	void SendRequest_Ready(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--发牌
	//roomID=房间ID
	//userID=用户ID
	//callback=回调
	void SendRequest_GetPoker(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--摊牌
	//roomID=房间ID
	//userID=用户ID
	//callback=回调
	void SendRequest_ShowPoker(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--钻石充值
	//num=购买的钻石数量
	//userID=用户ID
	//callback=回调
	void SendRequest_AddDiamond(unsigned long long userID, int num,  ccHttpRequestCallback callback);
	//发送请求--抢庒
	//roomID=房间ID
	//userID=用户ID
	//callback=回调
	void SendRequest_QiangZhuang(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//发送请求--下注
	//roomID=房间ID
	//userID=用户ID
	//num=下注倍数
	//callback=回调
	void SendRequest_Bet(int roomID, unsigned long long userID, int num,  ccHttpRequestCallback callback);
private:
	static NetworkManger* m_pInstance;
	NetworkManger(const string& url = string("https://www.baidu.com"));
	void SendRequest(ccHttpRequestCallback, const char* requestData = NULL);
private:
	string m_strBaseUrl;

};


