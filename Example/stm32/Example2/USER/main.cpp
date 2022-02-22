#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"



#include "tensorflow/lite/micro/examples/hello_world/main_functions.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/examples/hello_world/constants.h"
#include "tensorflow/lite/micro/examples/hello_world/model.h"
#include "tensorflow/lite/micro/examples/hello_world/output_handler.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "sine_model.h"

// Globals, used for compatibility with Arduino-style sketches.
namespace
{
    tflite::ErrorReporter* error_reporter = nullptr;
    const tflite::Model* model = nullptr;
    tflite::MicroInterpreter* interpreter = nullptr;
    TfLiteTensor* model_input = nullptr;
    TfLiteTensor* model_output = nullptr;

    // Create an area of memory to use for input, output, and intermediate arrays.
    // Finding the minimum value for your model may require some trial and error.
    constexpr uint32_t kTensorArenaSize = 2 * 1024;
    uint8_t tensor_arena[kTensorArenaSize];
} // namespace

void setup() 
{
  tflite::InitializeTarget();


  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  
   model = tflite::GetModel(sine_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  
  static tflite::AllOpsResolver resolver;

	static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  	interpreter = &static_interpreter;


  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

 
}

const uint16_t INFERENCE_PER_CYCLE = 200;
extern const float INPUT_RANGE = 2.f * 3.14159265359f;

int main(void)
{ 
 	u8 x=0;
	u8 lcd_id[12];				//存放LCD ID字符串
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	
	LED_Init();					  //初始化LED
 	LCD_Init();           //初始化LCD FSMC接口
	POINT_COLOR=RED;      //画笔颜色：红色
	setup();
	float unitValuePerDevision = INPUT_RANGE / static_cast<float>(INFERENCE_PER_CYCLE);
	model_input = interpreter->input(0);
  model_output = interpreter->output(0);
  while(1)
	{
				 for(uint16_t inferenceCount = 0; inferenceCount <= INFERENCE_PER_CYCLE; inferenceCount++)
        {
	        float x_val = static_cast<float>(inferenceCount) * unitValuePerDevision;

	        // Place our calculated x value in the model's input tensor
	        model_input->data.f[0] = x_val;

	        // Run inference, and report any error
	        TfLiteStatus invoke_status = interpreter->Invoke();
	        // Read the predicted y value from the model's output tensor
	        float y_val = model_output->data.f[0];
					LCD_ShowxNum(0,0,x_val*100,5,16,1);
					LCD_ShowxNum(100,0,y_val*100,5,16,1);

					LCD_Fast_DrawPoint(x_val*20,y_val*10+40,RED);
				}

	}
}
