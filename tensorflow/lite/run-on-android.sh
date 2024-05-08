#!/bin/bash
set -e

#./build-android.sh

ninja -C build-android

exeName=minimal
modelfile=/sdcard/tmp/simple_model.tflite

adb push build-android/$exeName /data/local/tmp/$exeName
adb shell chmod 777  /data/local/tmp/$exeName
adb shell time /data/local/tmp/$exeName $modelfile
