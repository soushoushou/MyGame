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
//鍖呭畯
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
#define PP_DOUNIU_TANPAI_REQ		(50028) //这个暂时别管，等调完我删掉
//8瀛楄妭涓绘満搴忚浆缃戠粶搴?
unsigned long long my_htonll(unsigned long long val);

//8瀛楄妭缃戠粶搴忚浆涓绘満搴?
unsigned long long my_ntohll(unsigned long long val);

//鍝嶅簲鏁版嵁鍧?
struct S_ACKResponse
{
	S_ACKResponse(){
		memset(m_buf, 0, 6400 * 1024);
		m_len = 0;
	}
	S_ACKResponse(void* data, int size)
	{
		memset(m_buf, 0, 6400 * 1024);
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
	char m_buf[6400 * 1024];
	int m_len;
};

//鍖呯粨鏋?
//鍒涘缓瑙掕壊璇锋眰
#pragma pack(1)
struct S_CreatePlayerReq
{
	S_CreatePlayerReq(string account, string roleName, int sex) :m_cmd(PP_DOUNIU_CREAT_ACCOUNT_REQ),
		m_account(account), m_roleName(roleName),m_sex(sex), m_yanZhengMa(1), m_yanZhengTime(1)
	{
		m_strAccountLen = m_account.length()+1;
		m_strRoleNameLen = m_roleName.length()+1;
		m_packageLen = 4 + 4 + 2 + m_strAccountLen + 2 + m_strRoleNameLen + 4 + 4 + 4;
		//杞崲瀛楄妭搴?
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_strAccountLen = htons(m_strAccountLen);
		m_strRoleNameLen = htons(m_strRoleNameLen);
		m_sex = htonl(m_sex);
		m_yanZhengMa = htonl(m_yanZhengMa);
		m_yanZhengTime = htonl(m_yanZhengTime);

	}
	short m_packageLen;						//鍖呴暱
	unsigned short m_cmd;							//鍗忚鍙?
	short m_strAccountLen;					//璐﹀彿闀垮害
	string m_account;						//璐﹀彿
	short m_strRoleNameLen;					//瑙掕壊鍚嶉暱搴?
	string m_roleName;						//瑙掕壊鍚?
	int m_sex;								//鎬у埆
	int m_yanZhengMa;						//楠岃瘉鐮?
	int m_yanZhengTime;						//楠岃瘉鏃堕棿
};

//鍒涘缓瑙掕壊鍝嶅簲
struct S_CreatePlayerACK
{
	S_CreatePlayerACK() :m_packageLen(8),m_cmd(0),m_statusCode(0){}
	//闈欐�佸嚱鏁帮紝鐢ㄤ簬灏嗕簩杩涘埗鏁版嵁杞崲鎴愯缁撴瀯浣?
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
	int m_statusCode;				//0澶辫触锛?鎴愬姛锛?鏁忔劅璇?
};
//鐧诲綍璇锋眰
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
//鑾峰彇鐧诲綍鍝嶅簲
struct S_LoginACK
{
	S_LoginACK() :m_cmd(0) {}
	//闈欐�佸嚱鏁帮紝鐢ㄤ簬灏嗕簩杩涘埗鏁版嵁杞崲鎴愯缁撴瀯浣?
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
	unsigned long long m_userID;			//不知道有什么卵用
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
};
//鑾峰彇瑙掕壊淇℃伅璇锋眰
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

//鑾峰彇瑙掕壊淇℃伅鍝嶅簲
struct S_GetPlayerInfoACK
{
	S_GetPlayerInfoACK() :m_cmd(0){}
	//闈欐�佸嚱鏁帮紝鐢ㄤ簬灏嗕簩杩涘埗鏁版嵁杞崲鎴愯缁撴瀯浣?
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

//鍒涘缓鎴块棿璇锋眰
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

//鍒涘缓鎴块棿鍝嶅簲
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

//鍔犲叆鎴块棿璇锋眰
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

//鍔犲叆鎴块棿鍝嶅簲
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
	int m_isOK;					//0澶辫触锛?鎴愬姛
	int m_roomID;
};

//鏌ヨ鎴樼哗璇锋眰
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

//鏌ヨ鎴樼哗鍝嶅簲
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
	vector<int> m_roomIDs;				//房间id
	vector<int> m_scores;				//房间对应的积分
};


