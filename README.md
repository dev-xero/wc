# WC

wc is a Unix utility tool that prints the number of lines, words or bytes in a text file. This is a relatively straight forward implementation of the tool in pure C.

## Compiling

You can compile the source file using `gcc` (GCC needs to be installed).

```bash
mkdir -p ./build
gcc -o ./build/wc ./wc.c
```

Alternatively, you can batch execute the commands if you have `make` installed.

```bash
make build
```

## Usage

wc expects a `flag` and `filepath` argument.

```bash
./build/wc [-FLAG] [FILEPATH]
```

### Flags

### 1. `-c`: Returns the number of bytes in the specified file.

  Example:

  ```bash
  ./build/wc -c test.txt
  ```

  Produces:

  ```bash
    342190 test.txt
  ```
