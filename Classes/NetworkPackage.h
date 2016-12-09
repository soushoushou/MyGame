#pragma once
#include <string>
#include <vector>
#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif
using namespace std;
//包宏
#define PP_DOUNIU_CREAT_ACCOUNT_REQ	(10000)
#define PP_DOUNIU_CREAT_ACCOUNT_ACK	(10001)
#define PP_DOUNIU_GET_ROLEINFO_REQ	(10002)
#define PP_DOUNIU_GET_ROLEINFO_ACK	(10003)
#define PP_DOUNIU_LOGIN_ACCOUNT_REQ	(10004)
#define PP_DOUNIU_LOGIN_ACCOUNT_ACK	(10005)
#define PP_DOUNIU_CREATE_ROOM_REQ	(50000)
#define PP_DOUNIU_CREATE_ROOM_ACK	(50001)
#define PP_DOUNIU_JOIN_ROOM_REQ		(50002)
#define PP_DOUNIU_JOIN_ROOM_ACK		(50003)
#define PP_DOUNIU_QUERY_ZHANJI_REQ	(50004)
#define PP_DOUNIU_QUERY_ZHANJI_ACK	(50005)
#define PP_DOUNIU_QUIT_ROOM_REQ		(50006)
#define PP_DOUNIU_QUIT_ROOM_ACK		(50007)
#define PP_DOUNIU_READY_REQ			(50008)
#define PP_DOUNIU_READY_ACK			(50009)
#define PP_DOUNIU_FAPAI_REQ			(50010)
#define PP_DOUNIU_FAPAI_ACK			(50011)
#define PP_DOUNIU_SUANNIU_REQ		(50012)
#define PP_DOUNIU_SUANNIU_ACK		(50013)
#define PP_DOUNIU_CHONGZHI_REQ		(50014)
#define PP_DOUNIU_CHONGZHI_ACK		(50015)
#define PP_DOUNIU_QIANGZHUANG_REQ	(50016)
#define PP_DOUNIU_QIANGZHUANG_ACK	(50017)
#define PP_DOUNIU_YAZHU_REQ			(50018)
#define PP_DOUNIU_YAZHU_ACK			(50019)
#define PP_DOUNIU_QUICK_CHAT_REQ	(50020)
#define PP_DOUNIU_QUICK_CHAT_ACK	(50021)
#define PP_DOUNIU_VOICE_CHAT_REQ	(50022)
#define PP_DOUNIU_VOICE_CHAT_ACK	(50023)
#define PP_DOUNIU_MEMBER_INFO_ACK	(50024)	
#define PP_DOUNIU_GAME_START_ACK	(50025)
#define PP_DOUNIU_GAME_OVER_ACK		(50026)
#define PP_DOUNIU_TANPAI_ACK		(50027)
#define PP_DOUNIU_TANPAI_REQ		(50028) //�����ʱ��ܣ��ȵ�����ɾ��


/////////////////////////////////////////////////////////////////////////////////
#define PP_ZZ_DOUNIU_WECHAT_LOGIN_REQ	(10000)
#define PP_ZZ_DOUNIU_WECHAT_LOGIN_ACK	(10001)
#define PP_ZZ_DOUNIU_GET_FOLEINFO_REQ	(10002)
#define PP_ZZ_DOUNIU_GET_FOLEINFO_ACK	(10003)
#define PP_ZZ_DOUNIU_ROLE_LOGIN_REQ	(10004)
#define PP_ZZ_DOUNIU_ROLE_LOGIN_ACK	(10005)
#define PP_ZZ_DOUNIU_CREATE_ROOM_REQ	(50000)
#define PP_ZZ_DOUNIU_CREATE_ROOM_ACK	(50001)
#define PP_ZZ_DOUNIU_JOIN_ROOM_REQ		(50002)
#define PP_ZZ_DOUNIU_JOIN_ROOM_ACK		(50003)
#define PP_ZZ_DOUNIU_QUERY_ZHANJI_REQ	(50004)
#define PP_ZZ_DOUNIU_QUERY_ZHANJI_ACK	(50005)
#define PP_ZZ_DOUNIU_QUIT_ROOM_REQ		(50006)
#define PP_ZZ_DOUNIU_QUIT_ROOM_ACK		(50007)
#define PP_ZZ_DOUNIU_READY_REQ			(50008)
#define PP_ZZ_DOUNIU_READY_ACK			(50009)
#define PP_ZZ_DOUNIU_FAPAI_REQ			(50010)
#define PP_ZZ_DOUNIU_FAPAI_ACK			(50011)
#define PP_ZZ_DOUNIU_TANPAI_REQ		(50012)
#define PP_ZZ_DOUNIU_TANPAI_ACK		(50013)
#define PP_ZZ_DOUNIU_WECHAT_ORDER_REQ		(50014)
#define PP_ZZ_DOUNIU_WECHAT_ORDER_ACK		(50015)
#define PP_ZZ_DOUNIU_QIANGZHUANG_REQ	(50016)
#define PP_ZZ_DOUNIU_QIANGZHUANG_ACK	(50017)
#define PP_ZZ_DOUNIU_YAZHU_REQ			(50018)
#define PP_ZZ_DOUNIU_YAZHU_ACK			(50019)
#define PP_ZZ_DOUNIU_QUICK_CHAT_REQ	(50020)
#define PP_ZZ_DOUNIU_QUICK_CHAT_ACK	(50021)
#define PP_ZZ_DOUNIU_VOICE_CHAT_REQ	(50022)
#define PP_ZZ_DOUNIU_VOICE_CHAT_ACK	(50023)
#define PP_ZZ_DOUNIU_MEMBER_INFO_NOTIFY	(50024)	
#define PP_ZZ_DOUNIU_GAME_START_ACK	(50025)
#define PP_ZZ_DOUNIU_GAME_OVER_ACK		(50026)
#define PP_ZZ_DOUNIU_INVITE_CODE_REQ		(50027)
#define PP_ZZ_DOUNIU_INVITE_CODE_ACK		(50028)
#define PP_ZZ_DOUNIU_NOTICE_INFO_NOTIFY		(50029)
#define PP_ZZ_DOUNIU_SHARE_INFO_NOTIFY		(50030)
#define PP_ZZ_DOUNIU_ORDER_RESULT_REQ		(50031)
#define PP_ZZ_DOUNIU_ORDER_RESULT_ACK		(50032)
#define PP_ZZ_DOUNIU_TEXT_CHAT_REQ		(50033)
#define PP_ZZ_DOUNIU_TEXT_CHAT_ACK		(50034)
#define PP_ZZ_DOUNIU_KEEP_ALIVE_REQ		(50035)
#define PP_ZZ_DOUNIU_KEEP_ALIVE_ACK		(50036)


