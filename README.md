# Lambda

Fantasy console that's:

- 16-bit
- 24-bit data bus

## Instructions

- `HLT` - `0x0000` - Halts console
- `CALL` - `0x01MMMMMM` - Push instruction pointer to top of stack and set instruction pointer to `0xMMMMMM`. Sets base pointer to top of stack.
- `RET` - `0x0001` - Pops stack down to the base pointer to where it will set final value as instruction pointer.
- `LOAD` - `0x2RDDDD` - Load data `0xDDDD` into register `0xR`.
