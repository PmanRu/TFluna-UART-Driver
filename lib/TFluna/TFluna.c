#include <avr/io.h>
#include <stdbool.h>

bool inches = false;

uint16_t TF_distance(char unit) {
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

    if (unit == 'C')  {return distance;}

    if (unit == 'I') {
      inches = true;
      return (distance / 2.5);
    }

    else {return 1;}
}

void TF_monitor(uint16_t distance) {
  //stores each individual digit from the distance value in reverse inside an array
  int asciiConvert[4];
  for (int i=0; i < sizeof(asciiConvert)/2; i++) {
    switch (i) {
      case 0:
        if (distance >= 1000) {
          asciiConvert[0] = (distance % 10) + '0';
          distance /= 10;
            break;
        }
          
        else {
          asciiConvert[0] = 99;
          break;
        }
          
      case 1:
        if (distance >= 100) {
          asciiConvert[1] = (distance % 10) + '0';
          distance /= 10;
          break;
        }

        else {
          asciiConvert[1] = 99;
          break;
        }

      case 2:
        if (distance >= 10) {
          asciiConvert[2] = (distance % 10) + '0';
          distance /= 10;
          break;
        }

        else {
          asciiConvert[2] = 99;
          break;
        }

      case 3:
        asciiConvert[3] = distance + '0';
        break;
    }
  }
    
  //Unit of measurement: inches
  if (inches) {
    for (int i=sizeof(asciiConvert)/2; i > 0; i--) {
      if (asciiConvert[i] == 99) {continue;}
      while(!(UCSR0A & (1<<UDRE0)));
      UDR0 = asciiConvert[i];
    }

    char measurement[] = "in";
    for (int j=0; j < (sizeof(measurement)-1); j++) {
      while(!(UCSR0A & (1<<UDRE0)));
      UDR0 = measurement[j];
    } 
  }

  //Unit of measurement: centimeters
  else {
    for (int i=sizeof(asciiConvert)/2; i > 0; i--) {
      if (asciiConvert[i] == 99) {continue;}
      while(!(UCSR0A & (1<<UDRE0)));
      UDR0 = asciiConvert[i];
    }

    char measurement[] = "cm";
    for (int j=0; j < (sizeof(measurement)-1); j++) {
      while(!(UCSR0A & (1<<UDRE0)));
      UDR0 = measurement[j];
    } 
  }

  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = '\n';
}