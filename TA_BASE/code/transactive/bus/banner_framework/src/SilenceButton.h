/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/banner_framework/src/SilenceButton.h $
  * @author:  Justin Ebedes
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2016/12/14 14:57:33 $
  * Last modified by:  $Author: Noel $
  *
  * This class represents a silence button that can be added
  * to any banner page.
  *
  */

#if !defined(AFX_SILENCEBUTTON_H__30A7F0A1_6BA3_4D7F_AC9B_937BC18C6B24__INCLUDED_)
#define AFX_SILENCEBUTTON_H__30A7F0A1_6BA3_4D7F_AC9B_937BC18C6B24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SilenceButton.h : header file
//

#include "bus/sound/sound_client/src/ISoundObserver.h"
#include <QPushButton>
#include <QPixmap.h>
namespace TA_Base_Bus
{
    class SoundManagerProxy;

	class SilenceButton : public QPushButton,
                          public ISoundObserver
    {

    public:

        /**
          * Constructor
          *
          * @param soundCategory  The name of the sound category that this button will 
          *                       silence and unsilence.
          */
        SilenceButton(const std::string& soundCategory);

    
        /** 
          * initialise
          *
          * Sets the initial state of the silence button.
          *
          * @param isSilenced  True if the button should initially be set as silenced,
          *                    and false otherwise.
          */
        void initialise(bool isSilenced);

    
        /** 
          * toggleState
          *
          * Toggles the state of the silence button.
          *
          */
        void toggleState();

    
        /** 
          * unsilence
          *
          * Unsilences the sound.
          *
          */
	    void unsilence();


	    /** 
	      * handleCategorySilenced
	      *
	      * Called when a category of sounds has its silence state updated.
	      *
	      * @param category    The category of sounds that has been silenced or unsilenced.
	      * @param isSilenced  True if the category was silenced, and false if it was
	      *					   unsilenced.
	      *
	      */
	    virtual void handleCategorySilenced(const std::string& category, bool isSilenced);


	    /** 
	      * handleAllSilenced
	      *
	      * Called when all categories of sounds have been silenced or unsilenced.
	      *
	      * @param isSilenced  True if all sounds have been silenced, and false if they
	      *					   have been unsilenced.
	      */
	    virtual void handleAllSilenced(bool isSilenced);


        // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(SilenceButton)
	    //}}AFX_VIRTUAL


        /**
          * Destructor
          */
	    virtual ~SilenceButton();
    private:

	    /**
	      * A wrapper for the SoundManager.
	      */
	    SoundManagerProxy* m_soundInterface;

	    /**
	      * True if silenced, and false otherwise.
	      */
        bool m_isSilenced;

		QIcon* m_muteImage;
		QIcon* m_unmuteImage;
        /**
          * The name of the sound category that the silence button will
          * silence and unsilence.
          */
        const std::string m_soundCategory;
    };

} // namespace TA_Base_Bus


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SILENCEBUTTON_H__30A7F0A1_6BA3_4D7F_AC9B_937BC18C6B24__INCLUDED_)
