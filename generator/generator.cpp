// xvk Interface Generator
// This tool will generate the entire xvkInterface.hpp file based on the definitions in the vulkan headers
// You do not need to build nor run this script, a pre-generated file is already included in the repository

#include <regex>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

#define GENERATOR_VERSION "0.3.0"

const regex versionLineMatchRegex{R"(\s*#define\s*VK_HEADER_VERSION\s+(\d+)\s*.*)"};
const regex lineMatchRegex{R"(\s*typedef\s*(void|VkResult)\s*\(VKAPI_PTR\s*\*PFN_vk(.*)\)\(\s*(.*)\s*\);)"}; // 1 = return type, 2 = function name, 3 = args
const regex instanceFuncMatchRegex{R"(^(VkInstance|VkPhysicalDevice).*)"};
const regex deviceFuncMatchRegex{R"(^(VkDevice|VkQueue|VkCommandBuffer).*)"};
const regex funcNameIgnoreRegex{R"(VoidFunction)"};
const regex argsRegex{R"(\s*(const\s+|const\s+struct\s+|struct\s+|)(\w+)(\s+|\s*\*+\s*|\s*\*+\s*const\**\s+)(\w+)(\[\d+\]|)(,(.+)|)$)"}; // 1 = const, 2 = type, 3 = pointer, 4 = name, 5 = arr, 7 = remainingArgs
const regex outputFileNameRegex{R"(.*/([^/]+)$)"}; // 1 = the file name

const std::map<std::string, std::string> includedHeaderFiles {
	// filename : ifdef
	{"vulkan_core.h", ""},
	{"vulkan_beta.h", "VK_ENABLE_BETA_EXTENSIONS"},
	{"vulkan_android.h", "VK_USE_PLATFORM_ANDROID_KHR"},
	{"vulkan_fuchsia.h", "VK_USE_PLATFORM_FUCHSIA"},
	{"vulkan_ios.h", "VK_USE_PLATFORM_IOS_MVK"},
	{"vulkan_macos.h", "VK_USE_PLATFORM_MACOS_MVK"},
	{"vulkan_metal.h", "VK_USE_PLATFORM_METAL_EXT"},
	{"vulkan_vi.h", "VK_USE_PLATFORM_VI_NN"},
	{"vulkan_wayland.h", "VK_USE_PLATFORM_WAYLAND_KHR"},
	{"vulkan_win32.h", "VK_USE_PLATFORM_WIN32_KHR"},
	{"vulkan_xcb.h", "VK_USE_PLATFORM_XCB_KHR"},
	{"vulkan_xlib.h", "VK_USE_PLATFORM_XLIB_KHR"},
	{"vulkan_xlib_xrandr.h", "VK_USE_PLATFORM_XLIB_XRANDR_EXT"},
	{"vulkan_ggp.h", "VK_USE_PLATFORM_GGP"},
};

struct FuncLine{
	string returnType;
	string name;
	string args;
	bool isCustomString;
	FuncLine(string returnType, string name, string args) : returnType(returnType), name(name), args(args), isCustomString(false) {}
	FuncLine(string customString) : returnType(""), name(""), args(customString), isCustomString(true) {}
};