//8字节主机序转网络�?
unsigned long long my_htonll(unsigned long long val);

//8字节网络序转主机�?
unsigned long long my_ntohll(unsigned long long val);

//响应数据�?
struct S_ACKResponse
{
	S_ACKResponse(){
		memset(m_buf, 0, 1000*1024);
		m_len = 0;
	}
	S_ACKResponse(void* data, int size)
	{
		memset(m_buf, 0, 1000 * 1024);
		memcpy(m_buf, data, size);
		m_len = size;
	}
	S_ACKResponse(const S_ACKResponse& s)
	{
		if (this == &s)
		{
			return;
		}
		memcpy(m_buf, s.m_buf, s.m_len);
		m_len = s.m_len;
	}
	S_ACKResponse operator = (S_ACKResponse& s)
	{
		if (this == &s)
		{
			return *this;
		}
		memcpy(m_buf, s.m_buf, s.m_len);
		m_len = s.m_len;
		return *this;
	}
	~S_ACKResponse()
	{
		int i = 0;
	}
	char m_buf[1000 * 1024];
	int m_len;
};

//包结�?
//创建角色请求
#pragma pack(1)
struct S_CreatePlayerReq
{
	S_CreatePlayerReq(string account, string roleName, int sex) :m_cmd(PP_DOUNIU_CREAT_ACCOUNT_REQ),
		m_account(account), m_roleName(roleName),m_sex(sex), m_yanZhengMa(1), m_yanZhengTime(1)
	{
		m_strAccountLen = m_account.length()+1;
		m_strRoleNameLen = m_roleName.length()+1;
		m_packageLen = 4 + 4 + 2 + m_strAccountLen + 2 + m_strRoleNameLen + 4 + 4 + 4;
		//转换字节�?
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_strAccountLen = htons(m_strAccountLen);
		m_strRoleNameLen = htons(m_strRoleNameLen);
		m_sex = htonl(m_sex);
		m_yanZhengMa = htonl(m_yanZhengMa);
		m_yanZhengTime = htonl(m_yanZhengTime);

	}
	short m_packageLen;						//包长
	unsigned short m_cmd;							//协议�?
	short m_strAccountLen;					//账号长度
	string m_account;						//账号
	short m_strRoleNameLen;					//角色名长�?
	string m_roleName;						//角色�?
	int m_sex;								//性别
	int m_yanZhengMa;						//验证�?
	int m_yanZhengTime;						//验证时间
};

//创建角色响应
struct S_CreatePlayerACK
{
	S_CreatePlayerACK() :m_packageLen(8),m_cmd(0),m_statusCode(0){}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_CreatePlayerACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_CreatePlayerACK s;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;				//0失败�?成功�?敏感�?
};
//登录请求
struct S_LoginReq
{
	S_LoginReq(string nickName,int checkTime,int checkNum) :m_cmd(PP_DOUNIU_LOGIN_ACCOUNT_REQ),
		 m_roleName(nickName),m_checkTime(checkTime),m_checkNum(checkNum)
	{
		m_strRoleNameLen = m_roleName.length() + 1;
		m_packageLen = 14 + m_strRoleNameLen;
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_checkTime = htonl(checkTime);
		m_checkNum = htonl(checkNum);
		m_strRoleNameLen=htons(m_strRoleNameLen);
	}
	unsigned short m_cmd;
	unsigned short m_packageLen;
	int m_checkTime;
	int m_checkNum;
	short m_strRoleNameLen;
	string m_roleName;
};
//获取登录响应
struct S_LoginACK
{
	S_LoginACK() :m_cmd(0) {}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_LoginACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_LoginACK s;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;		
		memcpy(&s.m_packageLen, pData, 2);

		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		memcpy(&s.m_userID, pData, 8);
		s.m_userID = my_ntohll((unsigned long long)(s.m_userID));
		pData += 8;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memset(buf, 0, 1024);
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_sex, pData, 4);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;
	unsigned long long m_playerID;
	unsigned long long m_userID;			//��֪����ʲô����
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
};
//获取角色信息请求
struct S_GetPlayerInfoReq
{
	S_GetPlayerInfoReq(unsigned long long playerID) :m_cmd(PP_DOUNIU_GET_ROLEINFO_REQ), m_packageLen(4 + sizeof(m_playerID)),
	m_playerID(playerID)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	short m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//获取角色信息响应
struct S_GetPlayerInfoACK
{
	S_GetPlayerInfoACK() :m_cmd(0){}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_GetPlayerInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_GetPlayerInfoACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_sex, pData, 4);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		memcpy(&s.m_currentDiamond, pData, 4);
		s.m_currentDiamond = ntohl(s.m_currentDiamond);
		pData += 4;
		memcpy(&s.m_currentMoney, pData, 4);
		s.m_currentMoney = ntohl(s.m_currentMoney);
		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
	int m_currentMoney;
};

//创建房间请求
struct S_CreateRoomReq
{
	S_CreateRoomReq() :m_cmd(PP_DOUNIU_CREATE_ROOM_REQ),m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
};

//创建房间响应
struct S_CreateRoomACK
{
	S_CreateRoomACK() :m_cmd(0){}

	static S_CreateRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_CreateRoomACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;
	int m_roomID;
};

