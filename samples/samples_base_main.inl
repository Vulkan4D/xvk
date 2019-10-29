#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

#define XVK_INTERFACE_RAW_FUNCTIONS_ACCESSIBILITY private
#include <xvk.hpp>
#include <GLFW/glfw3.h>

// Functions to implement 
void ApplicationInit();
void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void Draw(xvk::Instance* instance, xvk::Device* device, VkCommandBuffer cmdBuffer, VkImage image, VkImageSubresourceRange imageSubresourceRange);

#define APPLICATION_NAME "xvk sample application"
#define VULKAN_API_VERSION VK_API_VERSION_1_1
#define ENGINE_NAME "xvk"
#define ENGINE_VERSION VK_MAKE_VERSION(1, 0, 0)
#define APPLICATION_VERSION VK_MAKE_VERSION(1, 0, 0)

// Debug Callback
#ifdef _DEBUG
	VkDebugUtilsMessengerEXT vulkanCallbackExtFunction;
	static VKAPI_ATTR VkBool32 VKAPI_CALL vulkanDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* /*pUserData*/) {
			std::string type;
			switch (messageType) {
				default:
				case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: // Some event has happened that is unrelated to the specification or performance
					type = "";
				break;
				case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: // Something has happened that violates the specification or indicates a possible mistake
					type = "(validation)";
				break;
				case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: // Potential non-optimal use of Vulkan
					type = "(performance)";
				break;
			}
			switch (messageSeverity) {
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: // Diagnostic message
					std::cout << "VULKAN_VERBOSE" << type << ": " << pCallbackData->pMessage << std::endl;
				break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: // Informational message like the creation of a resource
					std::cout << "VULKAN_INFO" << type << ": " << pCallbackData->pMessage << std::endl;
				break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: // Message about behavior that is not necessarily an error, but very likely a bug in your application
					std::cout << "VULKAN_WARNING" << type << ": " << pCallbackData->pMessage << std::endl;
				break;
				default:
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: // Message about behavior that is invalid and may cause crashes
					std::cout << "VULKAN_ERROR" << type << ": " << pCallbackData->pMessage << std::endl;
				break;
			}
			return VK_FALSE; // The callback returns a boolean that indicates if the Vulkan call that triggered the validation layer message should be aborted. If the callback returns true, then the call is aborted with the VK_ERROR_VALIDATION_FAILED_EXT error. This is normally only used to test the validation layers themselves, so you should always return VK_FALSE.
	}
#endif

std::vector<const char*> requiredVulkanInstanceExtensions {
	#ifdef _DEBUG
	VK_EXT_DEBUG_UTILS_EXTENSION_NAME, // Debug extension (optional)
	#endif
	// extensions from glfw for creating a window will be added to this list
};
std::vector<const char*> requiredVulkanInstanceLayers {
	#ifdef _DEBUG
	"VK_LAYER_LUNARG_standard_validation", // validation layer (optional)
	#endif
};
std::vector<const char*> requiredVulkanDeviceExtensions {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};
std::vector<const char*> requiredVulkanDeviceLayers { };

// General vulkan functions are in this object
xvk::Loader vulkanLoader;

// Some Vulkan variables for displaying on screen
VkPhysicalDevice selectedPhysicalDevice = VK_NULL_HANDLE;
uint32_t graphicsQueueFamilyIndex = UINT32_MAX, presentQueueFamilyIndex = UINT32_MAX;
VkQueue graphicsQueue, presentQueue;
VkSurfaceKHR surface;
VkSemaphore imageAvailableSemaphore, renderingFinishedSemaphore;
VkSwapchainKHR swapChain;
VkCommandPool presentQueueCmdPool;
std::vector<VkCommandBuffer> presentQueueCmdBuffers {};

