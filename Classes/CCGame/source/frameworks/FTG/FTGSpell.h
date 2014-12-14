#pragma once

#include "cocos2d.h"
#include "../../CCGSprite.h"

NS_CC_BEGIN

struct FTGSpellData
{
	Point			startPosition;
	float			duration;
	std::vector<AnimationData*> animationsData;
};

class FTGSpell : public CCGSprite
{
public:

	enum SpellType
	{
		SPELL_NONE = 0,
		SPELL_AA,
		SPELL_AB,
		SPELL_BA,
		SPELL_BB,
		SPELL_CA,
		SPELL_CB,
		SPELL_DA,
		SPELL_DB,
		SPELL_EA,
		SPELL_EB,
		SPELL_FA,
		SPELL_FB,
		SPELL_GA,
		SPELL_GB,
		SPELL_MAX
	};

	FTGSpell(void);
	virtual ~FTGSpell(void);

	/** creators group */
	static FTGSpell* create();
	static FTGSpell* create(const std::string& filename);
	static FTGSpell* createWithSpellData(FTGSpellData* data);

	/** access functions */
	void setDuration(float duration) { _duration = duration; }

	/** bind spell */
	void bindSpell(FTGSpell::SpellType type, std::string animationName) { _spellMap[type] = animationName; }

protected:
	float _duration;
	std::string _spellMap[SPELL_MAX];	// stores animation name for each spell type.
};

NS_CC_END