//加入房间请求
struct S_JoinRoomReq
{
	S_JoinRoomReq(int roomID) :m_cmd(PP_DOUNIU_JOIN_ROOM_REQ),m_packageLen(8)
	{
		m_roomID = htonl(roomID);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_roomID;
};

//加入房间响应
struct S_JoinRoomACK
{
	S_JoinRoomACK() :m_cmd(0), m_isOK(0){}

	static S_JoinRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_JoinRoomACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_isOK;					//0失败�?成功
	int m_roomID;
};

//查询战绩请求
struct S_SearchZhanjiReq
{
	S_SearchZhanjiReq() :m_cmd(PP_DOUNIU_QUERY_ZHANJI_REQ),m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
};

//查询战绩响应
struct S_SearchZhanjiACK
{
	S_SearchZhanjiACK() :m_cmd(0){}

	static S_SearchZhanjiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_SearchZhanjiACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		int nums = (s.m_packageLen - 4) / 8;
		for (int i = 0; i < nums; ++i)
		{
			int room, score;
			memcpy(&room, pData, 4);
			room = ntohl(room);
			pData += 4;
			memcpy(&score, pData, 4);
			score = ntohl(score);
			pData += 4;
			s.m_roomIDs.push_back(room);
			s.m_scores.push_back(score);
		}
		return s;
	}

	unsigned short m_packageLen;
	unsigned short m_cmd;
	vector<int> m_roomIDs;				//����id
	vector<int> m_scores;				//�����Ӧ�Ļ���
};


//退出房间请�?
struct S_QuitRoomReq
{
	S_QuitRoomReq() :m_cmd(PP_DOUNIU_QUIT_ROOM_REQ),m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}

	short m_packageLen;
	unsigned short m_cmd;
};

//退出房间响�?
struct S_QuitRoomACK
{
	S_QuitRoomACK() :m_cmd(0), m_isOK(0){}

	static S_QuitRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_QuitRoomACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_isOK;			//0失败�?成功
	int m_roomID;
	unsigned long long m_playerID;
};

//准备游戏请求
struct S_ReadyPlayReq
{
	S_ReadyPlayReq() :m_cmd(PP_DOUNIU_READY_REQ), m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
};

//准备游戏响应
struct S_ReadyPlayACK
{
	S_ReadyPlayACK() :m_cmd(0){}

	static S_ReadyPlayACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ReadyPlayACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_isOK;						//0失败�?成功
	unsigned long long m_playerID;
};

//发牌请求
struct S_FaPaiReq
{
	S_FaPaiReq() :m_cmd(PP_DOUNIU_FAPAI_REQ),m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
};

//发牌响应
struct S_FaPaiACK
{
	S_FaPaiACK() :m_cmd(0){}

	static S_FaPaiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_FaPaiACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		int nPlayers = (s.m_packageLen - 8) / 28;
		for (int i = 0; i < nPlayers; ++i)
		{
			unsigned long long playerID = 0;
			memcpy(&playerID, pData, 8);
			playerID = my_ntohll(playerID);
			s.m_playerID.push_back(playerID);
			pData += 8;
			for (int j = 0; j < 5; ++j)
			{
				int poker = 0;
				memcpy(&poker, pData, 4);
				pData += 4;
				poker = ntohl(poker);
				s.m_pokers.push_back(poker);
			}
		}
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;				//0�ɹ�1ʧ��
	vector<unsigned long long> m_playerID;
	vector<int> m_pokers;
};

//摊牌请求
struct S_TanPaiReq
{
	S_TanPaiReq() :m_cmd(PP_DOUNIU_TANPAI_REQ),m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
};

//摊牌响应
struct S_TanPaiACK
{
	S_TanPaiACK() :m_cmd(0){}

	static S_TanPaiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_TanPaiACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		int nPlayers = (s.m_packageLen - 8) / 16;
		for (int i = 0; i < nPlayers; ++i)
		{
			unsigned long long playerID = 0;
			memcpy(&playerID, pData, 8);
			playerID = my_ntohll(playerID);
			s.m_playerID.push_back(playerID);
			pData += 8;
			int winOrLose = 0;
			memcpy(&winOrLose, pData, 4);
			pData += 4;
			winOrLose = ntohl(winOrLose);
			s.m_winOrLose.push_back(winOrLose);
			int score = 0;
			memcpy(&score, pData, 4);
			pData += 4;
			score = ntohl(score);
			s.m_score.push_back(score);
		}

		return s;
	}
	
	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;				//0�ɹ�1ʧ��
	vector<unsigned long long> m_playerID;
	vector<int> m_winOrLose;
	vector<int> m_score;
};

//冲钻石请�?
struct S_BuyDiamondReq
{
	S_BuyDiamondReq(int type, int wantBuy) :m_cmd(PP_DOUNIU_CHONGZHI_REQ), m_packageLen(12), m_wantBuy(0), m_wantType(type)
	{
		m_wantBuy = htonl(wantBuy);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_wantType = htonl(m_wantType);

	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_wantType;					//0��ʯ��1���
	int m_wantBuy;					//��ֵ����
};

//冲钻石响�?
struct S_BuyDiamondACK
{
	S_BuyDiamondACK() :m_cmd(0), m_isOK(0), m_currentNum(0){}

	static S_BuyDiamondACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_BuyDiamondACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_buyType, pData, 4);
		s.m_buyType = ntohl(s.m_buyType);
		pData += 4;
		memcpy(&s.m_currentNum, pData, 4);
		s.m_currentNum = ntohl(s.m_currentNum);
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_isOK;
	int m_buyType;				//0��ʯ��1���
	int m_currentNum;			//��ʯ����
};

//抢庒请求
struct S_QiangZhuangReq
{
	S_QiangZhuangReq(int isQiang) :m_cmd(PP_DOUNIU_QIANGZHUANG_REQ),m_packageLen(4){
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		isQiang = htonl(isQiang);
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_isQiang;					//�Ƿ�����,0��1����
};

//抢庒响应
struct S_QiangZhuangACK
{
	S_QiangZhuangACK() :m_cmd(0),m_ZhuangJiaID(0){}

