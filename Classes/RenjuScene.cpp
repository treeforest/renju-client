#include "RenjuScene.h"
#include "DataPack.h"

bool RenjuScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	// 棋盘落子状态初始化
	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			m_szState[i][j] = PlateState::Empty;
		}
	}

	// 摆放棋盘
	CreatePlate();

	// 添加棋子
	CreatBead();

	// 触摸
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	// 选中精灵
	m_selectSprite = Sprite::create("selected.png");
	m_selectSprite->setVisible(false);
	m_selectSprite->setAnchorPoint(ccp(0.5, 0.5));
	addChild(m_selectSprite);

	// 连接网络
	

	return true;
}

// 创建棋盘
void RenjuScene::CreatePlate()
{
	Sprite * plate = Sprite::create("background.png");
	addChild(plate);
	plate->setPosition(ccp(0, 0));
	plate->setAnchorPoint(ccp(0, 0));
	plate->setScale(Director::sharedDirector()->getWinSize().height / plate->getContentSize().height);
}

// 创建棋子
void RenjuScene::CreatBead()
{
	int i = 0;
	while (i < BEADNUM) {
		Bead * bead = Bead::create();
		if (i % 2 == 0) bead->InitBead(BeadType::BLACK);
		else bead->InitBead(BeadType::WHITE);
		bead->setVisible(false);
		addChild(bead);
		m_quBead.push(bead);

		CCLOG("%p", bead);

		i++;
	}
}

bool RenjuScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

// 点击两次才能移动（一次选择，一次移动）
void RenjuScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!m_bSelectd) {
		SelectLocation(touch);
	}
	else {
		DropChess(touch);
	}
}

// 待落子位置
void RenjuScene::SelectLocation(Touch * touch)
{
	PlateIndex index;
	if (!Screen2Plate(touch->getLocation(), index)) {
		return;
	}

	SetSelectState(index);
}

// 落子
void RenjuScene::DropChess(Touch * touch)
{
	PlateIndex index;
	if (!Screen2Plate(touch->getLocation(), index)) {
		return;
	}

	if (index.i != m_selectdLoc.i || index.j != m_selectdLoc.j){
		// 设置成新的待落子状态
		SetSelectState(index);
		return;
	}

	// 重置为未选中待落子位置
	m_bSelectd = false; 
	m_selectSprite->setVisible(false);

	// 设置该位置为已选中状态 TODO:
	m_szState[index.i][index.j] = PlateState::Black;

	// 落子
	Bead * bead = m_quBead.front();
	bead->setPosition(Plate2Screen(index));
	bead->setVisible(true);
	m_quBead.pop();

	// 进行历史记录
	RecordHistory(bead);
}

void RenjuScene::SetSelectState(const PlateIndex & index)
{
	m_bSelectd = true;
	m_selectdLoc = index;
	m_selectSprite->setPosition(Plate2Screen(index));
	m_selectSprite->setVisible(true);
}

/*
 * 屏幕坐标转换成棋盘索引
 *
 * 返回值
 *  若点击位置有棋子，或者为棋盘外，则返回false; 否则返回true
 */
bool RenjuScene::Screen2Plate(const Point & ptScreen, PlateIndex & index)
{
	int i, j;	// 棋盘位置索引
	int iX, iY; // 
	iX = static_cast<int>(ptScreen.x);
	iY = static_cast<int>(ptScreen.y);

	if (iX < PlateTouchRange::Left || iX > PlateTouchRange::Right
		|| iY < PlateTouchRange::Bottom || iY > PlateTouchRange::Right) {
		return false;
	}

	i = (iX - PlateTouchRange::Left) / BeadSize::Width;
	j = (iY - PlateTouchRange::Bottom) / BeadSize::Height;
	CCLOG("Touch: [x=%d,y=%d] [i=%d,j=%d]", iX, iY, i, j);
	if (m_szState[i][j] != PlateState::Empty){
		return false;
	}

	index.i = i;
	index.j = j;
	return true;
}

/*
 * 棋盘索引转换为屏幕坐标
 */
Point RenjuScene::Plate2Screen(const PlateIndex & index)
{
	float x = (index.i + 1) * BeadSize::Width;
	float y = (index.j + 1) * BeadSize::Height;
	return ccp(x, y);
}

/*
 * 进行历史记录
 */
void RenjuScene::RecordHistory(Bead * bead)
{
	m_history.vec.push_back(bead);
}