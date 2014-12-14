#include "CCGDataCache.h"

USING_NS_CC;

static CCGDataCache *s_SharedDataCache = nullptr;

CCGDataCache* CCGDataCache::getInstance()
{
	if (!s_SharedDataCache)
	{
		s_SharedDataCache = new (std::nothrow) CCGDataCache();
		CCASSERT(s_SharedDataCache, "FATAL: Not enough memory");
		s_SharedDataCache->init();
	}

	return s_SharedDataCache;
}

void CCGDataCache::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(s_SharedDataCache);
}

bool CCGDataCache::init()
{
	return true;
}

void CCGDataCache::addData(CCGData *data, const std::string& name)
{
	_datas.insert(name, data);
}

void CCGDataCache::removeData(const std::string& name)
{
	if (name.size() == 0)
		return;

	_datas.erase(name);
}

CCGData* CCGDataCache::getData(const std::string& name)
{
	return _datas.at(name);
}
