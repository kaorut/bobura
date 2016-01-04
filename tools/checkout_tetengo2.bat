@echo off
rem Checks out tetengo2.
rem Copyright (C) 2007-2016 kaoru
rem $Id$

git submodule update --init
git submodule foreach 'git checkout master && git pull'
