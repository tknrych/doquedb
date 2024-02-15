/*
 * Makefile.c --- Kernel/Plan/Relation/c
 * 
 * Copyright (c) 1999, 2023 Ricoh Company, Ltd.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

SUBDIRS =

/****************************************/
/* following variables MUST be defined  */

MODULE = Plan
SUBMODULE = Relation
SRCDIR = ..
HDRDIR = ../../$(MODULE)/$(SUBMODULE)
MESSAGE_DEFINITION =
MESSAGE_TARGET =

LOCAL_EXPORT_HDRDIR = ../../../include/$(MODULE)/$(SUBMODULE)
TOP_EXPORT_HDRDIR = ../../../../include/$(MODULE)/$(SUBMODULE)
TOP_INSTALL_DIR = ../../../../c.CONF
LOCAL_INSTALL_DIR = ../../c.CONF

/* above variables MUST be defined      */
/****************************************/

/* headers created for message */
MESSAGE_HDRS =

/* headers installed in Kernel */
LOCAL_EXPORT_HDRS = \
	$(HDRDIR)/Argument.h		\
	$(HDRDIR)/Bulk.h			\
	$(HDRDIR)/Declaration.h		\
	$(HDRDIR)/Distinct.h		\
	$(HDRDIR)/Expand.h			\
	$(HDRDIR)/Grouping.h		\
	$(HDRDIR)/Join.h			\
	$(HDRDIR)/Limit.h			\
	$(HDRDIR)/Module.h			\
	$(HDRDIR)/Procedure.h		\
	$(HDRDIR)/Projection.h		\
	$(HDRDIR)/RowElement.h		\
	$(HDRDIR)/RowInfo.h			\
	$(HDRDIR)/Selection.h		\
	$(HDRDIR)/Sort.h			\
	$(HDRDIR)/Table.h			\
	$(HDRDIR)/Union.h			\
	$(HDRDIR)/Unnest.h			\
	$(HDRDIR)/ValueList.h

/* headers installed in TOP */
TOP_EXPORT_HDRS = \
	$(MESSAGE_HDRS)

HDRS = \
	$(TOP_EXPORT_HDRS)				\
	$(LOCAL_EXPORT_HDRS)			\
	$(HDRDIR)/Filter.h				\
	$(HDRDIR)/Impl/BulkImpl.h		\
	$(HDRDIR)/Impl/DistinctImpl.h	\
	$(HDRDIR)/Impl/GroupingImpl.h	\
	$(HDRDIR)/Impl/JoinImpl.h		\
	$(HDRDIR)/Impl/ProcedureImpl.h	\
	$(HDRDIR)/Impl/SortImpl.h		\
	$(HDRDIR)/Impl/TableImpl.h		\
	$(HDRDIR)/Impl/UnionImpl.h		\
	$(HDRDIR)/Impl/UnnestImpl.h		\
	$(HDRDIR)/Impl/ValueListImpl.h

MESSAGE_OBJS =

IMPL_OBJS = \
	BulkImpl$O			\
	DistinctImpl$O		\
	GroupingImpl$O		\
	JoinImpl$O			\
	ProcedureImpl$O		\
	SortImpl$O			\
	TableImpl$O			\
	UnionImpl$O			\
	UnnestImpl$O		\
	ValueListImpl$O

OBJS = \
	$(MESSAGE_OBJS)		\
	Argument$O			\
	Bulk$O				\
	Distinct$O			\
	Expand$O			\
	Grouping$O			\
	Join$O				\
	Limit$O				\
	Procedure$O			\
	Projection$O		\
	RowElement$O		\
	RowInfo$O			\
	Selection$O			\
	Sort$O				\
	Table$O				\
	Union$O				\
	Unnest$O			\
	ValueList$O			\
	$(IMPL_OBJS)

#ifdef SYD_DLL
EXPORTFLAGS = \
	-DSYD_KERNEL_EXPORT_FUNCTION
#endif
EXTRACFLAGS = \
	$(EXPORTFLAGS)
EXTRALDFLAGS =
EXTRAPURIFYFLAGS =
EXTRAQUANTIFYFLAGS =
EXTRAPURECOVFLAGS =
EXTRALOCALCFLAGS = \
	-I../..

/********************************************************/

TARGET = $(SUBMODULE).ol

ALLTARGETS = \
	$(MESSAGE_TARGET) \
	$(TARGET)

/*
 * all
 */
AllTarget($(ALLTARGETS))

ObjectListTarget($(TARGET), $(OBJS), $(LOCAL_INSTALL_DIR))

InstallHeaderTarget($(LOCAL_EXPORT_HDRS), $(LOCAL_EXPORT_HDRDIR))

/*
 * clean
 */
CleanTarget($(ALLTARGETS))
CleanTarget($(OBJS))

#include "Makefile.h"

/*
  Copyright (c) 1999, 2023 Ricoh Company, Ltd.
  All rights reserved.
*/
