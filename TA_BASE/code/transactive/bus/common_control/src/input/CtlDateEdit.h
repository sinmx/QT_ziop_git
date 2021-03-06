/**
* The source code in this file is the property of 
* ST Engineering Electronics (LSG) and is not for redistribution
* in any form.
*
* Source:   $File:   $
* @author:  Luo Huirong
* @version: $Revision: #1 $
*
* Last modification: $DateTime: 2015/11/20 16:15:14 $
* Last modified by:  $Author: Luo Huirong $
* 
* The class implement customized DateEdit widgets.
*  
*
*/


#ifndef _CtlDateEditH_
#define _CtlDateEditH_

#include <QtDesigner/QtDesigner>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDateEdit>
 
#include "bus/common_control/src/common/ctlCommonEnhance.h"

QT_BEGIN_NAMESPACE
 
class  QDESIGNER_WIDGET_EXPORT CtlDateEdit : public QDateEdit 
{
    Q_OBJECT       
public:	 
	/** Constructor function
	*
	*  @param parent
	*/
	explicit CtlDateEdit(QWidget* parent = 0);
	/** Destructor  function
	*
	*/
	virtual ~CtlDateEdit(); 

	void setToolTip(std::string str);
	void setWhatsThis(std::string str);

    /**
	* setDateTime
    *
	* This property holds the QDateTime that is set in the QDateTimeEdit.
	* When setting this property the timespec of the QDateTimeEdit remains the same and the timespec of the new QDateTime is ignored.
	* By default, this property contains a date that refers to January 1, 2000 and a time of 00:00 : 00 and 0 milliseconds.
	*
	* @param dateTime: QDateTime
	*/	 
	void setDateTime(const QDateTime &dateTime);

	///set the display format
	void setDisplayFormat(const std::string &format);

	/**
	* setObjectName
	*
	* set object name and accessible Name
	*/
	void setObjectName(const QString &name);
};
QT_END_NAMESPACE
 

#endif
