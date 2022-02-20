# `xvk` a fast Vulkan wrapper / dynamic loader

`xvk` is a zero-cost **Vulkan Dynamic Loader** with only two very lightweight abstractions (for `VkInstance` and `VkDevice`) that do NOT require the developer to re-learn new functions. 
It literally does not have any public functions other than the ones from the classical Vulkan C API. 

Developers have the full flexibily of implementing higher-level abstractions around `xvk`'s dynamically loaded Vulkan functions that are very fast and safe (actually faster than using the functions from the usual linked vulkan loader). 

`xvk` is platform & compiler agnostic (except for a few `if WIN32` here and there, but this should be enough to compile/run anywhere)

You simply need to clone this repository (and submodules) then include a single header file.

`xvk` implements all vk* functions with zero cost. 

`xvk` also loads all khr and vendor-specific functions when available. 

`xvk` loads Vulkan 100% at runtime (which is also the best way to load vulkan according to Khronos). 

Also, `xvk` takes care of downloading and including the necessary Vulkan headers (downloaded via a git submodule).

This `xvk` repository also includes a few submodules for your convenience (like `glfw`), although you do not have to use them. 

Must you need the most recent vk functions that were added yesterday and not yet added in `xvk`, you simply have to build & run the included generator after updating the vulkan headers submodule. 

## Adding it to your project
```bash
# Simply run these two commands from within your project's source or include directory
git submodule add git@github.com:Vulkan4D/xvk.git
git submodule update --init --recursive
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
	
	// Create the vulkan Instance using a simple wrapper (you first have to fill a 'createInfo' struct)
	xvk::Instance vulkanInstance(&vulkanLoader, &createInfo); // throws if failed to create the instance
	
	// Call any instance-specific vulkan functions like this:
	// 	vulkanInstance.vkEnumeratePhysicalDevices(vulkanInstance.handle, ......)
	//  or like this without the vk prefix and first parameter removed (a convenient zero-cost abstraction)
	vulkanInstance.EnumeratePhysicalDevices(......)
	
	// Once you have found a suitable VkPhysicalDevice,
	//  you can create a logical device like this with this simple wrapper to VkDevice:
	xvk::Device vulkanDevice(&vulkanInstance, selectedPhysicalDevice, &deviceCreateInfo);
	
	// Now you may call any device-specific vulkan functions the same way as with the instance...
	// 	vulkanDevice.vkGetDeviceQueue(vulkanDevice.handle, ......);
	//  or, again, you may use the convenient zero-cost device abstraction without the vk prefix...
	vulkanDevice.GetDeviceQueue(......);
	
	// No need to destroy the original vulkan handles stored in xvk::Device and xvk::Instance
	//	their destructors will take care of that for you!
	
	return 0;
}
```

If you are using GCC and compiling for Linux, you might need to add -ldl in your compiler options.

## Sample Applications

`xvk` comes with sample applications, some of them use glfw, but you may use any other method for displaying something on screen. 

### Compiling and running sample applications

```bash
# cd inside xvk/samples/build subdirectory (create the build directory)
cd xvk/samples
mkdir build
cd build
# compile
cmake ..
cmake --build .
# You may now run them, their binary executables are compiled in the samples/build/samples_bin directory 
#	(you may have to add /Debug or /Release for MSVC builds)
samples_bin/1_basic_vulkan_init
samples_bin/2_basic_glfw_window
# ... more samples to come in the future
```
