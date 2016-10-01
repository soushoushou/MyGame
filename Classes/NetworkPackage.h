#pragma once
#include <string>
using namespace std;
//包宏
#define PP_DOUNIU_CREAT_ACCOUNT_REQ	(10000)
#define PP_DOUNIU_CREAT_ACCOUNT_ACK	(10001)
#define PP_DOUNIU_GET_ROLEINFO_REQ	(10002)
#define PP_DOUNIU_GET_ROLEINFO_ACK	(10003)
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
#define PP_DOUNIU_TANPAI_REQ		(50012)
#define PP_DOUNIU_TANPAI_ACK		(50013)
#define PP_DOUNIU_CHONGZHI_REQ		(50014)
#define PP_DOUNIU_CHONGZHI_ACK		(50015)
#define PP_DOUNIU_QIANGZHUANG_REQ	(50016)
#define PP_DOUNIU_QIANGZHUANG_ACK	(50017)
#define PP_DOUNIU_YAZHU_REQ			(50018)
#define PP_DOUNIU_YAZHU_ACK			(50019)


//包结构
//创建角色请求
#pragma pack(1)
struct S_CreatePlayerReq
{
	S_CreatePlayerReq() :m_cmd(PP_DOUNIU_CREAT_ACCOUNT_REQ),
		m_account("alw_123"), m_roleName("ALW"),m_sex(1), m_yanZhengMa(1), m_yanZhengTime(1)
	{
		m_strAccountLen = m_account.length()+1;
		m_strRoleNameLen = m_roleName.length()+1;
		m_packageLen = 4 + 2 + m_strAccountLen + 2 + m_strRoleNameLen + 4 + 4 + 4;
	}
	short m_packageLen;						//包长
	short m_cmd;							//协议号
	short m_strAccountLen;					//账号长度
	string m_account;						//账号
	short m_strRoleNameLen;					//角色名长度
	string m_roleName;						//角色名
	int m_sex;								//性别
	int m_yanZhengMa;						//验证码	
	int m_yanZhengTime;						//验证时间
};

//创建角色响应
struct S_CreatePlayerACK
{
	S_CreatePlayerACK() :m_packageLen(8),m_cmd(0),m_statusCode(0){}
	short m_packageLen;
	short m_cmd;
	int m_statusCode;				//0失败，1成功，2敏感词
};

//获取角色信息请求
struct S_GetPlayerInfoReq
{
	S_GetPlayerInfoReq() :m_cmd(PP_DOUNIU_GET_ROLEINFO_REQ),m_packageLen(4+sizeof(m_playerID)),m_playerID(0){}
	short m_packageLen;
	short m_cmd;
	unsigned long long m_playerID;
};

//获取角色信息响应
struct S_GetPlayerInfoACK
{
	S_GetPlayerInfoACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	unsigned long long m_playerID;
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
};

//创建房间请求
struct S_CreateRoomReq
{
	S_CreateRoomReq() :m_cmd(PP_DOUNIU_CREATE_ROOM_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//创建房间响应
struct S_CreateRoomACK
{
	S_CreateRoomACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_roomID;
};

//加入房间请求
struct S_JoinRoomReq
{
	S_JoinRoomReq() :m_cmd(PP_DOUNIU_JOIN_ROOM_REQ),m_packageLen(8){}
	short m_packageLen;
	short m_cmd;
	int m_roomID;
};

//加入房间响应
struct S_JoinRoomACK
{
	S_JoinRoomACK() :m_cmd(0), m_isOK(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;					//0失败，1成功
	int m_roomID;
};

//查询战绩请求
struct S_SearchZhanjiReq
{
	S_SearchZhanjiReq() :m_cmd(PP_DOUNIU_QUERY_ZHANJI_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//查询战绩响应
struct S_SearchZhanjiACK
{
	S_SearchZhanjiACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	short m_zhanjiLen;
	string m_zhanji;
};


//退出房间请求
struct S_QuitRoomReq
{
	S_QuitRoomReq() :m_cmd(PP_DOUNIU_QUIT_ROOM_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//退出房间响应
struct S_QuitRoomACK
{
	S_QuitRoomACK() :m_cmd(0), m_isOK(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;			//0失败，1成功
	int m_roomID;
};

//准备游戏请求
struct S_ReadyPlayReq
{
	S_ReadyPlayReq() :m_cmd(PP_DOUNIU_READY_REQ), m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//准备游戏响应
struct S_ReadyPlayACK
{
	S_ReadyPlayACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;						//0失败，1成功
};

//发牌请求
struct S_FaPaiReq
{
	S_FaPaiReq() :m_cmd(PP_DOUNIU_FAPAI_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//发牌响应
struct S_FaPaiACK
{
	S_FaPaiACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	short m_pokerlilstLen;
	string m_pokerList;
};

//摊牌请求
struct S_TanPaiReq
{
	S_TanPaiReq() :m_cmd(PP_DOUNIU_TANPAI_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//摊牌响应
struct S_TanPaiACK
{
	S_TanPaiACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_isSmaller;//0:大,1:小
};

//冲钻石请求
struct S_BuyDiamondReq
{
	S_BuyDiamondReq() :m_cmd(PP_DOUNIU_CHONGZHI_REQ), m_packageLen(8), m_wantBuy(0){}
	short m_packageLen;
	short m_cmd;
	int m_wantBuy;
};

//冲钻石响应
struct S_BuyDiamondACK
{
	S_BuyDiamondACK() :m_cmd(0),m_isOK(0),m_currentDiamond(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;
	int m_currentDiamond;
};

//抢庒请求
struct S_QiangZhuangReq
{
	S_QiangZhuangReq() :m_cmd(PP_DOUNIU_QIANGZHUANG_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//抢庒响应
struct S_QiangZhuangACK
{
	S_QiangZhuangACK() :m_cmd(0),m_ZhuangJiaID(0){}
	short m_packageLen;
	short m_cmd;
	unsigned long long m_ZhuangJiaID;
};

//押注请求
struct S_YaZhuReq
{
	S_YaZhuReq() :m_cmd(PP_DOUNIU_YAZHU_REQ),m_packageLen(8){}
	short m_packageLen;
	short m_cmd;
	int m_beishu;
};

//押注响应
struct S_YaZhuACK
{
	S_YaZhuACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;
};
#pragma pack(4)
