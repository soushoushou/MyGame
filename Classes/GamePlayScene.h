#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DebugSimpleServer.h"
#include "TimeLayer.h"
#include "SettingMenuInPlaying.h"
#include "UserProfileUI.h"
#include "ChatLayer.h"
#include "NetworkManger.h"
#include "SiteManager.h"
#include "PorkerManager.h"
#include "PopupLayer.h"
class NiuPoker;
class NiuPlayer;
class CDMRecordObject;
USING_NS_CC;
using namespace ui;

/** 更新状态 */
enum UpdateType{
    /** 准备状态 */
    StartState,
    /** 发牌状态 */
    SendPokerState,
    /** 抢庄状态 */
    HogState,
    /** 选择倍数状态 */
    ChooseMultipleState,
    /** 比大小状态 */
    CompareState
};


class GamePlayScene : public cocos2d::Layer
{
public:
	GamePlayScene(int playerID, int roomID, CCDictionary* stringsInConfig);
    ~GamePlayScene();
	static cocos2d::Scene* createScene(int playerID, int roomID, CCDictionary* stringsInConfig);
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	static GamePlayScene* create(int playerID, int roomID, CCDictionary* stringsInConfig);

	//virtual void onExit();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	SiteManager* getSiteManager() const;
	unsigned long long getPlayerID() const;
private:
	bool initBackground();
	bool initButtons();
	bool initPlayerProfile();	//初始化玩家信息

	/** 发牌移动动画 */
	void MovePk(NiuPlayer* play, NiuPoker* pk);

	
    
    /** 初始化抢庄和不抢按钮 */
    void showHogButton();
    /** 显示倍数按钮 */
    void showChooseMultipleButton();
    /** 显示结果 */
    void showCompare(int mPlayerID);
    /** 重新开局 */
    void startNewPlay();
    /** 不抢和抢庄超时事件 */
    void notHogBtnAction();
    /** 选择倍数超时事件 */
    void notChooseMulAction(float dt);
	/**算牛 */
	int countNiu(vector<int> vecPorkerIndex);
	/**延迟展示积分界面 */
	void delayShowCount();
	/** 显示单局积分结果 */
	void showOneRoundResultDialog(int playerID, int winStatus, vector<pair<int, int>> quickMessage);
	/** 显示全局积分结果 */
	void showAllRoundResultDialog(int playerID, vector<pair<int, int>> quickMessage);
	/** 显示算牛UI */
	void showSuanNiuUi();
	/** 隐藏算牛UI */
	void hideSuanNiuUi();
private:
	//其余4个玩家的玩家位置和头像位置
	struct PlayerAndProfilePos 
	{
		Point playerPos;
		Point profilePos;
		int profileType;		//0为水平，1为垂直
	};

	TimeLayer* m_timeLayer;
	ChatLayer* m_chatLayer;

	/** 设置 */
	SettingMenuInPlaying *m_btnSetting;
	/** 聊天 */
	Button* m_chatBtn;
	/** 有牛 */
	Button* m_youniuBtn;
	/** 没牛 */
	Button* m_wuniuBtn;
	/** 自动算牛 */
	Button* m_countniuBtn;
	/** 邀请 */
	Button* m_inviteBtn;
    /** 准备按钮 */
    Button* m_startGameBtn;
    /** 不抢按钮 */
    Button* m_notHogBtn;
    /** 抢庄按钮 */
    Button* m_HogBtn;
    /** 一倍按钮 */
    Button* m_OneBtn;
    /** 二倍按钮 */
    Button* m_TwoBtn;
    /** 三倍按钮 */
    Button* m_ThreeBtn;
    /** 四倍按钮 */
    Button* m_FourBtn;
    /** 五倍按钮 */
    Button* m_FiveBtn;
	bool m_bReady;
	/** 当前状态 0：发牌状态  */
	UpdateType m_iState;
    /** 是否创建抢庄按钮 */
    bool m_creatHogBtn;
    /** 是否创建倍数按钮 */
    bool m_creatMulBtn;
	Scale9Sprite * suanNiuBg_sprite;
	Scale9Sprite * suanNiuOne_sprite;
	Scale9Sprite * suanNiuTwo_sprite;
	Scale9Sprite * suanNiuThree_sprite;
	Scale9Sprite * suanNiuSum_sprite;
	Scale9Sprite * suanNiuAdd_sprite;
	Scale9Sprite * suanNiuAdd2_sprite;
	Scale9Sprite * suanNiuEqual_sprite;
	LabelTTF* m_countNiuLabels[4];			//0第一个数,1第二个数,2第三个数,3和
	bool m_creatSuanniuUI;
    int m_playNum;
    LabelTTF *m_pNoticeLabel;
	Label *m_pRoomNumberLabel;
	LabelTTF *m_pWaitYaZhuLabel;
	LabelTTF *m_pModelLabel;
    Button *m_recordBtn;
	int m_roomID;
	int m_playerID;
	int m_winStatus;
	vector<pair<int, int>> m_playerAndCount;
	int m_bankerModel;//设定的庄家模式，抢庄或轮庄，0或1
	int m_roundNum;//设定的单轮局数，10或20
	SiteManager* m_pSiteManager;
	PorkerManager* m_pPorkerManager;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CDMRecordObject *m_recordObject;
#endif
	bool m_bGameStart;
	vector<int> m_testID;
	vector<pair<string, string>> my_quickMessage;
	CCDictionary* m_StringsInConfig;
};


#endif // __GAMESCENE_SCENE_H__
