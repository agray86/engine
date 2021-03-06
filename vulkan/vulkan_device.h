// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_VULKAN_VULKAN_DEVICE_H_
#define FLUTTER_VULKAN_VULKAN_DEVICE_H_

#include <vector>

#include "flutter/vulkan/vulkan_handle.h"
#include "lib/ftl/compiler_specific.h"
#include "lib/ftl/macros.h"

namespace vulkan {

class VulkanProcTable;
class VulkanSurface;

class VulkanDevice {
 public:
  VulkanDevice(VulkanProcTable& vk,
               VulkanHandle<VkPhysicalDevice> physical_device);

  ~VulkanDevice();

  bool IsValid() const;

  const VulkanHandle<VkDevice>& GetHandle() const;

  const VulkanHandle<VkPhysicalDevice>& GetPhysicalDeviceHandle() const;

  const VulkanHandle<VkQueue>& GetQueueHandle() const;

  const VulkanHandle<VkCommandPool>& GetCommandPool() const;

  uint32_t GetGraphicsQueueIndex() const;

  void ReleaseDeviceOwnership();

  FTL_WARN_UNUSED_RESULT
  bool GetSurfaceCapabilities(const VulkanSurface& surface,
                              VkSurfaceCapabilitiesKHR* capabilities) const;

  FTL_WARN_UNUSED_RESULT
  bool GetPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* features) const;

  FTL_WARN_UNUSED_RESULT
  bool GetPhysicalDeviceFeaturesSkia(
      uint32_t* /* mask of GrVkFeatureFlags */ features) const;

  FTL_WARN_UNUSED_RESULT
  bool ChooseSurfaceFormat(const VulkanSurface& surface,
                           VkSurfaceFormatKHR* format) const;

  FTL_WARN_UNUSED_RESULT
  bool ChoosePresentMode(const VulkanSurface& surface,
                         VkPresentModeKHR* present_mode) const;

  FTL_WARN_UNUSED_RESULT
  bool QueueSubmit(std::vector<VkPipelineStageFlags> wait_dest_pipeline_stages,
                   const std::vector<VkSemaphore>& wait_semaphores,
                   const std::vector<VkSemaphore>& signal_semaphores,
                   const std::vector<VkCommandBuffer>& command_buffers,
                   const VulkanHandle<VkFence>& fence) const;

  FTL_WARN_UNUSED_RESULT
  bool WaitIdle() const;

 private:
  VulkanProcTable& vk;
  VulkanHandle<VkPhysicalDevice> physical_device_;
  VulkanHandle<VkDevice> device_;
  VulkanHandle<VkQueue> queue_;
  VulkanHandle<VkCommandPool> command_pool_;
  uint32_t graphics_queue_index_;
  bool valid_;

  std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties() const;

  FTL_DISALLOW_COPY_AND_ASSIGN(VulkanDevice);
};

}  // namespace vulkan

#endif  // FLUTTER_VULKAN_VULKAN_DEVICE_H_
