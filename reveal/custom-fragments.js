var CustomFragments = (function() {
    Reveal.addEventListener('fragmentshown', function(event) {
	    // event.fragment = the fragment DOM element
        dealWithFragments(event.fragment);
    });
    Reveal.addEventListener('fragmenthidden', function(event) {
        dealWithFragments(event.fragment);
    });
})();

function dealWithFragments (fragment) {
    var iframe = document.querySelector("div.slide-background.present > iframe:nth-child(1)");
    if (!iframe) return;

    // add 1 because we skip the start aka overview
    const id = Number(fragment.getAttribute ('data-fragment-index')) + 1;

    // format of iframe url is: index.html#X.Y
    const href = iframe.contentWindow.location.href;
    const h = href.indexOf('#')
    const new_href = href.substr(0, h + 2) + '.' + id;
    
    iframe.contentWindow.location.href = new_href;
    //console.log(new_href);
    
    //top.postMessage('from-revealjs', '*');
};