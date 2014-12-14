#pragma once

#include "cocos2d.h"
#include "../../CCGSpell.h"

NS_CC_BEGIN

struct STGSpellData;

/** should only have logical difference with CCGSpell.
*/
class STGSpell : public CCGSpell
{
public:

	enum SpellState
	{
		SPELL_STATE_NONE = 0,
		SPELL_STATE_START,
		SPELL_STATE_STEP1,
		SPELL_STATE_STEP2,
		SPELL_STATE_STEP3,
		SPELL_STATE_STEP4,
		SPELL_STATE_STEP5,
		SPELL_STATE_DESTORY,
		SPELL_STATE_MAX
	};

	STGSpell(void);
	virtual ~STGSpell(void);

	/** creators group */
	static STGSpell* create();
	static STGSpell* create(const std::string& filename);
	static STGSpell* createWithSpellData(STGSpellData* data);

	/** bind spell */
	void bindSpell(STGSpell::SpellState state, std::string animationName) { _spellMap[state] = animationName; }
	void setSpellMap(std::string map[STGSpell::SPELL_STATE_MAX]);

	/** callback functions */
	virtual void onHit() override;

	/** other functions */
	virtual STGSpell *clone() const override;
	void runState(STGSpell::SpellState state);

protected:
	std::string _spellMap[SPELL_STATE_MAX];	// stores animation name for each spell state.
};

struct STGSpellData : public SpellData
{
	std::string spellMap[STGSpell::SPELL_STATE_MAX];

	CREATE_FUNC(STGSpellData);
};

NS_CC_END