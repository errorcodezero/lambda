# Lambda

Cool fantasy console that has

- 4 cores where each core has:
    - 16 16-bit registers:
        - 13 General Purpose - 0-C
        - 1 Status Register - D
        - 1 Bank Register - E
        - 1 Zero Register - F
    - 24-bit instruction pointer
    - 16-bit stack pointer
    - 16-bit base pointer
    - 24-bit data bus
    - 256 interrupts

## Instructions

This is in hexadecimal and for simplicity, I'm avoiding prefixing all values with "0x". The first value indicates how many bytes precede it for a given instruction. The second indicates an enumerator. The repetition of a character that is not hexadecimal(0-F) does not necessarily indicate the same constant.

### 1 Byte Instructions

- `HLT` - Halt - `00`
- `RET` - Return - `01`

### 2 Byte Instructions 

- `CJMP` - Computed Jump - `10 SR`*
- `CCLL` - Computed Call - `11 SR`*
- `INC` - Increment - `12 RI`
- `DEC` - Decrement - `13 RI`
- `TJMP` - Tiny Jump - `14 II`
- `MOVE` - Move - `15 RR`
- `ADDR` - Add Registers - `16 RR`**
- `SUBR` - Subtract Registers - `17 RR`**
- `XORR` - Bitwise XOR Registers - `18 RR`**
- `ANDR` - Bitwise AND Registers - `19 RR`**
- `NOTR` - Bitwise NOT Registers - `1A RR`**
- `ORR` - Bitwise OR Registers - `1B RR`**

### 3 Byte Instructions

- `ADDB` - Add One Half Byte - `20 RI II`
- `SDDB` - Subtract One Half Byte - `21 RI II`
- `RJMPD` - Relative Jump Direct - `22 MM MM`
- `RJMPI` - Relative Jump Indirect - `23 MM MM`
- `CJMP` - Computed Jump - `24 SR MM`*
- `CCLL` - Computed Call - `25 SR MM`*
- `ADDR` - Add Registers - `26 SR RR`**\*
- `SUBR` - Subtract Registers - `27 SR RR`**\*

### 4 Byte Instructions

- `ADDI` - Add Intermediate - `30 RR II II`
- `SUBI` - Subtract Intermediate - `31 RR II II`
- `LDI` - Load Immediate - `32 0R NN NN`
- `AJMPD` - Absolute Jump Direct - `33 MM MM MM`
- `AJMPI` - Absolute Jump Indirect - `34 MM MM MM`
- `LDMD` - Relative Load - `35 SR MM MM`*

### 5-byte instructions

- `LDMD` - Absolute Load - `40 SR MM MM MM`*

*nonzero value for `S` will make this indirect, carry, or borrow depending on the context
**ordering for expressions is where the result will be stored followed by the operands where in the case of only two values, the first operand is also where the result will be stored
***both the top and bottom asterisks apply
