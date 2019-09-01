// https://github.com/denehyg/reveal.js-menu
menu: {
    side: 'left',
    width: 'normal',
    numbers: true,
    useTextContentForMissingTitles: true,
    hideMissingTitles: false,
    markers: true,
    custom: false,
    themes: false,
    themesPath: 'css/theme/',
    transitions: true,
    openButton: true,
    openSlideNumber: false,
    keyboard: true,
    sticky: false,
    autoOpen: true,
    delayInit: false,
    openOnInit: false,
    loadIcons: false
},

// https://github.com/tkrkt/reveal.js-elapsed-time-bar
allottedTime: 20 * 60 * 1000, // minutes
progressBarHeight: 5,
barColor: 'rgb(66, 175, 250)',

//
// plugins
//
dependencies: [
     { src: 'plugins/custom-fragments.js' }
    ,{ src: 'plugins/header.js' }
    ,{ src: 'plugins/elapsed-time-bar.js' }
    ,{ src: 'plugins/reveal.js-menu/menu.js' }

    , // default plugins past this point; also add new-line
