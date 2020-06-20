#include "Bead.h"


bool Bead::init()
{
	if (!Sprite::init()) {
		return false;
	}

	return true;
}

void Bead::InitBead(BeadType type)
{
	Texture2D * texture = NULL;

	if (type == BeadType::WHITE) {
		texture = TextureCache::sharedTextureCache()->addImage("white.png");
	}
	else { // BeadType::BLACK
		texture = TextureCache::sharedTextureCache()->addImage("black.png");
	}

	// Ãªµã
	setAnchorPoint(ccp(0.5, 0.5));

	// ÉèÖÃÎÆÀí
	setTexture(texture);
	setTextureRect(Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
}
