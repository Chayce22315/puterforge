export class AiClient {
  constructor(puter) {
    this.puter = puter;
  }

  async chat({ prompt, model, ...options }) {
    if (!prompt || typeof prompt !== "string") {
      throw new TypeError("prompt must be a non-empty string");
    }

    return this.puter.ai.chat(prompt, {
      ...(model ? { model } : {}),
      ...options,
    });
  }

  async listModels() {
    return this.puter.ai.listModels();
  }

  async listProviders() {
    return this.puter.ai.listModelProviders();
  }
}
