# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 设置当前Project的名字
set(LAUNCHER_PROJECT_NAME Launcher)
project(${LAUNCHER_PROJECT_NAME})

#设置Include文件夹
include_directories(${CMAKE_CURRENT_LIST_DIR}/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../Core/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../3rdParty/GLFW/includes)

#定义源文件目录
# 设置代码夹子
set(SRC_Path ${CMAKE_CURRENT_LIST_DIR})


#宏，实现visio studio的目录分组（过滤器）功能
#
file(
    GLOB
    ALL_CODES
	"${SRC_Path}/src/*.cpp"
)

link_directories(${CMAKE_CURRENT_LIST_DIR}/../3rdParty/GLFW/lib)
link_libraries(glfw3.lib) 

link_directories(${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/lib)
link_libraries(Core.lib) 


add_executable(${LAUNCHER_PROJECT_NAME} ${ALL_CODES})
#设置输出
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace)
set_target_properties(${LAUNCHER_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace)

set(REG_EXT "[^/]*([.]cpp|[.]c|[.]h|[.]hpp|[.]vs|[.]fs)$")

source_group("src" REGULAR_EXPRESSION "${SRC_Path}/src/${REG_EXT}")
