# Lambda

Cool fantasy console that has

- 4 cores where each core has:
    - 16 16-bit registers:
        - 13 General Purpose - 0-C
        - 1 Accumulator - D
        - 1 Status Register - E
        - 1 Bank Register - F
    - 24-bit instruction pointer
    - 16-bit stack pointer
    - 16-bit base pointer
    - 24-bit data bus
    - 256 interrupts

## Instructions

This is in hexadecimal and for simplicity, I'm avoiding prefixing all values with "0x". The first value indicates how many bytes precede it for a given instruction. The second indicates an enumerator. The repetition of a character that is not hexadecimal(0-F) does not necessarily indicate the same constant.

### 1 Byte Instructions

- `HLT` - Halt - `00` - Halts console
- `RET` - Return - `01` - Pops stack down to the base pointer to where it will set final value as instruction pointer.

### 2 Byte Instructions 

- `INC` - Increment - `10 RS`
- `DEC` - Decrement - `11 RS`
- `CLB` - Call Byte - `12 SS`
- `CLR` - Call Relative - `13 SS`
- `TJMP` - Tiny Jump - `14 II`
- `ADDR` - Add Registers - `15 RR`
- `ADDRC` - Add Registers with Carrying - `16 RR`
- `MOVE` - Move - `17 RR`

### 3 Byte Instructions

- `ADDB` - Add One Half Byte - `20 RI II`
- `SDDB` - Subtract One Half Byte - `21 RI II`
- `CLR` - Call Register - `22 II 0R`
- `RJMPD` - Relative Jump Direct - `34 MM MM`
- `RJMPI` - Relative Jump Indirect - `35 MM MM`

### 4 Byte Instructions

- `CLI` - Call Immediate - `30 MM MM MM`
- `CLM` - Call Memory - `31 MM MM MM`
- `ADDI` - Add Intermediate - `32 0R II II`
- `LDI` - Load Immediate - `33 0R NN NN`
- `AJMPD` - Absolute Jump Direct - `34 MM MM MM`
- `AJMPI` - Absolute Jump Indirect - `35 MM MM MM`

### 5-byte instructions

- `LDMD` - Load Memory Direct  - `40 0R MM MM MM`
- `LDMI` - Load Memory Indirect - `41 0R MM MM MM`
