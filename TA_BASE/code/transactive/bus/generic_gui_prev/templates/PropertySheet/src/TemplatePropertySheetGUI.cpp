/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/generic_gui_prev/templates/PropertySheet/src/TemplatePropertySheetGUI.cpp $
  * @author:  
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  *
  */

#include "stdafx.h"
#include "TemplatePropertySheetGUI.h"
#include "resource.h"
#include "TemplatePropertySheetDlg.h"

#include "bus\application_types\src\apptypes.h"
#include "core\utilities\src\RunParams.h"
#include "core\utilities\src\DebugUtil.h"

#include "bus\user_settings\src\SettingsMgr.h"
#include "core\exceptions\src\UserSettingsException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using TA_Base_Core::RunParams;
using TA_Base_Core::DebugUtil;
using TA_Base_Bus::SettingsMgr;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TemplatePropertySheetGUI::TemplatePropertySheetGUI()
{   
}


TemplatePropertySheetGUI::~TemplatePropertySheetGUI()
{
}


void TemplatePropertySheetGUI::createApplicationObject()
{
    CTemplatePropertySheetDlg* dlg = new CTemplatePropertySheetDlg(*this);
    setApplicationWnd(*dlg);
}


unsigned long TemplatePropertySheetGUI::getApplicationType()
{
	// TODO: Return a value from apptypes.h
	return 0;
}


void TemplatePropertySheetGUI::checkEntity(TA_Base_Core::IEntityData* guiEntity)
{
	setGuiEntity(*guiEntity);
}


void TemplatePropertySheetGUI::checkCommandLine()
{  
}


void TemplatePropertySheetGUI::entityChanged(const std::vector<std::string>& changes)
{
	//TODO: This will be called by GenericGUI when it receives a callback
	//indicating that the GUI entity has been modified. GenericGUI will have
	//invalidated the entity database object and will tell the GUI which
	//items were modified. This method just has to retrieve the details out
	//of it and update accordingly. If the details in it are invalid then this
	//should print a warning message to the user and continue to use the old settings (ie do not update the GUI).
}


void TemplatePropertySheetGUI::serverIsDown()
{
    // TODO: This method is used to ensure the GUI can handle when the server goes
	//up or down. The GUI should be updated to indicate the network status.
	//If the server has gone down it should enter some sort of read-only mode and
	//if the server comes back up it can restore to the correct operating mode.
}


void TemplatePropertySheetGUI::serverIsUp()
{
    // TODO: This method is used to ensure the GUI can handle when the server goes
	//up or down. The GUI should be updated to indicate the network status.
	//If the server has gone down it should enter some sort of read-only mode and
	//if the server comes back up it can restore to the correct operating mode.
}


void TemplatePropertySheetGUI::loadAllUserSettings()
{
    // First check if we should be loading the user settings.
    if ( RunParams::getInstance().get(RPARAM_USERPREFERENCES).empty() )
    {
       setWindowPosition();
       LOG( SourceInfo, DebugUtil::FunctionExit, "loadAllUserSettings" );            
       return;
    }

    if (getUserSetting() == NULL)
    {
        TA_Base_Bus::SettingsMgr* userSettings = new SettingsMgr(getSessionId(), getApplicationType());

        if (userSettings == NULL)
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugWarn, "new on SettingsMgr returned NULL. Cannot load user preferences");
        }

        setUserSetting( *userSettings );            
    }

    loadPositionSettings();
}


void TemplatePropertySheetGUI::saveAllUserSettings()
{
    // First check if we should be saving the user settings.
    if ( RunParams::getInstance().get(RPARAM_USERPREFERENCES).empty() )
    {
        return;
    }

    if (getUserSetting() == NULL)
    {
        TA_Base_Bus::SettingsMgr* userSettings = new SettingsMgr(getSessionId(), getApplicationType());

        if (userSettings == NULL)
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugWarn, "new on SettingsMgr returned NULL. Cannot load user preferences");
        }

        setUserSetting( *userSettings );            
    }
    
    savePositionSettings();
}


void TemplatePropertySheetGUI::prepareForClose()
{
	//TODO: This provides a standard method for each GUI to use to clean itself 
	//up ready to exit. This will be called whenever the application exits whether 
	//it is closed by the Control Station or by the user. This should perform 
	//tasks such as saving user settings, stopping any threads and asking the user 
	//if they want to save their settings. When this method is completed the GUI 
	//should be in a safe state to be closed.

    try
    {
        saveAllUserSettings();
    }
    catch ( TA_Base_Core::UserSettingsException&)
    {
        // Handle here with appropriate errror message
    }

    // TODO: Perform any shutdown tasks here
}

