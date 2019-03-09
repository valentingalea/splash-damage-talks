import theme from 'mdx-deck/themes'

const global_heading_size = '48px'
const global_font_size = '44px'

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
        fontSize: global_heading_size
    },
    ul: {
        fontSize: global_font_size
    },
    li: {
        fontSize: global_font_size
    },
    p: {
        fontSize: global_font_size,
        margin: '0'
    },
    a: {
        textDecoration: 'none'
    },
    code: {
        color: 'grey'
    }
}