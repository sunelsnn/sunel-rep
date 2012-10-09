# $Id: Makefile.am,v 1.25 2005/11/22 13:33:24 frehe Exp $


EXTRA_DIST = client.conf server.conf FCFoo-s

AM_CXXFLAGS = @AM_CXXFLAGS@ @DEBUG_TEAM@
INCLUDES = -I@RSSTRATEGY_INCLUDEPATH@ -I@RSVIEW_INCLUDEPATH@ \
	-I@RSSKILL_INCLUDEPATH@ -I@RSPREDICATE_INCLUDEPATH@ \
	-I@RSLIBRARY_INCLUDEPATH@ -I@RSBASICSYSTEM_INCLUDEPATH@ \
	-I@RSFRAMEWORK_INCLUDEPATH@ -I@RCCPARSER_INCLUDEPATH@ \
	-I@RSSS_INCLUDEPATH@


noinst_PROGRAMS = FCFoo 
include_HEADERS = $(FCFoo_HEADER)

FCFoo_LDFLAGS = @RS_ALL_STATIC@ -L@RSSTRATEGY_LIBPATH@ \
	-L@RCCPARSER_LIBPATH@ -L@RSPREDICATE_LIBPATH@ \
	-L@RSSKILL_LIBPATH@ -L@RSVIEW_LIBPATH@ -L@RSLIBRARY_LIBPATH@ \
	-L@RSBASICSYSTEM_LIBPATH@ -L@RSFRAMEWORK_LIBPATH@ \
	-L@RSSS_LIBPATH@


FCFoo_LDADD = -lrsskill -lrspredicate -lrsview -lrsstrategy \
	-lrsframework -lrsbasicsystem -lrslibrary -lrccparser 
#	-lrcssclangparser

FCFoo_HEADER = FCFooDecision.h FCFooCoachDecision.h FCFooTrainerDecision.h
FCFoo_SOURCES = FCFoo.cc FCFooDecision.cc FCFooCoachDecision.cc FCFooTrainerDecision.cc

FCFoo_DEPENDENCIES = @RCCPARSER_LIBPATH@/librccparser.la \
	@RSLIBRARY_LIBPATH@/librslibrary.la \
	@RSBASICSYSTEM_LIBPATH@/librsbasicsystem.la \
	@RSFRAMEWORK_LIBPATH@/librsframework.la \
	@RSPREDICATE_LIBPATH@/librspredicate.la \
	@RSSKILL_LIBPATH@/librsskill.la \
	@RSVIEW_LIBPATH@/librsview.la \
	@RSSTRATEGY_LIBPATH@/librsstrategy.la


MAINTAINERCLEANFILES = \
	Makefile.in
