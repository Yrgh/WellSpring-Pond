#pragma once
#include <video/Renderer.h>
#include <video/GenericRenderDevice.h>

class GenericSimpleRenderer : public Renderer {
  GenericRenderDevice *_device;
  
public:
  GenericSimpleRenderer(GenericRenderDevice *rd);

  void render(const Scene &) override;
};