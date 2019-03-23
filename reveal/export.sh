#! /bin/bash

mkdir ../docs/node_modules/
cp -r node_modules/reveal.js/. ../docs/node_modules/reveal.js/

plugs=../docs/plugins
rjm=reveal.js-menu
mkdir $plugs/$rjm
cp node_modules/$rjm/* $plugs/$rjm