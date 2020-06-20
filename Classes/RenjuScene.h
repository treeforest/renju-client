#ifndef __RENJU_SCENE_H__
#define __RENJU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

#include "network/SocketIO.h"
using namespace cocos2d::network;

#include "Bead.h"
#include "public.h"
#include <vector>
#include <queue>
using namespace std;

// 历史记录
struct History {
	vector<Bead*> vec;
};

class RenjuScene : public Layer
{
public:
	CREATE_FUNC(RenjuScene);
	bool init();

	void CreatePlate();
	void CreatBead();

	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;

	virtual void SelectLocation(Touch * touch);
	virtual void DropChess(Touch * touch);

	void SetSelectState(const PlateIndex & index);

	bool Screen2Plate(const Point & ptScreen, PlateIndex & index);
	Point Plate2Screen(const PlateIndex & index);

	void RecordHistory(Bead * bead);

private:
	// 标记棋盘的落子状态				
	PlateState m_szState[15][15];
	
	// 黑白棋子
	queue<Bead*> m_quBead;
	
	// 标记是否是否选中待落子的位置，选中为true，未选中为false				
	bool m_bSelectd;
	
	// 记录选中的待落子的位置				
	PlateIndex m_selectdLoc;	

	// 对选中位置进行标记的精灵
	Sprite * m_selectSprite;

	// 每局历史记录
	History m_history;

	// 网络套接字
	SIOClient *m_client;

	// 是否连接服务端
	bool m_bConnect;
};

#endif // __RENJU_SCENE_H__