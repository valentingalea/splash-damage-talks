import { CodeSurfer } from "mdx-deck-code-surfer"
export { default as theme } from "./theme"
import code_theme from "prism-react-renderer/themes/vsDark"

# Code Surfer

NOTE: designed to be embed into reveal.js

---
<CodeSurfer
  title="Section: auto"
  code={require("!raw-loader!../standards/snip/auto.cpp")}
  lang="cpp"
  theme={code_theme}
  steps={[
    { notes: " " },
    { range: [ 6, 12], notes: "" },
    { range: [17, 19] },
    { range: [21, 27] },
    { range: [29, 40] },
    { range: [46, 53] }
  ]}
/>
