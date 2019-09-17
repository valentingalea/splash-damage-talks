// @flow
// Original: https://github.com/dracula/visual-studio-code
// Converted automatically using ./tools/themeFromVsCode

/*:: import type { PrismTheme } from '../src/types' */

var theme /*: PrismTheme */ = {
  plain: {
    color: "rgb(248, 248, 242)",
    backgroundColor: "#282A36"
  },
  styles: [
    {
      types: ["prolog", "constant", "builtin"],
      style: {
        color: "rgb(189, 147, 249)"
      }
    },
    {
      types: ["function"],
      style: {
        color: "rgb(250, 208, 0)"
      }
    },
    {
      types: ["punctuation", "symbol"],
      style: {
        color: "rgb(248, 248, 242)"
      }
    },
    {
      types: ["string", "char", "tag", "selector"],
      style: {
        color: "rgb(158, 254, 255)"
      }
    },
    {
      types: ["keyword", "variable"],
      style: {
        color: "rgb(255, 157, 0)"
      }
    },
    {
      types: ["comment"],
      style: {
        color: "rgb(80, 250, 123)"
      }
    },
    {
      types: ["constant"],
      style: {
        color: "rgb(158, 254, 255)"
      }
    }
  ]
};

module.exports = theme;
