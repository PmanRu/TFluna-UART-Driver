#include <avr/io.h>
#include "TFluna.h"

int main() {

  //UART initialization
  UBRR0 = 16;
  UCSR0A = (1<<U2X0);
  UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
  UCSR0B = (1<<TXEN0) | (1<<RXEN0);
  
  uint16_t distance;

  while (1) {
    distance = TF_distance();
    TF_monitor(distance);
  }

  return 0;
}