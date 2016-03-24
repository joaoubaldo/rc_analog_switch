# rc_analog_switch
This project implements an analog signal switcher for R/C applications.

## Usage
Input is an R/C channel (RC_IN_PIN).  
Analog signal is switched based on RC_THR threshold. Can be easily adapted to support up to 8 channels.


## Requirements:
* Attiny85 (1Mhz internal clock works great)
* CD4051 analog multiplexer


## Connections:
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


##References:
R/C read: https://www.sparkfun.com/tutorials/348  
attiny85 pinout: http://highlowtech.org/wp-content/uploads/2011/10/ATtiny45-85.png  
CD4051 mux: http://playground.arduino.cc/Learning/4051
