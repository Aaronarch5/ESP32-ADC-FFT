#include "arduinoFFT.h"

#define SAMPLES 128*2
#define SAMPLING_FREQUENCY 2000

arduinoFFT FFT = arduinoFFT();

unsigned long sampling_period_us;
unsigned long microseconds;
int static_variable = 4096;
int static_variable2 =0;


double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  Serial.begin(115200);
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop() {
  for (int i = 0; i < SAMPLES; i++) {
      microseconds = micros();
      vReal[i] = analogRead(34)-4096/2;
      vImag[i] = 0;
      while(micros() < (microseconds + sampling_period_us)){};  
  }


  
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  //double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  //Serial.println(peak);

  for (int i = 0; i < SAMPLES/2; i++) {
    if (vReal[i]>4096)
        {
          vReal[i]=0;
        
        }
          
//    Serial.print("Variable_1:");
    Serial.println(vReal[i]);
//    Serial.print(",");
//    Serial.print("Variable_2:");
//    Serial.print(2000);
//    Serial.print(",");
//    Serial.print("Variable_3:");
//    Serial.println(0);
    
  }
 
  
}