	static S_QiangZhuangACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_QiangZhuangACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		if (s.m_statusCode == 0)
		{
			memcpy(&s.m_ZhuangJiaID, pData, 8);
			s.m_ZhuangJiaID = my_ntohll(s.m_ZhuangJiaID);
		}
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;						//0�ɹ�1ʧ��
	unsigned long long m_ZhuangJiaID;
};

//押注请求
struct S_YaZhuReq
{
	S_YaZhuReq(int beishu) :m_cmd(PP_DOUNIU_YAZHU_REQ),m_packageLen(8){
		m_beishu = htonl(beishu);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_beishu;
};

//押注响应
struct S_YaZhuACK
{
	S_YaZhuACK() :m_cmd(0){}

	static S_YaZhuACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_YaZhuACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = my_ntohll(s.m_isOK);

		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_isOK;
};

//�������
struct S_QuickChatReq 
{
	S_QuickChatReq(int quickChatSeq) :m_cmd(PP_DOUNIU_QUICK_CHAT_REQ), m_packageLen(8)
	{
		m_quickChatSeq = htonl(m_quickChatSeq);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_quickChatSeq;			//�������
};

struct S_QuickChatACK
{
	S_QuickChatACK() :m_cmd(0){}

	static S_QuickChatACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_QuickChatACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_quickChatSeq, pData, 4);
		s.m_quickChatSeq = ntohl(s.m_quickChatSeq);

		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_quickChatSeq;			//�������
};

//��������
struct S_VoiceChatReq
{
	S_VoiceChatReq(char* voiceBinaryData, int size) :m_cmd(PP_DOUNIU_VOICE_CHAT_REQ), m_voiceSize(size), m_voiceBuf(0)
	{
		m_packageLen = htonl(10 + m_voiceSize);
		m_cmd = htons(m_cmd);
		m_voiceSize = htonl(m_voiceSize);
		m_voiceBuf = new char[size];
		memcpy(m_voiceBuf, voiceBinaryData, size);
	}
	~S_VoiceChatReq()
	{
		if (m_voiceBuf)
		{
			delete[] m_voiceBuf;
			m_voiceBuf = 0;
		}
		
	}
	unsigned short m_cmd;
	unsigned int m_packageLen;
	unsigned int m_voiceSize;			//�������������ݴ�С
	char* m_voiceBuf;				//��������
};

struct S_VoiceChatACK
{
	S_VoiceChatACK() :m_cmd(0),m_voiceBuf(0){}
	S_VoiceChatACK(const S_VoiceChatACK& a)
	{
		this->m_packageLen = a.m_packageLen;
		this->m_cmd = a.m_cmd;
		this->m_voiceSize = a.m_voiceSize;
		this->m_voiceBuf = new char[this->m_voiceSize];
		memcpy(this->m_voiceBuf, a.m_voiceBuf, this->m_voiceSize);
	}
	static S_VoiceChatACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_VoiceChatACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_voiceSize, pData, 4);
		s.m_voiceSize = ntohl(s.m_voiceSize);
		pData += 4;
		s.m_voiceBuf = new char[s.m_voiceSize];
		memcpy(s.m_voiceBuf, (char*)pData, s.m_voiceSize);
		return s;
	}
	~S_VoiceChatACK()
	{
		if (m_voiceBuf)
		{
			delete[] m_voiceBuf;
			m_voiceBuf = 0;
		}
		
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned int m_voiceSize;			//�������������ݴ�С
	char* m_voiceBuf;				//��������
};

//in game
struct S_GetMemberInfoACK
{
	S_GetMemberInfoACK() :m_cmd(0){}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_GetMemberInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_GetMemberInfoACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_sex, pData, 4);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		memcpy(&s.m_currentDiamond, pData, 4);
		s.m_currentDiamond = ntohl(s.m_currentDiamond);
		pData += 4;
		memcpy(&s.m_currentMoney, pData, 4);
		s.m_currentMoney = ntohl(s.m_currentMoney);
		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
	int m_currentMoney;
};
//��ţ
struct S_SuanNiuReq
{
	S_SuanNiuReq() :m_cmd(PP_DOUNIU_SUANNIU_REQ), m_packageLen(4)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	unsigned short m_cmd;
};

struct S_SuanNiuACK
{
	S_SuanNiuACK() :m_cmd(0), m_playerID(0),m_niu(0) {}

	static S_SuanNiuACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_SuanNiuACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		if (s.m_statusCode == 0)
		{
			memcpy(&s.m_playerID, pData, 8);
			s.m_playerID = my_ntohll(s.m_playerID);
			memcpy(&s.m_niu, pData, 4);
			s.m_niu = my_ntohll(s.m_niu);
		}
		return s;
	}

	short m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;						//0�ɹ�1ʧ��
	unsigned long long m_playerID;
	int m_niu;
};
//��Ϸ��ʼ
struct S_GameStartACK 
{
	S_GameStartACK() :m_cmd(0){}
	static S_GameStartACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_GameStartACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
};

struct S_GameOverACK
{
	S_GameOverACK() :m_cmd(0){}
	static S_GameOverACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_GameOverACK s;

		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_winCount, pData, 4);
		s.m_winCount = ntohl(s.m_winCount);
		pData += 4;
		memcpy(&s.m_loseCount, pData, 4);
		s.m_loseCount = ntohl(s.m_loseCount);
		pData += 4;
		memcpy(&s.m_totalScore, pData, 4);
		s.m_totalScore = ntohl(s.m_totalScore);
		return s;
	}
	short m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	int m_winCount;					//ʤ������
	int m_loseCount;				//ʧ�ܴ���
	int m_totalScore;				//�þ��ܻ���

};






