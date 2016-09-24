#!/bin/bash

f="res/testfile.cpp"
[[ -n "$1" ]] && f="$1"
cat res/header.html
./cpp2html < "$f"
cat res/footer.html
