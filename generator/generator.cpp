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

#define GENERATOR_VERSION "0.2.0"

const regex versionLineMatchRegex{R"(\s*#define\s*VK_HEADER_VERSION\s+(\d+)\s*.*)"};
const regex lineMatchRegex{R"(\s*typedef\s*(void|VkResult)\s*\(VKAPI_PTR\s*\*PFN_vk(.*)\)\(\s*(.*)\s*\);)"}; // 1 = return type, 2 = function name, 3 = args
const regex instanceFuncMatchRegex{R"(^(VkInstance|VkPhysicalDevice).*)"};
const regex deviceFuncMatchRegex{R"(^(VkDevice|VkQueue|VkCommandBuffer).*)"};
const regex funcNameIgnoreRegex{R"(VoidFunction)"};
const regex argsRegex{R"(\s*(const\s+|)(\w+)(\s+|\s*\*+\s*|\s*\*+\s*const\**\s+)(\w+)(\[\d+\]|)(,(.+)|)$)"}; // 1 = const, 2 = type, 3 = pointer, 4 = name, 5 = arr, 7 = remainingArgs

struct FuncLine{
	string returnType;
	string name;
	string args;
	FuncLine(string returnType, string name, string args) : returnType(returnType), name(name), args(args) {}
};

int main(int argc, char** argv) {
	vector<FuncLine> globalFunctions, instanceFunctions, deviceFunctions;
	string vulkanCoreHeaderVersion = "";
	
	if (argc < 3) {
		cerr << "You must pass two arguments, the first is the path to vulkan_core.h from the official vulkan headers, the second is the path to the output file xvkInterface.hpp" << endl;
		return 1;
	}
	
	// Read vulkan core header
	ifstream vulkanCoreHeader(argv[1], fstream::in);
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
	
	// Generate lines
	
	// Global functions
	stringstream globalFunctionDefinitions(""), globalFunctionLoaders("");
	for (auto func : globalFunctions) {
		globalFunctionDefinitions << "		/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC( vk" << func.name << " ) // " << func.args << endl;
		globalFunctionLoaders << "			XVK_LOAD_GLOBAL_FUNC( vk" << func.name << " )" << endl;
	}
	
	// Instance functions
	stringstream instanceFunctionDefinitions(""), instanceFunctionLoaders(""), instanceAbstractionFunctions("");
	for (auto func : instanceFunctions) {
		instanceFunctionDefinitions << "		/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC( vk" << func.name << " ) // " << func.args << endl;
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
	stringstream deviceFunctionDefinitions(""), deviceFunctionLoaders(""), deviceAbstractionFunctions("");
	for (auto func : deviceFunctions) {
		deviceFunctionDefinitions << "		/* " << func.returnType << " */ XVK_DEF_INTERFACE_FUNC( vk" << func.name << " ) // " << func.args << endl;
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
	
	// Write to file
	ofstream out(argv[2], fstream::out | fstream::trunc);
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
	cout << "xvk interface was successfully generated into '" << argv[2] << "'" << endl;
}
