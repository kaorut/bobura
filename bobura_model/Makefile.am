# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

SOURCE_SUBDIRS = include src test

SUBDIRS = $(SOURCE_SUBDIRS)

EXTRA_DIST = \
    bobura_model.vcxproj bobura_model.vcxproj.filters \
    bobura_model.test.vcxproj bobura_model.test.vcxproj.filters

lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done
