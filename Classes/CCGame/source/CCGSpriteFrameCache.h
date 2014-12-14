#pragma once

#include "cocos2d.h"
#include "CCGSpriteFrame.h"

NS_CC_BEGIN

class Sprite;
class Texture2D;

class CCGSpriteFrameCache : public Ref
{
public:
    /** Returns the shared instance of the Sprite Frame cache */
    static CCGSpriteFrameCache* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static CCGSpriteFrameCache* sharedFTGSpriteFrameCache() { return CCGSpriteFrameCache::getInstance(); }

    /** Destroys the cache. It releases all the Sprite Frames and the retained instance. */
    static void destroyInstance();

    /** @deprecated Use destroyInstance() instead  */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedFTGSpriteFrameCache() { return CCGSpriteFrameCache::destroyInstance(); }

protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    CCGSpriteFrameCache(){}

public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCGSpriteFrameCache();
    bool init();

public:
    /** Adds multiple Sprite Frames from a plist file.
     * A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png
     * If you want to use another texture, you should use the addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName) method.
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
     @since v0.99.5
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames. 
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** Adds multiple Sprite Frames from a plist file content. The texture will be associated with the created sprite frames. 
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture);

    /** Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     */
    void addSpriteFrame(CCGSpriteFrame *frame, const std::string& frameName);

    /** Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeSpriteFrames();

    /** Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     */
    void removeUnusedSpriteFrames();

    /** Deletes an sprite frame from the sprite frame cache. */
    void removeSpriteFrameByName(const std::string& name);

    /** Removes multiple Sprite Frames from a plist file.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    * @since v0.99.5
    */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** Removes multiple Sprite Frames from a plist file content.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    */
    void removeSpriteFramesFromFileContent(const std::string& plist_content);

    /** Removes all Sprite Frames associated with the specified textures.
     * It is convenient to call this method when a specific texture needs to be removed.
     * @since v0.995.
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it. 
     * @js getSpriteFrame
     * @lua getSpriteFrame
     */
	CCGSpriteFrame* getFTGSpriteFrameByName(const std::string& name);

	/** Return SpriteFrame* type in order to compatible with default SpriteFrameCache. */
	SpriteFrame* getSpriteFrameByName(const std::string& name) { return static_cast<SpriteFrame*>(getFTGSpriteFrameByName(name)); }
	CC_DEPRECATED_ATTRIBUTE SpriteFrame* spriteFrameByName(const std::string&name) { return getSpriteFrameByName(name); }

private:
    /*Adds multiple Sprite Frames with a dictionary. The texture will be associated with the created sprite frames.
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /** Removes multiple Sprite Frames from Dictionary.
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(ValueMap& dictionary);

protected:
    Map<std::string, CCGSpriteFrame*> _spriteFrames;
    ValueMap _spriteFramesAliases;
    std::set<std::string>*  _loadedFileNames;
};

// end of sprite_nodes group
/// @}

NS_CC_END
