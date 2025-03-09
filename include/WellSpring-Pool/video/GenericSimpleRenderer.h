#pragma once
#include <video/Renderer.h>
#include <video/GenericRenderDevice.h>

class GenericSimpleRenderer : public Renderer {
  GenericRenderDevice *_device;
  
public:
  GenericSimpleRenderer(GenericRenderDevice *rd);

  inline GenericSimpleRenderer() : _device(nullptr) {}

  void render(const Scene &) override;
};