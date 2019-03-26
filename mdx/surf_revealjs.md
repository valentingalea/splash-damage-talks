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

---
<CodeSurfer
  title="BuildGraph (example)"
  code={require("!raw-loader!../flow/buildgraph.xml")}
  theme={code_theme}
  lang="xml"
  steps={[
    { notes: "" },
    { range: [ 4, 11] },
    { range: [13, 14] },
    { range: [18, 23] },
    { lines: [ 34 ] },
    { range: [53, 59] },
    { range: [73, 79] },
    { range: [132, 141] }
  ]}
/>

---
export const flowA = 9

<CodeSurfer
  title="Normal Commit Flow"
  code={require("!raw-loader!../flow/submit.txt")}
  theme={code_theme}
  lang="yaml"
  steps={[
    { notes: "" },
    { range: [flowA +  1, flowA +  5] },
    { range: [flowA + 10, flowA + 15] },
    { range: [flowA + 23, flowA + 28] },
    { range: [flowA + 36, flowA + 41] }
  ]}
/>

---
export const flowB = 9

<CodeSurfer
  title="Pre-Commit Flow"
  code={require("!raw-loader!../flow/pre-submit.txt")}
  theme={code_theme}
  lang="yaml"
  steps={[
    { notes: "" },
    { range: [flowB +  1, flowB +  5] },
    { range: [flowB + 10, flowB + 15] },
    { range: [flowB + 23, flowB + 28] },
    { range: [flowB + 36, flowB + 41] },
    { lines: [flowB + 43, flowB + 47] },
    { range: [flowB + 50, flowB + 53] },
    { range: [flowB + 62, flowB + 66] },
  ]}
/>

---
<CodeSurfer
  title="Unit Test Example"
  code={require("!raw-loader!../flow/testing.cpp")}
  theme={code_theme}
  lang="cpp"
  steps={[
    { notes: "" },
    { range: [ 8, 10], notes: "syntactic sugar macros" },
    { range: [52, 53], notes: "test names must follow specific naming" },
    { range: [54, 58], notes: "Given..." },
    { range: [65, 67], notes: "...When..." },
    { range: [69, 72], notes: "...Then" }
  ]}
/>

---
<CodeSurfer
  title="Game Module Layout Example"
  code={require("!raw-loader!../flow/modules.txt")}
  theme={code_theme}
  lang="yaml"
  steps={[
    { notes: "" },
    { range: [ 3, 16], notes: "Game-logic module" },
    { range: [19, 29], notes: "Testing module" },
    { range: [32, 34], notes: "Editor-only module" },
    { range: [37, 39], notes: "Interface-only module" },
    { range: [ 3, 16], notes: "Game-logic module" },
    { lines: [ 4 ], notes: "UnrealBuildTool spec file" },
    { range: [ 6, 10], notes: "Implementation (*.cpp)" },
    { range: [12, 16], notes: "Interface (*.h)" }
  ]}
/>

---
export const arch_A = 5
export const arch_B = 34
export const arch_C = 64

<CodeSurfer
  title="Architecture"
  code={require("!raw-loader!../flow/splash-engine.txt")}
  theme={code_theme}
  lang="yaml"
  steps={[
    { notes: "" },
    { lines: [ arch_A+0 ], notes: "master Perforce depot" },
    { lines: [ arch_A+2 ], notes: "engine 'vanilla' drops from Epic" },
    { lines: [ arch_A+5 ], notes: "Splash Engine" },
    { range: [ arch_A+8, arch_A+11], notes: "company games/projects" },
    { range: [ arch_B+2, arch_B+6 ], notes: "individual downloaded versions" },
    { range: [ arch_C+1, arch_C+7], notes: "Splash Engine layout" },
    {   lines: [ arch_C+3 ], notes: "'vanilla' version for merge diff" },
    {   lines: [ arch_C+4 ], notes: "master branch" },
    { range: [ arch_C+5, arch_C+8 ], notes: "individual project staging" }
  ]}
/>
