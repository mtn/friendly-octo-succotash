#!/bin/bash
asciidoctor-pdf priority_queues.adoc -D ../ -o priority_queues.pdf
asciidoctor-pdf avl.adoc -D ../ -o avl_trees.pdf
asciidoctor-pdf bfs.adoc -D ../ -o bfs.pdf
