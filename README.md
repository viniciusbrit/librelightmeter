# librelightmeter
A light meter designed for analog photography based on an ~~a TEMT6000~~ ambient light sensor running off a microcontroller. ~~an Arduino Pro Micro [ATmega32U4]~~.

### Current iteration: Prototype 0.1

### Project Progress
- [x] Build A Prototype.
- [ ] Find Sensor With Enough Range.
- [ ] Find another cheaper microcontroller.
- [ ] Design PCB.
- [ ] Write firmware.

### Known Issues
- [x] Find a way to measure more than 1000 lux with the sensor. 
  > Unfixable.
  > The TEMT6000 sensor only measures up to around 1000 lux. There's no way to circumvent this without blocking the amount of light the sensor reads somehow.
- [ ] Make it so measured value does not change when changing ISO.

### Licenses
CERN Open Hardware Licence Version 2.0 - Strongly Reciprocal
GNU GENERAL PUBLIC LICENSE Verson 3.0
