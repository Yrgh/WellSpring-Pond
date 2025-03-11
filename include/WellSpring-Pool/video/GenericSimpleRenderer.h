#pragma once
#include <video/Renderer.h>
#include <video/RenderDevice.h>

class GenericSimpleRenderer : public Renderer {
  RenderDevice *_device;
  
public:
  GenericSimpleRenderer() = default;

  GenericSimpleRenderer(RenderDevice &);

  void render(const Scene &) override;
};