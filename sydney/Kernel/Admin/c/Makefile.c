/*
 * Makefile.c --- Kernel/Admin/c
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

MODULE = Admin
TARGET_BASE = SyAdmin
SRCDIR = ..
HDRDIR = ../$(MODULE)
MESSAGE_DEFINITION =
MESSAGE_TARGET =

LOCAL_EXPORT_HDRDIR = ../../include/$(MODULE)
TOP_EXPORT_HDRDIR = ../../../include/$(MODULE)
TOP_INSTALL_DIR = ../../../c.CONF

/* above variables MUST be defined      */
/****************************************/

/* headers created for message */
MESSAGE_HDRS =

/* headers installed in Kernel */
LOCAL_EXPORT_HDRS = \
	$(HDRDIR)/Database.h \
	$(HDRDIR)/File.h \
	$(HDRDIR)/Manager.h \
	$(HDRDIR)/Replicator.h \
	$(HDRDIR)/Restart.h \
	$(HDRDIR)/Transaction.h \
	$(HDRDIR)/Unmount.h \
	$(HDRDIR)/Utility.h

/* headers installed in TOP */
TOP_EXPORT_HDRS = \
	$(HDRDIR)/Debug.h \
	$(HDRDIR)/EndBackup.h \
	$(HDRDIR)/Externalizable.h \
	$(HDRDIR)/LogData.h \
	$(HDRDIR)/Module.h \
	$(HDRDIR)/Mount.h \
	$(HDRDIR)/Verification.h \
	$(MESSAGE_HDRS)

HDRS = \
	$(TOP_EXPORT_HDRS) \
	$(LOCAL_EXPORT_HDRS) \
	$(HDRDIR)/FakeError.h \
	$(HDRDIR)/Operation.h \
	$(HDRDIR)/StartBackup.h

MESSAGE_OBJS =

OBJS = \
	$(MESSAGE_OBJS) \
	Admin$O \
	Database$O \
	EndBackup$O \
	Externalizable$O \
	File$O \
	LogData$O \
	Manager$O \
	Mount$O \
	Replicator$O \
	Restart$O \
	StartBackup$O \
	Transaction$O \
	Unmount$O \
	Utility$O \
	Verification$O

#ifdef SYD_DLL
EXPORTFLAGS = \
	-DSYD_EXPORT_FUNCTION \
	-DSYD_KERNEL_EXPORT_FUNCTION
#endif
EXTRACFLAGS = \
	$(EXPORTFLAGS)
EXTRALDFLAGS =
EXTRAPURIFYFLAGS =
EXTRAQUANTIFYFLAGS =
EXTRAPURECOVFLAGS =
EXTRALOCALCFLAGS =

/********************************************************/

TARGET = $(MODULE).ol

ALLTARGETS = \
	$(MESSAGE_TARGET) \
	$(TARGET)

/*
 * all
 */
AllTarget($(ALLTARGETS))

ObjectListTarget($(TARGET), $(OBJS), $(TOP_INSTALL_DIR))

/*
 * message
 */
/* MessageTarget($(MESSAGE_TARGET), $(MESSAGE_DEFINITION), $(BUILD_JAR)) */

/*
 * install library and header
 */
InstallHeaderTarget($(TOP_EXPORT_HDRS), $(TOP_EXPORT_HDRDIR))
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
