# filepacker-cpp

A simple file packing tool written in C++ that serializes source files into JSON and creates files from the JSON.

Built with [nlohmann/json](https://github.com/nlohmann/json).

---

## What it does

- Reads one or more files you provide
- Packs them into a single JSON file containing the filename, type, and content of each file
- Can restore the original files back from the JSON

---

## Build

```bash
cmake -B build
cmake --build build
```

---

## Usage

Input

```bash
./build/rw-json I output file1.cpp file2.h file3.cpp
```

**Arguments:**
1. The executable
2. Mode
3. Name for the output JSON file. Don't include ".json" in the name for the output file. Code handles that automatically.
4. One or more filenames to pack 
---

Output

```bash
./build/rw-json O output
```

**Arguments:**
1. The executable
2. Mode
3. Name for the input JSON file. Don't include ".json" in the name for the output file. Code handles that automatically.


---

## Created JSON format

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

## Created files from JSON
Files from JSON are directed to an `output/` folder in your current directory.
```
output/
├── main.cpp
└── utils.h
```

---

## Dependencies

- C++17 or later
- CMake 3.14 or later
- [nlohmann/json](https://github.com/nlohmann/json) (downloaded automatically by CMake)
