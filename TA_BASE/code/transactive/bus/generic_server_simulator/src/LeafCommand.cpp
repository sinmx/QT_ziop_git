/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/generic_server_simulator/src/LeafCommand.cpp $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  */
#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32

#include "bus/generic_server_simulator/src/LeafCommand.h"


using namespace TA_Base_Bus;

LeafCommand::LeafCommand(CommandOwner * owner, const char * name)
: ICommand(owner, name)
{
}

bool LeafCommand::isCommand(const std::string & name) const
{
    return (name == getName());
}

bool LeafCommand::hasSubCommand(const std::string & name) const
{
    return false;
}

