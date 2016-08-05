#pragma once
#include <vector>
const int pkWidth_small = 60;//71;//牌的宽
const int pkHeight_small = 79;//96;//牌的高
const int pkWidth_Big=88;
const int pkHeight_Big=112;
const int pkJianJu = 20;//牌与牌之间的间距
//花色
enum HuaSe
{
	HeiTao = 0,//花色比较：黑桃>红桃>草花>方块
	HongTao,
	MeiHua,
	FangKuai,
	Gui,
	HuaSeBM = 4     //花色背面
};
//牌号
enum PaiHao
{
	Yi = 1, Er, San, Si, Wu, Liu, Qi, Ba, Jiu, Shi, ShiYi, ShiEr, ShiSan, XiaoGui, DaGui, PaiHaoBM = 2
};
//标签
enum BiaoQian
{
	Zhuang,		//庄家
	Not_Zhuang,	//非庄家
	FenShu,
	NpcTwoBuChu,
	NpcOneBuChu
};
//斗牛牌型，共有15种牌型
enum NIU_CARD_TYPE
{
	NIU_ZERO = 1,	//没牛
	NIU_YI,		//牛一
	NIU_ER,		//牛二
	NIU_SAN,	//牛三
	NIU_SI,		//牛四
	NIU_WU,		//牛五
	NIU_LIU,	//牛六
	NIU_QI,		//牛七
	NIU_BA,		//牛八
	NIU_JIU,	//牛九
	NIU_SHI,	//牛牛
	YIN_NIU,	//银牛，十和十以上的花牌组成的牛牛
	JIN_NIU,	//金牛，五张十以上的花牌组成的牛牛
	WU_XIAO,	//五小，5张牌牌点总数小于或者等于10
	ZHA_DAN,	//炸弹：四张牌点一样的牌
};
