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
    { range: [51, 60], notes: "some more examples: virtual declarations" },
    { range: [145, 154], notes: "...readability and naming"},
    { range: [161, 168], notes: "...disapprove of Singleton" },
    { range: [181, 185], notes: "...etc" },
    { range: [178, 196], notes: "archictural zoom level 1"},
    { range: [167, 198], notes: "archictural zoom level 2"},
    { range: [159, 200], notes: "archictural zoom level 3"},
    { range: [139, 204], notes: "archictural zoom level - full class"},
  ]}
/>
