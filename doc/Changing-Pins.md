## Changing Pins
Pin Marking|-|-|-|-
:---|---|---|---|---
pin name STM32|PA4|PA1|PB10|PA8
pin name arduino|A2|A1|D6|D7
peripheral measurement|ADC2_IN4|ADC1_IN1|GPIO_PB10|GPIO_PA8
peripheral 8-bit bus|GPIO-PA4|GPIO_PA1|GPIO_PB10|GPIO_PA8
user label measurement|XM|YP|XP|YM
user label 8-bit bus|LCD-D/C|LCD-WR|LCD-D6|LCD-D7

Pin Settings 8-bit bus|-|-|-|-
---|---|---|---|---
mode|OUTPUT_PP|OUTPUT_PP|OUTPUT_PP|OUTPUT_PP
pull|NOPULL|NOPULL|NOPULL|NOPULL

Pin Settings x-measurement|-|-|-|-
---|---|---|---|---
mode|OUTPUT_PP|ANALOG|OUTPUT_PP|INPUT
pull|NOPULL|NOPULL|NOPULL|NOPULL

Pin Settings y-measurement|-|-|-|-
---|---|---|---|---
mode|ANALOG|OUTPUT_PP|INPUT|OUTPUT_PP
pull|NOPULL|NOPULL|NOPULL|NOPULL

Pin Settings z-measurement|-|-|-|-
---|---|---|---|---
mode|ANALOG|ANALOG|OUTPUT_PP|OUTPUT_PP
pull|NOPULL|NOPULL|NOPULL|NOPULL
gpio-set|||set|reset
