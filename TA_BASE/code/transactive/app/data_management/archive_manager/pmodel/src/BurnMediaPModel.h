#if !defined(BURNTHREAD_HELPER_CLASS__1468A462_430F_4418_BC92_334001E5F340__INCLUDED_)
#define BURNTHREAD_HELPER_CLASS__1468A462_430F_4418_BC92_334001E5F340__INCLUDED_

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File:  $
  * @author: 
  * @version: $Revision:  $
  *
  * Last modification: $DateTime:  $
  * Last modified by:  $Author:  $
  *
  *
  */

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <list>
#include "cots/Nero/inc/NeroAPIglue.h"
#include "app/data_management/archive_manager/pmodel/src/WriteArchiveHelper.h"
#include "app/data_management/archive_manager/pmodel/src/resource.h"
#include "app/data_management/archive_manager/pmodel/src/StateManager.h"
#include "bus/generic_gui_pmod/src/transactiveviewmodel.h"
#include "core/threads/src/Thread.h"


namespace TA_Base_App
{
    class BurnMediaPModel  : public TA_Base_Bus::AbstractPModel, public TA_Base_Core::Thread
    {
    public:
			BurnMediaPModel(TA_Base_Bus::IGUIApplicationController* appController, const char * pmodelName);
			virtual ~BurnMediaPModel();
			void setDetails(const std::string& volumeLabel, const std::string& cdLabel, const WriteArchiveHelper::FileDetailsVector* files,bool bCdBurn);
       
         /**
          * run
          * 
          * Inherited from Thread.  This calls the initialisation and write methods.
          * By having a separate thread do this, we can allow user interaction to continue with
          * the GUI.  If Cancel is pressed, the thread will wait until Nero has decided 
          * that it is safe to cancel, then the process will be cancelled.
          *
          * This class inherits from Thread instead of having a separate class for it, because
          * the write process has lots of GUI interaction throughout.
          */

        virtual void run();

        /**
          * terminate
          *
          * If the thread is still running, it tells the thread to stop when Nero decides
          * it is safe to do so.
          */
        
        virtual void terminate();

		std::string getLogString()
		{
			return m_logString;
		}

		void cleanUpNero();

		StateManager::EState getStateManagerState()
		{
			return m_stateManager.getState();
		}

		void setStateManagerState( StateManager::EState state )
		 {
			 m_stateManager.setState(state);
		 }

		std::string m_selectImageFilePath;
		bool m_bFileDialog;

    private:


        /**
          * neroApiInit
          *
          * Initialises Nero, includes setting up the hardware and the CD configuration.
          * NOTE: Each call to neroApiInit must be accompanied by a call to neroApiFree.
          * 
          *
          * @exception  ArchiveException
          *             Thrown if:
          *             1) The NeroAPI.dll cannot be found or opened.
          *             2) The Nero initialisation fails.
          *             3) There are no CDRW/CDROM drives present or accessible.
          *             4) The drive cannot be connected to.
          */

        void neroApiInit();

        /**
          * neroApiFree
          *
          * Cleans up Nero.  Each call to neroApiInit must be accompanied by
          * a call to neroApiFree.
          */

        void neroApiFree();
        
        /**
          * doBurn
          *
          * Creates the ISO item tree, writes the data to CD and cleans up.
          *
          * @exception  ArchiveException
          *             Thrown if:
          *             1) There are no files to burn.
          *             2) The burn fails.
          */

        void doBurn();

        /**
          * NeroSetMajorPhaseCallback
          *
          * Called from Nero when a major phase has completed.
          * This updates the log display.
          */

	    static void NERO_CALLBACK_ATTR neroSetMajorPhaseCallback(void *pUserData, NERO_MAJOR_PHASE phase, void *reserved);

        /**
          * NeroSetPhaseCallback
          *
          * Called from Nero when a major phase has completed.
          * This updates the stage display.
          */	    
        
        static void NERO_CALLBACK_ATTR neroSetPhaseCallback(void *pUserData, const char *text);

