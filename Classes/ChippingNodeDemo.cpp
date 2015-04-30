#include "ChippingNodeDemo.h"

USING_NS_CC;

Scene* ClippingNodeDemo::createScene()
{
	auto scene = Scene::create();
	auto layer = ClippingNodeDemo::create();
	scene->addChild(layer);
	return scene;
}

bool ClippingNodeDemo::init()
{
	if (!Layer::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
	origin = Director::getInstance()->getVisibleOrigin();

	Sprite* gameTitle = Sprite::create("game_title.png");

	Size clipSize = gameTitle->getContentSize();

	Sprite* spark = Sprite::create("spark.png");
	spark->setPosition(clipSize.width/ 2, 0);

	ClippingNode* clippingNode = ClippingNode::create();
	clippingNode->setAlphaThreshold(0);
	clippingNode->setContentSize(clipSize);
	clippingNode->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	this->addChild(clippingNode);


	clippingNode->setStencil(gameTitle);   //����ģ��

	clippingNode->addChild(gameTitle, 1);  //����ӱ���,����ȫ��ʾ����,��Ϊ��ģ��һ����С
	clippingNode->addChild(spark, 2);       //�ᱻ�ü�

	MoveTo* moveAction = MoveTo::create(2.0f, Vec2(clipSize.width, 0));
	MoveTo* moveBackAction = MoveTo::create(2.0f, Vec2(-clipSize.width, 0));
	Sequence* seq = Sequence::create(moveAction, moveBackAction, NULL);
	RepeatForever* repeatAction = RepeatForever::create(seq);
	spark->runAction(repeatAction); //���������ƶ����ظ�����

	//[1].����ͼƬ(Layer����)
	Sprite* bg = Sprite::create("HelloWorld.png");
	bg->setPosition(visibleSize / 2);
	this->addChild(bg);

	//[2].�����ü��ڵ� : holesClipper
	holesClipper = ClippingNode::create();
	holesClipper->setPosition(visibleSize / 2);
	this->addChild(holesClipper);

	//��������
	holesClipper->setInverted(true); //������ʾ��δ���ü�������ʣ�ಿ��
	holesClipper->setAlphaThreshold(0.5f);
	holesClipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));

	//[3].����ģ�� : holesStencil
	holesStencil = Node::create();
	holesClipper->setStencil(holesStencil); //���ģ��

	//���һ��ģ������ ball
	holesStencil->addChild(Sprite::create("ball.png"), -1);

	//[4].�����װ� : holes
	holes = Node::create();
	holesClipper->addChild(holes);  //���õװ�

	//�����һ���װ����� blocks
	Sprite* content = Sprite::create("blocks.png");
	holesClipper->addChild(content, -1, 1);

	//[5].�����¼�
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(ClippingNodeDemo::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void ClippingNodeDemo::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	//[1].��ȡ����, ת��Ϊ���holesClipper�ڵ�� �������
	Vec2 point = touches[0]->getLocation();
	point = holesClipper->convertToNodeSpace(point);

	//[2].��ȡ�װ��������Rect
	Sprite *content = (Sprite*)unused_event->getCurrentTarget()->getChildByTag(1);
	Rect rect = Rect(-100, -100, 200, 200);
	CCLOG("1");
	//[3].�������ڵװ��ڲ�, ����"��"
	if (rect.containsPoint(point))
	{
		CCLOG("2");
		pokeHoleAtPoint(point);
	}
}

void ClippingNodeDemo::pokeHoleAtPoint(Vec2 point)
{
	CCLOG("Add a Hole!!!");
	//[1].��ӵװ����� : һ�����ĺۼ�
	auto hole = Sprite::create("hole_effect.png");
	hole->setPosition(point);
	holes->addChild(hole);

	//[2].���ģ������ : һ��С��
	auto holeStencil = Sprite::create("hole_stencil.png");
	holeStencil->setPosition(point);
	holesStencil->addChild(holeStencil);

	//[3].����Ч�� : �Ŵ���С
	holesClipper->runAction(Sequence::create(ScaleTo::create(0.05f, 1.05f), ScaleTo::create(0.05f, 1.0f), NULL));
}