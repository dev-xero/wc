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

wc expects an optional `flag` and `filepath` argument.

```bash
./build/wc [-FLAG] [FILEPATH]
```

Example

```bash
./build/wc test.txt

7145 58164 342190 test.txt
```

## Flags

### 1. `-c`: Prints the byte count.

  Example:

  ```bash
  ./build/wc -c test.txt

  342190 test.txt
  ```

### 2. `-l`: Prints the line count.

  Example:

  ```bash
  ./build/wc -l test.txt

  7145 test.txt
  ```
  
### 3. `-w`: Prints the word count.

  Example:

  ```bash
  ./build/wc -w test.txt

  58164 test.txt
  ```

### 4. `-m`: Prints the UTF-8 character count.

  Example:

  ```bash
  ./build/wc -m test.txt

   339292 test.txt
  ```