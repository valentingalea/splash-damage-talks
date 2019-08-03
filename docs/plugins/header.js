var Header = (function() {
    var div = create('div', {class: 'header'});
    var logo = create('img', { src: 'img/SD/SD-logo-white.svg'} );
    var text = create('span', {}, '@valentin_galea' );
    div.appendChild(text);
    div.appendChild(logo);
    select('.reveal').appendChild(div);

    Reveal.addEventListener('slidechanged', function(event) {
        if (event.currentSlide.id == 'the_end' ) {
            div.style.visibility = 'hidden';
        } else {
            div.style.visibility = 'visible';
        }
    });
})();

function create(tagName, attrs, content) {
    var el = document.createElement(tagName);
    if (attrs) {
        Object.getOwnPropertyNames(attrs).forEach(function(n) {
            el.setAttribute(n, attrs[n]);
        });
    }
    if (content) {
        el.innerHTML = content;
    }
    return el;
}

function select(selector, el) {
    if (!el) {
        el = document;
    }
    return el.querySelector(selector);
}