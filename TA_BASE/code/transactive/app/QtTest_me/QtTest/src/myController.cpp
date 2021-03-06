
/**
* The source code in this file is the property of
* Ripple Systems and is not for redistribution
* in any form.
*
* Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/event/event_viewer/pmodel/src/EventViewerAppController.cpp $
* @author:
* @version: $Revision:  $
*
* Last modification: $DateTime: $
* Last modified by:  $Author: Shiva $
*
* This is the implementation of the
* GenericGUI IGUIApplicationController interfaces.
*/
#include "StdAfx.h"
#include "myController.h"
#include "myPmodel.h"


#include "bus/application_types/src/apptypes.h"
#include "bus/security/rights_library/src/RightsLibrary.h"

#include "core/data_access_interface/entity_access/src/ArchiveManagerEntityData.h"
#include "core/data_access_interface/entity_access/src/IEntityData.h"
#include "core/data_access_interface/src/IOperator.h"
#include "core/data_access_interface/src/OperatorAccessFactory.h"
#include "core/exceptions/src/UserSettingsException.h"
#include "core/exceptions/src/DatabaseException.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/GenericGuiException.h"
#include "core/exceptions/src/ProcessAlreadyRunningException.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DebugUtil.h"


using TA_Base_Core::DebugUtil;
using TA_Base_Core::RunParams;
using TA_Base_Bus::SettingsMgr;


namespace TA_Base_App
{

    myController::myController(TA_Base_Bus::ITransActiveWinApp * pApp, const char * appName)
        : TA_Base_Bus::AbstractGUIAppController(pApp, appName)
    {

    }

    myController::~myController()
    {

    }

    unsigned long myController::getApplicationType()
    {
        return ARCHIVE_MANAGER_APPTYPE;
    }


    void myController::allocAppResource()
    {

    }

    void myController::cleanup()
    {
        AbstractGUIAppController::cleanup();
    }


    void myController::prepareForClose()
    {
        //This provides a standard method for each GUI to use to clean itself
        //up ready to exit. This will be called whenever the application exits whether
        //it is closed by the Control Station or by the user. This should perform
        //tasks such as saving user settings, stopping any threads and asking the user
        //if they want to save their settings. When this method is completed the GUI
        //should be in a safe state to be closed.

        try
        {
            saveAllUserSettings();
        }
        catch ( TA_Base_Core::UserSettingsException& e )
        {
            LOG_EXCEPTION_CATCH( SourceInfo, "UserSettingsException", e.what() );

            // Get the operator name from the session id.

            std::string operatorName( "" );
            try
            {
                std::auto_ptr< TA_Base_Core::IOperator > theOperator(
                    TA_Base_Core::OperatorAccessFactory::getInstance().getOperatorFromSession(
                    TA_Base_Core::RunParams::getInstance().get( RPARAM_SESSIONID ), false ) );
                if ( 0 != theOperator.get() )
                {
                    operatorName = theOperator->getName();
                }
            }
            catch( TA_Base_Core::DatabaseException& e )
            {
                LOG_EXCEPTION_CATCH( SourceInfo, "DatabaseException", e.what() );
            }
            catch( TA_Base_Core::DataException& e )
            {
                LOG_EXCEPTION_CATCH( SourceInfo, "DataException", e.what() );
            }

            if ( operatorName.empty() )
            {
                operatorName = "(unknown)";
            }

            /*TA_Base_Bus::TransActiveMessage userMsg;
            userMsg << operatorName << e.what();
            UINT selectedButton = userMsg.showMsgBox(IDS_UW_050017);*/ ///TODO
        }

        // Clean up the rights library
        //TA_Base_Bus::RightsLibrary* library = TA_ArchiveManager::getRightsLibrary();
        //delete library;
        //library = NULL;

        AbstractGUIAppController::prepareForClose();
    }

