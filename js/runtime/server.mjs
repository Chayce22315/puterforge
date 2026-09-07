import readline from "node:readline";
import { init } from "@heyputer/puter.js/src/init.cjs";

const authToken = process.env.puterAuthToken;

if (!authToken) {
  console.error("puterAuthToken is not set");
  process.exit(1);
}

const puter = init(authToken);
const input = readline.createInterface({
  input: process.stdin,
  crlfDelay: Infinity,
});

const send = (payload) => {
  process.stdout.write(`${JSON.stringify(payload)}\n`);
};

const handle = async (request) => {
  switch (request.type) {
    case "ping":
      send({ type: "pong" });
      return;

    case "list-models":
      send({
        type: "models",
        models: await puter.ai.listModels(),
      });
      return;

    case "chat":
      send({
        type: "chat-result",
        response: await puter.ai.chat(request.prompt, {
          model: request.model,
        }),
      });
      return;

    default:
      send({
        type: "error",
        error: `unknown request type: ${request.type}`,
      });
  }
};

input.on("line", async (line) => {
  if (!line.trim()) return;

  try {
    await handle(JSON.parse(line));
  } catch (error) {
    send({
      type: "error",
      error: error instanceof Error ? error.message : String(error),
    });
  }
});
