/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "model.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "nvs_flash.h"
#include "camera_pins.h"
#include "esp_camera.h"
#include "test_img.h"
#include "gpio_motor.h"
#include "pwm_motor.h"

#include <esp_log.h>

// Globals, used for compatibility with Arduino-style sketches.
namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;
  int inference_count = 0;

constexpr int kTensorArenaSize = 614400;



}  // namespace
void camer_init()
{
 camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;// 2 20000000
    config.pixel_format = PIXFORMAT_RGB888;
    //init with high specs to pre-allocate larger buffers
    config.frame_size = FRAMESIZE_QCIF;
    config.fb_count = 1;// 2 2
    
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    printf("Camera init failed with error 0x %x", err);
    return;
  }
    sensor_t * s = esp_camera_sensor_get();

   s->set_brightness(s, 2);     // -2 to 2
  s->set_contrast(s, 0);       // -2 to 2
  s->set_saturation(s, 0);     // -2 to 2
  s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
  s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
  s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
  s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
  s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
  s->set_aec2(s, 1);           // 0 = disable , 1 = enable
  s->set_ae_level(s, 0);       // -2 to 2
  s->set_aec_value(s, 300);    // 0 to 1200
  s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
  s->set_agc_gain(s, 0);       // 0 to 30
  s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
  s->set_bpc(s, 1);            // 0 = disable , 1 = enable
  s->set_wpc(s, 1);            // 0 = disable , 1 = enable
  s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
  s->set_lenc(s, 1);           // 0 = disable , 1 = enable
  s->set_hmirror(s, 1);        // 0 = disable , 1 = enable
  s->set_vflip(s, 1);          // 0 = disable , 1 = enable
  s->set_dcw(s, 1);            // 0 = disable , 1 = enable
  s->set_colorbar(s, 0);       // 0 = disable , 1 = enable
}

void setup() {
  camer_init();
  
  

  printf("Hello world!\n");
   
}


extern "C" void app_main() {
  setup();

  
	 uint8_t *tensor_arena;
  tensor_arena = (uint8_t *)malloc(614400);
  tflite::InitializeTarget();
  
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }
 
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  while (true) 
  {
    // Obtain pointers to the model's input and output tensors.
    input = interpreter->input(0);
    output = interpreter->output(0);

    camera_fb_t * fb = esp_camera_fb_get();
    esp_camera_fb_return(fb);
    fb = esp_camera_fb_get();
    printf("len=%d\n",fb->len);
    int temp=0;
    int crop_size[3]={128,128,3};
    int count=0;
    int oring__w=176;

    // fb存储的是BGR数据
    for(int i=0;i<crop_size[0]*crop_size[1]*crop_size[2];i++)
    {
     printf("%d,",fb->buf[count]);
      if(temp==0)
        input->data.int8[i] = fb->buf[count]*0.9178016211133283-127.50911549119088;
      if(temp==1)
        input->data.int8[i] = fb->buf[count]*0.938288264441751 -123.1041593892868;
      if(temp==2)
        input->data.int8[i] = fb->buf[count]*0.9341180943775653-110.70924631090934;
      temp++;
      
      if(temp==3)
      temp=0;
      if((i%5000)==1)
         vTaskDelay(100 / portTICK_PERIOD_MS);
      if(i%(crop_size[1]*crop_size[2])==0)
        count=(i/(crop_size[1]*crop_size[2]))*oring__w*crop_size[2];
      count=count+1;
    }
    printf("\n\n");
    if (kTfLiteOk != interpreter->Invoke()) {
      TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed.");
    }
    for(int i=0;i<40;i++)
    printf("%d\n",output->data.int8[i]);

    printf("Hello world!\n");
    esp_camera_fb_return(fb);
    
  }
}
*/