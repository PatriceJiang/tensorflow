#!/bin/bash

dst=~/code/blockpuzzle_cocos2dx/external

build_dir=build-android-lib-armeabi-v7a
dst_dir=$dst/android/armeabi-v7a/tf/
#ninja -C $build_dir
cp -v $build_dir/libtensorflow-lite.a $dst_dir
cp -v $build_dir/_deps/xnnpack-build/libXNNPACK.a $dst_dir
cp -v $build_dir/_deps/farmhash-build/libfarmhash.a $dst_dir
cp -v $build_dir/_deps/cpuinfo-build/libcpuinfo.a $dst_dir

build_dir=build-android-lib-arm64-v8a
dst_dir=$dst/android/arm64-v8a/tf/
#ninja -C $build_dir
cp -v $build_dir/libtensorflow-lite.a $dst_dir
cp -v $build_dir/_deps/xnnpack-build/libXNNPACK.a $dst_dir
cp -v $build_dir/_deps/farmhash-build/libfarmhash.a $dst_dir
cp -v $build_dir/_deps/cpuinfo-build/libcpuinfo.a $dst_dir

build_dir=build-ios-lib
dst_dir=$dst/ios/libs/tf
#ninja -C $build_dir
cp -v $build_dir/libtensorflow-lite.a $dst_dir
cp -v $build_dir/_deps/xnnpack-build/libXNNPACK.a $dst_dir
cp -v $build_dir/_deps/farmhash-build/libfarmhash.a $dst_dir
cp -v $build_dir/_deps/cpuinfo-build/libcpuinfo.a $dst_dir

echo "copy ios libs"
cp -v install/ios/lib/*.a  $dst/ios/libs/tf/
llvm-strip --strip-debug $dst/ios/libs/tf/*.a
echo "copy android arm64"
cp -v install/android-arm64-v8a/lib/*.a $dst/android/arm64-v8a/tf/
llvm-strip --strip-debug $dst/android/arm64-v8a/tf/*.a
echo "copy android armeabi"
cp -v install/android-armeabi-v7a/lib/*.a $dst/android/armeabi-v7a/tf/
llvm-strip --strip-debug $dst/android/armeabi-v7a/tf/*.a
