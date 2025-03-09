#pragma once
#include <SDL3/SDL_vulkan.h>
#include <video/GenericRenderDevice.h>

class VulkanRenderDevice : public GenericRenderDevice {
protected:
  void doesNothing() override;
private:
  VkInstance instance;
public:
  void initSystem() override;
  void cleanupSystem() override;
};