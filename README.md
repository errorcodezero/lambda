# Lambda

Cool fantasy console that has

- 4 cores where each core has:
    - 13 16-bits General Purpose registers - 0-C
    - 1 Status Register - D: 000ZCSOI
        - Zero Flag
        - Carry Flag
        - Sign Flag
        - Overflow Flag
        - Interrupt Flag
    - 1 Bank Register - E
    - 1 Zero Register - F
    - 24-bit instruction pointer
    - 16-bit stack pointer
    - 16-bit base pointer
- 24-bit data bus
- 256 interrupts
- 16777217 bytes of memory
- 4 mutexes per core
- Little-endian

## Instructions

This is in hexadecimal and for simplicity, I'm avoiding prefixing all values with "0x". The first value modulus 9 indicates how many bytes precede it for a given instruction. The second indicates an enumerator. The repetition of a character that is not hexadecimal(0-F) does not necessarily indicate the same constant.

### 1 Byte Instructions

- [X] `HLT` - Halt - `00`
- `RET` - Return - `01`

### 2 Byte Instructions 

- [X] `INC` - Increment - `10 RI`
- [X] `DEC` - Decrement - `11 RI`
- [X] `TJMP` - Tiny Jump - `12 II`
- [X] `LSHFT` - Bit Shift Left Registers - `13 SR`
- [X] `RSHFT` - Bit Shift Right Registers - `14 SR`
- [X] `ADDR` - Add Registers - `15 RR`**
- [X] `SUBR` - Subtract Registers - `16 RR`**
- [X] `XORR` - Bitwise XOR Registers - `17 RR`**
- [X] `ANDR` - Bitwise AND Registers - `18 RR`**
- [X] `NOTR` - Bitwise NOT Registers - `19 RR`**
- [X] `ORR` - Bitwise OR Registers - `1A RR`**
- [X] `NORR` - Bitwise NOR Registers - `1B RR`**
- [X] `NANDR` - Bitwise NAND Registers - `1C RR`**
- [X] `XNORR` - Bitwise XNOR Registers - `1D RR`**
- `PSHI` - Push Immediate Stack - `1E II`
- `POP` - Pop/Peek Stack - `1F SR` - 0 for stack will pop 8-bit value, 1 for stack will pop 16-bit value, 2 for stack will peep 8-bit value, and 4 for stack will peep 16-bit value.
- `CMP` - Compare Registers - `A0 RR`
- `CJIZ` - Computed Jump If Zero - `A1 SR`*
- `CJIG` - Computed Jump If Greater- `A2 SR`*
- `CJIL` - Computed Jump If Lesser- `A3 SR`*
- `DMUTI` - Disable Mutex Index - `A4 II`

### 3 Byte Instructions

- [X] `ADDB` - Add One Half Byte - `20 RI II`
- [X] `SUBB` - Subtract One Half Byte - `21 RI II`
- `RJMPIZD` - Relative Jump If Zero Direct - `22 MM MM`
- `RJMPIZI` - Relative Jump If Zero Indirect - `23 MM MM`
- `RJMPIGD` - Relative Jump If Greater Direct - `24 MM MM`
- `RJMPIGI` - Relative Jump If Greater Indirect - `25 MM MM`
- `RJMPILD` - Relative Jump If Lesser Direct - `26 MM MM`
- `RJMPILI` - Relative Jump If Lesser Indirect - `27 MM MM`
- [X] `ADDRR` - Add Registers - `2A SR RR`\*\*\*
- [X] `SUBRR` - Subtract Registers - `2B SR RR`\*\*\*
- [X] `XANOR` - Bitwise AND/OR/XOR/NAND/NOR/XNOR Registers - `2C SR RR`** - 0 for `S` will make this bitwise AND, 1 will make this bitwise OR, 2 will make this bitwise XOR, 3 will make this bitwise NAND, 4 will make this bitwise NOR, 5 will make this bitwise XNOR
- `MMUTMOI` - Modify Mutex Mode with Index - `2D II MM`
- `MWR` - Move with Register - `2E SR`*

### 4 Byte Instructions

- [X] `ADDI` - Add Immediate - `30 RR II II`
- [X] `SUBI` - Subtract Immediate - `31 RR II II`
- [X] `LDI` - Load Immediate - `32 0R NN NN`
- `AJMPIZD` - Absolute Jump If Zero Direct - `33 MM MM MM`
- `AJMPIZI` - Absolute Jump If Zero Indirect - `34 MM MM MM`
- `AJMPIGD` - Absolute Jump If Greater Direct - `35 MM MM MM`
- `AJMPIGI` - Absolute Jump If Greater Indirect - `36 MM MM MM`
- `AJMPILD` - Absolute Jump If Lesser Direct - `37 MM MM MM`
- `AJMPILI` - Absolute Jump If Lesser Indirect - `38 MM MM MM`
- [X] `RLD` - Relative Load - `39 SR MM MM`*
- `DMUTAM` - Delete Mutex Absolute Memory - `C0 MM MM MM` - If the given memory address is within range of a mutex, it nullifies that mutex within the mutex table.
- [X] `ADDINC` - Add Immediate No Carry - `C1 RR II II`
- [X] `SUBINC` - Subtract Immediate No Borrow - `C2 RR II II`
- `RLM` - Relative Move - `39 SR MM MM` - 0 for S means one byte, no indirection, 2 means two bytes, no indirection, 3 means 1 byte with indirection, 4 means 2 byte with indirection

### 5-byte Instructions

- [X] `ALD` - Absolute Load - `40 SR MM MM MM`*
- `ALM` - Absolute Move - `41 SR MM MM MM`* - 0 for S means one byte, no indirection, 2 means two bytes, no indirection, 3 means 1 byte with indirection, 4 means 2 byte with indirection

### 6 Byte Instructions

- `MMUTMRI` - Modify Mutex Memory Relative with Index - `50 II MM MM MM MM`\*\*\*\*

### 8 Byte Instructions

- `MMUTMAI` - Modify Mutex Memory Absolute with Index - `70 II MM MM MM MM MM MM`\*\*\*\*

*nonzero value for `S` will make this indirect, carry, or borrow depending on the context

**ordering for expressions is where the result will be stored followed by the operands where in the case of only two values, the first operand is also where the result will be stored

*\*\*both first and second asterisks apply

*\*\*\*Arguments are from the mutex table

## Mutexes

A mutex table is stored within the CPU allowing it to store up to 16 mutexes and 4 per core. Each mutex is stored as such:

| Index | Memory Start | Memory End | Core | Mode |
| ----- | ------------ | ---------- | ---- | -----|
|  II   |   MM MM MM   |  MM MM MM  |  SS  |  RT  |

- `T` toggles the mutex where 0 is disabled and 1 is enabled.
- `R` toggles interrupts where 0 is for triggering spinlocks and 1 is for triggering interrupts.

## Interrupts

These are various interrupts that can be triggered by different actions:
- `00` - Reset
- `01` - Non-Maskable
- `02` - Mutex Permisson Failure
- `03` - Signal
