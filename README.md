# Malicious File Extension Checker

A small C++ command-line tool that flags files whose extension is on a blocklist of commonly abused types (`exe`, `scr`, `bat`, `vbs`, ...). The blocklist lives in a plain text file, so it can be changed without recompiling.

This is a first-pass filter of the kind used in mail gateways and upload forms. It looks only at the file name, so it does not replace content inspection: a renamed executable will pass.

## Build

```bash
g++ -std=c++11 -o extension_checker main.cpp
```

or with CMake:

```bash
cmake -B build && cmake --build build
```

## Usage

```bash
./extension_checker [extensions_file] [file ...]
```

- `extensions_file`: blocklist to load, one extension per line. Defaults to `malicious_extensions.txt` in the current directory.
- `file ...`: file names to check. With none given, a built-in set of examples is checked.

```
$ ./extension_checker
file1.exe has a malicious file extension!
document.txt is safe.
script.js has a malicious file extension!
image.jpeg is safe.
archive.rar is safe.
virus.scr has a malicious file extension!

$ ./extension_checker malicious_extensions.txt report.PDF setup.MSI
report.PDF is safe.
setup.MSI has a malicious file extension!
```

## How it works

1. `loadMaliciousExtensions` reads the blocklist, trims whitespace, lowercases each entry, and stores it in an `std::unordered_set` for constant-time lookup.
2. `getFileExtension` takes everything after the last dot in the file name. A name with no dot has no extension and is treated as safe.
3. `isMaliciousExtension` lowercases the extension and looks it up, so matching is case-insensitive.

## The blocklist

`malicious_extensions.txt` ships with: `exe`, `bat`, `cmd`, `scr`, `js`, `vbs`, `com`, `msi`, `dll`, `pif`. Add or remove lines to fit your policy.

## Limitations and ideas

- Checks names only. Adding magic-byte detection would catch renamed files.
- Double extensions such as `invoice.pdf.exe` are caught, since only the last extension counts, but `payload.exe.txt` is not.
- Could scan a directory recursively instead of taking names as arguments.
