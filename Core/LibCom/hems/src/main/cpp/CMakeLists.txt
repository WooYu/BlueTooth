# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project(Hems VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)

message(STATUS PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR})


#头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Comm)
include_directories(${PROJECT_SOURCE_DIR}/Comm/autel_thread)
include_directories(${PROJECT_SOURCE_DIR}/Config)
include_directories(${PROJECT_SOURCE_DIR}/DataMgr)
include_directories(${PROJECT_SOURCE_DIR}/Devices)
include_directories(${PROJECT_SOURCE_DIR}/Devices/V2G)
include_directories(${PROJECT_SOURCE_DIR}/Devices/ATS)
include_directories(${PROJECT_SOURCE_DIR}/Devices/APP)
include_directories(${PROJECT_SOURCE_DIR}/HeartBeat)
include_directories(${PROJECT_SOURCE_DIR}/JniInterface)
include_directories(${PROJECT_SOURCE_DIR}/LibCom)
include_directories(${PROJECT_SOURCE_DIR}/LibCom/Serial)
include_directories(${PROJECT_SOURCE_DIR}/LibCom/Can)
include_directories(${PROJECT_SOURCE_DIR}/PowerBalance)
include_directories(${PROJECT_SOURCE_DIR}/System)
include_directories(${PROJECT_SOURCE_DIR}/Ext/includes)

#源文件搜索路径
aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Comm SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Comm/autel_thread SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Config SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/DataMgr SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Devices SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Devices/APP SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Devices/V2G SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/Devices/ATS SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/HeartBeat SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/JniInterface SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/LibCom SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/LibCom/Serial SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/LibCom/Can SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/PowerBalance SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/System SRC_LIST)

#添加链接库路径
link_directories(${PROJECT_SOURCE_DIR}/Ext/libs)

message(STATUS SRC_LIST: ${SRC_LIST})

# 配置一个头文件将一些 CMake 设置传入到源代码中
# 以 HemsConfig.h.in 为模版，替换相关变量
# 以生成 HemsConfig.h
configure_file("${PROJECT_SOURCE_DIR}/HemsConfig.h.in" "${PROJECT_BINARY_DIR}/HemsConfig.h")

# 将构建目录添加到 include 的搜索路径中以便找到
# HemsConfig.h 文件
include_directories("${PROJECT_BINARY_DIR}")

message(STATUS PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR})


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        Hems

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${SRC_LIST}
        )

#共享库搜索路径
#link_libraries(${PROJECT_SOURCE_DIR}/Ext/libs/libusb.so)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries( # Specifies the target library.
        Hems
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        usb)