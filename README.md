# Hyperapp Reason Bindings (WIP)

Very raw bindings for the
[Hyperapp](https://github.com/hyperapp/hyperapp) UI library.

# Build

You'll need these installed:

- bs-platform
- rollup

Full BuckleScript build:

    npm run build:bs

Incremental and watch for changes (but you probably don't need this if
you've set your editor to compile on save):

    npm run watch:bs

Bundle:

    npm run build:js

Bundle and watch for changes:

    npm run watch:js

Production bundle: for now, manually edit the `rollup.config.js` and
uncomment the `uglify()` line, then make a bundle as above.

# Run

Open `index.html`.
