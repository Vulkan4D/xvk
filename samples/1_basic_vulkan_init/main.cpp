#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <cstring>

// Include xvk
#include "xvk.hpp"

#define VULKAN_API_VERSION VK_API_VERSION_1_1
#define ENGINE_NAME "xvk"
#define ENGINE_VERSION VK_MAKE_VERSION(1, 0, 0)
#define APPLICATION_NAME "xvk samples - basic vulkan init"
#define APPLICATION_VERSION VK_MAKE_VERSION(1, 0, 0)

std::vector<const char*> requiredVulkanInstanceExtensions {
	#ifdef _DEBUG
	VK_EXT_DEBUG_UTILS_EXTENSION_NAME, // Debug extension (optional)
	#endif
};
std::vector<const char*> requiredVulkanInstanceLayers {
	#ifdef _DEBUG
	"VK_LAYER_LUNARG_standard_validation", // validation layer (optional)
	#endif
};

int main() {
	
	// Load Vulkan library
	xvk::Loader vulkanLoader;
	if (!vulkanLoader()) {
		throw std::runtime_error("Failed to load vulkan library");
		return 1;
	}

	// Check if all required extensions are available
	uint32_t availableExtensionsCount = 0;
	vulkanLoader.vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
	if (availableExtensionsCount == 0) throw std::runtime_error("Error enumerating available vulkan extensions count");
	std::vector<VkExtensionProperties> availableExtensions(availableExtensionsCount);
	if (vulkanLoader.vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, availableExtensions.data()) != VK_SUCCESS)
		throw std::runtime_error("Error enumerating available vulkan extensions");
	for (std::string reqExt : requiredVulkanInstanceExtensions) {
		if (std::none_of(availableExtensions.begin(), availableExtensions.end(), [&reqExt](VkExtensionProperties availExt){
			return reqExt == availExt.extensionName;
		})) throw std::runtime_error(std::string("Required extension not available: ") + reqExt);
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
		})) throw std::runtime_error(std::string("Required vulkan instance extension not available: ") + reqLayer);
	}

	// Prepare structs for the Vulkan Instance
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = APPLICATION_NAME;
	appInfo.applicationVersion = APPLICATION_VERSION;
	appInfo.pEngineName = ENGINE_NAME;
	appInfo.engineVersion = ENGINE_VERSION;
	appInfo.apiVersion = VULKAN_API_VERSION;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = (uint32_t)requiredVulkanInstanceExtensions.size();
	createInfo.ppEnabledExtensionNames = requiredVulkanInstanceExtensions.data();
	createInfo.enabledLayerCount = (uint32_t)requiredVulkanInstanceLayers.size();
	createInfo.ppEnabledLayerNames = requiredVulkanInstanceLayers.data();
	
	// Create the Vulkan instance
	xvk::Instance vulkanInstance(&vulkanLoader, &createInfo);

	// Get physical devices
	uint32_t nbPhysicalDevices = 0;
	if ((vulkanInstance.EnumeratePhysicalDevices(&nbPhysicalDevices, nullptr)) != VK_SUCCESS) {
		throw std::runtime_error("Failed to enumerate physical devices");
	}
	std::vector<VkPhysicalDevice> physicalDevices(nbPhysicalDevices);
	if ((vulkanInstance.EnumeratePhysicalDevices(&nbPhysicalDevices, physicalDevices.data())) != VK_SUCCESS) {
		throw std::runtime_error("Failed to enumerate physical devices");
	}
	
	// Select a suitable physical device
	VkPhysicalDevice selectedPhysicalDevice = VK_NULL_HANDLE;
	for (auto physicalDevice : physicalDevices) {
		
		// Check device properties
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vulkanInstance.GetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		vulkanInstance.GetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
		if (deviceProperties.limits.maxImageDimension2D < 4096) continue; // not a suitable device if cannot render images of at least 4096 pixels ?
		
		// Check device features
		uint32_t queueFamiliesCount = 0;
		vulkanInstance.GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, nullptr);
		if (queueFamiliesCount == 0) continue; // not a suitable device if no queue families ?
		
		// Check queue families...
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamiliesCount);
		vulkanInstance.GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, queueFamilyProperties.data());
		// Maybe loop through queue families and check some more properties... select some family queue index for next step...
		
		// Select this physical device if it is suitable for your needs
		selectedPhysicalDevice = physicalDevice;
		break;
	}
	if (selectedPhysicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("Failed to find a suitable physical device");
	}

	// Create logical device
	std::vector<float> queuePriorities = {1.0};
	VkDeviceQueueCreateInfo queueCreateInfo = {
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		nullptr, // pNext
		0, // flags,
		0, // queue family index (may be figured out during the physical device selection)
		(uint32_t)queuePriorities.size(),
		queuePriorities.data()
	};
	VkDeviceCreateInfo deviceCreateInfo = {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		nullptr, // pNext
		0, // flags
		1, // queueCreateInfoCount
		&queueCreateInfo, // can be an array to create a logical device with multiple queues
		0, // enabled layer count
		nullptr, // array enabled layer names
		0, // enabled extensions count
		nullptr, // array enabled extensions names
		nullptr // enabled features
	};
	
	// Create the actual vulkan device
	xvk::Device vulkanDevice(&vulkanInstance, selectedPhysicalDevice, &deviceCreateInfo);
	
	// ... you may now do anything you want with your vulkan application, through vulkanDevice
	
	// No need to destroy the original vulkan handles stored in xvk::Device and xvk::Instance
	//	their destructors will take care of that for you !
	
	return 0; // end program
}
