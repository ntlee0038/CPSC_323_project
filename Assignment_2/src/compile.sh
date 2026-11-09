#!/bin/bash

clang++ -std=c++17 \
-isysroot "$(xcrun --sdk macosx --show-sdk-path)" \
-isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1 \
main.cpp lexer.cpp parser.cpp -o parser
