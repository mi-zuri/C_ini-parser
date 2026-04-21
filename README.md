# C_ini-parser

A small INI file parser written in C11 with a dot-notation CLI lookup. University assignment (CA-LLP).

## Format supported

- `[section]` headers — alphanumeric + hyphens
- `key=value` pairs — alphanumeric + hyphens for keys, arbitrary values
- `;` and `#` line comments
- Whitespace stripped around keys, values, and names

See `example-3.0.ini` and `example-4.5.ini` for full examples.

## Usage

```bash
./main <file> <section.parameter>
```

Example:

```bash
./main config.ini database.host
```

Prints the value of `host` under `[database]`, or exits with an error.

## Error codes

| Code | Meaning |
|---|---|
| `NO_FILE_ERROR` | file not found / unreadable |
| `EMPTY_SECTION_ERROR` | `[]` with no name |
| `INVALID_NAME_ERROR` | non-alphanumeric section or key |
| `NO_SECTION_ERROR` | key outside of any section |
| `MALLOC_ERROR` | allocation failed |
| `ARGUMENTS_ERROR` | wrong CLI usage |

## Implementation

- Sections stored in a linked list (unbounded count)
- Parameters in dynamic arrays, grown in chunks of 8
- Line buffer fixed at 256 bytes
- Explicit copy semantics — slower but keeps the list implementation simple and safe

## Build

```bash
cmake -S . -B build
cmake --build build
./build/main example-3.0.ini slippery-balance.humiliating-bone
```

Or directly:

```bash
clang -std=c11 -Wall -Wextra main.c errors.c list.c parser.c search.c section.c -o main
```
