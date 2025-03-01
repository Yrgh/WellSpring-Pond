#pragma once
#include <SDL3/SDL_vulkan.h>
#include <video/GenericRenderDevice.h>

class VulkanRenderDevice : public GenericRenderDevice {
protected:
  void doesNothing() override;
public:
  
};