//////////////////////////////////////////////////
struct S_ZZ_CreatePlayerReq
{
	S_ZZ_CreatePlayerReq(string account, string roleName, int sex) :m_cmd(PP_DOUNIU_CREAT_ACCOUNT_REQ),
		m_account(account), m_roleName(roleName), m_sex(sex), m_yanZhengMa(1), m_yanZhengTime(1)
	{
		m_strAccountLen = m_account.length() + 1;
		m_strRoleNameLen = m_roleName.length() + 1;
		m_packageLen = sizeof(m_packageLen)*6 + sizeof(m_cmd) + m_strAccountLen + m_strRoleNameLen;
		//转换字节�?
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_strAccountLen = htonl(m_strAccountLen);
		m_strRoleNameLen = htonl(m_strRoleNameLen);
		m_sex = htonl(m_sex);
		m_yanZhengMa = htonl(m_yanZhengMa);
		m_yanZhengTime = htonl(m_yanZhengTime);

	}
	unsigned int m_packageLen;						//包长
	unsigned short m_cmd;							//协议�?
	unsigned short m_strAccountLen;					//账号长度
	string m_account;						//账号
	unsigned short m_strRoleNameLen;					//角色名长�?
	string m_roleName;						//角色�?
	int m_sex;								//性别
	int m_yanZhengMa;						//验证�?
	int m_yanZhengTime;						//验证时间
};

//创建角色响应
struct S_ZZ_CreatePlayerACK
{
	S_ZZ_CreatePlayerACK() :m_packageLen(10), m_cmd(0), m_statusCode(0){}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_ZZ_CreatePlayerACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_CreatePlayerACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;				//0失败�?成功�?敏感�?
};

//΢�ŵ�¼����
struct S_ZZ_WechatLoginReq
{
	S_ZZ_WechatLoginReq(string wechatCode, int checkTime, int checkNum) :m_cmd(PP_ZZ_DOUNIU_WECHAT_LOGIN_REQ),
		m_wechatCode(wechatCode), m_checkTime(checkTime), m_checkNum(checkNum)
	{
		m_strCodeLen = m_wechatCode.length() + 1;
		m_packageLen = 16 + m_strCodeLen;
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_checkTime = htonl(checkTime);
		m_checkNum = htonl(checkNum);
		m_strCodeLen = htons(m_strCodeLen);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned short m_strCodeLen;
	string m_wechatCode;
	int m_checkTime;
	int m_checkNum;
};
//获取登录响应
struct S_ZZ_LoginACK
{
	S_ZZ_LoginACK() :m_cmd(0) {}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_ZZ_LoginACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_LoginACK s;
		memcpy(&s.m_packageLen, pData, 4);
		pData += 4;
		s.m_packageLen = ntohl(s.m_packageLen);
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memset(buf, 0, 1024);
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_profileLen, pData, 2);
		s.m_profileLen = ntohs(s.m_profileLen);
		pData += 2;
		char buf2[65535];
		memset(buf2, 0, 65535);
		memcpy(buf2, pData, s.m_playerNameLen);
		s.m_strProfile = buf2;
		pData += s.m_profileLen;
		memcpy(&s.m_sex, pData, 4);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;
	unsigned long long m_playerID;
	short m_playerNameLen;
	string m_strPlayerName;
	short m_profileLen;
	string m_strProfile;
	int m_sex;
};
//获取角色信息请求
struct S_ZZ_GetPlayerInfoReq
{
	S_ZZ_GetPlayerInfoReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_GET_FOLEINFO_REQ), m_packageLen(6 + sizeof(m_playerID)),
		m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//获取角色信息响应
struct S_ZZ_GetPlayerInfoACK
{
	S_ZZ_GetPlayerInfoACK() :m_cmd(0){}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_ZZ_GetPlayerInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_GetPlayerInfoACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_sex, pData, 4);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		memcpy(&s.m_currentDiamond, pData, 4);
		s.m_currentDiamond = ntohl(s.m_currentDiamond);
		pData += 4;
		memcpy(&s.m_currentMoney, pData, 4);
		s.m_currentMoney = ntohl(s.m_currentMoney);
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned int m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
	int m_currentMoney;
};

//��ɫ��¼����
struct S_ZZ_RoleLoginReq
{
	S_ZZ_RoleLoginReq(unsigned long long playerID, int checkTime, int checkNum) :m_cmd(PP_ZZ_DOUNIU_ROLE_LOGIN_REQ),
		m_playerID(playerID), m_checkTime(checkTime), m_checkNum(checkNum)
	{
		m_packageLen = 22;
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_checkTime = htonl(checkTime);
		m_checkNum = htonl(checkNum);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	int m_checkTime;
	int m_checkNum;
};

//��ɫ��¼ack
struct S_ZZ_RoleLoginACK
{
	S_ZZ_RoleLoginACK() :m_cmd(0) {}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_ZZ_RoleLoginACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_RoleLoginACK s;
		memcpy(&s.m_packageLen, pData, 4);
		pData += 4;
		s.m_packageLen = ntohl(s.m_packageLen);
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;
	unsigned long long m_playerID;
};

//创建房间请求
struct S_ZZ_CreateRoomReq
{
	S_ZZ_CreateRoomReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_CREATE_ROOM_REQ), m_packageLen(14)
		, m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//创建房间响应
struct S_ZZ_CreateRoomACK
{
	S_ZZ_CreateRoomACK() :m_cmd(0){}

	static S_ZZ_CreateRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_CreateRoomACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;
	int m_roomID;
};

//加入房间请求
struct S_ZZ_JoinRoomReq
{
	S_ZZ_JoinRoomReq(unsigned long long playerID, int roomID) :m_cmd(PP_ZZ_DOUNIU_JOIN_ROOM_REQ), m_packageLen(18),
		m_playerID(playerID)
	{
		m_roomID = htonl(roomID);
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_roomID;
	unsigned long long m_playerID;
};

//加入房间响应
struct S_ZZ_JoinRoomACK
{
	S_ZZ_JoinRoomACK() :m_cmd(0), m_isOK(0){}

