# stm32_SRAM_demo
Demo program that benchmarks a SRAM compatible memory chip. <br>
It uses the FMC peripheral of the STM32F746ZG to access SRAM memory chips. <br>
The benchmark "settings" can be changed through the UART interface. <br>
This demo was tested with the [FM28V020](https://www.infineon.com/dgdl/Infineon-FM28V020_256_KBIT_(32K_X_8)_F-RAM_MEMORY-DataSheet-v09_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0ec8aa524123) 256k SRAM compatible chip. <br>
It has 8 data lines and 15 address lines.
### Pin configuration
| GPIO Pin | FMC Data pin |
|----------|--------------|
| PD14     | FMC_D0       |
| PD15     | FMC_D1       |
| PD0      | FMC_D2       |
| PD1      | FMC_D3       |
| PE7      | FMC_D4       |
| PE8      | FMC_D5       |
| PE9      | FMC_D6       |
| PE10     | FMC_D7       |

| GPIO Pin | FMC Address Pin |
|----------|-----------------|
| PF0      | FMC_A0          |
| PF1      | FMC_A1          |
| PF2      | FMC_A2          |
| PF3      | FMC_A3          |
| PF4      | FMC_A4          |
| PF5      | FMC_A5          |
| PF12     | FMC_A6          |
| PF13     | FMC_A7          |
| PF14     | FMC_A8          |
| PF15     | FMC_A9          |
| PG0      | FMC_A10         |
| PG1      | FMC_A11         |
| PG2      | FMC_A12         |
| PG3      | FMC_A13         |
| PG4      | FMC_A14         |

| GPIO Pin | Other FMC pin |
|----------|---------------|
| PD5      | FMC_NWE       |
| PD4      | FMC_NOE       |
| PD7      | FMC_NE1       |
