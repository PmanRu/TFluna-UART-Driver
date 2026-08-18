# UART Driver for the TF-luna Ranging Lidar Sensor

### How it Works
Before sending distance values, the sensor sends the header byte 0x59 twice. Taking that information from the datasheet, I configured it so the ATmega328P is constantly polling until it receives both of the header bytes in consecutive order allowing the MCU to proceed with storing the distance bytes. Once accomplished, the distance value is extracted and converted to ascii for the serial monitor.

### TFluna library
- `TF_distance()` returns the distance value
- `TF_monitor()` sends the distance values to the serial monitor