//閫�鍑烘埧闂磋姹?
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

//閫�鍑烘埧闂村搷搴?
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
	int m_isOK;			//0澶辫触锛?鎴愬姛
	int m_roomID;
	unsigned long long m_playerID;
};

//鍑嗗娓告垙璇锋眰
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

//鍑嗗娓告垙鍝嶅簲
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
	int m_isOK;						//0澶辫触锛?鎴愬姛
	unsigned long long m_playerID;
};

//鍙戠墝璇锋眰
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

//鍙戠墝鍝嶅簲
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
	int m_statusCode;				//0成功1失败
	vector<unsigned long long> m_playerID;
	vector<int> m_pokers;
};

//鎽婄墝璇锋眰
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

//鎽婄墝鍝嶅簲
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
	int m_statusCode;				//0成功1失败
	vector<unsigned long long> m_playerID;
	vector<int> m_winOrLose;
	vector<int> m_score;
};

//鍐查捇鐭宠姹?
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
	int m_wantType;					//0钻石，1金币
	int m_wantBuy;					//充值数量
};

//鍐查捇鐭冲搷搴?
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
	int m_buyType;				//0钻石，1金币
	int m_currentNum;			//钻石或金币
};

//鎶㈠簰璇锋眰
struct S_QiangZhuangReq
{
	S_QiangZhuangReq(int isQiang) :m_cmd(PP_DOUNIU_QIANGZHUANG_REQ),m_packageLen(4){
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		isQiang = htonl(isQiang);
	}
	short m_packageLen;
	unsigned short m_cmd;
	int m_isQiang;					//是否抢庒,0抢1不抢
};

//鎶㈠簰鍝嶅簲
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
	int m_statusCode;						//0成功1失败
	unsigned long long m_ZhuangJiaID;
};

//鎶兼敞璇锋眰
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

//鎶兼敞鍝嶅簲
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

//快捷聊天
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
	int m_quickChatSeq;			//聊天序号
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
	int m_quickChatSeq;			//聊天序号
};

//语音聊天
struct S_VoiceChatReq
{
	S_VoiceChatReq(char* voiceBinaryData,int size) :m_cmd(PP_DOUNIU_VOICE_CHAT_REQ), m_voiceSize(size)
	{
		m_packageLen = htonl(10 + m_voiceSize);
		m_cmd = htons(m_cmd);
		m_voiceSize = htonl(m_voiceSize);
		memcpy(m_voiceBuf, voiceBinaryData, size);
	}
	unsigned short m_cmd;
	unsigned int m_packageLen;
	unsigned int m_voiceSize;			//语音二进制数据大小
	char m_voiceBuf[6400*1024-10];				//语音缓冲
};

struct S_VoiceChatACK
{
	S_VoiceChatACK() :m_cmd(0){}
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
		memcpy(s.m_voiceBuf, (char*)pData, s.m_voiceSize);
		return s;
	}
	unsigned int m_packageLen;
	unsigned short m_cmd;
	unsigned int m_voiceSize;			//语音二进制数据大小
	char m_voiceBuf[6400*1024-10];				//语音缓冲
};

//in game
struct S_GetMemberInfoACK
{
	S_GetMemberInfoACK() :m_cmd(0){}
	//闈欐�佸嚱鏁帮紝鐢ㄤ簬灏嗕簩杩涘埗鏁版嵁杞崲鎴愯缁撴瀯浣?
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
//算牛
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
	int m_statusCode;						//0成功1失败
	unsigned long long m_playerID;
	int m_niu;
};
//游戏开始
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
	int m_winCount;					//胜利次数
	int m_loseCount;				//失败次数
	int m_totalScore;				//该局总积分

};
#pragma pack(4)
