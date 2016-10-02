#include "TCPRequest.h"
#include "NetworkPackage.h"
#include <string>
using namespace std;

CTCPRequest::CTCPRequest() :m_nDataLen(0), m_pCallback(nullptr)
{
	m_dataMutex.lock();
	memset(m_dataBuf, 0, g_nMaxRequsetDataSize);
	m_dataMutex.unlock();
}


CTCPRequest::~CTCPRequest()
{
}

int checkCPUendian(){
	union {
		unsigned int a;
		unsigned char b;
	}c;
	c.a = 1;
	return (c.b == 1);
}

void CTCPRequest::setRequestData(char* requestData, int size)
{
	m_dataMutex.lock();
	memset(m_dataBuf, 0, g_nMaxRequsetDataSize);
	if (size > g_nMaxRequsetDataSize)
	{
		m_nDataLen = 0;
		m_dataMutex.unlock();
		return;
	}
	memcpy(m_dataBuf, requestData, size);
	m_nDataLen = size;
	m_dataMutex.unlock();
}

void CTCPRequest::setResponseCallback(const TCPResponseCallback& callback)
{
	m_dataMutex.lock();
	m_pCallback = callback;
	m_dataMutex.unlock();
}

void CTCPRequest::runResponseCallback(void* pResponseData)
{
	m_dataMutex.lock();
	m_pCallback(this,pResponseData);
	m_dataMutex.unlock();
}