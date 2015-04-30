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

	ClippingNode* holesClipper; //�ü��ڵ�
	Node* holesStencil;         //ģ��ڵ�
	Node* holes;                //�װ�ڵ�

	//�����ص�
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	//���С��
	void pokeHoleAtPoint(Vec2 point);
};
#endif