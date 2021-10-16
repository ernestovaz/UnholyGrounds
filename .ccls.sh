#!/bin/bash
echo 'clang'  > .ccls
find src/ -type f -iname *.h -printf '-I%h\n' | sort -u >> .ccls
