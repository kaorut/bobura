@echo off

git submodule update --init
git submodule foreach 'git checkout master && git pull'
