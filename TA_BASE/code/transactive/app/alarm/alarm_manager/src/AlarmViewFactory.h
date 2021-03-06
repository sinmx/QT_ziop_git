#if !defined(AlarmViewFactory_H)
#define AlarmViewFactory_H

//#include "bus/generic_gui_view/src/HelpLauncher.h"
//#include "bus/generic_gui_view/src/TransActiveMessage.h"
#include "bus/generic_gui_view/src/TransActiveWinApp.h"
//#include "bus/generic_gui_pmod/src/PModelInterface.h"

//#include "core/exceptions/src/GenericGUIException.h"
//#include "core/exceptions/src/ProcessAlreadyRunningException.h"
//#include "core/exceptions/src/CannotUseSysControllerException.h"
//#include "core/exceptions/src/UserCancelException.h"

//#include "core/threads/src/Thread.h"
//#include "core/utilities/src/DebugUtil.h"
//#include "core/utilities/src/RunParams.h"
//#include "core/utilities/src/TAAssert.h"
//#include "core/message/src/MessagePublicationManager.h"
//#include "core/message/src/AuditMessageSender.h"
//#include "core/message/src/NameValuePair.h"
//#include "core/message/types/ApplicationStatusAudit_MessageTypes.h"


 

//using TA_Base_Core::GenericGUIException;
//using TA_Base_Core::DebugUtil;
//using TA_Base_Core::RunParams;
//using TA_Base_Bus::TransActiveWinApp;

namespace TA_Base_App
{

	class AlarmViewFactory : public TA_Base_Bus::IViewFactory
	{	

	public:

		AlarmViewFactory(TA_Base_Bus::ITransActiveApp* winApp);
		virtual ~AlarmViewFactory(){};
		/** get the view based on specific name
		* 
		*
		* @param viewType
		* @param viewID
		* @return ITransActiveView *
		*/
		TA_Base_Bus::ITransActiveView * AlarmViewFactory::createView(const char * viewType);

	private:
		TA_Base_Bus::ITransActiveApp* m_winApp;
		 
	};

} // namespace TA_Base_App

#endif