#!/bin/bash
asciidoctor-pdf index.adoc -D ../ -o kalicharan.pdf
open ../kalicharan.pdf
