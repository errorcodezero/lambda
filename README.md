# Lambda

Fantasy console that's:

- 16-bit
- 24-bit data bus

## Instructions

This is in hexadecimal and for simplicity, I'm avoiding prefixing all values with "0x". The first value indicates how many bytes precede it for a given instruction. The second indicates an enumerator. The repetition of a character that is not hexadecimal(0-F) does not necessarily indicate the same constant.

### 1 Byte Instructions

- `HLT` - Halt - `00` - Halts console
- `RET` - Return - `01` - Pops stack down to the base pointer to where it will set final value as instruction pointer.

### 2 Byte Instructions 

- `INC` - Increment - `10 RS` - Increments register `R` by `S`
- `DEC` - Decrement - `11 RS` - Decrements register `R` by unsigned value of `S`
- `CLR` - Call Register - `12 0R` - Push instruction pointer to top of stack and set instruction pointer to `MMMMMM`. Sets base pointer to top of stack.
- `CLB` - Call Byte - `13 SS` - Call memory address at 
- `RJMP` - Relative Jump - `14 II` - Relative jump using the two's compliment of `II`

### 3 Byte Instructions

- `ADDB` - Add One Half Byte - `20 RI II` - Add `III` to register `R` and store data in accumulator. Enables carry flag if an overflow occurs.
- `ADDR` - Add Registers - `20 RR` - Add register `R` without carrying to register `R` and store data in accumulator. Enable carry flag if an overflow occurs.
- `ADDRC` - Add Registers with Carrying - `21 RR` - Add register `R` to register `R` as well as the carry flag and stores result in accumulator

### 4 Byte Instructions

- `CLI` - Call Immediate - `30 MM MM MM` - Push instruction pointer to top of stack and set instruction pointer to `MMMMMM`. Sets base pointer to top of stack.
- `CLM` - Call Memory - `31 MM MM MM` - Push instruction pointer to top of stack and set instruction pointer to memory address stored at `MMMMMM` and the next two preceding memory slots. Sets base pointer to top of stack.
- `ADDI` - Add Intermediate - `32 0R II II` - Add `IIII` to register `R` and store data in accumulator. Enables carry flag if an overflow occurs.
- `CLM` - Call Memory - `33 MM MM MM` - Push instruction pointer to top of stack and set instruction pointer to memory address stored at `MMMMMM` and the next two preceding memory slots. Sets base pointer to top of stack.
- `LDI` - Load Immediate - `34 0R NN NN` - Load data `NNNN` into register `R`.
- `AJMP` - Absolute Jump - `35 MM MM MM` - Essentially just `CALL` except it doesn't touch the stack.

### 5-byte instructions

- `LDM` - Load Memory - `40 0R MM MM MM` - Load data from `MMMMMM`
