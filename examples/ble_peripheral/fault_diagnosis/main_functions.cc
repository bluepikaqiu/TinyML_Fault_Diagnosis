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

//#include "hello_world/main_functions.h"
//#include "hello_world/constants.h"
//#include "hello_world/sine_model_quantized_model_data.h"
//#include "hello_world/output_handler.h"
//#include "tensorflow/lite/experimental/micro/micro_mutable_op_resolver.h"
//#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
//#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
//#include "tensorflow/lite/schema/schema_generated.h"
#include "fault_diagnosis/main_functions.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "fault_diagnosis/constants.h"
//#include "fault_diagnosis/sine_model_quantized_model_data.h"
#include "fault_diagnosis/model_keras_to_tflite.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "nrf_delay.h"
#include "arm_math.h"

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input_pointer = nullptr;
TfLiteTensor* output_pointer = nullptr;
int inference_count = 0;
constexpr int kTensorArenaSize = 22 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

using HelloWorldOpResolver = tflite::MicroMutableOpResolver<10>;
TfLiteStatus RegisterOps(HelloWorldOpResolver& op_resolver) {
  TF_LITE_ENSURE_STATUS(op_resolver.AddQuantize());
  TF_LITE_ENSURE_STATUS(op_resolver.AddDequantize());
  //TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected(tflite::Register_FULLY_CONNECTED_INT8()));
	//TF_LITE_ENSURE_STATUS(op_resolver.AddDepthwiseConv2D(tflite::Register_DEPTHWISE_CONV_2D_INT8()));
  //TF_LITE_ENSURE_STATUS(op_resolver.AddConv2D(tflite::Register_CONV_2D_INT8()));
	
	TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected());
	TF_LITE_ENSURE_STATUS(op_resolver.AddDepthwiseConv2D());
  TF_LITE_ENSURE_STATUS(op_resolver.AddConv2D());
	
	//TF_LITE_ENSURE_STATUS(op_resolver.AddMul());
	//TF_LITE_ENSURE_STATUS(op_resolver.AddAdd());
  //TF_LITE_ENSURE_STATUS(op_resolver.AddMaxPool2D(tflite::Register_MAX_POOL_2D_INT8()));
  //TF_LITE_ENSURE_STATUS(op_resolver.AddSoftmax(tflite::Register_SOFTMAX_INT8()));
	
	TF_LITE_ENSURE_STATUS(op_resolver.AddMaxPool2D());
  TF_LITE_ENSURE_STATUS(op_resolver.AddSoftmax());
	
  TF_LITE_ENSURE_STATUS(op_resolver.AddReshape());
  return kTfLiteOk;
}
}  // namespace

TfLiteStatus TFLM_Inference(const float32_t *feature_matrix, uint8_t *pred_label, const int flag) 
{
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  // static tflite::MicroErrorReporter micro_error_reporter;
  // error_reporter = &micro_error_reporter;
  
  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = ::tflite::GetModel(CWRU_Bearing_2_best_model_with_fe_tflite);
  TFLITE_CHECK_EQ(model->version(), TFLITE_SCHEMA_VERSION);
	
	memset(tensor_arena, 0, sizeof(tensor_arena));
	
  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  HelloWorldOpResolver resolver;
  TF_LITE_ENSURE_STATUS(RegisterOps(resolver));
	
  // Build an interpreter to run the model with.
  tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TF_LITE_ENSURE_STATUS(interpreter->AllocateTensors());
	size_t used_memory = interpreter->arena_used_bytes();
	//printf("Tensor arena used: %d bytes\n", used_memory);
	//nrf_delay_ms(25);


  // Obtain pointers to the model's input and output tensors.
  input_pointer = interpreter->input(0);
  output_pointer = interpreter->output(0);
	
  // Set the input tensor shape to (1, 9, 9, 1)
  input_pointer->dims->size = 4; // Set number of dimensions
  input_pointer->dims->data[0] = 1; // Batch size
  input_pointer->dims->data[1] = 9; // Height
  input_pointer->dims->data[2] = 9; // Width
  input_pointer->dims->data[3] = 1; // Channels

  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
  //static_cast<float> transform the sympol to float
	float32_t feature_matrix_3d[1][9][9][1];
	for (int row = 0; row < 9; ++row) 
	{
		for (int col = 0; col < 9; ++col) 
		{
			int index = row * 9 + col;
			feature_matrix_3d[0][row][col][0] = feature_matrix[index];
		}
	}
	
   memcpy(input_pointer->data.f, feature_matrix_3d, sizeof(feature_matrix_3d));
	
  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
			printf("Invoke Error!\n");
			nrf_delay_ms(25);
  }
	
	int8_t y_quantized[10];
	float32_t y[10];
	for (int i = 0; i < 10; i++) {
  // Obtain the quantized output from model's output tensor
  y_quantized[i] = output_pointer->data.int8[i];
  // Dequantize the output from integer to floating-point
		y[i] = (y_quantized[i] - output_pointer->params.zero_point) * output_pointer->params.scale; //zero_point: -128, scale: 1/256
	}
	
	// float32_t *output_data = output_pointer->data.f;
	float32_t max_probability;
	uint32_t max_index;
	arm_absmax_f32(&y[0], 10, &max_probability, &max_index); // Return predicted label
	
	/*
	for (int i = 0; i < 10; ++i) {
		printf("Class %d probability: %f\n", i, output_data[i]);
		nrf_delay_ms(25);
	}
	
	printf("Predicted label: %d\n", max_index);
	nrf_delay_ms(25);
	*/
	
	/*
	if(max_index == true_label)
	{
		(*index)++;
		printf("index: %d\n", *index);
		nrf_delay_ms(25);
	}
	*/
	pred_label[flag] = max_index;
	
  // Output the results. A custom HandleOutput function can be implemented
  // for each supported hardware target.


  // Keep track of how many inferences we have performed.
  // Inference_count = 0;
	
	return kTfLiteOk;
}

/*
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
	
	printf("%f, %f\n", x, y_val);
	nrf_delay_ms(25);

  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle)
  {
    inference_count = 0;
  }
}
*/