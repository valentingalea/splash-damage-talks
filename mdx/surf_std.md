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
    { notes: "the header file" },
    { range: [ 1, 15], notes: "mix of large commented areas..." },
    { range: [21, 28], notes: "...and real example code" },
    { range: [30, 35], notes: "UE4 guidelines" },
    { range: [46, 48], notes: "C++ guidelines"},
    { lines:  [4], notes: "notice the chapter tagging system" },
    { lines: [11], notes: "inspired by the C++ ISO standard itself" },
    { lines: [14], notes: "handy in searches, code reviews, etc" },
    { range: [50, 60], notes: "some more examples: virtual declarations" },
    { range: [82, 90], notes: "UE4 UObjects..."},
    { range: [92, 98], notes: "replication funcs and vars..." },
    { range: [150, 156], notes: "etc" }
  ]}
/>
