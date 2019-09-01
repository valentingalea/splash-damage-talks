import { CodeSurfer } from "mdx-deck-code-surfer"
export { default as theme } from "./theme"
import code_theme from "prism-react-renderer/themes/vsDark"

# Code Surfer

NOTE: designed to be embed into reveal.js

---
<CodeSurfer
  title="The standard"
  code={require("!raw-loader!../standards/snip/overview.h")}
  lang="cpp"
  showNumbers={false}
  theme={code_theme}
  steps={[
    { notes: "" },
    { lines:  [4], notes: "notice the chapter tagging system" },
    { lines: [11], notes: "inspired by the C++ ISO standard itself" },
    { lines: [14], notes: "handy in searches, code reviews..." },
    { lines: [22], notes: "...etc" }
  ]}
/>
