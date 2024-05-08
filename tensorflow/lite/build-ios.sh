#!/bin/bash
#ndk_path=/Users/admin/Library/Android/sdk/ndk/25.2.9519653
set -x
cmake  -Bbuild-ios-lib \
    -S . \
    -DCMAKE_INSTALL_PREFIX=/Users/admin/github/tensorflow/tensorflow/lite/install/ios \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_SYSROOT=iphoneos \
    -DCMAKE_MACOS_DEPLOYMENT_TARGET=12 \
    -DFLATBUFFERS_INSTALL=OFF \
    -DTFLITE_ENABLE_METAL=ON \
    -DXNNPACK_PLATFORM_JIT=OFF \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -GNinja

    #-DANDROID_ABI=arm64-v8a \
    #-S examples/minimal \