	static S_ZZ_JoinRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_JoinRoomACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_isOK;					//0失败�?成功
	int m_roomID;
};

//查询战绩请求
struct S_ZZ_SearchZhanjiReq
{
	S_ZZ_SearchZhanjiReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_QUERY_ZHANJI_REQ), 
		m_packageLen(14), m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//查询战绩响应
struct S_ZZ_SearchZhanjiACK
{
	S_ZZ_SearchZhanjiACK() :m_cmd(0){}

	static S_ZZ_SearchZhanjiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_SearchZhanjiACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		int nums = (s.m_packageLen - 4) / 8;
		for (int i = 0; i < nums; ++i)
		{
			int room, score;
			memcpy(&room, pData, 4);
			room = ntohl(room);
			pData += 4;
			memcpy(&score, pData, 4);
			score = ntohl(score);
			pData += 4;
			s.m_roomIDs.push_back(room);
			s.m_scores.push_back(score);
		}
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	vector<int> m_roomIDs;				//����id
	vector<int> m_scores;				//�����Ӧ�Ļ���
};


//退出房间请�?
struct S_ZZ_QuitRoomReq
{
	S_ZZ_QuitRoomReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_QUIT_ROOM_REQ), 
		m_playerID(playerID),m_packageLen(14)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//退出房间响�?
struct S_ZZ_QuitRoomACK
{
	S_ZZ_QuitRoomACK() :m_cmd(0), m_isOK(0){}

	static S_ZZ_QuitRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_QuitRoomACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_isOK;			//0失败�?成功
	int m_roomID;
	unsigned long long m_playerID;
};

//准备游戏请求
struct S_ZZ_ReadyPlayReq
{
	S_ZZ_ReadyPlayReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_READY_REQ), m_packageLen(14),
		m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//准备游戏响应
struct S_ZZ_ReadyPlayACK
{
	S_ZZ_ReadyPlayACK() :m_cmd(0){}

	static S_ZZ_ReadyPlayACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_ReadyPlayACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_isOK;						//0失败�?成功
	unsigned long long m_playerID;
};

//发牌请求
struct S_ZZ_FaPaiReq
{
	S_ZZ_FaPaiReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_FAPAI_REQ), m_packageLen(14),
		m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//发牌响应
struct S_ZZ_FaPaiACK
{
	S_ZZ_FaPaiACK() :m_cmd(0){}

	static S_ZZ_FaPaiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_FaPaiACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		int nPlayers = (s.m_packageLen - 8) / 28;
		for (int i = 0; i < nPlayers; ++i)
		{
			unsigned long long playerID = 0;
			memcpy(&playerID, pData, 8);
			playerID = my_ntohll(playerID);
			s.m_playerID.push_back(playerID);
			pData += 8;
			for (int j = 0; j < 5; ++j)
			{
				int poker = 0;
				memcpy(&poker, pData, 4);
				pData += 4;
				poker = ntohl(poker);
				s.m_pokers.push_back(poker);
			}
		}
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;				//0�ɹ�1ʧ��
	vector<unsigned long long> m_playerID;
	vector<int> m_pokers;
};

//摊牌请求
struct S_ZZ_TanPaiReq
{
	S_ZZ_TanPaiReq(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_TANPAI_REQ), m_packageLen(14),
		m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long  m_playerID;
};

//摊牌响应
struct S_ZZ_TanPaiACK
{
	S_ZZ_TanPaiACK() :m_cmd(0){}

	static S_ZZ_TanPaiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_TanPaiACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		int nPlayers = (s.m_packageLen - 8) / 16;
		for (int i = 0; i < nPlayers; ++i)
		{
			unsigned long long playerID = 0;
			memcpy(&playerID, pData, 8);
			playerID = my_ntohll(playerID);
			s.m_playerID.push_back(playerID);
			pData += 8;
			int winOrLose = 0;
			memcpy(&winOrLose, pData, 4);
			pData += 4;
			winOrLose = ntohl(winOrLose);
			s.m_winOrLose.push_back(winOrLose);
			int score = 0;
			memcpy(&score, pData, 4);
			pData += 4;
			score = ntohl(score);
			s.m_score.push_back(score);
			int niu = 0;
			memcpy(&niu, pData, 4);
			niu = ntohl(niu);
			s.m_niuIndex.push_back(niu);
		}

		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;				//0�ɹ�1ʧ��
	vector<unsigned long long> m_playerID;
	vector<int> m_winOrLose;
	vector<int> m_score;
	vector<int> m_niuIndex;
};

///��֭����
////冲钻石请�?
//struct S_ZZ_BuyDiamondReq
//{
//	S_ZZ_BuyDiamondReq(int type, int wantBuy) :m_cmd(PP_ZZ_DOUNIU_WECHAT_ORDER_REQ), m_packageLen(14), m_wantBuy(0), m_wantType(type)
//	{
//		m_wantBuy = htonl(wantBuy);
//		m_packageLen = htonl(m_packageLen);
//		m_cmd = htons(m_cmd);
//		m_wantType = htonl(m_wantType);
//
//	}
//	unsigned int m_packageLen;
//	unsigned short m_cmd;
//	int m_wantType;					//0��ʯ��1���
//	int m_wantBuy;					//��ֵ����
//};
////��֭����
////冲钻石响�?
//struct S_ZZ_BuyDiamondACK
//{
//	S_ZZ_BuyDiamondACK() :m_cmd(0), m_isOK(0), m_currentNum(0){}
//
//	static S_ZZ_BuyDiamondACK convertDataFromBinaryData(void* binaryData)
//	{
//		char* pData = (char*)binaryData;
//		S_ZZ_BuyDiamondACK s;
//
//		memcpy(&s.m_packageLen, pData, 4);
//		s.m_packageLen = ntohl(s.m_packageLen);
//		pData += 4;
//		memcpy(&s.m_cmd, pData, 2);
//		s.m_cmd = ntohs(s.m_cmd);
//		pData += 2;
//
//		memcpy(&s.m_isOK, pData, 4);
//		s.m_isOK = ntohl(s.m_isOK);
//		pData += 4;
//		memcpy(&s.m_buyType, pData, 4);
//		s.m_buyType = ntohl(s.m_buyType);
//		pData += 4;
//		memcpy(&s.m_currentNum, pData, 4);
//		s.m_currentNum = ntohl(s.m_currentNum);
//		return s;
//	}
//
//	unsigned int m_packageLen;
//	unsigned short m_cmd;
//	int m_isOK;
//	int m_buyType;				//0��ʯ��1���
//	int m_currentNum;			//��ʯ����
//};

//抢庒请求
struct S_ZZ_QiangZhuangReq
{
	S_ZZ_QiangZhuangReq(unsigned long long playerID) :m_cmd(PP_DOUNIU_QIANGZHUANG_REQ), m_packageLen(14),
		m_playerID(playerID)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

//抢庒响应
struct S_ZZ_QiangZhuangACK
{
	S_ZZ_QiangZhuangACK() :m_cmd(0), m_ZhuangJiaID(0){}

