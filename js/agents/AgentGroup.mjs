export class AgentGroup {
  constructor(name = "default") {
    this.name = name;
    this.models = [];
  }

  add(model) {
    if (!model || this.models.includes(model)) return;
    this.models.push(model);
  }

  remove(model) {
    this.models = this.models.filter((item) => item !== model);
  }

  clear() {
    this.models = [];
  }

  toJSON() {
    return {
      name: this.name,
      models: [...this.models],
    };
  }
}
