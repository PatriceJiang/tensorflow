#!/bin/bash
ndk_path=/Users/admin/Library/Android/sdk/ndk/25.2.9519653
set -x
cmake  -Bbuild-android-armeabi \
    -S examples/minimal \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_TOOLCHAIN_FILE="$ndk_path/build/cmake/android.toolchain.cmake" \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=armeabi-v7a \
    -G Ninja

cmake  -Bbuild-android-arm64 \
    -S examples/minimal \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_TOOLCHAIN_FILE="$ndk_path/build/cmake/android.toolchain.cmake" \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=arm64-v8a \
    -G Ninja
