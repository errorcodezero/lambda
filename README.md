# Lambda

Fantasy console that's:

- 16-bit
- 24-bit data bus

## Instructions

This is in hexadecimal and for simplicity, I'm avoiding prefixing all values with "0x". The first value indicates how many bytes precede it for a given instruction. The second indicates an enumerator. The repetition of a character that is not hexadecimal(0-F) does not necessarily indicate the same constant.

- `HLT` - Halt - `00` - Halts console
- `RET` - Return - `01` - Pops stack down to the base pointer to where it will set final value as instruction pointer.
- `CALL`- Call - `30 MM MM MM` - Push instruction pointer to top of stack and set instruction pointer to `MMMMMM`. Sets base pointer to top of stack.
- `LDI` - Load Immediate - `31 0R NN NN` - Load data `NNNN` into register `R`.
- `RJMP` - Relative Jump - `10 II` - Relative jump using the two's compliment of `II`
- `AJMP` - Absolute Jump - `32 MM MM MM` - Essentially just `CALL` except it doesn't touch the stack.
- `LDM` - Load Memory - `40 0R MM MM MM` - Load data from `MMMMMM`
- `ADDI` - Add Intermediate - `34 0R II II` - Add `IIII` to register `R`
- `ADDRC` - Add Registers with Carrying - `20 RR` - Add register `R` with carrying to register `R`
- `ADDR` - Add Registers - `21 RR` - Add register `R` without carrying to register `R`
