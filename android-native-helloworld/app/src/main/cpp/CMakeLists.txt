cmake_minimum_required(VERSION 3.10)

# android_native_app_glue ships as source with the NDK; build it as a static lib.
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

target_include_directories(native_app_glue PUBLIC
    ${ANDROID_NDK}/sources/android/native_app_glue)

add_library(native-activity SHARED
    main.cpp)

target_include_directories(native-activity PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(native-activity
    native_app_glue
    ${log-lib}
    ${android-lib})

# The entry point is only referenced by the glue code, so force the linker to keep it.
set_target_properties(native-activity PROPERTIES
    LINK_FLAGS "-u ANativeActivity_onCreate")
