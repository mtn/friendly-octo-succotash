# notes
My personal notes from reading books (eventually) including:
* Kalicharan's [Advanced Topics in C](http://www.apress.com/us/book/9781430264002)
* CLRS [Introduction to Algorithms](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/026203384)
* Weiss [Data Structures and Algorithms in C++](https://www.amazon.com/Data-Structures-Algorithm-Analysis-C/dp/013284737X)

I've also included some by-topic notes I created for each of the main topics covered in [CS-162 Winter 2017](http://people.cs.uchicago.edu/~ftchong/CS162/). Sources for these notes that aren't included among the books are mentioned within the documents.

## Dependencies

Rendered with [asciidoctor-pdf](https://github.com/asciidoctor/asciidoctor-pdf). Asciidoctor-pdf is currently in alpha, but can be obtained easily via `gem install`:

    gem install asciidoctor-pdf -pre

Previously depended on asciimath, which unfortunately isn't yet supported (so some math won't render any more, which I'll fix later).

## Rerendering
Source files are grouped by book and chapter, with each chapter having a `*.adoc` file which can be modified to make changes. To rerender pdf for each book:

    asciidoctor-pdf index.adoc -D ../ -o BOOK_NAME.pdf

within the appropriate source directory.

Alternatively (much easier), execute

    ./build.sh

within the appropriate source directory. In some cases (where only one file is built), there's also a script to build and render, since it's a bit tiresome to build and then open the pdf which is one directory up for lazy people like me, but annoying to always open the rendered PDF:

    ./render.sh

