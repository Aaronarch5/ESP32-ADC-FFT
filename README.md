# FFT Plotting on ESP32 using arduinoFFT Library

This project demonstrates how to use the `arduinoFFT` library on an ESP32 to perform a Fast Fourier Transform (FFT) on analog signals read from a specified pin. The code reads the signal, applies a Hamming window, computes the FFT, converts the results to magnitude, and then prints the frequency components to the Serial Monitor.

## Components

- ESP32
- Analog signal source connected to pin 34

## Dependencies

- Arduino IDE
- `arduinoFFT` library

## Installation

1. Install the Arduino IDE from [here](https://www.arduino.cc/en/software).
2. Open Arduino IDE, go to **Sketch** > **Include Library** > **Manage Libraries**.
3. Search for `arduinoFFT` and install it.

## Wiring

Connect your analog signal source to pin 34 of the ESP32.

## How to Use
- Connect your ESP32 to the computer and upload the provided code.
- Open the Serial Monitor in Arduino IDE (set the baud rate to 115200).
- The frequency components will be printed to the Serial Monitor.

## Explanation
Setup:

- Initializes Serial communication at a baud rate of 115200.
- Calculates the sampling period in microseconds based on the defined sampling frequency.
## Loop:

- Reads analog values from pin 34 and stores them in vReal.
- Applies a Hamming window to the sampled data.
- Performs the FFT on the windowed data.
- Converts the complex numbers to magnitudes.
- Prints the magnitude values to the Serial Monitor.
Notes

The following code reads analog values, computes the FFT, and prints the frequency components to the Serial Monitor.

```cpp
#include "arduinoFFT.h"

#define SAMPLES 128*2
#define SAMPLING_FREQUENCY 2000

arduinoFFT FFT = arduinoFFT();

unsigned long sampling_period_us;
unsigned long microseconds;
int static_variable = 4096;
int static_variable2 = 0;

double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  Serial.begin(115200);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  for (int i = 0; i < SAMPLES; i++) {
    microseconds = micros();
    vReal[i] = analogRead(34) - 4096 / 2;
    vImag[i] = 0;
    while (micros() < (microseconds + sampling_period_us)) {};
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  for (int i = 0; i < SAMPLES / 2; i++) {
    if (vReal[i] > 4096) {
      vReal[i] = 0;
    }
    Serial.println(vReal[i]);
  }
}
