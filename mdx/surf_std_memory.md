import { CodeSurfer } from "mdx-deck-code-surfer"
export { default as theme } from "./theme"
import code_theme from "prism-react-renderer/themes/vsDark"

# Code Surfer

NOTE: designed to be embed into reveal.js

---
<CodeSurfer
  title="Section: Memory"
  code={require("!raw-loader!../standards/snip/memory.cpp")}
  lang="cpp"
  theme={code_theme}
  steps={[
    { notes: "" },
    { range: [8, 11], notes: "UE4 template allocators advice" },
    { range: [18, 21], notes: "custom containers best practices" },
    { range: [25, 29], notes: "" },
    { range: [31, 35], notes: "" },
    { range: [37, 43], notes: "" },
  ]}
/>