    void myController::checkEntity(TA_Base_Core::IEntityData* guiEntity)
    {
        // KT 3 Mar 04: PW #3136: Added to ensure only one instance of the Archive Manager is running at once.
        // Note: This only ensures that there is one instance connected to the schema specified by the
        // DbConnection runparam.  It cannot ensure that there is only one instance running system wide, if
        // multiple schemas are available.  However, this situation is unlikely.

        FUNCTION_ENTRY( "checkEntity" );

        TA_ASSERT( guiEntity != NULL, "The IEntityData pointer passed in was NULL" );

        m_guiEntity = guiEntity;

        //TA_Base_Core::ArchiveManagerEntityData* entityData = dynamic_cast< TA_Base_Core::ArchiveManagerEntityData* >( guiEntity );
        //if ( 0 == entityData )
        //{
        //    //std::string message = IGuiObserver::getInstance()->getStringResourceFormated(UE050125_INVALID_ENTITY,TA_Base_Core::ArchiveManagerEntityData::getStaticType());
        //    //TA_THROW(  TA_Base_Core::GenericGUIException( message, TA_Base_Core::GenericGUIException::ENTITY_CONFIGURATION_INVALID) );
        //}

        //std::string workstationName( "" );
        //if ( entityData->isArchiveManagerAlreadyRunning( workstationName ) )
        //{
        //    std::string applicationName( TA_Base_Core::RunParams::getInstance().get( RPARAM_APPNAME ).c_str() );
        //    if ( applicationName.empty() )
        //    {
        //        //applicationName = IGuiObserver::getInstance()->getStringResource(IDS_ARCHIVEMANAGER);
        //    }

        //    std::string reason;
        //    if ( workstationName.empty() )
        //    {
        //        //reason = IGuiObserver::getInstance()->getStringResourceFormated( UE050108_REASON_DB_FAILED, applicationName );
        //    }
        //    else
        //    {
        //        //reason = IGuiObserver::getInstance()->getStringResourceFormated( UE050108_REASON_RUNNING, applicationName, workstationName);
        //    }

        //    /*TA_Base_Bus::TransActiveMessage userMsg;
        //    userMsg << applicationName << reason;
        //    UINT selectedButton = userMsg.showMsgBox(IDS_UE_050108);*////////////////TODO

        //    TA_THROW( TA_Base_Core::ProcessAlreadyRunningException( "The Archive Manager must be terminated as an instance of it is already connected to this schema." ) );
        //}

        FUNCTION_EXIT;
    }

    void myController::serverIsDown()
    {
        // This method is used to ensure the GUI can handle when the server goes
        //up or down. The GUI should be updated to indicate the network status.
        //If the server has gone down it should enter some sort of read-only mode and
        //if the server comes back up it can restore to the correct operating mode.

        /*if ( getApplicationWnd() != 0 )
        {
        CArchiveManagerDlg* dlg = dynamic_cast< CArchiveManagerDlg* >( getApplicationWnd() );
        if ( dlg == 0 )
        {
        LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugError,
        "Failed to update the server status because the dynamic cast failed." );
        }
        else
        {
        dlg->setServerStatus( false );
        }
        }*///////////////TODO
    }


    void myController::serverIsUp()
    {
        // This method is used to ensure the GUI can handle when the server goes
        //up or down. The GUI should be updated to indicate the network status.
        //If the server has gone down it should enter some sort of read-only mode and
        //if the server comes back up it can restore to the correct operating mode.

        /*  if ( getApplicationWnd() != 0 )
        {
        CArchiveManagerDlg* dlg = dynamic_cast< CArchiveManagerDlg* >( getApplicationWnd() );
        if ( dlg == 0 )
        {
        LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugError,
        "Failed to update the server status because the dynamic cast failed." );
        }
        else
        {
        dlg->setServerStatus( true );
        }
        }*//////////////////////TODO
    }


    void myController::loadAllUserSettings()
    {
        FUNCTION_ENTRY( "loadAllUserSettings" );

        // First check if we should be loading the user settings.

        /*  if ( RunParams::getInstance().get(RPARAM_USERPREFERENCES).empty() )
        {
        setWindowPosition();
        return;
        }

        if (getUserSetting() == 0)
        {
        setUserSetting(*(new SettingsMgr(getSessionId(), getApplicationType() )));
        }

        loadPositionSettings();*//////////////TODO
    }


    void myController::saveAllUserSettings()
    {
        FUNCTION_ENTRY( "saveAllUserSettings" );

        // First check if we should be saving the user settings.

        /* if ( RunParams::getInstance().get(RPARAM_USERPREFERENCES).empty() )
        {
        return;
        }

        if (getUserSetting() == 0)
        {
        setUserSetting(*( new SettingsMgr(getSessionId(), getApplicationType() )));
        }

        savePositionSettings();*////////////////TODO
    }


    TA_Base_Bus::ITransActivePModel * myController::createPModel( const std::string & pModelName )
    {
        TA_Base_Bus::ITransActivePModel * pModel = NULL;
        pModel = new myPmodel(this, pModelName.c_str());

        /*if (pModelName == ARCHIVE_MANAGER_DLG_MODEL)
        {
            pModel = new ArchiveManagerDlgPModel(this, pModelName.c_str());
        }
        else if (pModelName == RESTORE_ARCHIVE_DLG_PMODEL)
        {
            pModel = new RestoreArchivePModel(this, pModelName.c_str());
        }
        else if (pModelName == BURN_MEDIA_DLG_PMODEL)
        {
            pModel = new BurnMediaPModel(this, pModelName.c_str());
        }
        else if (pModelName == WRITE_ARCHIVE_DLG_PMODEL)
        {
            pModel = new WriteArchivePModel(this, pModelName.c_str());
        }
        else
        {
            std::string errorDesc = "presentation model name is not valid: " + pModelName;
            TA_ASSERT(FALSE, errorDesc.c_str());
        }*/
        return pModel;
    }

} // namespace TA_Base_App
