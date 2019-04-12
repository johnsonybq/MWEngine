# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 设置当前Project的名字
set(ENGINE_PROJECT_NAME Framework)
project(${ENGINE_PROJECT_NAME})

#设置Include文件夹
include_directories(${CMAKE_CURRENT_LIST_DIR}/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../Core/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../MWMath/Include)
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
	"${SRC_Path}/src/Entity/*.h"
	"${SRC_Path}/src/Entity/*.cpp"
	"${SRC_Path}/Include/*.h"
    "${SRC_Path}/Include/Entity/*.h"
)

#设置lib库文件夹
add_library(${ENGINE_PROJECT_NAME} SHARED ${ALL_CODES})

link_directories(${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)
link_libraries(MWMath.lib) 
#设置输出
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)
set_target_properties(${THIS_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)
set_target_properties(${THIS_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)

set(REG_EXT "[^/]*([.]cpp|[.]c|[.]h|[.]hpp|[.]vs|[.]fs)$")

source_group("src" REGULAR_EXPRESSION "${SRC_Path}/src/${REG_EXT}")
source_group("src\\Entity" REGULAR_EXPRESSION "${SRC_Path}/src/Entity/${REG_EXT}")
source_group("Include" REGULAR_EXPRESSION "${SRC_Path}/Include/${REG_EXT}")
source_group("Include\\Entity" REGULAR_EXPRESSION "${SRC_Path}/Include/Entity/${REG_EXT}")