        /**
          * NeroAddLogLine
          *
          * Called from Nero when a line should be added to the log display.
          * This updates the log display.
          */	    
        
	    static void NERO_CALLBACK_ATTR neroAddLogLine(void *pUserData, NERO_TEXT_TYPE type, const char *text);

        /**
          * NeroAbortedCallback
          *
          * Called from Nero aborts.
          */	    
    
	    static BOOL NERO_CALLBACK_ATTR neroAbortedCallback(void *pUserData);

        /**
          * NeroProgressCallback
          *
          * Called from Nero when the write has progressed.
          * This updates the progress bar.
          */	    
    
	    static BOOL NERO_CALLBACK_ATTR neroProgressCallback (void *pUserData, DWORD dwProgressInPercent);

        /**
          * NeroIdleCallback
          *
          * This is the message pump that keeps the whole Archive Manager GUI alive while Nero burns. 
          * The normal Windows procedure of processing messages while waiting for the hardware to 
          * send a "finished" message is actually turned inside out, and Nero takes control of the PC 
          * and lets Windows do its processing when Nero feels like letting it.
          */	    
    
	    static BOOL NERO_CALLBACK_ATTR neroIdleCallback(void *pUserData);

        /**
          * NeroUserDialog
          *
          * Called from Nero when the user may need to be prompted.
          * Prompts the user.
          */	    
    
	    static NeroUserDlgInOut NERO_CALLBACK_ATTR neroUserDialog(void *pUserData, NeroUserDlgInOut type, void *data);

        /**
          * addFile
          *
          * Adds the given file to the list of files to write to removable media.
          *  Call addFile() for every file that will be written to CD.
          *
          *  Limitations:
          *  -   only writes a single directory layer (NERO_ISO_ITEM.subDirFirstItem not used)
          *  -   only writes to CD's root directory
          *  -   writes in the order you call this routine
          *
          * @param      const std::string& fileNameWithPath
          *             The file name incl. the full path.
          * @param      const std::string& fileName
          *             The file name without the full path.
          * @param      bool isDirectory
          *             True if the file is actually a directory.
          *             False otherwise (by default).
          *
          * @exception  ArchiveException
          *             Thrown if:
          *             1) The file does not exist/cannot be found.
          *             2) The file is a directory and isDirectory is false.
          *             3) The file is not a directory and isDirectory is true.
          *             4) The file cannot be added to the list.
          */

        void addFile( const std::string& fileNameWithPath, const std::string& fileName, bool isDirectory = false );

		// TD16705

		/**
		  * formatStringHelper
		  *
		  * changed a string from ?YYYY_MM_DD*.dmp to ?DDMMYY*.dmp
		  *
		  * @param      const std::string& strSrc
		  *				The string to be changed 
		  *				
		  */

		std::string formatStringHelper( const std::string& strSrc);

        //
        // The files to write to CD in write order as passed to
        // this dialog and in a form ready for passing to Nero.
        //

        const WriteArchiveHelper::FileDetailsVector* m_files;
		std::list<NERO_ISO_ITEM*> m_neroIsoItemsList;

        //
        // The label to write on the CD manually (m_volumeLabel) and 
        // electronically (m_cdLabel) containing the archive date and part information.
        // KT 10 Mar 04: PW #3136 Added reformatted volume label for CD (m_cdLabel).
        // 

        std::string m_volumeLabel;
        std::string m_cdLabel;
        
        //
        // Manages the state of the GUI.
        //
        
        StateManager m_stateManager;

        //
        // Objects required for Nero.
        //
   	    
        NERO_DEVICEHANDLE		m_neroDeviceHandle;
	    NERO_PROGRESS			m_neroProgress;
   	    NERO_SETTINGS			m_neroSettings;
	    NERO_SCSI_DEVICE_INFOS* m_neroDeviceInfos;

		//log string
		std::string m_logString;

		bool m_bCdBurn;
    };    
    
} // TA_Base_App

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(BURNTHREAD_HELPER_CLASS__1468A462_430F_4418_BC92_334001E5F340__INCLUDED_)
