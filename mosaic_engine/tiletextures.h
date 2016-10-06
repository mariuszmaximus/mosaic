#ifndef TILETEXTURES_H
#define TILETEXTURES_H

#include <tile.h>
#include <QOpenGLTexture>


/**
 * @brief Create an array texture from tiles
 * @param tiles The tiles
 * @param textureSize The size in pixels of each tile texture
 * @param texture The generated array texture.  The array texture is only
 *        generated if the texture has not been created previously, if it is
 *        not null, and if the tiles vector is not empty.
 * @return true if the array texture was created.  False otherwise.
 */
bool moCreateTileTextures(const std::vector<MoTile>& tiles,
                          int textureSize,
                          QOpenGLTexture* texture);

#endif // TILETEXTURES_H
