#!/bin/bash
ndk_path=/Users/admin/Library/Android/sdk/ndk/25.2.9519653
set -x

for arch in armeabi-v7a arm64-v8a x86 x86_64
do
cmake  -Bbuild-android-lib-$arch \
    -S . \
    -DCMAKE_INSTALL_PREFIX=install/android-$arch \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DTFLITE_ENABLE_GPU=ON \
    -DCMAKE_TOOLCHAIN_FILE="$ndk_path/build/cmake/android.toolchain.cmake" \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=$arch \
    -G Ninja
done

