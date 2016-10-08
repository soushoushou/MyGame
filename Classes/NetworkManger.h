#pragma once
#include <string>
#include <map>
#include "TCPClient.h"
#include "TCPRequest.h"
#include <deque>
USING_NS_CC;
using namespace std;

//网络通信类
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	static void destroyInstance();

	void shutDownNetwork();
	void startNetwork();

	//发送各种请求，取消回调，因为子线程无法绘制UI
	bool SendRequest_Login(const S_LoginReq& requestData);
	bool SendRequest_CreateUser(const S_CreatePlayerReq& requestData);
	bool SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData);
	bool SendRequest_CreateRoom(const S_CreateRoomReq& requestData);
	bool SendRequest_JoinRoom(const S_JoinRoomReq& requestData);
	bool SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData);
	bool SendRequest_QuitRoom(const S_QuitRoomReq& requestData);
	bool SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData);
	bool SendRequest_FaPai(const S_FaPaiReq& requestData);
	bool SendRequest_TanPai(const S_TanPaiReq& requestData);
	bool SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData);
	bool SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData);
	bool SendRequest_YaZhu(const S_YaZhuReq& requestData);

	//消息队列相关
	bool ackQueueIsEmpty();						//消息队列是否为空
	void pushACKQueue(void* data, int size);	//入队
	void popACKQueue();							//出队
	short getQueueFrontACKCmd();				//获得队头结点的协议号
	void* getQueueFrontACKBinaryData();			//获得对头结点的二进制数据
private:
	NetworkManger();
	bool SendRequest(void* requestData, int size/*, const TCPResponseCallback& responseCallback*/);
private:
	//ACK响应的消息队列
	class CACKResponseQueue
	{
	public:
		void pushACKResponse(void* responseData, int size);		//响应消息入队
		bool isEmpty();											//判空
		void popACKResponse();									//出队
		S_ACKResponse getFrontFromQueue();						//获得队头数据
	protected:
	private:
		deque<S_ACKResponse> m_queue;							//消息队列
	};

	CACKResponseQueue m_ackQueue;			//ack消息队列，用于主线程获得ack响应消息后进行渲染
	static NetworkManger* m_pInstance;
	CTCPClient* m_tcpClient;
	

};


