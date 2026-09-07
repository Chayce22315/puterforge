export class ModelCatalog {
  constructor(puter) {
    this.puter = puter;
    this.models = [];
    this.providers = [];
  }

  async refresh() {
    this.models = await this.puter.ai.listModels();
    this.providers = await this.puter.ai.listModelProviders();
    return this.snapshot();
  }

  snapshot() {
    return {
      models: this.models,
      providers: this.providers,
      count: this.models.length,
    };
  }

  byProvider(provider) {
    return this.models.filter((model) => model.provider === provider);
  }

  search(query) {
    const value = query.trim().toLowerCase();
    if (!value) return this.models;

    return this.models.filter((model) =>
      [model.id, model.name, model.provider, ...(model.aliases ?? [])]
        .filter(Boolean)
        .some((field) => String(field).toLowerCase().includes(value)),
    );
  }
}
