#include <video/GPUInterface.h>
#include <scene/Scene.h>

class DefaultRenderer {
public:
    GPUInterface *gpu;

    void render(const Scene &);
};