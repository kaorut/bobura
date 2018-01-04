# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SOURCE_SUBDIRS = include src test

SUBDIRS = $(SOURCE_SUBDIRS) res.test

EXTRA_DIST = \
    bobura_core.vcxproj bobura_core.vcxproj.filters \
    bobura_core.test.vcxproj bobura_core.test.vcxproj.filters

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done
