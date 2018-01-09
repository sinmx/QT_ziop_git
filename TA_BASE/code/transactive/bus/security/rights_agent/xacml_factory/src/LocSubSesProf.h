#if !defined(LOCSUBSESPROF_H_INCLUDED)
#define LOCSUBSESPROF_H_INCLUDED

/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/security/rights_agent/xacml_factory/src/LocSubSesProf.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2015/10/09 15:42:35 $
 * Last modified by:  $Author: CM $
 *
 */

namespace TA_Base_Bus
{
	struct LocSubSesProf
	{
		LocSubSesProf( const unsigned long location, const unsigned long subsystem,
			const std::string& sessionId, const unsigned long profile );

		bool operator==(const LocSubSesProf& rhs) const;
		bool operator< (const LocSubSesProf& rhs) const;

		const unsigned long m_location;
		const unsigned long m_subsystem;
		const std::string   m_sessionId;
		const unsigned long m_profile;
	};

	
}

#endif // !defined(LOCSUBSESPROF_H_INCLUDED)