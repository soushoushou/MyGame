#include "DebugSimpleServer.h"
#include <iostream>


DebugSimpleServer* DebugSimpleServer::m_pServerInstance = nullptr;

DebugSimpleServer::DebugSimpleServer()
{
	m_alwInRoom = false;
	srand(time(NULL));
	thread t(&DebugSimpleServer::update, this);
	t.detach();
}


DebugSimpleServer::~DebugSimpleServer()
{
	if (this == m_pServerInstance)
	{
		delete m_pServerInstance;
		m_pServerInstance = nullptr;
	}
}

DebugSimpleServer* DebugSimpleServer::getInstance()
{
	if (!m_pServerInstance)
	{
		m_pServerInstance = new DebugSimpleServer();
	}
	return m_pServerInstance;
}

//随机产生用户名
string DebugSimpleServer::createPlayerName()
{
	string result(17, 0);
	for (int i = 0; i < 16; ++i)
	{
		result[i] = char(rand() % 100+1);
	}
	return result;
}

//产生扑克
void DebugSimpleServer::createPoke()
{
	int hash[52] = { 0 };
	if (m_mapPlayer2Pokes.size()>0)
	{
		m_mapPlayer2Pokes.clear();
	}
	for (int i = 0; i < m_vecPlayersInRoom.size(); ++i)
	{
		vector<int> t;
		while (t.size() < 5)
		{
			int index = rand() % 52;
			if (hash[index] == 0)
			{
				t.push_back(index);
				hash[index] = 1;
			}
		}
		m_mapPlayer2Pokes.insert(make_pair(m_vecPlayersInRoom[i],t));
	}
}


//返回扑克
map<string, vector<int>> DebugSimpleServer::getPokes()
{
	if (m_mapPlayer2Pokes.size() == 0)
	{
		createPoke();
	}
	return m_mapPlayer2Pokes;
}


//是否玩家都准备就绪
bool DebugSimpleServer::isAllReady()
{
	m_mutex.lock();
	bool result = (m_vecPlayersInRoom.size() == 5);
	m_mutex.unlock();
	return result;
}

//客户端用户已准备好
void DebugSimpleServer::playerReady(string name)
{
	m_mutex.lock();
	m_vecPlayersInRoom.push_back(name);
	m_alwInRoom = true;
	m_mutex.unlock();
}

void DebugSimpleServer::update()
{
	while (1)
	{
		m_mutex.lock();
		if (m_alwInRoom)
		{
			if (m_vecPlayersInRoom.size() < 5)
			{
				//有概率玩家进入房间
				if (rand() % 10000000 < 1)
				{
					if (rand() % 100 < 1)
					{
						m_vecPlayersInRoom.push_back(createPlayerName());
					}
				}
			}
		}
		else
		{
			if (m_vecPlayersInRoom.size() < 4)
			{
				//有概率玩家进入房间
				if (rand() % 10000000 < 1)
				{
					if (rand() % 100 < 1)
					{
						m_vecPlayersInRoom.push_back(createPlayerName());
					}
				}
			}
		}
	
		m_mutex.unlock();
	}
}