#ifndef __BEAD_H__
#define __BEAD_H__

#include "cocos2d.h"
USING_NS_CC;

enum class BeadType {
	BLACK, // 黑子
	WHITE, // 白子
};

/** 
 黑白棋子类
 */
class Bead : public Sprite
{
public:
	CREATE_FUNC(Bead);
	bool init();

	void InitBead(BeadType type);
};

#endif // __BEAD_H__