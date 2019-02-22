import theme from 'mdx-deck/themes'

export default {
    // extends the default theme
    ...theme,

    // custom colors
    colors: {
         ...theme.colors, // include existing theme colors
        text: 'rgb(212, 212, 212)',
        background: 'rgb(30, 30, 30)'
    },

    // element styles
    h2: {
        fontSize: '1.5em'
    },
    ul: {
        fontSize: '1em'
    },
    li: {
        fontSize: '1em'
    }
}