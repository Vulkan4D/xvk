# `xvk` - a fast and lightweight Vulkan wrapper / dynamic loader

`xvk` works on both Windows and Linux and is compiler-agnostic (only requires a C++11 compatible compiler)

Using `xvk` is probably the easiest and fastest way to get started with making your first Vulkan application, but is also very fast and zero-cost abstraction for all performance-critical functions. 

You simply need to clone this repository (and submodules) then include a single header file.

`xvk` loads Vulkan 100% at runtime (which is also the safest way to load vulkan according to Khronos). 

`xvk` will run faster than a naive linked-library implementation, because of the fact that we are loading the function pointers at runtime, when calling these functions we also save some cpu time usually spent inside an abstraction in the loader, we are now directly accessing the function pointers inside the drivers instead. 

Also, `xvk` takes care of downloading and including the necessary Vulkan headers (downloaded via a git submodule).

`xvk` implements all vk* functions as is, meaning no need to re-learn vulkan, but also gives you a few additionnal and convenient inlined functions that abstracts away VkInstance and VkDevice handles, all in a zero-cost way. 

No seriously, it's the easiest way to implement Vulkan in your project... 

## Adding it to your project
```bash
# Simply run this command from within your project's source or include directory
git submodule add --recursive git@github.com:Vulkan4D/xvk.git
```

If you are NOT already using `git` for your project, simply run `git init` first

## Basic Usage

```C++
#include "xvk/xvk.hpp"

xvk::Loader vulkanLoader;

int main() {
	
	// Dynamically Load the Vulkan library
	if (!vulkanLoader()) { // convenient operator() to actually load the library
		// ERROR: Failed to load vulkan library. 
		// The application does not have to crash here, you may simply choose to use OpenGL instead...
		return -1;
	}
	
	// Create the vulkan Instance using a simple wrapper
	xvk::Instance vulkanInstance(&vulkanLoader, &createInfo); // throws if failed to create the instance
	
	// Call any instance-specific vulkan functions like this : 
	// 	vulkanInstance.vkEnumeratePhysicalDevices(vulkanInstance.handle, ......)
	// Or like this without the vk prefix and first parameter removed (a convenient zero-cost abstraction)
	vulkanInstance.EnumeratePhysicalDevices(......)
	
	// Once you have found a suitable VkPhysicalDevice, 
	// you can create a logical device like this with a simple wrapper : 
	xvk::Device vulkanDevice(&vulkanInstance, selectedPhysicalDevice, &deviceCreateInfo);
	
	// Now you may call any device-specific vulkan functions the same way as with the instance...
	// 	vulkanDevice.vkGetDeviceQueue(vulkanDevice.handle, ......);
	// Or, Again, you may use the convenient zero-cost device abstraction without the vk prefix...
	vulkanDevice.GetDeviceQueue(......);
	
	// No need to destroy the original vulkan handles stored in xvk::Device and xvk::Instance
	//	their destructors will take care of that for you !
	
	return 0;
}
```

If you are using GCC and compiling for Linux, you might need to add -ldl in your compiler options.

## Sample Application

`xvk` comes with a very simple sample application that uses glfw, but you may use any other method for displaying something on screen. 

### Compiling and running the sample application

```bash
# cd inside xvk/sample/build subdirectory
cd xvk/sample
mkdir build
cd build
# compile it
cmake ..
cmake --build .
# run it
./xvkSampleApplication
```