int main(int argc, char** argv) {
	vector<FuncLine> globalFunctions, instanceFunctions, deviceFunctions;
	string vulkanCoreHeaderVersion = "";
	
	if (argc < 3) {
		cerr << "You must pass two arguments, the first is the path to vulkan's include directory containing vulkan_core.h from the official vulkan headers, the second is the path to the output file xvkInterface.hpp" << endl;
		return 1;
	}
	
	// Read vulkan core header
	for (auto[filename, ifdef] : includedHeaderFiles) {
		if (ifdef != "") {
			instanceFunctions.emplace_back("");
			instanceFunctions.emplace_back(std::string("#ifdef ") + ifdef);
			deviceFunctions.emplace_back("");
			deviceFunctions.emplace_back(std::string("#ifdef ") + ifdef);
			globalFunctions.emplace_back("");
			globalFunctions.emplace_back(std::string("#ifdef ") + ifdef);
		}
		std::string filepath = std::string(argv[1]) + "/" + filename;
		ifstream vulkanCoreHeader(filepath, fstream::in);
		for (string line; getline(vulkanCoreHeader, line);) {
			
			cmatch lineMatch;
			if (vulkanCoreHeaderVersion == "" && regex_match(line.c_str(), lineMatch, versionLineMatchRegex)) {
				vulkanCoreHeaderVersion = lineMatch[1].str();
				continue;
			}
			if (regex_match(line.c_str(), lineMatch, lineMatchRegex)) {
				string returnType = lineMatch[1].str();
				string funcName = lineMatch[2].str();
				string funcArgs = lineMatch[3].str();
				cmatch argsMatch;
				if (regex_match(funcName.c_str(), argsMatch, funcNameIgnoreRegex)) continue;
				if (regex_match(funcArgs.c_str(), argsMatch, instanceFuncMatchRegex)) {
					instanceFunctions.emplace_back(returnType, funcName, funcArgs);
				} else if (regex_match(funcArgs.c_str(), argsMatch, deviceFuncMatchRegex)) {
					deviceFunctions.emplace_back(returnType, funcName, funcArgs);
				} else {
					globalFunctions.emplace_back(returnType, funcName, funcArgs);
				}
			}
		}
		vulkanCoreHeader.close();
		if (ifdef != "") {
			instanceFunctions.emplace_back("#endif\n");
			deviceFunctions.emplace_back("#endif\n");
			globalFunctions.emplace_back("#endif\n");
		}
	}
	
	// Generate lines
	
	// Global functions
	stringstream globalFunctionDefinitions(""), globalFunctionDefinitions_h(""), globalFunctionDefinitions_cpp(""), globalFunctionLoaders("");
	for (auto func : globalFunctions) {
		if (func.isCustomString) {
			globalFunctionDefinitions << "		" << func.args << endl;
			globalFunctionDefinitions_h << "	" << func.args << endl;
			globalFunctionDefinitions_cpp << "	" << func.args << endl;
			globalFunctionLoaders << "			" << func.args << endl;
			continue;
		}
		globalFunctionDefinitions << "		/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC( vk" << func.name << " ) // " << func.args << endl;
		globalFunctionDefinitions_h << "	/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC_H( vk" << func.name << " ) // " << func.args << endl;
		globalFunctionDefinitions_cpp << "	XVK_DEF_INTERFACE_FUNC_C( vk" << func.name << " )"<< endl;
		globalFunctionLoaders << "			XVK_LOAD_GLOBAL_FUNC( vk" << func.name << " )" << endl;
	}
	
	// Instance functions
	stringstream instanceFunctionDefinitions(""), instanceFunctionDefinitions_h(""), instanceFunctionDefinitions_cpp(""), instanceFunctionLoaders(""), instanceAbstractionFunctions("");
	for (auto func : instanceFunctions) {
		if (func.isCustomString) {
			instanceFunctionDefinitions << "		" << func.args << endl;
			instanceFunctionDefinitions_h << "	" << func.args << endl;
			instanceFunctionDefinitions_cpp << "	" << func.args << endl;
			instanceFunctionLoaders << "			" << func.args << endl;
			instanceAbstractionFunctions << endl << "		" << func.args << endl;
			continue;
		}
		instanceFunctionDefinitions << "		/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC( vk" << func.name << " ) // " << func.args << endl;
		instanceFunctionDefinitions_h << "	/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC_H( vk" << func.name << " ) // " << func.args << endl;
		instanceFunctionDefinitions_cpp << "	XVK_DEF_INTERFACE_FUNC_C( vk" << func.name << " )"<< endl;
		instanceFunctionLoaders << "			XVK_LOAD_INSTANCE_FUNC( vk" << func.name << " )" << endl;
		// instance abstraction
		string inputArgs = func.args;
		int forwardedArgsCount = 0;
		stringstream forwardedArgs("");
		cmatch handleMatch;
		if (regex_match(func.args.c_str(), handleMatch, regex(R"(VkInstance\s*instance,?\s*(.*))"))) {
			inputArgs = handleMatch[1];
			forwardedArgs << "handle";
			forwardedArgsCount++;
		}
		string tmpArgs = inputArgs;
		while (tmpArgs != "") {
			cmatch argMatch;
			if (regex_match(tmpArgs.c_str(), argMatch, argsRegex)) { // Match: 1 = const, 2 = type, 3 = pointer, 4 = name, 5 = arr, 7 = remainingArgs
				if (forwardedArgsCount) {
					forwardedArgs << ", ";
				}
				forwardedArgs << argMatch[4].str();
				forwardedArgsCount++;
				tmpArgs = argMatch.size() > 7 ? argMatch[7].str() : "";
			} else {
				throw runtime_error(string("In Instance Function 'vk" + func.name + "', Args format not supported: ") + tmpArgs);
			}
		}
		instanceAbstractionFunctions << endl << "		inline " << func.returnType << " " << func.name << " (" << inputArgs << ") {" << R"(
			XVK_CHECK_FUNC(vk)" << func.name << R"()
			)" << (func.returnType == "void" ? "" : "return ") << "vk" << func.name << "(" << forwardedArgs.str() << ");" << R"(
		})" << endl;
		
	}
	
	// Device functions
	stringstream deviceFunctionDefinitions(""), deviceFunctionDefinitions_h(""), deviceFunctionDefinitions_cpp(""), deviceFunctionLoaders(""), deviceAbstractionFunctions("");
	for (auto func : deviceFunctions) {
		if (func.isCustomString) {
			deviceFunctionDefinitions << "		" << func.args << endl;
			deviceFunctionDefinitions_h << "	" << func.args << endl;
			deviceFunctionDefinitions_cpp << "	" << func.args << endl;
			deviceFunctionLoaders << "			" << func.args << endl;
			deviceAbstractionFunctions << endl << "		" << func.args << endl;
			continue;
		}
		deviceFunctionDefinitions << "		/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC( vk" << func.name << " ) // " << func.args << endl;
		deviceFunctionDefinitions_h << "	/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC_H( vk" << func.name << " ) // " << func.args << endl;
		deviceFunctionDefinitions_cpp << "	XVK_DEF_INTERFACE_FUNC_C( vk" << func.name << " )"<< endl;
		deviceFunctionLoaders << "			XVK_LOAD_DEVICE_FUNC( vk" << func.name << " )" << endl;
		// device abstraction
		string inputArgs = func.args;
		int forwardedArgsCount = 0;
		stringstream forwardedArgs("");
		cmatch handleMatch;
		if (regex_match(func.args.c_str(), handleMatch, regex(R"(VkDevice\s*device,?\s*(.*))"))) {
			inputArgs = handleMatch[1];
			forwardedArgs << "handle";
			forwardedArgsCount++;
		}
		string tmpArgs = inputArgs;
		while (tmpArgs != "") {
			cmatch argMatch;
			if (regex_match(tmpArgs.c_str(), argMatch, argsRegex)) { // Match: 1 = const, 2 = type, 3 = pointer, 4 = name, 5 = arr, 7 = remainingArgs
				if (forwardedArgsCount) {
					forwardedArgs << ", ";
				}
				forwardedArgs << argMatch[4].str();
				forwardedArgsCount++;
				tmpArgs = argMatch.size() > 7 ? argMatch[7].str() : "";
			} else {
				throw runtime_error(string("In Device Function 'vk" + func.name + "', Args format not supported: ") + tmpArgs);
			}
		}
		deviceAbstractionFunctions << endl << "		inline " << func.returnType << " " << func.name << " (" << inputArgs << ") {" << R"(
			XVK_CHECK_FUNC(vk)" << func.name << R"()
			)" << (func.returnType == "void" ? "" : "return ") << "vk" << func.name << "(" << forwardedArgs.str() << ");" << R"(
		})" << endl;
		
	}
	
	// Write to files
	{// .hpp
		string outputFile {argv[2]};
		outputFile += ".hpp";
		ofstream out(outputFile.c_str(), fstream::out | fstream::trunc);
		out << R"(#pragma once

// DO NOT EDIT THIS FILE
// This file was generated via the xvk generator version )" << GENERATOR_VERSION << R"(
// from Vulkan-Headers Version )" << vulkanCoreHeaderVersion << R"(

#include "xvkBase.hpp"

namespace xvk { namespace Interface {
	
	class LoaderInterface : public xvk::Base::LoaderBase {
	XVK_INTERFACE_LOADER_RAW_FUNCTIONS_ACCESSIBILITY:
)" << globalFunctionDefinitions.str() << R"(
	protected: 
		using LoaderBase::LoaderBase;
		virtual ~LoaderInterface(){}
		void LoadFunctionPointersInterface() {
)" << globalFunctionLoaders.str() << R"(
		}
	};
	
	class InstanceInterface : public xvk::Base::InstanceBase {
	XVK_INTERFACE_RAW_FUNCTIONS_ACCESSIBILITY:
)" << instanceFunctionDefinitions.str() << R"(
	XVK_INTERFACE_ABSTRACTED_FUNCTIONS_ACCESSIBILITY:
)" << instanceAbstractionFunctions.str() << R"(
	protected: 
		using InstanceBase::InstanceBase;
		virtual ~InstanceInterface(){}
		void LoadFunctionPointersInterface() override {
)" << instanceFunctionLoaders.str() << R"(
		}
	};
	
	class DeviceInterface : public xvk::Base::DeviceBase {
	XVK_INTERFACE_RAW_FUNCTIONS_ACCESSIBILITY:
)" << deviceFunctionDefinitions.str() << R"(
	XVK_INTERFACE_ABSTRACTED_FUNCTIONS_ACCESSIBILITY:
)" << deviceAbstractionFunctions.str() << R"(
	protected: 
		using DeviceBase::DeviceBase;
		virtual ~DeviceInterface(){}
		void LoadFunctionPointersInterface() override {
)" << deviceFunctionLoaders.str() << R"(
		}
	};
}}
)";
		out.close();
	}
	
	{// .h
		string outputFile {argv[2]};
		outputFile += ".h";
		ofstream out(outputFile.c_str(), fstream::out | fstream::trunc);
		out << R"(#pragma once

// This file should only be used when XVK_EXPOSE_NATIVE_VULKAN_FUNCTIONS_NAMESPACE is defined
// DO NOT EDIT THIS FILE
// This file was generated via the xvk generator version )" << GENERATOR_VERSION << R"(
// from Vulkan-Headers Version )" << vulkanCoreHeaderVersion << R"(

namespace XVK_EXPOSE_NATIVE_VULKAN_FUNCTIONS_NAMESPACE {
	XVK_DEF_INTERFACE_FUNC_H( vkGetInstanceProcAddr )
	XVK_DEF_INTERFACE_FUNC_H( vkGetDeviceProcAddr )

)" << globalFunctionDefinitions_h.str() << R"(
)" << instanceFunctionDefinitions_h.str() << R"(
)" << deviceFunctionDefinitions_h.str() << R"(
}
)";
		out.close();
	}
	
	{// .c
		string outputFile {argv[2]};
		outputFile += ".c";
		ofstream out(outputFile.c_str(), fstream::out | fstream::trunc);
		out << R"(
// This file should only be used when XVK_EXPOSE_NATIVE_VULKAN_FUNCTIONS_NAMESPACE is defined
// DO NOT ADD THIS FILE TO COMPILE. Include it in one of your source files instead, after setting your configuration and having included all headers.
// DO NOT EDIT THIS FILE
// This file was generated via the xvk generator version )" << GENERATOR_VERSION << R"(
// from Vulkan-Headers Version )" << vulkanCoreHeaderVersion << R"(

namespace XVK_EXPOSE_NATIVE_VULKAN_FUNCTIONS_NAMESPACE {
	XVK_DEF_INTERFACE_FUNC_C( vkGetInstanceProcAddr )
	XVK_DEF_INTERFACE_FUNC_C( vkGetDeviceProcAddr )

)" << globalFunctionDefinitions_cpp.str() << R"(
)" << instanceFunctionDefinitions_cpp.str() << R"(
)" << deviceFunctionDefinitions_cpp.str() << R"(
}
)";
		out.close();
	}
	
	std::cout << "xvk interface was successfully generated into '" << argv[2] << "' .hpp/.h/.c" << endl;
}
