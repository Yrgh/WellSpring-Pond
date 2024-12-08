#include <Window.h>
#include <string>

// We don't want them to get blended together
typedef int TextureID;
typedef int ShaderID;
typedef int MeshID;
typedef int BufferID;

// A polymorphic class to use 3D GPU frameworks without having to write NEARLY as much code (especially for Vulkan).
class GPUInterface {
protected:
    float _aspect; // This should be set by setViewport

    virtual void _addWindow(Window *);
    virtual void _removeWindow(Window *);
public:
    virtual ~GPUInterface();

    virtual TextureID createTexture(int width, int height, int channels);
    virtual void deleteTexture(TextureID id);
    virtual void bindTexture(TextureID id, int slot);
    virtual void setTexture(TextureID tex, BufferID buf);
    virtual void setTexture(TextureID tex, void *data);
    virtual void getTexture(TextureID tex, BufferID buf);
    virtual void getTexture(TextureID tex, void *data);

    virtual BufferID createBuffer(int size);
    virtual void deleteBuffer(BufferID id);
    virtual void updateBuffer(BufferID id, void *data);
    virtual void *readBuffer(BufferID id);

    virtual ShaderID createRenderShader(const std::string &vertex, const std::string &fragment);
    virtual void deleteShader(ShaderID id);
    virtual void useShader(ShaderID id);

    virtual MeshID loadMesh(void *vertexData, int vertexSize, uint32_t *indexData, int indexSize);
    virtual void deleteMesh(MeshID id);
    virtual void updateMesh(MeshID id, void *vertexData, int vertexSize, uint32_t *indexData, int indexSize);
    virtual void drawMesh(MeshID id /* TODO */);

    virtual void setClearColor(float r, float g, float b, float a = 1.0);
    virtual void clear();

    virtual void setViewport(float x, float y, float w, float h);

    inline void addWindow(Window &window) {
        _addWindow(&window);
        window._on_destroy.subscribe(BIND_METHOD(*this, _removeWindow));
    }

    // Make sure to check that the window is added first
    virtual void setWindow(Window &window);

    // Default
    virtual void cullBack();
    inline void cullCCW() { cullBack(); }
    // Reversed
    virtual void cullFront(); 
    inline void cullCW() { cullFront(); }
    // Disabled
    virtual void cullNone();

    // I guess...?
    virtual void finishFrame();
};