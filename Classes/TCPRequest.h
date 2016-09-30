#pragma once
#include "cocos2d.h"
#include <thread>
#include <mutex>
using namespace std;
USING_NS_CC;

const int g_nMaxRequsetDataSize = 8 * 1024;
typedef std::function<void(Ref*, void* pResponseData)> TCPResponseCallback;			//响应回调原型

class CTCPRequest:public Ref
{
public:
	CTCPRequest();
	virtual ~CTCPRequest();
	void setResponseCallback(const TCPResponseCallback& callback);
	void setRequestData(char* requestData, int size);
	void runResponseCallback(void* pResponseData);
	void* getRequestData(){ return m_dataBuf; }
	int getRequestDataLen(){ return m_nDataLen; }
private:
	char m_dataBuf[g_nMaxRequsetDataSize];		//数据缓冲
	int m_nDataLen;								//实际数据长度
	TCPResponseCallback m_pCallback;
	mutex m_dataMutex;
	
};

