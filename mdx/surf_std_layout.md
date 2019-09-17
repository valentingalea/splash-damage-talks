import { CodeSurfer } from "mdx-deck-code-surfer"
export { default as theme } from "./theme"
import code_theme from "./theme-surf"

# Code Surfer

NOTE: designed to be embed into reveal.js

---
<CodeSurfer
  title="Section: Layout"
  code={require("!raw-loader!../standards/snip/layout.cpp")}
  lang="cpp"
  theme={code_theme}
  steps={[
    { notes: " " },
  ]}
/>
