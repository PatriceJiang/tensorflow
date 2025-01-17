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
    exit(1);                                                 \
  }

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "minimal <tflite model>\n");
    return 1;
  }
  const char* filename = argv[1];

  // Load model
  std::unique_ptr<tflite::FlatBufferModel> model =
      tflite::FlatBufferModel::BuildFromFile(filename);
  TFLITE_MINIMAL_CHECK(model != nullptr);

  // Build the interpreter with the InterpreterBuilder.
  // Note: all Interpreters should be built with the InterpreterBuilder,
  // which allocates memory for the Interpreter and does various set up
  // tasks so that the Interpreter can read the provided model.
  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder builder(*model, resolver);
  std::unique_ptr<tflite::Interpreter> interpreter;
  builder(&interpreter);
  TFLITE_MINIMAL_CHECK(interpreter != nullptr);

  // Allocate tensor buffers.
  TFLITE_MINIMAL_CHECK(interpreter->AllocateTensors() == kTfLiteOk);
  printf("=== Pre-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(interpreter.get());

  printf("********input size %d\n", (int)interpreter->inputs().size());
  printf("********input tensor 0: %s\n", interpreter->GetInputName(0));
  printf("********input tensor 1: %s\n", interpreter->input_tensor(1)->name);

  // Fill input buffers
  // TODO(user): Insert code to fill input tensors.
  // Note: The buffer of the input tensor with index `i` of type T can
  // be accessed with `T* input = interpreter->typed_input_tensor<T>(i);`
  float* input0 = interpreter->typed_input_tensor<float>(0);
  // float* input1 = interpreter->typed_input_tensor<float>(1);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      auto s = ((i * 8) + j) * 3;
      input0[s + 0] = 0;
      input0[s + 1] = 0;
      input0[s + 2] = 0;
    }
  }

  TFLITE_MINIMAL_CHECK(interpreter->Invoke() == kTfLiteOk);

  float* output = interpreter->typed_output_tensor<float>(0);
  for (int i = 0; i < 43; i++) {
    printf("w %d: %f\n", i, output[i]);
  }

  // input0[0] = 3;
  // input0[1] = 10;
  // // input1[0] = 10;
  // // input1[1] = 20;
  // // input1[2] = 100;

  // for (float i = 0; i < 20; i++) {
  //   input0[0] = i;
  //   input0[1] = i;
  //   // input1[3] = i*10;
  //   // input1[4] = i*20;

  //   TFLITE_MINIMAL_CHECK(interpreter->Invoke() == kTfLiteOk);
  //   float* output = interpreter->typed_output_tensor<float>(0);
  //   printf("input %f, output %f\n", i, output[0]);
  // }

  // Run inference
  // TFLITE_MINIMAL_CHECK(interpreter->Invoke() == kTfLiteOk);
  // printf("\n\n=== Post-invoke Interpreter State ===\n");
  // tflite::PrintInterpreterState(interpreter.get());

  // Read output buffers
  // TODO(user): Insert getting data out code.
  // Note: The buffer of the output tensor with index `i` of type T can
  // be accessed with `T* output = interpreter->typed_output_tensor<T>(i);`
  // float* output = interpreter->typed_output_tensor<float>(0);

  // printf(
  // "########################################################################"
  // "########\n");
  // printf("output %f\n", *output);

  return 0;
}