	static S_ZZ_QiangZhuangACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_QiangZhuangACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		if (s.m_statusCode == 0)
		{
			memcpy(&s.m_ZhuangJiaID, pData, 8);
			s.m_ZhuangJiaID = my_ntohll(s.m_ZhuangJiaID);
		}
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;						//0�ɹ�1ʧ��
	unsigned long long m_ZhuangJiaID;
};

//押注请求
struct S_ZZ_YaZhuReq
{
	S_ZZ_YaZhuReq(unsigned long long playerID,int beishu) :m_cmd(PP_ZZ_DOUNIU_YAZHU_REQ), m_packageLen(18){
		m_beishu = htonl(beishu);
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	int m_beishu;
};

//押注响应
struct S_ZZ_YaZhuACK
{
	S_ZZ_YaZhuACK() :m_cmd(0){}

	static S_ZZ_YaZhuACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_YaZhuACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = my_ntohll(s.m_isOK);

		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_isOK;
};

//�������
struct S_ZZ_QuickChatReq
{
	S_ZZ_QuickChatReq(unsigned long long playerID,int quickChatSeq) :m_cmd(PP_ZZ_DOUNIU_QUICK_CHAT_REQ), m_packageLen(18)
	{
		m_quickChatSeq = htonl(m_quickChatSeq);
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	int m_quickChatSeq;			//�������
};

struct S_ZZ_QuickChatACK
{
	S_ZZ_QuickChatACK() :m_cmd(0){}

