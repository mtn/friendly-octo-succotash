# kalicharan-adv-c-notes
My personal notes from reading books including
    * Kalicharan's [Advanced Topics in C](http://www.apress.com/us/book/9781430264002)
    * CLRS [Introduction to Algorithms](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/026203384)
    * Weiss [Data Structures and Algorithms in C++](https://www.amazon.com/Data-Structures-Algorithm-Analysis-C/dp/013284737X)

I've come up with some chapter structure that is pretty close to Kalicharan by virtue of reading that first, but that will definitely evolve over time.

Rendered with [asciidoctor-pdf](https://github.com/asciidoctor/asciidoctor-pdf). Asciidoctor-pdf is currently in alpha, but can be obtained easily via `gem install`:

    gem install asciidoctor-pdf -pre

Previously depended on asciimath, which unfortunately isn't yet supported (so some math might not render any more, which I'll fix later).

Files are grouped by chapter, with each chapter having a `*.adoc` file which can be modified to make changes. To rerender `index.pdf`:

    asciidoctor-pdf index.adoc
