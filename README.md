# puterforge

a ai coding app powered by puter :3

## current status

this repository contains the native windows foundation and the first ai architecture layers for puterforge.

- native c++ windows executable
- reusable native window surface
- cmake release build
- node.js runtime scaffold for puter.js
- dynamic puter model catalog
- ai client abstraction
- dynamic subagent groups
- extensible tool registry
- initial orchestrator
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

## architecture

```text
native c++
   ├── window
   ├── application state
   └── platform services
          │
          ▼
     javascript runtime
          │
          ├── puter.js
          ├── ai client
          ├── model catalog
          ├── agents
          ├── tools
          └── orchestrator
```

## next milestones

1. native editor surface
2. project/file explorer
3. terminal service
4. model picker with search/categories/providers
5. c++ ↔ javascript bridge
6. real subagent execution loop
7. tests and packaged releases
