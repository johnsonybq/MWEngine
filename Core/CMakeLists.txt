# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 设置当前Project的名字
set(ENGINE_PROJECT_NAME Core)
project(${ENGINE_PROJECT_NAME})

#设置Include文件夹
include_directories(${CMAKE_CURRENT_LIST_DIR}/Include)

#定义源文件目录
# 设置代码夹子
set(SRC_Path ${CMAKE_CURRENT_LIST_DIR})


#宏，实现visio studio的目录分组（过滤器）功能
#
file(
    GLOB
    ALL_CODES
	"${SRC_Path}/src/*.h"
	"${SRC_Path}/src/*.cpp"
	"${SRC_Path}/src/Log/*.h"
	"${SRC_Path}/src/Log/*.cpp"
	"${SRC_Path}/src/Module/*.h"
	"${SRC_Path}/src/Module/*.cpp"
	"${SRC_Path}/src/Memory/*.cpp"
	"${SRC_Path}/src/System/*.h"
	"${SRC_Path}/src/System/*.cpp"
	"${SRC_Path}/src/Reflect/*.h"
	"${SRC_Path}/src/Reflect/*.cpp"
	"${SRC_Path}/src/Serialize/*.h"
	"${SRC_Path}/src/Serialize/*.cpp"
	"${SRC_Path}/src/ByteArray/*.cpp"
	"${SRC_Path}/Include/*.h"
	"${SRC_Path}/Include/Log/*.h"
    "${SRC_Path}/Include/EBus/*.h"
	"${SRC_Path}/Include/Memory/*.h"
	"${SRC_Path}/Include/ByteArray/*.h"
	"${SRC_Path}/Include/Module/*.h"
	"${SRC_Path}/Include/System/*.h"
	"${SRC_Path}/Include/Reflect/*.h"
	"${SRC_Path}/Include/Serialize/*.h"
)

#设置lib库文件夹
#link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
#link_libraries(glew32s.lib) 
#link_libraries(assimp.lib)
#link_libraries(glfw3.lib) 
#link_libraries(SOIL.lib) 
#link_libraries(GLAD.lib) 
#link_libraries(STB_IMAGE.lib) 

#add_executable(Framework ${ALL_CODES})
#add_library(Core ${ALL_CODES})
add_library(${ENGINE_PROJECT_NAME} ${ALL_CODES})
#设置输出
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)
set_target_properties(${THIS_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)
set_target_properties(${THIS_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)

set(REG_EXT "[^/]*([.]cpp|[.]c|[.]h|[.]hpp|[.]vs|[.]fs)$")

source_group("src" REGULAR_EXPRESSION "${SRC_Path}/src/${REG_EXT}")
source_group("src\\Module" REGULAR_EXPRESSION "${SRC_Path}/src/Module/${REG_EXT}")
source_group("src\\Log" REGULAR_EXPRESSION "${SRC_Path}/src/Log/${REG_EXT}")
source_group("src\\Memory" REGULAR_EXPRESSION "${SRC_Path}/src/Memory/${REG_EXT}")
source_group("src\\System" REGULAR_EXPRESSION "${SRC_Path}/src/System/${REG_EXT}")
source_group("src\\Reflect" REGULAR_EXPRESSION "${SRC_Path}/src/Reflect/${REG_EXT}")
source_group("src\\Serialize" REGULAR_EXPRESSION "${SRC_Path}/src/Serialize/${REG_EXT}")
source_group("src\\ByteArray" REGULAR_EXPRESSION "${SRC_Path}/src/ByteArray/${REG_EXT}")
source_group("Include" REGULAR_EXPRESSION "${SRC_Path}/Include/${REG_EXT}")
source_group("Include\\EBus" REGULAR_EXPRESSION "${SRC_Path}/Include/EBus/${REG_EXT}")
source_group("Include\\Memory" REGULAR_EXPRESSION "${SRC_Path}/Include/Memory/${REG_EXT}")
source_group("Include\\ByteArray" REGULAR_EXPRESSION "${SRC_Path}/Include/ByteArray/${REG_EXT}")
source_group("Include\\Module" REGULAR_EXPRESSION "${SRC_Path}/Include/Module/${REG_EXT}")
source_group("Include\\Log" REGULAR_EXPRESSION "${SRC_Path}/Include/Log/${REG_EXT}")
source_group("Include\\System" REGULAR_EXPRESSION "${SRC_Path}/Include/System/${REG_EXT}")
source_group("Include\\Reflect" REGULAR_EXPRESSION "${SRC_Path}/Include/Reflect/${REG_EXT}")
source_group("Include\\Serialize" REGULAR_EXPRESSION "${SRC_Path}/Include/Serialize/${REG_EXT}")