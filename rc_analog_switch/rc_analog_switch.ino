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
const int RC_THR = 1500;  // typical signal range is between 1000 and 2000
const int CD4051_IN1 = 2;
const int CD4051_IN2 = 1;
const int CD4051_IN3 = 0;

int rc_val;
int current_ch;

void setup() {
  pinMode(CD4051_IN1, OUTPUT);
  pinMode(CD4051_IN2, OUTPUT);
  pinMode(CD4051_IN3, OUTPUT);
  pinMode(RC_IN_PIN, INPUT);
}

int switch_to_channel(int ch) {
  // (S0 = 1; S1 = 2; S2 = 4)
  digitalWrite(CD4051_IN1, bitRead(ch, 0));
  digitalWrite(CD4051_IN2, bitRead(ch, 1));
  digitalWrite(CD4051_IN3, bitRead(ch, 2));
  return ch;
}

void loop() {
  rc_val = pulseIn(RC_IN_PIN, HIGH, 25000);
  if (rc_val > RC_THR && current_ch != 1) {     // video 2
    current_ch = switch_to_channel(1);
  } else if (rc_val <= RC_THR && current_ch != 0) {       // video 1
    current_ch = switch_to_channel(0);
  }
  delay(10);
}
