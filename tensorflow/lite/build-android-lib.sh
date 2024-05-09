#!/bin/bash
ndk_path=/Users/admin/Library/Android/sdk/ndk/25.2.9519653
set -x
cmake  -Bbuild-android-lib-armeabi-v7a \
    -S . \
    -DCMAKE_INSTALL_PREFIX=install/android-armeabi-v7a \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DTFLITE_ENABLE_GPU=ON \
    -DCMAKE_TOOLCHAIN_FILE="$ndk_path/build/cmake/android.toolchain.cmake" \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=armeabi-v7a \
    -G Ninja

cmake  -Bbuild-android-lib-arm64-v8a \
    -S . \
    -DCMAKE_INSTALL_PREFIX=install/android-arm64-v8a \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DTFLITE_ENABLE_GPU=ON \
    -DCMAKE_TOOLCHAIN_FILE="$ndk_path/build/cmake/android.toolchain.cmake" \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=arm64-v8a \
    -G Ninja
