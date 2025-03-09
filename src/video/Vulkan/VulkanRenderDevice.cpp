#include <video/Vulkan/VulkanRenderDevice.h>

void VulkanRenderDevice::doesNothing() {}

void VulkanRenderDevice::initSystem() {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
}