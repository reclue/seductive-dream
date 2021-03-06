#include "storage/texturestorage.h"

#include <filesystem>


namespace {

static const GLenum DEFAULT_TEXTURE_UNIT { GL_TEXTURE0 };

static std::filesystem::path defaultTexturePath {
    R"png(./resources/textures/default_texture.png)png"
};

} // namespace


TextureStorage::TextureStorage() :
    m_textures {} {

    defaultTexturePath = std::filesystem::canonical(defaultTexturePath);

    m_textures.insert({ defaultTexturePath.string(),
                        std::make_shared<Texture>(defaultTexturePath) });
}

TextureStorage::TextureStorage(
    const std::initializer_list<std::filesystem::path>& paths) :
    TextureStorage {} {

    for (auto path : paths) {
        path = std::filesystem::canonical(path);

        if (!m_textures.count(path.string())) {
            m_textures.insert({ path.string(), std::make_shared<Texture>(path) });
        }
    }
}

TextureStorage::~TextureStorage() {
    for (auto& [key, texture] : m_textures) {
        texture.reset();
    }

    m_textures.clear();
}

TextureStorage::ValueType
    TextureStorage::Get(std::filesystem::path path) {
    return Get(path, DEFAULT_TEXTURE_UNIT);
}

const TextureStorage::ValueType
    TextureStorage::Get(std::filesystem::path path) const {
    return Get(path, DEFAULT_TEXTURE_UNIT);
}

TextureStorage::ValueType
    TextureStorage::GetDefaultTexture() {
    return GetDefaultTexture(DEFAULT_TEXTURE_UNIT);
}

const TextureStorage::ValueType
    TextureStorage::GetDefaultTexture() const {
    return GetDefaultTexture(DEFAULT_TEXTURE_UNIT);
}


TextureStorage::ValueType
    TextureStorage::Get(std::filesystem::path path, GLenum textureUnit) {

    path = std::filesystem::canonical(path);

    if (!m_textures.count(path.string())) {
        m_textures.insert({ path.string(), std::make_shared<Texture>(path) });
    }

    m_textures.at(path.string())->SetTextureUnit(textureUnit);

    return m_textures.at(path.string());
}

TextureStorage::ValueType TextureStorage::Get(const TextureParams& textureData) {
    return Get(textureData.GetPath(), textureData.GetUnit());
}

const TextureStorage::ValueType
    TextureStorage::Get(const TextureParams& textureData) const {
    return Get(textureData.GetPath(), textureData.GetUnit());
}

const TextureStorage::ValueType
    TextureStorage::Get(std::filesystem::path path, GLenum textureUnit) const {

    path = std::filesystem::canonical(path);

    if (!m_textures.count(path.string())) {
        m_textures.insert({ path.string(), std::make_shared<Texture>(path) });
    }

    m_textures.at(path.string())->SetTextureUnit(textureUnit);

    return m_textures.at(path.string());
}

TextureStorage::ValueType
    TextureStorage::GetDefaultTexture(GLenum textureUnit) {

    m_textures.at(defaultTexturePath.string())->SetTextureUnit(textureUnit);
    return m_textures.at(defaultTexturePath.string());
}

const TextureStorage::ValueType
    TextureStorage::GetDefaultTexture(GLenum textureUnit) const {

    m_textures.at(defaultTexturePath.string())->SetTextureUnit(textureUnit);
    return m_textures.at(defaultTexturePath.string());
}

std::filesystem::path TextureStorage::GetDefaultTexturePath() const {
    return defaultTexturePath;
}