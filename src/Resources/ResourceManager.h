#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace RenderEngine
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

class ResourceManager
{
public:
	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();

	~ResourceManager() = delete;
		ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	

	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);
	
	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
													    const std::string& textureName,
													    const std::string& shaderName,
													    const unsigned int spriteWidth,
													    const unsigned int spriteHeight,
													    const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
																	    const std::string& textureName,
																	    const std::string& shaderName,
																   	    const unsigned int spriteWidth,
																	    const unsigned int spriteHeight,
																	    const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName,
															     std::string texturePath,
															     std::vector<std::string> subTextures,
															     const unsigned int subTextureWidth,
															     const unsigned int subTextureHeight);

	static bool loadJSONResources(const std::string& JSONPath);

private:
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpritesMap;

	static ShaderProgramsMap m_shaderPrograms;
	static TexturesMap m_textures;
	static SpritesMap m_sprites;
	static AnimatedSpritesMap m_animatedSprites;

	static std::string m_path;

	static std::string getFileString(const std::string& relativFilePath);
};