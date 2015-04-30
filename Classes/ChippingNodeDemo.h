#ifndef _TEST_CHIPPINGNODEDEMO_H__
#define _TEST_CHIPPINGNODEMEMO_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
class ClippingNodeDemo : public cocos2d::Layer
{

public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	void menuCloseCallback(Ref* sender);
	CREATE_FUNC(ClippingNodeDemo);

	Size visibleSize;
	Size winSize;
	Vec2 origin;

	ClippingNode* holesClipper; //裁剪节点
	Node* holesStencil;         //模板节点
	Node* holes;                //底板节点

	//触摸回调
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	//添加小洞
	void pokeHoleAtPoint(Vec2 point);
};
#endif