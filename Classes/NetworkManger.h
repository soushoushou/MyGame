#pragma once
#include <string>
#include <map>
#include "TCPClient.h"
#include "TCPRequest.h"
#include <deque>
USING_NS_CC;
using namespace std;

const int g_popRadio = 45;				//心跳频率

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
	bool SendRequest(const S_ZZ_WechatLoginReq& requestData);
	bool SendRequest(const S_ZZ_RoleLoginReq& requestData);
	bool SendRequest(const S_ZZ_ReconnectReq& requestData);
	//bool SendRequest(const S_ZZ_CreatePlayerReq& requestData);
	bool SendRequest(const S_ZZ_GetPlayerInfoReq& requestData);
	bool SendRequest(const S_ZZ_CreateRoomReq& requestData);
	bool SendRequest(const S_ZZ_JoinRoomReq& requestData);
	bool SendRequest(const S_ZZ_SearchZhanjiReq& requestData);
	bool SendRequest(const S_ZZ_QuitRoomReq& requestData);
	bool SendRequest(const S_ZZ_ReadyPlayReq& requestData);
	//bool SendRequest(const S_ZZ_FaPaiReq& requestData);
	bool SendRequest(const S_ZZ_SuanNiuTanPaiReq& requestData);
	bool SendRequest(const S_ZZ_QuickChatReq& requestData);
	//bool SendRequest(const S_ZZ_SuanNiuReq& requestData);
	bool SendRequest(const S_ZZ_WechatOrderReq& requestData);
	bool SendRequest(const S_ZZ_QiangZhuangReq& requestData);
	bool SendRequest(const S_ZZ_YaZhuReq& requestData);
	bool SendRequest(const S_ZZ_VoiceChatReq& requestData);
	bool SendRequest(const S_ZZ_InviteReq& requestData);
	bool SendRequest(const S_ZZ_TextChatReq& requestData);
	bool SendRequest(const S_ZZ_KeepaliveReq& requestData);
	bool SendRequest(const S_ZZ_CheckUpdateReq& requestData);

	//消息队列相关
	bool ackQueueIsEmpty();						//消息队列是否为空
	void pushACKQueue(void* data, int size);	//入队
	void popACKQueue();							//出队
	unsigned short getQueueFrontACKCmd();				//获得队头结点的协议号
	void* getQueueFrontACKBinaryData();			//获得对头结点的二进制数据
private:
	NetworkManger();
	bool _SendRequest(void* requestData, int size);
private:
	//ACK响应的消息队列
	class CACKResponseQueue
	{
	public:
		void pushACKResponse(void* responseData, int size);		//响应消息入队
		bool isEmpty();											//判空
		void popACKResponse();									//出队
		S_ACKResponse* getFrontFromQueue();						//获得队头数据
	protected:
	private:
		deque<S_ACKResponse*> m_queue;							//消息队列
	};

	CACKResponseQueue m_ackQueue;			//ack消息队列，用于主线程获得ack响应消息后进行渲染
	static NetworkManger* m_pInstance;
	CTCPClient* m_tcpClient;

};


