# puterforge

a ai app powered by puter :3

## current status

this repository contains the first native windows bootstrap for puterforge.

- native c++ windows executable
- cmake build
- node.js runtime scaffold for puter.js
- github actions build for a windows x64 `.exe`

## local build

```powershell
cmake -S native -B build -A x64
cmake --build build --config Release
```

output:

```text
build/Release/puterforge.exe
```
