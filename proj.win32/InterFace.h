#pragma once
#include "cocos2d.h"

/**
 * 游戏逻辑及规则制定
 */
class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	//判断落子点是否正确
	virtual BOOL bIsDropPointRight();

	//进行落子操作
	virtual void MoveBean();

	//AI最佳落子点确定
	virtual void BestDropPoint();

	//比赛结果判断	0-平局	1-黑子胜	2-白子胜	
	virtual int MatchResult();

	//记录历史比赛
	virtual void RecordHistoricalMatch();
private:

};

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}