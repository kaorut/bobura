# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SOURCE_SUBDIRS = include src

SUBDIRS = $(SOURCE_SUBDIRS) res

EXTRA_DIST = \
    bobura.vcxproj bobura.vcxproj.filters

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done
