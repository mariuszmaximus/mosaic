#include <tiletextures.h>
#include <utilities.h>


bool createTileTextures(const std::vector<MoTile> &tiles,
                        int textureSize,
                        QOpenGLTexture *texture) {
    if (!texture) return false;
    if (texture->isCreated()) return false;
    if (tiles.empty()) return false;

    texture->setMipLevels(1);
    texture->setLayers(tiles.size());
    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setFormat(QOpenGLTexture::RGBA8U);
    texture->setSize(textureSize, textureSize);
    MO_CHECK_GL_ERROR;

    texture->allocateStorage();
    MO_CHECK_GL_ERROR;

    // Now upload the textures
    for (size_t i = 0; i < tiles.size(); ++i) {
        const MoTile& tile = tiles[i];
        QImage tileImage = tile.getImage()->scaled(textureSize, textureSize,
                                                   Qt::IgnoreAspectRatio,
                                                   Qt::FastTransformation);
        tileImage = tileImage.convertToFormat(QImage::Format_RGBA8888);
        texture->setData(0, i, QOpenGLTexture::RGBA_Integer,
                         QOpenGLTexture::UInt32_RGBA8,
                         (void*)tileImage.bits());
    }
    return true;
}
