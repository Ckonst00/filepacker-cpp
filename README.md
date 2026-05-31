# filepacker-cpp

A simple file packing tool written in C++ that serializes source files into JSON and (restores them back - NOT YET).

Built with [nlohmann/json](https://github.com/nlohmann/json).

---

## What it does

- Reads one or more files you provide
- Packs them into a single JSON file containing the filename, type, and content of each file
- Can restore the original files back from the JSON - NOT YET

---

## Build

```bash
cmake -B build
cmake --build build
```

---

## Usage

```bash
./build/rw-json I output.json file1.cpp file2.h file3.cpp
```

**Arguments:**
1. Mode
2. The executable
3. Name for the output JSON file
4. One or more filenames to pack

---

## Output format

```json
[
    {
        "filename": "main.cpp",
        "type": "cpp",
        "content": "..."
    },
    {
        "filename": "utils.h",
        "type": "h",
        "content": "..."
    }
]
```

---

## Dependencies

- C++17 or later
- CMake 3.14 or later
- [nlohmann/json](https://github.com/nlohmann/json) (downloaded automatically by CMake)
