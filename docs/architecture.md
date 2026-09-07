# architecture

## native layer

c++ owns the windows process, native ui surface, application state, and platform services.

## javascript layer

javascript owns ai orchestration and higher-level application logic.

### ai

- `ai/AiClient.mjs` wraps puter ai calls
- `ai/ModelCatalog.mjs` discovers models and providers dynamically

### agents

- `agents/AgentGroup.mjs` stores user-selected model groups
- `orchestrator/Orchestrator.mjs` coordinates an agent task

### tools

`tools/ToolRegistry.mjs` provides the extension point for filesystem, terminal, project, and test tools.

## ci

github actions validates the javascript runtime, runs foundation tests, builds the native windows x64 executable with cmake, and uploads `puterforge.exe` as an artifact.