void CreateSwapChainAndRecordCommandBuffers(xvk::Instance* instance, xvk::Device* device) {
	
	// Get surface capabilities
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	if (instance->GetPhysicalDeviceSurfaceCapabilitiesKHR(selectedPhysicalDevice, surface, &surfaceCapabilities) != VK_SUCCESS) 
		throw std::runtime_error("Failed to check surface capabilities for presentation");
	
	// Get supported surface formats
	uint32_t surfaceFormatsCount;
	if (instance->GetPhysicalDeviceSurfaceFormatsKHR(selectedPhysicalDevice, surface, &surfaceFormatsCount, nullptr) != VK_SUCCESS || surfaceFormatsCount == 0)
		throw std::runtime_error("Failed to get surface formats count");
	std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatsCount);
	if (instance->GetPhysicalDeviceSurfaceFormatsKHR(selectedPhysicalDevice, surface, &surfaceFormatsCount, surfaceFormats.data()) != VK_SUCCESS) 
		throw std::runtime_error("Failed to get surface formats");
	
	// Get supported present modes
	uint32_t presentModesCount;
	if (instance->GetPhysicalDeviceSurfacePresentModesKHR(selectedPhysicalDevice, surface, &presentModesCount, nullptr) != VK_SUCCESS || presentModesCount == 0) 
		throw std::runtime_error("Faileed to get surface present modes count");
	std::vector<VkPresentModeKHR> presentModes;
	if (instance->GetPhysicalDeviceSurfacePresentModesKHR(selectedPhysicalDevice, surface, &presentModesCount, presentModes.data()) != VK_SUCCESS) 
		throw std::runtime_error("Faileed to get surface present modes");

	// Select number of swap chain images
	uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
	if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount) {
		imageCount = surfaceCapabilities.maxImageCount;
	}
	
	// Select a surface format
	VkSurfaceFormatKHR selectedSurfaceFormat  = surfaceFormats[0]; // Select the first supported format by default
	// If only one format is available and is undefined, it means that there is no preference, we may use our own preferred format.
	if(surfaceFormats.size() == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED) {
		selectedSurfaceFormat = {
			VK_FORMAT_R8G8B8A8_UNORM,
			VK_COLORSPACE_SRGB_NONLINEAR_KHR
		};
	} else {
		for (auto f : surfaceFormats) {
			// Use the first one that matches what that we need
			if (f.format == VK_FORMAT_R8G8B8A8_UNORM) {
				selectedSurfaceFormat = f;
				break;
			}
		}
	}
	
	// Select swap chain extent (surface resolution)
	VkExtent2D swapChainExtent;
	if (surfaceCapabilities.currentExtent.width == -1) {
		swapChainExtent = { 1280, 720 }; // Our preferred size
		if (swapChainExtent.width < surfaceCapabilities.minImageExtent.width) {
			swapChainExtent.width = surfaceCapabilities.minImageExtent.width;
		}
		if (swapChainExtent.height < surfaceCapabilities.minImageExtent.height) {
			swapChainExtent.height = surfaceCapabilities.minImageExtent.height;
		}
		if (swapChainExtent.width > surfaceCapabilities.maxImageExtent.width) {
			swapChainExtent.width = surfaceCapabilities.maxImageExtent.width;
		}
		if (swapChainExtent.height > surfaceCapabilities.maxImageExtent.height) {
			swapChainExtent.height = surfaceCapabilities.maxImageExtent.height;
		}
	} else {
		swapChainExtent = surfaceCapabilities.currentExtent;
	}
	
	// Swap chain usage flags
	VkImageUsageFlags swapChainUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	// Color attachment flag is always supported, but we must check for the other flags
	if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) == 0) {
		throw std::runtime_error("Surface usage flag unsupported: VK_IMAGE_USAGE_TRANSFER_DST_BIT");
	}
	
	// Select present mode
	VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	if (std::find(presentModes.begin(), presentModes.end(), presentMode) == presentModes.end()) {
		presentMode = VK_PRESENT_MODE_FIFO_KHR;
	}
	
	// Select transform
	VkSurfaceTransformFlagBitsKHR transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	if ((surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) == 0) {
		transform = surfaceCapabilities.currentTransform;
	}
	
	// Create the swap chain
	auto oldSwapChain = swapChain;
	VkSwapchainCreateInfoKHR swapChainCreateInfo {
		VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		nullptr, // pNext
		0, // flags
		surface,
		imageCount,
		selectedSurfaceFormat.format,
		selectedSurfaceFormat.colorSpace,
		swapChainExtent,
		1, // imageArrayLayers
		swapChainUsageFlags,
		VK_SHARING_MODE_EXCLUSIVE,
		0, // queue family index count
		nullptr, // queue family indices
		transform,
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		presentMode,
		VK_TRUE, // clipped
		oldSwapChain
	};
	if (device->CreateSwapchainKHR(&swapChainCreateInfo, nullptr, &swapChain) != VK_SUCCESS)
		throw std::runtime_error("Failed to create swap chain");
	if (oldSwapChain != VK_NULL_HANDLE) {
		device->DestroySwapchainKHR(oldSwapChain, nullptr);
	}
	
	// Get images from swap chain
	uint32_t swapChainImagesCount = 0;
	if (device->GetSwapchainImagesKHR(swapChain, &swapChainImagesCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Failed to get swap chain images count");
	std::vector<VkImage> swapChainImages(swapChainImagesCount);
	if (device->GetSwapchainImagesKHR(swapChain, &swapChainImagesCount, swapChainImages.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to get swap chain images");
		
	// Allocate command buffers
	presentQueueCmdBuffers.resize(swapChainImagesCount);
	VkCommandBufferAllocateInfo cmdBufferAllocateInfo {
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		nullptr, // pNext
		presentQueueCmdPool,
		VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		swapChainImagesCount
	};
	if (device->AllocateCommandBuffers(&cmdBufferAllocateInfo, presentQueueCmdBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers");
		
	VkImageSubresourceRange imageSubresourceRange {
		VK_IMAGE_ASPECT_COLOR_BIT, // aspect mask
		0, // base MipMap level
		1, // level count
		0, // base array layer
		1 // layer count
	};
		
	// Begin recording command buffers
	VkCommandBufferBeginInfo cmdBufferBeginInfo {
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		nullptr, // pNext
		VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
		nullptr // pInheritanceInfo
	};
	for (uint32_t i = 0; i < swapChainImagesCount; ++i) {
		VkImageMemoryBarrier barrierFromPresentToClear {
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			nullptr, // pNext
			VK_ACCESS_MEMORY_READ_BIT, // srcAccessMast
			VK_ACCESS_TRANSFER_WRITE_BIT, // dstAccessMask
			VK_IMAGE_LAYOUT_UNDEFINED, // oldLayout
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, // newLayout
			presentQueueFamilyIndex, // src queue index
			presentQueueFamilyIndex, // dst queue index
			swapChainImages[i], // image
			imageSubresourceRange
		};
		VkImageMemoryBarrier barrierFromClearToPresent {
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			nullptr, // pNext
			VK_ACCESS_TRANSFER_WRITE_BIT, // srcAccessMask
			VK_ACCESS_MEMORY_READ_BIT, // dstAccessMast
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, // oldLayout
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, // newLayout
			presentQueueFamilyIndex, // src queue index
			presentQueueFamilyIndex, // dst queue index
			swapChainImages[i], // image
			imageSubresourceRange
		};
		device->BeginCommandBuffer(presentQueueCmdBuffers[i], &cmdBufferBeginInfo);
		device->CmdPipelineBarrier(
			presentQueueCmdBuffers[i],
			VK_PIPELINE_STAGE_TRANSFER_BIT, // srcStageMask
			VK_PIPELINE_STAGE_TRANSFER_BIT, // dstStageMask
			0, // dependencyFlags
			0, // memoryBarrierCount
			nullptr, // memoryBarriers
			0, // bufferMemoryBarrierCount
			nullptr, // bufferMemoryBarriers
			1, // imageMemoryBarrierCount
			&barrierFromPresentToClear // imageMemoryBarriers
		);
		
		// Draw commands
		Draw(instance, device, presentQueueCmdBuffers[i], swapChainImages[i], imageSubresourceRange);
		
		device->CmdPipelineBarrier(
			presentQueueCmdBuffers[i],
			VK_PIPELINE_STAGE_TRANSFER_BIT,
			VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			0, // dependencyFlags
			0, // memoryBarrierCount,
			nullptr, // memoryBarriers
			0, // bufferMemoryBarrierCount
			nullptr, // bufferMemoryBarriers
			1, // imageMemoryBarrierCount
			&barrierFromClearToPresent
		);
		if (device->EndCommandBuffer(presentQueueCmdBuffers[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to record command buffers");
	}
}

int main() {
	
	// init GLFW
	if (!glfwInit()) {
		throw std::runtime_error("glfw init failed");
	}

	// Check for vulkan support
	if (!glfwVulkanSupported()) {
		throw std::runtime_error("Vulkan not supported");
	}
	
	// Load Vulkan library
	if (!vulkanLoader()) {
		throw std::runtime_error("Failed to load vulkan library");
	}
	
	// Application-specific Init
	ApplicationInit();

	// Required vulkan instance extensions for GLFW
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	requiredVulkanInstanceExtensions.reserve(glfwExtensionCount);
	for (uint32_t i = 0; i < glfwExtensionCount; i++) {
		requiredVulkanInstanceExtensions.push_back(glfwExtensions[i]);
	}
	
	// Check if all required instance extensions are available
	uint32_t availableInstanceExtensionsCount = 0;
	vulkanLoader.vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtensionsCount, nullptr);
	if (availableInstanceExtensionsCount == 0) throw std::runtime_error("Error enumerating available vulkan instance extensions count");
	std::vector<VkExtensionProperties> availableInstanceExtensions(availableInstanceExtensionsCount);
	if (vulkanLoader.vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtensionsCount, availableInstanceExtensions.data()) != VK_SUCCESS)
		throw std::runtime_error("Error enumerating available vulkan instance extensions");
	for (std::string reqExt : requiredVulkanInstanceExtensions) {
		if (std::none_of(availableInstanceExtensions.begin(), availableInstanceExtensions.end(), [&reqExt](VkExtensionProperties availExt){
			return reqExt == availExt.extensionName;
		})) throw std::runtime_error(std::string("Required vulkan instance extension not available: ") + reqExt);
	}
	
	// Check if all required instance layers are available
	uint32_t availableInstanceLayersCount = 0;
	vulkanLoader.vkEnumerateInstanceLayerProperties(&availableInstanceLayersCount, nullptr);
	if (availableInstanceLayersCount == 0) throw std::runtime_error("Error enumerating available vulkan instance layers count");
	std::vector<VkLayerProperties> availableInstanceLayers(availableInstanceLayersCount);
	if (vulkanLoader.vkEnumerateInstanceLayerProperties(&availableInstanceLayersCount, availableInstanceLayers.data()) != VK_SUCCESS)
		throw std::runtime_error("Error enumerating available vulkan instance layers");
	for (std::string reqLayer : requiredVulkanInstanceLayers) {
		if (std::none_of(availableInstanceLayers.begin(), availableInstanceLayers.end(), [&reqLayer](VkLayerProperties availLayer){
			return reqLayer == availLayer.layerName;
		})) throw std::runtime_error(std::string("Required vulkan instance layer not available: ") + reqLayer);
	}

	// Prepare appInfo for the Vulkan Instance
	VkApplicationInfo appInfo {
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		nullptr, //pNext
		APPLICATION_NAME,
		APPLICATION_VERSION,
		ENGINE_NAME,
		ENGINE_VERSION,
		VULKAN_API_VERSION
	};

	// Create the Vulkan instance
	VkInstanceCreateInfo createInfo {
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		nullptr, // pNext
		0, // flags
		&appInfo,
		(uint32_t)requiredVulkanInstanceLayers.size(),
		requiredVulkanInstanceLayers.data(),
		(uint32_t)requiredVulkanInstanceExtensions.size(),
		requiredVulkanInstanceExtensions.data()
	};
	xvk::Instance instance(&vulkanLoader, &createInfo);
	
	// Debug callbacks
	#ifdef _DEBUG
		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo {
			VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			nullptr,// pNext
			0,// flags
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, // messageSeverity
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, // messageType
			vulkanDebugCallback,// pfnUserCallback
			nullptr,// pUserData
		};
		if (false) { // log verbose
			debugUtilsMessengerCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
			debugUtilsMessengerCreateInfo.messageType |= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;
		}
		if (instance.CreateDebugUtilsMessengerEXT(&debugUtilsMessengerCreateInfo, nullptr, &vulkanCallbackExtFunction) != VK_SUCCESS) {
			std::cout << "Failed to set Vulkan Debug Callback Function" << std::endl;
		}
	#endif

	// Create Window/Surface
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST", nullptr, nullptr);
	if (glfwCreateWindowSurface(instance.handle, window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create vulkan surface through GLFW");
	}
	
	// Input Events
	glfwSetKeyCallback(window, KeyInputCallback);
	
	// Get physical devices
	uint32_t nbPhysicalDevices = 0;
	if ((instance.EnumeratePhysicalDevices(&nbPhysicalDevices, nullptr)) != VK_SUCCESS) {
		throw std::runtime_error("Failed to enumerate physical devices");
	}
	std::vector<VkPhysicalDevice> physicalDevices(nbPhysicalDevices);
	if ((instance.EnumeratePhysicalDevices(&nbPhysicalDevices, physicalDevices.data())) != VK_SUCCESS) {
		throw std::runtime_error("Failed to enumerate physical devices");
	}
	
	// Select a suitable physical device
	for (auto physicalDevice : physicalDevices) {
		
		// Check device properties
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		instance.GetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		instance.GetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
		if (deviceProperties.limits.maxImageDimension2D < 4096) continue;
		
		// Check device queue families
		uint32_t queueFamiliesCount = 0;
		instance.GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, nullptr);
		if (queueFamiliesCount == 0) continue;
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamiliesCount);
		instance.GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, queueFamilyProperties.data());
		for (uint32_t i = 0; i < queueFamiliesCount; ++i) {
			VkBool32 supportsPresent;
			instance.GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportsPresent);
			bool supportsGraphics = queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT;
			if (supportsPresent && supportsGraphics) {
				presentQueueFamilyIndex = i;
				graphicsQueueFamilyIndex = i;
				break;
			}
			if (presentQueueFamilyIndex == UINT32_MAX && supportsPresent) 
				presentQueueFamilyIndex = i;
			if (graphicsQueueFamilyIndex == UINT32_MAX && supportsGraphics) {
				graphicsQueueFamilyIndex = i;
			}
		}
		if (presentQueueFamilyIndex == UINT32_MAX || graphicsQueueFamilyIndex == UINT32_MAX) continue;
		
		// Get all available device extensions and layers
		uint32_t availableDeviceExtensionsCount = 0, availableDeviceLayersCount = 0;
		instance.EnumerateDeviceExtensionProperties(physicalDevice, nullptr, &availableDeviceExtensionsCount, nullptr);
		instance.EnumerateDeviceLayerProperties(physicalDevice, &availableDeviceLayersCount, nullptr);
		std::vector<VkExtensionProperties> availableDeviceExtensions(availableDeviceExtensionsCount);
		std::vector<VkLayerProperties> availableDeviceLayers(availableDeviceLayersCount);
		if (availableDeviceExtensionsCount == 0) throw std::runtime_error("Error enumerating available vulkan device extensions count");
		if (instance.EnumerateDeviceExtensionProperties(physicalDevice, nullptr, &availableDeviceExtensionsCount, availableDeviceExtensions.data()) != VK_SUCCESS)
			throw std::runtime_error("Error enumerating available vulkan device extensions");
		#ifdef _DEBUG
			if (availableDeviceLayersCount == 0) throw std::runtime_error("Error enumerating available vulkan device layers count");
		#endif
		if (instance.EnumerateDeviceLayerProperties(physicalDevice, &availableDeviceLayersCount, availableDeviceLayers.data()) != VK_SUCCESS)
			throw std::runtime_error("Error enumerating available vulkan device layers");
		// Check if all required device extensions and layers are available
		for (std::string reqExt : requiredVulkanDeviceExtensions) {
			if (std::none_of(availableDeviceExtensions.begin(), availableDeviceExtensions.end(), [&reqExt](VkExtensionProperties availExt){
				return reqExt == availExt.extensionName;
			})) goto NextPhysicalDevice;
		}
		for (std::string reqLayer : requiredVulkanDeviceLayers) {
			if (std::none_of(availableDeviceLayers.begin(), availableDeviceLayers.end(), [&reqLayer](VkLayerProperties availLayer){
				return reqLayer == availLayer.layerName;
			})) goto NextPhysicalDevice;
		}
		
		// Current physical device is good
		selectedPhysicalDevice = physicalDevice;
		break;
		
		NextPhysicalDevice: continue;
	}
	if (selectedPhysicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("Failed to find a suitable physical device");
	}

	// Prepare structs for logical device creation...
	std::vector<float> queuePriorities {1.0};
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos {};
	queueCreateInfos.push_back({
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		nullptr, // pNext
		0, // flags,
		graphicsQueueFamilyIndex,
		(uint32_t)queuePriorities.size(),
		queuePriorities.data()
	});
	if (presentQueueFamilyIndex != graphicsQueueFamilyIndex) {
		queueCreateInfos.push_back({
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			nullptr, // pNext
			0, // flags,
			presentQueueFamilyIndex,
			(uint32_t)queuePriorities.size(),
			queuePriorities.data()
		});
	}
	
	// Create the vulkan device
	VkDeviceCreateInfo deviceCreateInfo {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		nullptr, // pNext
		0, // flags
		(uint32_t)queueCreateInfos.size(), // queueCreateInfoCount
		queueCreateInfos.data(), // can be an array to create a logical device with multiple queues
		0, // enabled layer count
		nullptr, // array enabled layer names
		(uint32_t)requiredVulkanDeviceExtensions.size(),
		requiredVulkanDeviceExtensions.data(),
		nullptr // enabled features
	};
	xvk::Device device(&instance, selectedPhysicalDevice, &deviceCreateInfo);
	
	// Get queues
	device.GetDeviceQueue(graphicsQueueFamilyIndex, 0/*queue index for this queue family*/, &graphicsQueue);
	device.GetDeviceQueue(presentQueueFamilyIndex, 0/*queue index for this queue family*/, &presentQueue);
	
	// Semaphores
	VkSemaphoreCreateInfo semaphoreCreateInfo {
		VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		nullptr, // pNext
		0 // flags
	};
	if (device.CreateSemaphore(&semaphoreCreateInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS)
		throw std::runtime_error("Failed to create semaphore");
	if (device.CreateSemaphore(&semaphoreCreateInfo, nullptr, &renderingFinishedSemaphore) != VK_SUCCESS)
		throw std::runtime_error("Failed to create semaphore");
		
	// Command Pool
	VkCommandPoolCreateInfo cmdPoolCreateInfo {
		VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		nullptr, // pNext
		0, // flags
		presentQueueFamilyIndex
	};
	if (device.CreateCommandPool(&cmdPoolCreateInfo, nullptr, &presentQueueCmdPool))
		throw std::runtime_error("Failed to create command pool");
	
	CreateSwapChainAndRecordCommandBuffers(&instance, &device);
	
	// Running...
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		uint32_t imageIndex;
		VkResult result = device.AcquireNextImageKHR(
			swapChain, // swap chain
			UINT64_MAX, // timeout
			imageAvailableSemaphore, // semaphore 
			VK_NULL_HANDLE, // fence
			&imageIndex // output image index
		);
		switch (result) {
			case VK_SUCCESS:
			case VK_SUBOPTIMAL_KHR:
				break;
			case VK_ERROR_OUT_OF_DATE_KHR:
				// refresh swap chain with new resolution
				CreateSwapChainAndRecordCommandBuffers(&instance, &device);
				continue;
			default:
				throw std::runtime_error("Failed to acquire swap chain image");
				break;
		}
			
		// Submit
		VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		VkSubmitInfo submitInfo {
			VK_STRUCTURE_TYPE_SUBMIT_INFO,
			nullptr, // pNext
			1, // waitSemaphoreCount
			&imageAvailableSemaphore, // array of semaphores to wait for
			&waitDstStageMask, // array of the same amount of elements as semaphores to wait for
			(uint32_t)presentQueueCmdBuffers.size(),
			presentQueueCmdBuffers.data(),
			1, // signalSemaphoreCount
			&renderingFinishedSemaphore // array of semaphores to signal when rendering is finished
		};
		if (device.QueueSubmit(presentQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
			throw std::runtime_error("Failed to submit queue");
		
		VkPresentInfoKHR presentInfo {
			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			nullptr,// pNext
			1, // waitSemaphoreCount
			&renderingFinishedSemaphore, 
			1, // swap chain count
			&swapChain,
			&imageIndex,
			nullptr, // pResults
		};
		result = device.QueuePresentKHR(presentQueue, &presentInfo);
		switch (result) {
			case VK_SUCCESS:
				break;
			case VK_ERROR_OUT_OF_DATE_KHR:
				// refresh swap chain with new resolution
				CreateSwapChainAndRecordCommandBuffers(&instance, &device);
				continue;
			default:
				throw std::runtime_error("Failed to present queue");
				break;
		}
	}
	
	// Wait for device to finish processing...
	device.DeviceWaitIdle();
	
	// Free command buffers (not necessary here, since destroying a command pool frees its command buffers)
	device.FreeCommandBuffers(presentQueueCmdPool, (uint32_t)presentQueueCmdBuffers.size(), presentQueueCmdBuffers.data());
	presentQueueCmdBuffers.clear();
	
	// Destroy command pools
	device.DestroyCommandPool(presentQueueCmdPool, nullptr);
	
	// Destroy semaphores
	device.DestroySemaphore(imageAvailableSemaphore, nullptr);
	device.DestroySemaphore(renderingFinishedSemaphore, nullptr);
	
	// Destroy swap chain
	device.DestroySwapchainKHR(swapChain, nullptr);
	
	// Cleanup vulkan surface and glfw
	instance.DestroySurfaceKHR(surface, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
	
	#ifdef _DEBUG
		instance.DestroyDebugUtilsMessengerEXT(vulkanCallbackExtFunction, nullptr);
	#endif
}
