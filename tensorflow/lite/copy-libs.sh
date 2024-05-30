#!/bin/bash

dst=~/code/blockpuzzle_cocos2dx/external

for arch in armeabi-v7a arm64-v8a x86
do
build_dir=build-android-lib-$arch
dst_dir=$dst/android/$arch/tf/
ninja -C $build_dir
cp -v $build_dir/libtensorflow-lite.a $dst_dir
cp -v $build_dir/_deps/xnnpack-build/libXNNPACK.a $dst_dir
cp -v $build_dir/_deps/farmhash-build/libfarmhash.a $dst_dir
cp -v $build_dir/_deps/cpuinfo-build/libcpuinfo.a $dst_dir
cp -v install/android-$arch/lib/*.a $dst/android/$arch/tf/
llvm-strip --strip-debug --strip-unneeded $dst/android/$arch/tf/*.a
done


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