	static S_ZZ_QuickChatACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_QuickChatACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_quickChatSeq, pData, 4);
		s.m_quickChatSeq = ntohl(s.m_quickChatSeq);

		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	int m_quickChatSeq;			//�������
};

//��������
struct S_ZZ_VoiceChatReq
{
	S_ZZ_VoiceChatReq(unsigned long long playerID, char* voiceBinaryData, int size) :m_cmd(PP_ZZ_DOUNIU_VOICE_CHAT_REQ), 
		m_playerID(playerID),m_voiceSize(size), m_voiceBuf(0)
	{
		m_packageLen = htonl(18 + m_voiceSize);
		m_cmd = htons(m_cmd);
		m_voiceSize = htonl(m_voiceSize);
		m_voiceBuf = new char[size];
		memcpy(m_voiceBuf, voiceBinaryData, size);
	}
	~S_ZZ_VoiceChatReq()
	{
		if (m_voiceBuf)
		{
			delete[] m_voiceBuf;
			m_voiceBuf = 0;
		}

	}
	unsigned short m_cmd;
	unsigned int m_packageLen;
	unsigned long long m_playerID;
	unsigned int m_voiceSize;			//�������������ݴ�С
	char* m_voiceBuf;				//��������
};

struct S_ZZ_VoiceChatACK
{
	S_ZZ_VoiceChatACK() :m_cmd(0), m_voiceBuf(0){}
	S_ZZ_VoiceChatACK(const S_ZZ_VoiceChatACK& a)
	{
		this->m_packageLen = a.m_packageLen;
		this->m_cmd = a.m_cmd;
		this->m_playerID = a.m_playerID;
		this->m_voiceSize = a.m_voiceSize;
		this->m_voiceBuf = new char[this->m_voiceSize];
		memcpy(this->m_voiceBuf, a.m_voiceBuf, this->m_voiceSize);
	}
	static S_ZZ_VoiceChatACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_VoiceChatACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_voiceSize, pData, 4);
		s.m_voiceSize = ntohl(s.m_voiceSize);
		pData += 4;
		s.m_voiceBuf = new char[s.m_voiceSize];
		memcpy(s.m_voiceBuf, (char*)pData, s.m_voiceSize);
		return s;
	}
	~S_ZZ_VoiceChatACK()
	{
		if (m_voiceBuf)
		{
			delete[] m_voiceBuf;
			m_voiceBuf = 0;
		}

	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned int m_voiceSize;			//�������������ݴ�С
	char* m_voiceBuf;				//��������
};

//in game
struct S_ZZ_GetMemberInfoACK
{
	S_ZZ_GetMemberInfoACK() :m_cmd(0){}
	//静态函数，用于将二进制数据转换成该结构�?
	static S_ZZ_GetMemberInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_GetMemberInfoACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll((unsigned long long)(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_sex, pData, 4);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		memcpy(&s.m_currentDiamond, pData, 4);
		s.m_currentDiamond = ntohl(s.m_currentDiamond);
		pData += 4;
		memcpy(&s.m_currentMoney, pData, 4);
		s.m_currentMoney = ntohl(s.m_currentMoney);
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
	int m_currentMoney;
};
//��ţ
struct S_ZZ_SuanNiuReq
{
	S_ZZ_SuanNiuReq() :m_cmd(PP_DOUNIU_SUANNIU_REQ), m_packageLen(6)
	{
		m_packageLen = htonl(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
};

struct S_ZZ_SuanNiuACK
{
	S_ZZ_SuanNiuACK() :m_cmd(0), m_playerID(0), m_niu(0) {}

	static S_ZZ_SuanNiuACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_SuanNiuACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		if (s.m_statusCode == 0)
		{
			memcpy(&s.m_playerID, pData, 8);
			s.m_playerID = my_ntohll(s.m_playerID);
			memcpy(&s.m_niu, pData, 4);
			s.m_niu = my_ntohll(s.m_niu);
		}
		return s;
	}

	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;						//0�ɹ�1ʧ��
	unsigned long long m_playerID;
	int m_niu;
};
//��Ϸ��ʼ
struct S_ZZ_GameStartACK
{
	S_ZZ_GameStartACK() :m_cmd(0){}
	static S_ZZ_GameStartACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_GameStartACK s;

		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

struct S_ZZ_GameOverACK
{
	S_ZZ_GameOverACK() :m_cmd(0){}
	static S_ZZ_GameOverACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_GameOverACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;

		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_winCount, pData, 4);
		s.m_winCount = ntohl(s.m_winCount);
		pData += 4;
		memcpy(&s.m_loseCount, pData, 4);
		s.m_loseCount = ntohl(s.m_loseCount);
		pData += 4;
		memcpy(&s.m_totalScore, pData, 4);
		s.m_totalScore = ntohl(s.m_totalScore);
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	int m_winCount;					//ʤ������
	int m_loseCount;				//ʧ�ܴ���
	int m_totalScore;				//�þ��ܻ���

};

//����
struct S_ZZ_INVITE_REQ
{
	S_ZZ_INVITE_REQ(unsigned long long playerID, int inviteCode) :m_cmd(PP_ZZ_DOUNIU_INVITE_CODE_REQ),
		m_playerID(playerID), m_inviteCode(inviteCode)
	{
		m_packageLen = htonl(18);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
		m_inviteCode = htonl(m_inviteCode);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned int m_inviteCode;
};

struct S_ZZ_INVITE_ACK
{
	S_ZZ_INVITE_ACK() :m_cmd(0){}
	static S_ZZ_INVITE_ACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_INVITE_ACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		pData += 4;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;

		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	int m_statusCode;
	unsigned long long m_playerID;


};

//������Ϣ֪ͨ
struct S_ZZ_NoticeInfoACK
{
	S_ZZ_NoticeInfoACK() :m_cmd(0){}
	static S_ZZ_NoticeInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_NoticeInfoACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_noticeLen, pData, 2);
		s.m_noticeLen = ntohs(s.m_noticeLen);
		pData += 2;
		char buf[65535] = {0};
		memcpy(buf, pData, s.m_noticeLen);
		s.m_strNotice = buf;
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned short m_noticeLen;
	string m_strNotice;
};

//������Ϣ֪ͨ
struct S_ZZ_ShareInfoACK
{
	S_ZZ_ShareInfoACK() :m_cmd(0){}
	static S_ZZ_ShareInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_ShareInfoACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_shareURLLen, pData, 2);
		s.m_shareURLLen = ntohs(s.m_shareURLLen);
		pData += 2;
		char buf[65535] = { 0 };
		memcpy(buf, pData, s.m_shareURLLen);
		s.m_strURL = buf;
		pData += s.m_shareURLLen;
		memcpy(&s.m_shareTitleLen, pData, 2);
		s.m_shareTitleLen = ntohs(s.m_shareTitleLen);
		pData += 2;
		memset(buf, 0, 65535);
		memcpy(buf, pData, s.m_shareTitleLen);
		s.m_strTitle = buf;
		pData += s.m_shareTitleLen;
		memcpy(&s.m_shareDescriptionLen, pData, 2);
		s.m_shareDescriptionLen = ntohs(s.m_shareDescriptionLen);
		memset(buf, 0, 65535);
		memcpy(buf, pData, s.m_shareDescriptionLen);
		s.m_strDescription = buf;
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned short m_shareURLLen;
	string m_strURL;
	unsigned short m_shareTitleLen;
	string m_strTitle;
	unsigned short m_shareDescriptionLen;
	string m_strDescription;
};

//�����ı���������
struct S_ZZ_TEXT_CHAT_REQ
{
	S_ZZ_TEXT_CHAT_REQ(unsigned long long playerID, string text) :m_cmd(PP_ZZ_DOUNIU_TEXT_CHAT_REQ),
		m_playerID(playerID), m_strText(text)
	{
		m_textLen = htons(m_strText.length() + 1);
		m_packageLen = htonl(16 + m_textLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned short m_textLen;
	string m_strText;
};

struct S_ZZ_TEXT_CHAT_ACK
{
	S_ZZ_TEXT_CHAT_ACK() :m_cmd(0){}
	static S_ZZ_TEXT_CHAT_ACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_TEXT_CHAT_ACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		memcpy(&s.m_textLen, pData, 2);
		s.m_textLen = ntohs(s.m_textLen);
		pData += 2;
		char buf[1000] = { 0 };
		memcpy(buf, pData, s.m_textLen);
		s.m_strText = buf;
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
	unsigned short m_textLen;
	string m_strText;

};


//��������
struct S_ZZ_KeepaliveREQ
{
	S_ZZ_KeepaliveREQ(unsigned long long playerID) :m_cmd(PP_ZZ_DOUNIU_KEEP_ALIVE_REQ),
		m_playerID(playerID)
	{
		m_packageLen = htonl(14);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;
};

struct S_ZZ_KeepaliveACK
{
	S_ZZ_KeepaliveACK() :m_cmd(0){}
	static S_ZZ_KeepaliveACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ZZ_KeepaliveACK s;
		memcpy(&s.m_packageLen, pData, 4);
		s.m_packageLen = ntohl(s.m_packageLen);
		pData += 4;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(s.m_playerID);
		pData += 8;
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned long long m_playerID;

};

#pragma pack(4)
