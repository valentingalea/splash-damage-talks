import { CodeSurfer } from "mdx-deck-code-surfer"
export { default as theme } from "./theme"
import code_theme from "prism-react-renderer/themes/vsDark"

# Code Surfer

NOTE: designed to be embed into reveal.js

---
<CodeSurfer
  title="Section: Braces"
  code={require("!raw-loader!../standards/snip/braces.cpp")}
  lang="cpp"
  theme={code_theme}
  steps={[
    { notes: " " },
    { range: [ 8, 24], notes: "" },
    { range: [34, 47] }
  ]}
/>
