export class ToolRegistry {
  #tools = new Map();

  register(name, handler, description = "") {
    if (!name || typeof handler !== "function") {
      throw new TypeError("tool name and handler are required");
    }
    this.#tools.set(name, { name, description, handler });
    return this;
  }

  has(name) {
    return this.#tools.has(name);
  }

  async run(name, input = {}) {
    const tool = this.#tools.get(name);
    if (!tool) throw new Error(`unknown tool: ${name}`);
    return tool.handler(input);
  }

  definitions() {
    return [...this.#tools.values()].map(({ name, description }) => ({
      name,
      description,
    }));
  }
}
