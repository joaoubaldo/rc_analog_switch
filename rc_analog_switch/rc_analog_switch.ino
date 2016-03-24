/*
Author: Joao Coutinho <me joaoubaldo com>
Description:
This project implements an analog signal switcher for R/C applications.
Input is an R/C channel (RC_IN_PIN). 
Analog signal is switched based on RC_THR threshold. Can be easily adapted to support up to 8 channels.

Requirements:
Attiny85 (1Mhz internal clock works great)
CD4051 analog multiplexer

Connections:
  attiny |  4051
    5(0) |   9
    6(1) |   10
    7(2) |   11

RC_IN_PIN --> attiny (2)
Video1    --> 4051 (13)
Video2    --> 4051 (14)

4051 (6, 7, 8) --> GND
4051 (16)      --> Vcc
4051 (3)       --> OUTPUT SIGNAL
attiny (4)     --> GND
attiny (8)     --> Vcc

References:
R/C read: https://www.sparkfun.com/tutorials/348
attiny85 pinout: http://highlowtech.org/wp-content/uploads/2011/10/ATtiny45-85.png
CD4051 mux: http://playground.arduino.cc/Learning/4051
*/
const int RC_IN_PIN = 3;
const int RC_THR = 1500;
const int CD4051_IN1 = 2;
const int CD4051_IN2 = 1;
const int CD4051_IN3 = 0;

int ch1;

void setup() {
  pinMode(CD4051_IN1, OUTPUT);
  pinMode(CD4051_IN2, OUTPUT);
  pinMode(CD4051_IN3, OUTPUT);
  pinMode(RC_IN_PIN, INPUT);
}

void loop() {
  ch1 = pulseIn(RC_IN_PIN, HIGH, 25000);
  // (S0 = 1; S1 = 2; S2 = 4)
  if (ch1 > RC_THR) {             // video 2
    digitalWrite(CD4051_IN1, bitRead(1,0));
    digitalWrite(CD4051_IN2, bitRead(1,1));
    digitalWrite(CD4051_IN3, bitRead(1,2));
  } else {                        // video 1
    digitalWrite(CD4051_IN1, bitRead(0,0));
    digitalWrite(CD4051_IN2, bitRead(0,1));
    digitalWrite(CD4051_IN3, bitRead(0,2));
  }
  delay(100);
}
