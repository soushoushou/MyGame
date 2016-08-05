#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DebugSimpleServer.h"
#include "TimeLayer.h"
#include "SettingMenuInPlaying.h"
class NiuPoker;
class NiuPlayer;
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
    GamePlayScene();
    ~GamePlayScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GamePlayScene);

	//virtual void onExit();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
private:
	bool initBackground();
	bool initButtons();
	bool initPlayerProfile();
	/** ≥ı ºªØÕÊº“–≈œ¢ */
	bool initPlayer();
	/** …˙≥…“ª∏ˆ≈∆ */
	NiuPoker* selectPoker(int huaSe, int num);
	/** ¥¥Ω®“ª∏±∆ÀøÀ≈∆ */
	bool createPokers();
	/** œ¥≈∆ */
	bool xiPai();
	/** ∑¢≈∆ */
	void SendPk();
	/** ∑¢≈∆“∆∂Ø∂Øª≠ */
	void MovePk(NiuPlayer* play, NiuPoker* pk);

	void func(Node* pSender, void* pData);
    
    /** 初始化抢庄和不抢按钮 */
    void showHogButton();
    /** 显示倍数按钮 */
    void showChooseMultipleButton();
    /** 显示结果 */
    void showCompare();
    /** 重新开局 */
    void startNewPlay();
    /** 不抢和抢庄超时事件 */
    void notHogBtnAction();
    /** 选择倍数超时事件 */
    void notChooseMulAction();
private:
	TimeLayer* m_timeLayer;
	SettingMenuInPlaying *m_btnSetting;
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
	/** À˘”–µƒ≈∆ */
	__Array* m_arrPokers;
	/** ÕÊº“ */
	CC_SYNTHESIZE(NiuPlayer*, m_player, Player);
	/** ÕÊº“”“ */
	NiuPlayer* m_playerRight;
	/** ÕÊº“…œ∂˛ */
	NiuPlayer* m_playerTopRight;
	/** ÕÊº“…œ“ª */
	NiuPlayer* m_playerTopLeft;
	/** ÕÊº“◊Û */
	NiuPlayer* m_playerLeft;
	/** ÕÊº“◊¯±Í */
	Point playerDiZhuLablePt;
	/** ÕÊº“”““ª◊¯±Í */
	Point playerOneLablePt;
	/** ÕÊº“…œ∂˛◊¯±Í */
	Point playerTwoLablePt;
	/** ÕÊº“◊Û»˝◊¯±Í */
	Point playerThreeLablePt;
	/**  «∑Ò∑¢ÕÍ≈∆ */
	bool m_isSend;
	/** “—∑¢≥ˆµ⁄º∏’≈≈∆ */
	int m_iSendPk;
	/** µ±«∞◊¥Ã¨ 0£∫∑¢≈∆◊¥Ã¨  */
	UpdateType m_iState;
    /** 是否创建抢庄按钮 */
    bool m_creatHogBtn;
    /** 是否创建倍数按钮 */
    bool m_creatMulBtn;
    int m_playNum;
    LabelTTF *m_pNoticeLabel;
};


#endif // __GAMESCENE_SCENE_H__
