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
    { range: [25, 29], notes: "...and real example code" },
    { range: [31, 37], notes: "domain specific guidelines" },
    { range: [47, 49], notes: "C++ guidelines"},
    { lines:  [4], notes: "notice the chapter tagging system" },
    { lines: [11], notes: "inspired by the C++ ISO standard itself" },
    { lines: [14], notes: "handy in searches, code reviews, etc" },
    { range: [51, 60], notes: "some more examples: virtual declarations" },
    { range: [145, 154], notes: "...readability and naming"},
    { range: [161, 168], notes: "...disapprove of Singleton" },
    { range: [181, 185], notes: "...etc" }
  ]}
/>
