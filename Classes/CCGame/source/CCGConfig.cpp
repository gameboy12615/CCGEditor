#include "CCGConfig.h"

USING_NS_CC;

static CCGConfig *s_SharedConfig = nullptr;

CCGConfig* CCGConfig::getInstance()
{
	if (!s_SharedConfig)
	{
		s_SharedConfig = new (std::nothrow) CCGConfig();
		CCASSERT(s_SharedConfig, "FATAL: Not enough memory");
		s_SharedConfig->init();
	}

	return s_SharedConfig;
}

bool CCGConfig::init()
{
	_nearDistance = 100.0f;

	return true;
}