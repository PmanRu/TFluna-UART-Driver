#include <avr/io.h>

int main() {

  UBRR0 = 16;
  UCSR0A = (1<<U2X0);
  UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
  UCSR0B = (1<<TXEN0) | (1<<RXEN0);
  
  while (1) {

    uint8_t headerCheck[2] = {0, 0};
    while (headerCheck[0] != 0x59 || headerCheck[1] != 0x59) {
      for (int i=0; i<sizeof(headerCheck); i++) {
        while(!(UCSR0A & (1<<RXC0)));
        headerCheck[i] = UDR0;
      }
    }

    while(!(UCSR0A & (1<<RXC0)));
    uint8_t low = UDR0;

    while(!(UCSR0A & (1<<RXC0)));
    uint8_t high = UDR0;
    int asciiConvert[4];
    uint16_t distance = (high<<8) | low;
    
    for (int i=0; i < sizeof(asciiConvert)/2; i++) {
      switch (i) {
        case 0:
          if (distance >= 1000) {
            asciiConvert[0] = distance;
            
            while (asciiConvert[0] % 100) {
              asciiConvert[0]--;
            }
            asciiConvert[0] /= 100;

            while (asciiConvert[0] % 10) {
              asciiConvert[0]--;
            }
            asciiConvert[0] = (asciiConvert[0]/10) + '0';
            break;
          }
          
          else {
            asciiConvert[0] = 99;
            break;
          }

        case 1:
          if (distance >= 100) {
            asciiConvert[1] = distance;
            
            while (asciiConvert[1] % 100) {
              asciiConvert[1]--;
            }
            asciiConvert[1] /= 100;

            asciiConvert[1] = (asciiConvert[1] % 10) + '0';
            break;
          }

          else {
            asciiConvert[1] = 99;
            break;
          }

        case 2:
          if (distance >= 10) {
            asciiConvert[2] = distance;
            
            while (asciiConvert[2] % 10) {
              asciiConvert[2]--;
            }
            asciiConvert[2] %= 100;

            asciiConvert[2] = (asciiConvert[2]/10) + '0';
            break;
          }

          else {
            asciiConvert[2] = 99;
            break;
          }

        case 3:
          asciiConvert[3] = (distance % 10) + '0';
          break;
      }
    }

    for (int i=0; i < sizeof(asciiConvert)/2; i++) {
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

  return 0;
}