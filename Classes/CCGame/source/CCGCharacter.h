#pragma once

#include "cocos2d.h"
#include "CCGSpell.h"
#include "CCGSprite.h"
#include "CCGDataCache.h"

NS_CC_BEGIN

struct CharacterData : public CCGData
{
	std::string		name;
};

/** this is pure class, should not create instance form it */
class CCGCharacter : public CCGSprite, public Clonable
{
public:

	CCGCharacter(void);
	virtual ~CCGCharacter(void);

	/** cast spell */
	virtual CCGSpell* castSpell(std::string dataName) = 0;

	/** basic state functions */
	bool isNear() { return _isNear; }
	void setNear(bool isNear) { _isNear = isNear; }

	/** access functions */
	void setPlayer(bool isPlayer) { _isPlayer = isPlayer; }
	bool isPlayer() { return _isPlayer; }

	/** spells generate by this character */
	void addSpell(CCGSpell * spell);
	Vector<CCGSpell*>& getSpells() { return _spells; }

	/** other functions */
	void checkNear(CCGCharacter* other);

protected:

	/** init additional */
	virtual bool initAdditional(void);

	/** loacl callback functions */
	void update(float delta) { onUpdate(delta); }
	virtual void onUpdate(float delta) = 0;

	Vector<CCGSpell*> _spells;
	bool _isPlayer{ false };

	/** character basic states */
	bool _isNear{ false };
};

NS_CC_END