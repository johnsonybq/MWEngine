# CMake ��Ͱ汾��Ҫ��
cmake_minimum_required (VERSION 2.8)

# ���õ�ǰProject������
set(ENGINE_PROJECT_NAME Core)
project(${ENGINE_PROJECT_NAME})

#����Include�ļ���
include_directories(${CMAKE_CURRENT_LIST_DIR}/Include)

#����Դ�ļ�Ŀ¼
# ���ô������
set(SRC_Path ${CMAKE_CURRENT_LIST_DIR})


#�꣬ʵ��visio studio��Ŀ¼���飨������������
#
file(
    GLOB
    ALL_CODES
	"${SRC_Path}/src/*.h"
	"${SRC_Path}/src/*.cpp"
	"${SRC_Path}/Include/*.h"
    "${SRC_Path}/Include/EBus/*.h"
	"${SRC_Path}/Include/Memory/*.h"
	"${SRC_Path}/Include/ByteArray/*.h"
)

#����lib���ļ���
#link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
#link_libraries(glew32s.lib) 
#link_libraries(assimp.lib)
#link_libraries(glfw3.lib) 
#link_libraries(SOIL.lib) 
#link_libraries(GLAD.lib) 
#link_libraries(STB_IMAGE.lib) 

#add_executable(Framework ${ALL_CODES})
#add_library(Core ${ALL_CODES})
add_library(${ENGINE_PROJECT_NAME} SHARED ${ALL_CODES})
#�������
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/dll)
set_target_properties(${ENGINE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/../WorkSpace/dll)

set(REG_EXT "[^/]*([.]cpp|[.]c|[.]h|[.]hpp|[.]vs|[.]fs)$")

source_group("src" REGULAR_EXPRESSION "${SRC_Path}/src/${REG_EXT}")
source_group("Include" REGULAR_EXPRESSION "${SRC_Path}/Include/${REG_EXT}")
source_group("Include\\EBus" REGULAR_EXPRESSION "${SRC_Path}/Include/EBus/${REG_EXT}")
source_group("Include\\Memory" REGULAR_EXPRESSION "${SRC_Path}/Include/Memory/${REG_EXT}")
source_group("Include\\ByteArray" REGULAR_EXPRESSION "${SRC_Path}/Include/ByteArray/${REG_EXT}")