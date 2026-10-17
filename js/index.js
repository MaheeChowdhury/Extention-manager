import fs from "fs/promises";
import fsn from "fs";
import path from "path";

const basePath = "C:\\Users\\Administrator\\Desktop\\Small node.js Project";

const entries = await fs.readdir(basePath, { withFileTypes: true });

for (const entry of entries) {
  if (entry.isDirectory()) continue;

  const ext = path.extname(entry.name).slice(1).toLowerCase();
  if (!ext) continue;

  const targetDir = path.join(basePath, ext);
  await fs.mkdir(targetDir, { recursive: true });

  const sourcePath = path.join(basePath, entry.name);
  const destinationPath = path.join(targetDir, entry.name);

  if (sourcePath === destinationPath) continue;
  if (fsn.existsSync(destinationPath)) continue;

  await fs.rename(sourcePath, destinationPath);
}

console.log("Files organized successfully.");