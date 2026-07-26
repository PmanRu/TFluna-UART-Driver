#include <avr/io.h>
#include "TFluna.h"

int main() {

  UBRR0 = 16;
  UCSR0A = (1<<U2X0);
  UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
  UCSR0B = (1<<TXEN0) | (1<<RXEN0);
  
  while (1) {
    TFluna('C');
  }

  return 0;
}