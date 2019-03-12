# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 设置当前Project的名字
set(ENGINE_PROJECT_NAME MWMath)
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
	"${SRC_Path}/Include/GLM/*.hpp"
	"${SRC_Path}/Include/GLM/detail/*.hpp"
	"${SRC_Path}/Include/GLM/detail/*.inl"
	"${SRC_Path}/Include/GLM/ext/*.hpp"
	"${SRC_Path}/Include/GLM/ext/*.inl"
	"${SRC_Path}/Include/GLM/gtc/*.hpp"
	"${SRC_Path}/Include/GLM/gtc/*.inl"
	"${SRC_Path}/Include/GLM/gtx/*.hpp"
	"${SRC_Path}/Include/GLM/gtx/*.inl"
	"${SRC_Path}/Include/GLM/simd/*.h"
)

add_library(${ENGINE_PROJECT_NAME} SHARED ${ALL_CODES})
#设置输出
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/dll)
set_target_properties(${ENGINE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/dll)

set(REG_EXT "[^/]*([.]cpp|[.]c|[.]h|[.]hpp|[.]vs|[.]fs)$")

source_group("src" REGULAR_EXPRESSION "${SRC_Path}/src/${REG_EXT}")
source_group("Include" REGULAR_EXPRESSION "${SRC_Path}/Include/${REG_EXT}")
source_group("Include\\GLM" REGULAR_EXPRESSION "${SRC_Path}/Include/GLM/${REG_EXT}")
source_group("Include\\GLM\\detail" REGULAR_EXPRESSION "${SRC_Path}/Include/GLM/detail/${REG_EXT}")
source_group("Include\\GLM\\ext" REGULAR_EXPRESSION "${SRC_Path}/Include/GLM/ext/${REG_EXT}")
source_group("Include\\GLM\\gtc" REGULAR_EXPRESSION "${SRC_Path}/Include/GLM/gtc/${REG_EXT}")
source_group("Include\\GLM\\gtx" REGULAR_EXPRESSION "${SRC_Path}/Include/GLM/gtx/${REG_EXT}")
source_group("Include\\GLM\\simd" REGULAR_EXPRESSION "${SRC_Path}/Include/GLM/simd/${REG_EXT}")
