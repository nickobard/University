#include "NullTexture.hpp"

bool NullTexture::LoadTexture(const string &path) {
    return true;
}

bool NullTexture::LoadTexture(const string &path, const TextureSize<float> &size) {
    return true;
}

void NullTexture::RenderTexture(const Vector2<float> &position) const {

}

bool NullTexture::SetNativeTextureSize() {
    return true;
}
