#include <Arduino.h>

/* this function will be invoked when additionalTask was created */

const int led1 = 2; // Pin of the LED
SemaphoreHandle_t xBinarySemaphore; // Tipo que simula el semáforo

void toggleONLED( void * parameter );
void toggleOFFLED( void * parameter );

void setup(){

  Serial.begin(112500);
  pinMode(led1, OUTPUT);
  xBinarySemaphore = xSemaphoreCreateBinary();
  
  /* we create a new task here */
  xTaskCreate (toggleONLED, /* Task function. */
  "Toggle ONLED", /* name of task. */ 
  1000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL); /* Task handle to keep track of created task */

  /* we create a new task here */
  xTaskCreate (toggleOFFLED, /* Task function. */
  "Toggle OFFLED", /* name of task. */ 
  1000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL); /* Task handle to keep track of created task */

  xSemaphoreGive (xBinarySemaphore);

}

/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop(){

  delay(1000);

}

void toggleONLED(void * parameter){

  while(1){
    
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("LED ON");
    digitalWrite(led1, HIGH);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1000);
        
  }
  
}

void toggleOFFLED(void * parameter){

  while(1){
    
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("LED OFF");
    digitalWrite(led1, LOW);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1000);

  }

}