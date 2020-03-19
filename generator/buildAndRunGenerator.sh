cd `dirname $0`
mkdir -p build
cd build
cmake .. &&\
cmake --build . &&\
./generateXvkInterface "../../Vulkan-Headers/include/vulkan" "../../xvkInterface"
