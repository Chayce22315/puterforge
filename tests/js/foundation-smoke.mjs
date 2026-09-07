import assert from "node:assert/strict";
import { ToolRegistry } from "../../js/tools/ToolRegistry.mjs";

const registry = new ToolRegistry();
registry.register("ping", () => "pong");
assert.equal(await registry.run("ping"), "pong");
console.log("foundation smoke passed");
