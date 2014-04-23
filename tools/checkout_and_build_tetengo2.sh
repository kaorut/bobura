#!/bin/sh
# Checks out and build tetengo2.
# Copyright (C) 2007-2014 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

git submodule update --init
git submodule foreach 'git checkout master && git pull'

pushd $SOLUTION_DIR/lib/tetengo2

./bootstrap.sh
./configure $1
make $2

popd
