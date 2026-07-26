# UART Driver for the TF-luna Ranging Lidar Sensor
Before sending distance values, the sensor sends the header byte 0x59 twice. Taking that information from the datasheet, it was clear a system had to be set where the the ATmega328P is constantly polling until it receives the 2 header bytes consecutively in order to proceed with storing the distance bytes. Once accomplished, the value distance value had to be extracted and converted to ascii for the serial monitor.

Units of measurement:
- centimeters (default)
- inches

### How to select desired Unit
The parameter for the `TFluna()` function within the TFluna library must be `'C'` for cm or `'I'` for inches
