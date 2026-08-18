#include <avr/io.h>

uint16_t TF_distance() {
  //checks for header bytes
  uint8_t headerCheck[2] = {0, 0};
  while (headerCheck[0] != 0x59 || headerCheck[1] != 0x59) {
    for (int i=0; i<sizeof(headerCheck); i++) {
      while(!(UCSR0A & (1<<RXC0)));
      headerCheck[i] = UDR0;
    }
  }

  //stores low distance byte
  while(!(UCSR0A & (1<<RXC0)));
  uint8_t low = UDR0;

  //stores high distance byte
  while(!(UCSR0A & (1<<RXC0)));
  uint8_t high = UDR0;
  uint16_t distance = (high<<8) | low;

  return distance;
}

void TF_monitor(uint16_t distance) {

  //Stores each digit from the distance value inside an array in reverse
  int asciiConvert[4];
  int num = 1000;
  for (int i=0; i < sizeof(asciiConvert)/2; i++) {
    if (distance < 10) {
      asciiConvert[i] = distance + '0';
      while (i < sizeof(asciiConvert)/2) {
        ++i;
        asciiConvert[i] = 99;
      }
    }
    
    else if (distance >= num) {
      asciiConvert[i] = (distance % 10) + '0';
      distance /= 10;
      num /= 10;
      continue;
    }

    else {
      asciiConvert[i] = 99;
      num /= 10;
      continue;
    }
  }

  for (int i=((sizeof(asciiConvert)/2)-1); i >= 0; i--) {
    if (asciiConvert[i] == 99) {continue;}

    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = asciiConvert[i];
  }

  char measurement[] = "cm";
  for (int j=0; j < (sizeof(measurement)-1); j++) {
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = measurement[j];
  } 
  
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = '\n';
}