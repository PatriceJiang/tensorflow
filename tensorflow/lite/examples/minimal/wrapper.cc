/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <cstdio>
#include <memory>
#include <unordered_map>
#include <utility>

#include "tensorflow/lite/core/kernels/register.h"
#include "tensorflow/lite/core/model_builder.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

// This is an example that is minimal to read a model
// from disk and perform inference. There is no data being loaded
// that is up to you to add as a user.
//
// NOTE: Do not add any dependencies to this that cannot be built with
// the minimal makefile. This example must remain trivial to build with
// the minimal build tool.
//
// Usage: minimal <tflite model>

#define TFLITE_MINIMAL_CHECK(x)                              \
  if (!(x)) {                                                \
    fprintf(stderr, "Error at %s:%d\n", __FILE__, __LINE__); \
    return -1;                                               \
  }

#define PUBLIC __attribute__((visibility("default")))

namespace {

struct ModelInfo {
  std::unique_ptr<tflite::FlatBufferModel> model;
  std::unique_ptr<tflite::Interpreter> interpreter;
};

std::unordered_map<int, ModelInfo*> models;
int modelId = 100;
}  // namespace

extern "C" {
PUBLIC bool unloadModel(int id) {
  auto itr = models.find(id);
  if (itr == models.end()) return false;
  delete itr->second;
  models.erase(itr);
  return true;
}

PUBLIC int loadModel(char* dat, size_t len) {
  auto model = tflite::FlatBufferModel::BuildFromBuffer(dat, len);
  TFLITE_MINIMAL_CHECK(model != nullptr);

  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder builder(*model, resolver);
  std::unique_ptr<tflite::Interpreter> interpreter;
  builder(&interpreter);
  TFLITE_MINIMAL_CHECK(interpreter != nullptr);

  // Allocate tensor buffers.
  TFLITE_MINIMAL_CHECK(interpreter->AllocateTensors() == kTfLiteOk);
  // printf("=== Pre-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(interpreter.get());
  //  printf("********input size %d\n", (int)interpreter->inputs().size());
  // printf("********input tensor 0: %s\n", interpreter->GetInputName(0));
  // printf("********input tensor 1: %s\n", interpreter->input_tensor(1)->name);

  ModelInfo* minfo = new ModelInfo();

  minfo->model = std::move((model));
  minfo->interpreter = std::move(interpreter);

  models[++modelId] = minfo;
  return modelId;
};

PUBLIC bool executeModel(int modelId, float* input, size_t lenInput,
                         float* output, size_t lenOut) {
  auto itr = models.find(modelId);
  if (itr == models.end()) return false;

  auto model = itr->second;
  float* input0 = model->interpreter->typed_input_tensor<float>(0);

  memcpy(input0, input, sizeof(float) * lenInput);

  if (model->interpreter->Invoke() != kTfLiteOk) {
    return false;
  }

  float* output0 = model->interpreter->typed_output_tensor<float>(0);
  memcpy(output, output0, sizeof(float) * lenOut);
  return true;
}
}