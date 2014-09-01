#!/bin/sh
# File path lister.
# Copyright (C) 2007-2014 kaoru
# $Id$

list_sources()
{
    find \
        $1/bobura/include \
        $1/bobura/src \
        $1/bobura_core/include \
        $1/bobura_core/src \
        $1/bobura_model/include \
        $1/setup/include \
        $1/setup/src \
        -type f \
        -name '*.h' -or \
        -name '*.cpp'
}

list_test_sources()
{
    find \
        $1/bobura_core/test \
        $1/bobura_model/test \
        -type f \
        -name '*.h' -or \
        -name '*.cpp';
}

