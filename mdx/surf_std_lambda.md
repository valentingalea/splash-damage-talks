import { CodeSurfer } from "mdx-deck-code-surfer"
export { default as theme } from "./theme"
import code_theme from "prism-react-renderer/themes/vsDark"

# Code Surfer

NOTE: designed to be embed into reveal.js

---
<CodeSurfer
  title="Section: lambda"
  code={require("!raw-loader!../standards/snip/lambda.cpp")}
  lang="cpp"
  theme={code_theme}
  steps={[
    { notes: " " },
    { range: [ 3,  8], notes: "" },
    { range: [17, 22] },
    { range: [24, 28] },
    { range: [34, 43] }
  ]}
/>