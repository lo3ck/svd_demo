cmake_minimum_required( VERSION 2.6 )
project( svd_demo )

set(CMAKE_VERBOSE_MAKEFILE OFF)

if(DEFINED target)
  message("Target platform is ${target}")
else()
  set(target "x86")
  message("Default target platform is ${target}")
endif()



if (${target} MATCHES "arm")
    
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_C_COMPILER arm-poky-linux-gnueabi-gcc)
    set(CMAKE_CXX_COMPILER arm-poky-linux-gnueabi-g++)
    set(CMAKE_FIND_ROOT_PATH "/opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi/usr/include/")
    set(CMAKE_PREFIX_PATH "/opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi/usr/lib/cmake")
    set(CMAKE_LIBRARY_PATH "/opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi/usr/lib")
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin_arm/)
    #add_compile_options(-g)
    add_compile_options(-O2)
    add_compile_options(-D PLATFORM_ARM)
else()

    # x86 simulation
    
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

    set(EGL_LIBRARY ${EXECUTABLE_OUTPUT_PATH}/lib/libEGL.so)
    set(OPENGLES3_LIBRARY ${EXECUTABLE_OUTPUT_PATH}/lib/libGLESv2.so)
    
    add_compile_options(-g)
    add_compile_options(-O0)
    add_compile_options(-D PLATFORM_X86)
endif()


add_compile_options(-Wall)

find_package( Threads )
find_library(M_LIB m)


include_directories( include )
 
SUBDIRS( svd
         
         )	