#!/bin/sh
# Checks out and build tetengo2.
# Copyright (C) 2007-2014 kaoru
# $Id$

SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

git submodule update --init
git submodule foreach 'git checkout master && git pull'

cd $SOLUTION_DIR/lib/tetengo2

./bootstrap.sh
./configure $2
make $3

cd $SOLUTION_DIR
