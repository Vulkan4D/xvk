
// This file should only be used when XVK_EXPOSE_NATIVE_VULKAN_FUNCTIONS_NAMESPACE is defined
// DO NOT ADD THIS FILE TO COMPILE. Include it in one of your source files instead, after setting your configuration and having included all headers.
// DO NOT EDIT THIS FILE
// This file was generated via the xvk generator version 0.3.1
// from Vulkan-Headers Version 187

namespace XVK_EXPOSE_NATIVE_VULKAN_FUNCTIONS_NAMESPACE {
	XVK_DEF_INTERFACE_FUNC_C( vkGetInstanceProcAddr )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceProcAddr )

	
	#ifdef VK_USE_PLATFORM_ANDROID_KHR
	#endif

	
	#ifdef VK_ENABLE_BETA_EXTENSIONS
	#endif

	XVK_DEF_INTERFACE_FUNC_C( vkCreateInstance )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumerateInstanceExtensionProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumerateInstanceLayerProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumerateInstanceVersion )
	
	#ifdef VK_USE_PLATFORM_FUCHSIA
	#endif

	
	#ifdef VK_USE_PLATFORM_GGP
	#endif

	
	#ifdef VK_USE_PLATFORM_IOS_MVK
	#endif

	
	#ifdef VK_USE_PLATFORM_MACOS_MVK
	#endif

	
	#ifdef VK_USE_PLATFORM_METAL_EXT
	#endif

	
	#ifdef VK_USE_PLATFORM_VI_NN
	#endif

	
	#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_WIN32_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_XCB_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_XLIB_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
	#endif


	
	#ifdef VK_USE_PLATFORM_ANDROID_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkCreateAndroidSurfaceKHR )
	#endif

	
	#ifdef VK_ENABLE_BETA_EXTENSIONS
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceVideoCapabilitiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceVideoFormatPropertiesKHR )
	#endif

	XVK_DEF_INTERFACE_FUNC_C( vkDestroyInstance )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumeratePhysicalDevices )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFeatures )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFormatProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceImageFormatProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceQueueFamilyProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceMemoryProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDevice )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumerateDeviceExtensionProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumerateDeviceLayerProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSparseImageFormatProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumeratePhysicalDeviceGroups )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFeatures2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceProperties2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFormatProperties2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceImageFormatProperties2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceQueueFamilyProperties2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceMemoryProperties2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSparseImageFormatProperties2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalBufferProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalFenceProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalSemaphoreProperties )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroySurfaceKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfaceSupportKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfaceCapabilitiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfaceFormatsKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfacePresentModesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDevicePresentRectanglesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceDisplayPropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceDisplayPlanePropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDisplayPlaneSupportedDisplaysKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDisplayModePropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDisplayModeKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDisplayPlaneCapabilitiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDisplayPlaneSurfaceKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFeatures2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFormatProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceImageFormatProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceQueueFamilyProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceMemoryProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSparseImageFormatProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumeratePhysicalDeviceGroupsKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalBufferPropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalSemaphorePropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalFencePropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfaceCapabilities2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfaceFormats2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceDisplayProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceDisplayPlaneProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDisplayModeProperties2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDisplayPlaneCapabilities2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceFragmentShadingRatesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDebugReportCallbackEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDebugReportCallbackEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkDebugReportMessageEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceExternalImageFormatPropertiesNV )
	XVK_DEF_INTERFACE_FUNC_C( vkReleaseDisplayEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfaceCapabilities2EXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDebugUtilsMessengerEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDebugUtilsMessengerEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkSubmitDebugUtilsMessageEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceMultisamplePropertiesEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceCalibrateableTimeDomainsEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceToolPropertiesEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceCooperativeMatrixPropertiesNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateHeadlessSurfaceEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireDrmDisplayEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDrmDisplayEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireWinrtDisplayNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetWinrtDisplayNV )
	
	#ifdef VK_USE_PLATFORM_FUCHSIA
	XVK_DEF_INTERFACE_FUNC_C( vkCreateImagePipeSurfaceFUCHSIA )
	#endif

	
	#ifdef VK_USE_PLATFORM_GGP
	XVK_DEF_INTERFACE_FUNC_C( vkCreateStreamDescriptorSurfaceGGP )
	#endif

	
	#ifdef VK_USE_PLATFORM_IOS_MVK
	XVK_DEF_INTERFACE_FUNC_C( vkCreateIOSSurfaceMVK )
	#endif

	
	#ifdef VK_USE_PLATFORM_MACOS_MVK
	XVK_DEF_INTERFACE_FUNC_C( vkCreateMacOSSurfaceMVK )
	#endif

	
	#ifdef VK_USE_PLATFORM_METAL_EXT
	XVK_DEF_INTERFACE_FUNC_C( vkCreateMetalSurfaceEXT )
	#endif

	
	#ifdef VK_USE_PLATFORM_VI_NN
	XVK_DEF_INTERFACE_FUNC_C( vkCreateViSurfaceNN )
	#endif

	
	#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkCreateWaylandSurfaceKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceWaylandPresentationSupportKHR )
	#endif

	
	#ifdef VK_USE_PLATFORM_WIN32_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkCreateWin32SurfaceKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceWin32PresentationSupportKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceSurfacePresentModes2EXT )
	#endif

	
	#ifdef VK_USE_PLATFORM_XCB_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkCreateXcbSurfaceKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceXcbPresentationSupportKHR )
	#endif

	
	#ifdef VK_USE_PLATFORM_XLIB_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkCreateXlibSurfaceKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPhysicalDeviceXlibPresentationSupportKHR )
	#endif

	
	#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireXlibDisplayEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetRandROutputDisplayEXT )
	#endif


	
	#ifdef VK_USE_PLATFORM_ANDROID_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkGetAndroidHardwareBufferPropertiesANDROID )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryAndroidHardwareBufferANDROID )
	#endif

	
	#ifdef VK_ENABLE_BETA_EXTENSIONS
	XVK_DEF_INTERFACE_FUNC_C( vkCreateVideoSessionKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyVideoSessionKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetVideoSessionMemoryRequirementsKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkBindVideoSessionMemoryKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateVideoSessionParametersKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkUpdateVideoSessionParametersKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyVideoSessionParametersKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginVideoCodingKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndVideoCodingKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdControlVideoCodingKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDecodeVideoKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEncodeVideoKHR )
	#endif

	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDevice )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceQueue )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueSubmit )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueWaitIdle )
	XVK_DEF_INTERFACE_FUNC_C( vkDeviceWaitIdle )
	XVK_DEF_INTERFACE_FUNC_C( vkAllocateMemory )
	XVK_DEF_INTERFACE_FUNC_C( vkFreeMemory )
	XVK_DEF_INTERFACE_FUNC_C( vkMapMemory )
	XVK_DEF_INTERFACE_FUNC_C( vkUnmapMemory )
	XVK_DEF_INTERFACE_FUNC_C( vkFlushMappedMemoryRanges )
	XVK_DEF_INTERFACE_FUNC_C( vkInvalidateMappedMemoryRanges )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceMemoryCommitment )
	XVK_DEF_INTERFACE_FUNC_C( vkBindBufferMemory )
	XVK_DEF_INTERFACE_FUNC_C( vkBindImageMemory )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferMemoryRequirements )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageMemoryRequirements )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageSparseMemoryRequirements )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueBindSparse )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateFence )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyFence )
	XVK_DEF_INTERFACE_FUNC_C( vkResetFences )
	XVK_DEF_INTERFACE_FUNC_C( vkGetFenceStatus )
	XVK_DEF_INTERFACE_FUNC_C( vkWaitForFences )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateSemaphore )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroySemaphore )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateEvent )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyEvent )
	XVK_DEF_INTERFACE_FUNC_C( vkGetEventStatus )
	XVK_DEF_INTERFACE_FUNC_C( vkSetEvent )
	XVK_DEF_INTERFACE_FUNC_C( vkResetEvent )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateQueryPool )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyQueryPool )
	XVK_DEF_INTERFACE_FUNC_C( vkGetQueryPoolResults )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateBufferView )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyBufferView )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateImage )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyImage )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageSubresourceLayout )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateImageView )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyImageView )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateShaderModule )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyShaderModule )
	XVK_DEF_INTERFACE_FUNC_C( vkCreatePipelineCache )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyPipelineCache )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPipelineCacheData )
	XVK_DEF_INTERFACE_FUNC_C( vkMergePipelineCaches )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateGraphicsPipelines )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateComputePipelines )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyPipeline )
	XVK_DEF_INTERFACE_FUNC_C( vkCreatePipelineLayout )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyPipelineLayout )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateSampler )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroySampler )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDescriptorSetLayout )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDescriptorSetLayout )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDescriptorPool )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDescriptorPool )
	XVK_DEF_INTERFACE_FUNC_C( vkResetDescriptorPool )
	XVK_DEF_INTERFACE_FUNC_C( vkAllocateDescriptorSets )
	XVK_DEF_INTERFACE_FUNC_C( vkFreeDescriptorSets )
	XVK_DEF_INTERFACE_FUNC_C( vkUpdateDescriptorSets )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateFramebuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyFramebuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateRenderPass )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyRenderPass )
	XVK_DEF_INTERFACE_FUNC_C( vkGetRenderAreaGranularity )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateCommandPool )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyCommandPool )
	XVK_DEF_INTERFACE_FUNC_C( vkResetCommandPool )
	XVK_DEF_INTERFACE_FUNC_C( vkAllocateCommandBuffers )
	XVK_DEF_INTERFACE_FUNC_C( vkFreeCommandBuffers )
	XVK_DEF_INTERFACE_FUNC_C( vkBeginCommandBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkEndCommandBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkResetCommandBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindPipeline )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetViewport )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetScissor )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetLineWidth )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthBias )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetBlendConstants )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthBounds )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetStencilCompareMask )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetStencilWriteMask )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetStencilReference )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindDescriptorSets )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindIndexBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindVertexBuffers )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDraw )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndexed )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndirect )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndexedIndirect )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDispatch )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDispatchIndirect )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyImage )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBlitImage )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyBufferToImage )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyImageToBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdUpdateBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdFillBuffer )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdClearColorImage )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdClearDepthStencilImage )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdClearAttachments )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdResolveImage )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetEvent )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdResetEvent )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWaitEvents )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdPipelineBarrier )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginQuery )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndQuery )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdResetQueryPool )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWriteTimestamp )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyQueryPoolResults )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdPushConstants )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginRenderPass )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdNextSubpass )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndRenderPass )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdExecuteCommands )
	XVK_DEF_INTERFACE_FUNC_C( vkBindBufferMemory2 )
	XVK_DEF_INTERFACE_FUNC_C( vkBindImageMemory2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceGroupPeerMemoryFeatures )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDeviceMask )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDispatchBase )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageMemoryRequirements2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferMemoryRequirements2 )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageSparseMemoryRequirements2 )
	XVK_DEF_INTERFACE_FUNC_C( vkTrimCommandPool )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceQueue2 )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateSamplerYcbcrConversion )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroySamplerYcbcrConversion )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDescriptorUpdateTemplate )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDescriptorUpdateTemplate )
	XVK_DEF_INTERFACE_FUNC_C( vkUpdateDescriptorSetWithTemplate )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDescriptorSetLayoutSupport )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndirectCount )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndexedIndirectCount )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateRenderPass2 )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginRenderPass2 )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdNextSubpass2 )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndRenderPass2 )
	XVK_DEF_INTERFACE_FUNC_C( vkResetQueryPool )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSemaphoreCounterValue )
	XVK_DEF_INTERFACE_FUNC_C( vkWaitSemaphores )
	XVK_DEF_INTERFACE_FUNC_C( vkSignalSemaphore )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferDeviceAddress )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferOpaqueCaptureAddress )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceMemoryOpaqueCaptureAddress )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateSwapchainKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroySwapchainKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSwapchainImagesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireNextImageKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkQueuePresentKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceGroupPresentCapabilitiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceGroupSurfacePresentModesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireNextImage2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateSharedSwapchainsKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceGroupPeerMemoryFeaturesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDeviceMaskKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDispatchBaseKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkTrimCommandPoolKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryFdKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryFdPropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkImportSemaphoreFdKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSemaphoreFdKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdPushDescriptorSetKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdPushDescriptorSetWithTemplateKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDescriptorUpdateTemplateKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDescriptorUpdateTemplateKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkUpdateDescriptorSetWithTemplateKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateRenderPass2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginRenderPass2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdNextSubpass2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndRenderPass2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSwapchainStatusKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkImportFenceFdKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetFenceFdKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireProfilingLockKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkReleaseProfilingLockKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageMemoryRequirements2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferMemoryRequirements2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageSparseMemoryRequirements2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateSamplerYcbcrConversionKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroySamplerYcbcrConversionKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkBindBufferMemory2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkBindImageMemory2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDescriptorSetLayoutSupportKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndirectCountKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndexedIndirectCountKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSemaphoreCounterValueKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkWaitSemaphoresKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkSignalSemaphoreKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetFragmentShadingRateKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkWaitForPresentKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferDeviceAddressKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferOpaqueCaptureAddressKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceMemoryOpaqueCaptureAddressKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateDeferredOperationKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyDeferredOperationKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeferredOperationMaxConcurrencyKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeferredOperationResultKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDeferredOperationJoinKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPipelineExecutablePropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPipelineExecutableStatisticsKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPipelineExecutableInternalRepresentationsKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetEvent2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdResetEvent2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWaitEvents2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdPipelineBarrier2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWriteTimestamp2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueSubmit2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWriteBufferMarker2AMD )
	XVK_DEF_INTERFACE_FUNC_C( vkGetQueueCheckpointData2NV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyBuffer2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyImage2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyBufferToImage2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyImageToBuffer2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBlitImage2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdResolveImage2KHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDebugMarkerSetObjectTagEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkDebugMarkerSetObjectNameEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDebugMarkerBeginEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDebugMarkerEndEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDebugMarkerInsertEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindTransformFeedbackBuffersEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginTransformFeedbackEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndTransformFeedbackEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginQueryIndexedEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndQueryIndexedEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndirectByteCountEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateCuModuleNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateCuFunctionNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyCuModuleNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyCuFunctionNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCuLaunchKernelNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageViewHandleNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageViewAddressNVX )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndirectCountAMD )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawIndexedIndirectCountAMD )
	XVK_DEF_INTERFACE_FUNC_C( vkGetShaderInfoAMD )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginConditionalRenderingEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndConditionalRenderingEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetViewportWScalingNV )
	XVK_DEF_INTERFACE_FUNC_C( vkDisplayPowerControlEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkRegisterDeviceEventEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkRegisterDisplayEventEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSwapchainCounterEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetRefreshCycleDurationGOOGLE )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPastPresentationTimingGOOGLE )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDiscardRectangleEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkSetHdrMetadataEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkSetDebugUtilsObjectNameEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkSetDebugUtilsObjectTagEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueBeginDebugUtilsLabelEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueEndDebugUtilsLabelEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueInsertDebugUtilsLabelEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBeginDebugUtilsLabelEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdEndDebugUtilsLabelEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdInsertDebugUtilsLabelEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetSampleLocationsEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetImageDrmFormatModifierPropertiesEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateValidationCacheEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyValidationCacheEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkMergeValidationCachesEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetValidationCacheDataEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindShadingRateImageNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetViewportShadingRatePaletteNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetCoarseSampleOrderNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateAccelerationStructureNV )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyAccelerationStructureNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetAccelerationStructureMemoryRequirementsNV )
	XVK_DEF_INTERFACE_FUNC_C( vkBindAccelerationStructureMemoryNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBuildAccelerationStructureNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyAccelerationStructureNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdTraceRaysNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateRayTracingPipelinesNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetRayTracingShaderGroupHandlesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetRayTracingShaderGroupHandlesNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetAccelerationStructureHandleNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWriteAccelerationStructuresPropertiesNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCompileDeferredNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryHostPointerPropertiesEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWriteBufferMarkerAMD )
	XVK_DEF_INTERFACE_FUNC_C( vkGetCalibratedTimestampsEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawMeshTasksNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawMeshTasksIndirectNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawMeshTasksIndirectCountNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetExclusiveScissorNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetCheckpointNV )
	XVK_DEF_INTERFACE_FUNC_C( vkGetQueueCheckpointDataNV )
	XVK_DEF_INTERFACE_FUNC_C( vkInitializePerformanceApiINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkUninitializePerformanceApiINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetPerformanceMarkerINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetPerformanceStreamMarkerINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetPerformanceOverrideINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquirePerformanceConfigurationINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkReleasePerformanceConfigurationINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkQueueSetPerformanceConfigurationINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPerformanceParameterINTEL )
	XVK_DEF_INTERFACE_FUNC_C( vkSetLocalDimmingAMD )
	XVK_DEF_INTERFACE_FUNC_C( vkGetBufferDeviceAddressEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetLineStippleEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkResetQueryPoolEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetCullModeEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetFrontFaceEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetPrimitiveTopologyEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetViewportWithCountEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetScissorWithCountEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindVertexBuffers2EXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthTestEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthWriteEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthCompareOpEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthBoundsTestEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetStencilTestEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetStencilOpEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetGeneratedCommandsMemoryRequirementsNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdPreprocessGeneratedCommandsNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdExecuteGeneratedCommandsNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindPipelineShaderGroupNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateIndirectCommandsLayoutNV )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyIndirectCommandsLayoutNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCreatePrivateDataSlotEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyPrivateDataSlotEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkSetPrivateDataEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetPrivateDataEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetFragmentShadingRateEnumNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetVertexInputEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSubpassShadingHUAWEI )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBindInvocationMaskHUAWEI )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryRemoteAddressNV )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetPatchControlPointsEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetRasterizerDiscardEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetDepthBiasEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetLogicOpEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetPrimitiveRestartEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetColorWriteEnableEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawMultiEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdDrawMultiIndexedEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateAccelerationStructureKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkDestroyAccelerationStructureKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBuildAccelerationStructuresKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdBuildAccelerationStructuresIndirectKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkBuildAccelerationStructuresKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCopyAccelerationStructureKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCopyAccelerationStructureToMemoryKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCopyMemoryToAccelerationStructureKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkWriteAccelerationStructuresPropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyAccelerationStructureKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyAccelerationStructureToMemoryKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdCopyMemoryToAccelerationStructureKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetAccelerationStructureDeviceAddressKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdWriteAccelerationStructuresPropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceAccelerationStructureCompatibilityKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetAccelerationStructureBuildSizesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdTraceRaysKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCreateRayTracingPipelinesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetRayTracingCaptureReplayShaderGroupHandlesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdTraceRaysIndirectKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkCmdSetRayTracingPipelineStackSizeKHR )
	
	#ifdef VK_USE_PLATFORM_FUCHSIA
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryZirconHandleFUCHSIA )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryZirconHandlePropertiesFUCHSIA )
	XVK_DEF_INTERFACE_FUNC_C( vkImportSemaphoreZirconHandleFUCHSIA )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSemaphoreZirconHandleFUCHSIA )
	#endif

	
	#ifdef VK_USE_PLATFORM_GGP
	#endif

	
	#ifdef VK_USE_PLATFORM_IOS_MVK
	#endif

	
	#ifdef VK_USE_PLATFORM_MACOS_MVK
	#endif

	
	#ifdef VK_USE_PLATFORM_METAL_EXT
	#endif

	
	#ifdef VK_USE_PLATFORM_VI_NN
	#endif

	
	#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_WIN32_KHR
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryWin32HandleKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryWin32HandlePropertiesKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkImportSemaphoreWin32HandleKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetSemaphoreWin32HandleKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkImportFenceWin32HandleKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetFenceWin32HandleKHR )
	XVK_DEF_INTERFACE_FUNC_C( vkGetMemoryWin32HandleNV )
	XVK_DEF_INTERFACE_FUNC_C( vkAcquireFullScreenExclusiveModeEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkReleaseFullScreenExclusiveModeEXT )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceGroupSurfacePresentModes2EXT )
	#endif

	
	#ifdef VK_USE_PLATFORM_XCB_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_XLIB_KHR
	#endif

	
	#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
	#endif


}
