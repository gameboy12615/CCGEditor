#pragma once

#include "cocos2d.h"

NS_CC_BEGIN

class CCGData : public Ref
{
public:
	virtual ~CCGData() { }
	virtual bool init() { return true; }
};

class CCGDataCache : public Ref
{
public:

	/** Returns the shared instance of the Data cache */
	static CCGDataCache* getInstance();
	static void destroyInstance();
	bool init(void);

	/** Adds a data with a name */
	void addData(CCGData *data, const std::string& name);
	void removeData(const std::string& name);
	CCGData* getData(const std::string& name);

protected:
	Map<std::string, CCGData*> _datas;
};

NS_CC_END