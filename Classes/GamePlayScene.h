#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DebugSimpleServer.h"
#include "TimeLayer.h"
class NiuPoker;
class NiuPlayer;
USING_NS_CC;
using namespace ui;

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
    /** 初始化玩家信息 */
    bool initPlayer();
    /** 生成一个牌 */
    NiuPoker* selectPoker(int huaSe, int num);
    /** 创建一副扑克牌 */
    bool createPokers();
    /** 洗牌 */
    bool xiPai();
    /** 发牌 */
    void SendPk();
    /** 发牌移动动画 */
    void MovePk(NiuPlayer* play, NiuPoker* pk);
    
    void func(Node* pSender, void* pData);
private:
	TimeLayer* m_timeLayer;
	Button* m_startGameBtn;
	bool m_bReady;
    /** 所有的牌 */
    __Array* m_arrPokers;
    /** 玩家 */
    CC_SYNTHESIZE(NiuPlayer*, m_player, Player);
    /** 玩家右 */
    NiuPlayer* m_playerRight;
    /** 玩家上二 */
    NiuPlayer* m_playerTopRight;
    /** 玩家上一 */
    NiuPlayer* m_playerTopLeft;
    /** 玩家左 */
    NiuPlayer* m_playerLeft;
    /** 玩家坐标 */
    Point playerDiZhuLablePt;
    /** 玩家右一坐标 */
    Point playerOneLablePt;
    /** 玩家上二坐标 */
    Point playerTwoLablePt;
    /** 玩家左三坐标 */
    Point playerThreeLablePt;
    /** 是否发完牌 */
    bool m_isSend;
    /** 已发出第几张牌 */
    int m_iSendPk;
    /** 当前状态 0：发牌状态  */
    int m_iState;
};


#endif // __GAMESCENE_SCENE_H__
