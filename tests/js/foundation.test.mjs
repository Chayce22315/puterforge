import assert from "node:assert/strict";
import { ModelCatalog } from "../../js/ai/ModelCatalog.mjs";
import { ToolRegistry } from "../../js/tools/ToolRegistry.mjs";
import { AgentGroup } from "../../js/agents/AgentGroup.mjs";

const fakePuter = {
  ai: {
    async listModels() {
      return [
        { id: "demo/a", name: "demo a", provider: "demo", aliases: ["a"] },
        { id: "other/b", name: "other b", provider: "other", aliases: [] },
      ];
    },
    async listModelProviders() {
      return ["demo", "other"];
    },
  },
};

const catalog = new ModelCatalog(fakePuter);
await catalog.refresh();
assert.equal(catalog.snapshot().count, 2);
assert.equal(catalog.byProvider("demo").length, 1);
assert.equal(catalog.search("other").length, 1);

const group = new AgentGroup("test");
group.add("demo/a");
group.add("demo/a");
assert.deepEqual(group.toJSON().models, ["demo/a"]);

group.remove("demo/a");
assert.equal(group.models.length, 0);

const tools = new ToolRegistry();
tools.register("echo", ({ value }) => value);
assert.equal(await tools.run("echo", { value: "ok" }), "ok");

console.log("foundation tests passed");
