/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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

#include "tensorflow/lite/micro/examples/fault_diagnosis/main_functions.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/examples/fault_diagnosis/constants.h"
#include "tensorflow/lite/micro/examples/fault_diagnosis/models/hello_world_float_model_data.h"
#include "tensorflow/lite/micro/examples/fault_diagnosis/sine_model_quantized_model_data.h"
#include "tensorflow/lite/micro/examples/fault_diagnosis/output_handler.h"
#include "tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;
constexpr int kTensorArenaSize = 3 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

using HelloWorldOpResolver = tflite::MicroMutableOpResolver<35>;
TfLiteStatus RegisterOps(HelloWorldOpResolver& op_resolver) {
  TF_LITE_ENSURE_STATUS(op_resolver.AddQuantize());
  TF_LITE_ENSURE_STATUS(op_resolver.AddDequantize());
  TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected());
  TF_LITE_ENSURE_STATUS(op_resolver.AddConv2D());
  TF_LITE_ENSURE_STATUS(op_resolver.AddMaxPool2D());
  TF_LITE_ENSURE_STATUS(op_resolver.AddSoftmax());
  TF_LITE_ENSURE_STATUS(op_resolver.AddReshape());
  
  return kTfLiteOk;
}
}  // namespace

TfLiteStatus setup() 
{
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;
  
  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = ::tflite::GetModel(g_sine_model_quantized_model_data);
  TFLITE_CHECK_EQ(model->version(), TFLITE_SCHEMA_VERSION);

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  HelloWorldOpResolver resolver;
  TF_LITE_ENSURE_STATUS(RegisterOps(resolver));

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TF_LITE_ENSURE_STATUS(interpreter->AllocateTensors());

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 0;
  return kTfLiteOk;
}

// The name of this function is important for Arduino compatibility,which constanly running.
void loop()
{
  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
  //static_cast<float> transform the sympol to float
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle); //'static_cast<data type>' : cast type
  float x = position * kXrange;

  // Quantize the input from floating-point to integer
  // int8_t x_quantized = x / input->params.scale + input->params.zero_point;
  // Place the quantized input in the model's input tensor
  input->data.f[0] = x;
  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x: %f\n",
                         static_cast<double>(x));
    return;
  }

  // Obtain the quantized output from model's output tensor
  // int8_t y_quantized = output->data.int8[0];
  // Dequantize the output from integer to floating-point
  // float y = (y_quantized - output->params.zero_point) * output->params.scale;
  float y_val = output->data.f[0];
  // Output the results. A custom HandleOutput function can be implemented
  // for each supported hardware target.
  HandleOutput(error_reporter, x, y_val);

  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle)
  {
    inference_count = 0;
  }
}
