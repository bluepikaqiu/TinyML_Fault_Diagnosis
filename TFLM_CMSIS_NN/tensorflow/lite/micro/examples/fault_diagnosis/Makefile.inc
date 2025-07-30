EXAMPLE_NAME := fault_diagnosis

HELLO_WORLD_TEST_SRCS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/hello_world_test.cc

HELLO_WORLD_SRCS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/main.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/main_functions.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/constants.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/${EXAMPLE_NAME}/sine_model_quantized.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_float_model_data.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/sine_model_quantized_model_data.cc

HELLO_WORLD_HDRS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/constants.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/main_functions.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/sine_model_data.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_float_model_data.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/sine_model_quantized_model_data.h

HELLO_WORLD_GENERATOR_INPUTS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_float.tflite \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_int8.tflite \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/sine_model_quantized.tflite

HELLO_WORLD_GENERATED_SRCS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_float_model_data.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_int8_model_data.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/${EXAMPLE_NAME}/sine_model_quantized_model_data.cc

HELLO_WORLD_GENERATED_HDRS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_float_model_data.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/models/hello_world_int8_model_data.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/sine_model_quantized_model_data.h

OUTPUT_HANDLER_TEST_SRCS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler_test.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.cc

OUTPUT_HANDLER_TEST_HDRS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.h \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/constants.h

$(eval $(call microlite_test,$(EXAMPLE_NAME)_test,\
$(HELLO_WORLD_TEST_SRCS),,$(HELLO_WORLD_GENERATOR_INPUTS)))

# Builds a standalone binary.
$(eval $(call microlite_test,$(EXAMPLE_NAME),\
$(HELLO_WORLD_SRCS),$(HELLO_WORLD_HDRS)))

# Tests producing an output.
$(eval $(call microlite_test,output_handler_test,\
$(OUTPUT_HANDLER_TEST_SRCS),$(OUTPUT_HANDLER_TEST_HDRS)))

# Add sources and headers generated from $(HELLO_WORLD_GENERATOR_INPUTS).
HELLO_WORLD_SRCS += $(HELLO_WORLD_GENERATED_SRCS)
HELLO_WORLD_HDRS += $(HELLO_WORLD_GENERATED_HDRS)

list_$(EXAMPLE_NAME)_example_sources:
	@echo $(HELLO_WORLD_SRCS)

list_$(EXAMPLE_NAME)_example_headers:
	@echo $(HELLO_WORLD_HDRS)