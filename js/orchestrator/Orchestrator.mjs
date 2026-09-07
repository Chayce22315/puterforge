export class Orchestrator {
  constructor({ ai, tools, emit = () => {} }) {
    this.ai = ai;
    this.tools = tools;
    this.emit = emit;
  }

  async run({ model, prompt, context = "" }) {
    this.emit({ type: "agent.started", model, prompt });

    const response = await this.ai.chat({
      model,
      prompt: [
        "you are an agent inside puterforge.",
        "use the available project context to reason about the task.",
        context ? `project context:\n${context}` : "",
        `task:\n${prompt}`,
      ].filter(Boolean).join("\n\n"),
    });

    this.emit({ type: "agent.completed", model });
    return response;
  }
}
