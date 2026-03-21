# Lambda

Fantasy console that's:

- 16-bit
- 24-bit data bus

## Instructions

- `HLT` - Halt - `0x0000` - Halts console
- `CALL`- Call - `0x01MMMMMM` - Push instruction pointer to top of stack and set instruction pointer to `0xMMMMMM`. Sets base pointer to top of stack.
- `RET` - Return - `0x0001` - Pops stack down to the base pointer to where it will set final value as instruction pointer.
- `LDI` - Load Immediate - `0x2RNNNN` - Load data `0xNNNN` into register `0xR`.
- `RRJMP` - Relative Right Jump - `0x30II` - Relative jump which increments the instruction pointer by `0xII`.
- `RLJMP` - Relative Left Jump - `0x31II` - Relative jump which decrements the instruction pointer by `0xII`.
- `AJMP` - Absolute Jump - `0x32MMMMMM` - Essentially just `CALL` except it doesn't touch the stack.
- `LDM` - Load Memory - `0x33MMMMMM` - Load data from `0xMMMMMM`
