## Pins at 8-bit 

name|LCD|arduino|STM32|STM32-Port B|active  
----------|-------|---------|-------|-------|--------  
LCD reset|LCD-RST|D20-A4|PC1|PC1|low  
LCD chip select |LCD-CS|D19-A3|PB0|PC0|low  
LCD data/com select|LCD-D/C -- Touch_X-|D18-A2|PA4|PA4|low = com -- high  
LCD write strobe|LCD-WR -- Touch_Y+|D17-A1|PA1|PA1|rising edge (idle: high) -- high  
LCD read strobe|LCD-RD|D16-A0|PA0|PA0|rising edge (idle: high)  
Ground|GND|GND|GND|GND|low  
Vcc|5V|5V|5V|5V|high  
Vcc|3,3V|3,3V|3,3V|3,3V|high  
----------|-------|---------|-------|-------|--------  
LCD data|LCD-D2|D2|PA10|PB2|high  
LCD data|LCD-D3|D3|PB3|PB3|high  
LCD data|LCD-D4|D4|PB5|PB4|high  
LCD data|LCD-D5|D5|PB4|PB5|high  
LCD data|LCD-D6 -- Touch_X+|D6|PB10|PB6|high -- analog  
LCD data|LCD-D7 -- Touch_Y-|D7|PA8|PB7|high -- analog  
LCD data|LCD-D0|D8|PA9|PB0|high  
LCD data|LCD-D1|D9|PC7|PB1|high  
----------|-------|---------|-------|-------|--------  
SD select|SD-SS|D10  
SD data|SD-DI|D11   
SD data|SD-DO|D12  
SD clock|SD-SCK|D13
