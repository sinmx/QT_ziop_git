# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/data_access_interface/tis_agent_4669/Makefile $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2015/10/09 15:42:35 $
# Last modified by:  $Author: CM $
#
# Make file for the TA_TISAgentDAI_4669 classes.
#

PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/core/data_access_interface/tis_agent_4669
PROJ_NAME	= TA_TISAgentDAI_4669

PROJ_SOURCE	= PredefinedMessageLibraryHelper.cpp \
		PredefinedMessageLibraryAccessFactory.cpp \
                PredefinedMessageLibraryData.cpp \
                ConfigPredefinedMessageLibraryData.cpp \
                

PROJ_TYPE	= lib
PROJ_INC_DIR    = ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR    = $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

DEPENDENT_LIBRARIES = $(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/tis_agent_4669/IDL

PROJ_CFLAGS = -DTA_ASSERT_LOG=1
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak


install:
        #Do Nothing
