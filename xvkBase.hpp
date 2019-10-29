#pragma once

// You may override the following macros in your application

// Interface functions accessibility
//	these are useful to override when you are extending xvk classes for your own higher-level abstraction
#ifndef XVK_INTERFACE_LOADER_RAW_FUNCTIONS_ACCESSIBILITY
	#define XVK_INTERFACE_LOADER_RAW_FUNCTIONS_ACCESSIBILITY public
#endif
#ifndef XVK_INTERFACE_RAW_FUNCTIONS_ACCESSIBILITY
	#define XVK_INTERFACE_RAW_FUNCTIONS_ACCESSIBILITY public
#endif
#ifndef XVK_INTERFACE_ABSTRACTED_FUNCTIONS_ACCESSIBILITY
	#define XVK_INTERFACE_ABSTRACTED_FUNCTIONS_ACCESSIBILITY public
#endif

// XVK_CHECK_FUNC
// This macro will validate that the function pointer is loaded before calling it, avoiding a segfault.
// However, this should never be needed if available extensions are checked correctly before calling these functions.
// In release mode, we should leave it empty and keep these functions truly zero-cost
// You may override this macro to do whatever you want
#ifndef XVK_CHECK_FUNC
	#ifdef _DEBUG
		#define XVK_CHECK_FUNC(func) \
			if (!func) throw std::runtime_error("Vulkan Function " #func " failed to load");
	#else
		#define XVK_CHECK_FUNC(func)
	#endif
#endif


////////////////////////////////////////////////////////////////////


// This include is needed for loading libraries dynamically. In GCC for linux you need to add -ldl in your compiler options
#ifdef _WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

// for std::runtime_error
#include <stdexcept>

// Here we automatically include the vulkan header if it is not already included
#ifndef VULKAN_H_
	#define VK_NO_PROTOTYPES
	#include "Vulkan-Headers/include/vulkan/vulkan.h"
#endif

// Function loading macros
#define XVK_DEF_INTERFACE_FUNC(func) \
	PFN_##func func = 0;
#define XVK_LOAD_GLOBAL_FUNC(func) \
	if (!(func = (PFN_##func) vkGetInstanceProcAddr(nullptr, #func))){\
		throw std::runtime_error("Failed to load vulkan global function pointer for " #func);\
	}
#define XVK_LOAD_INSTANCE_FUNC(func) \
	func = (PFN_##func) loader->vkGetInstanceProcAddr(handle, #func);
#define XVK_LOAD_DEVICE_FUNC(func) \
	func = (PFN_##func) instance->vkGetDeviceProcAddr(handle, #func);

namespace xvk { namespace Base {
	class LoaderBase {
	protected:
		#ifdef _WIN32
			HINSTANCE vulkanLib = nullptr;
		#else
			void* vulkanLib = nullptr;
		#endif
		
		LoaderBase() {}
		
		virtual void LoadFunctionPointersInterface() = 0;
		
		~LoaderBase() {
			// Unload vulkan loader library
			if (vulkanLib) {
				#ifdef _WIN32
					FreeLibrary(vulkanLib);
				#else
					dlclose(vulkanLib);
				#endif
				vulkanLib = nullptr;
			}
		}
		
	public:
	
		XVK_DEF_INTERFACE_FUNC( vkGetInstanceProcAddr )
		
		bool operator()() {
			if (vulkanLib) return true;
			#ifdef _WIN32
				vulkanLib = LoadLibrary("vulkan-1.dll");
			#else
				vulkanLib = dlopen("libvulkan.so", RTLD_NOW);
			#endif
			if (!vulkanLib) {
				return false;
			}
			#ifdef _WIN32
				vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(vulkanLib, "vkGetInstanceProcAddr");
			#else
				vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(vulkanLib, "vkGetInstanceProcAddr");
			#endif
			if (!vkGetInstanceProcAddr) {
				return false;
			}
			LoadFunctionPointersInterface();
			return true;
		}
		
	};
	
	class InstanceBase {
	public: 
		LoaderBase* loader;
		VkInstance handle;
		
	protected:
	
		InstanceBase() : handle(VK_NULL_HANDLE){}
		InstanceBase(LoaderBase* loader, VkInstance instance) : loader(loader), handle(instance) {}
		
		virtual ~InstanceBase() {}
		
		virtual void LoadFunctionPointersInterface() = 0;
		
		void LoadFunctionPointers() {
			XVK_LOAD_INSTANCE_FUNC( vkGetDeviceProcAddr )
			LoadFunctionPointersInterface();
		}
		
	public:
	
		XVK_DEF_INTERFACE_FUNC( vkGetDeviceProcAddr )
		
	};
	
	class DeviceBase {
	public: 
		InstanceBase* instance;
		VkDevice handle;
		
	protected:
	
		DeviceBase() : handle(VK_NULL_HANDLE){}
		DeviceBase(InstanceBase* instance, VkDevice device) : instance(instance), handle(device) {}
		
		virtual ~DeviceBase() {}
		
		virtual void LoadFunctionPointersInterface() = 0;
		
		void LoadFunctionPointers() {
			LoadFunctionPointersInterface();
		}
		
	};
}}
