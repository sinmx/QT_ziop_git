/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/configuration/config_plugins/event_plan_association/src/EventPlanAssocDatabaseAccessor.h $
  * @author:  Brad Cleaver
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  * This class uses the Data Access Interface to retrieve event plan association information and returns it to
  * the caller in a variety of formats. It abstracts some of the database access from the views.
  * 
  */


#if !defined(_EVENT_PLAN_ASSOC_DATABASE_ACCESSOR_H_)
#define _EVENT_PLAN_ASSOC_DATABASE_ACCESSOR_H_

#include <map>
#include <vector>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/IDatabaseAccessor.h"

// Forward declarations
namespace TA_Base_Core
{
    class IConfigEventPlanAssocData;
    class IConfigItem;
}


namespace TA_Base_App
{
    class EventPlanAssocDatabaseAccessor : public IDatabaseAccessor
    {

    public:

        struct EventPlanAssociation
        {
            CString status;     // This will be the current applied status of the item (ie new, modified etc)
                                // It will be set elsewhere so we don't worry about it
            bool enabled;       // Specifies whether the association is active.
            CString entity;     // The entity name or blank.
            CString entityType; // The entity type name or blank.
            CString eventType;  // The event type name.
            CString plan;       // The plan name.
        };


        /**
         * Constructor
         */
        EventPlanAssocDatabaseAccessor();


        /**
         * Destructor
         */
        virtual ~EventPlanAssocDatabaseAccessor();


        /**
         * loadItems
         *
         * This will retrieve all the event plan associations from the database and store them in m_eventPlanAssocs.
         *
         * @exception DataException - This will be thrown if there is an error with the event plan association
         *                            data and it cannot be retrieved for some reason.
         * @exception DatabaseException - This will be thrown if there is an error communicating with the
         *                                database.
         */
        void loadItems();

        
        /**
         * getItemNames
         *
         * This method cannot be used by event plan associations and will just assert
         */
        std::map<CString,unsigned long> getItemNames(CProgressCtrl& progress);
        

        /**
         * getAllItemDetails
         *
         * This retrieves the items' details in a display format.
         * Precondition: loadItems() must be called before this method
         * 
         * @param CProgressCtrl - This is used to show how long the loading is taking
         *
         * @return map<unsigned long, EventPlanAssociation> - This is all the event plan assocations keyed
         *                                                    on their unique identifier
         */
        std::map<unsigned long,EventPlanAssociation> getAllItemDetails(CProgressCtrl& progress);
        
        
        /**
         * getItemDetails
         *
         * This retrieves the item's details in a display format. The items is specified by passing
         * in its unique identifier.
         * Precondition: loadItems() must be called before this method
         * 
         * @param unsigned long - The identifier of the item to retrieve details for
         *
         * @return EventPlanAssociation - This is all the event plan assocation details
         */
        EventPlanAssociation getItemDetails(unsigned long identifier);
 
        
        /**
         * getItem
         *
         * This returns a database object for the item specified. The item is specified by
         * passing in its unique identifier..
         * Precondition: loadItems() must be called before this method
         *
         * @param unsigned long - The identifier of the item to retrieve
         *
         * @return IConfigItem* - The database object for this item. This will be NULL if one
         *                            is not found.
         */
        virtual TA_Base_Core::IConfigItem* getItem(unsigned long identifier);


        /**
         * deleteItem
         *
         * This will delete the specified item from the database and it will then delete the
         * IConfigItem object held.
         *
         * @param unsigned long - This is the unique identifier for the item to delete
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is an error
         *                              deleting the item
         */
        virtual void deleteItem(unsigned long id);


        /**
         * newItem
         *
         * This creates a new item. This item will be added to the internal list
         * of current items but will not yet be applied to the database.
         *
         * @return IConfigItem* - The newly created item ready for its data to be populated
         */
        virtual TA_Base_Core::IConfigItem* newItem();


        /**
         * copyItem
         *
         * This creates a new item with the same data in it as the item passed in.
         * This item will be added to the internal list of current items but will not yet be
         * applied to the database.
         *
         * @param unsigned long - The unique identifier of the item to copy
         * 
         * @return IConfigItem* - The newly created item ready for its data to be populated
         *
         * @exception DatabaseException - This is thrown if data could not be retrieved for the item
         *                                that is being copied.
         */
        virtual TA_Base_Core::IConfigItem* copyItem(const unsigned long idOfItemToCopy);

        
        /**
         * areCurrentChangesPending
         *
         * This is called to determine if there are any current changes that have not been applied.
         * If this returns true then it will populate the vector of strings passed in with all items
         * not applied.
         * 
         * @param vector<string>& - This is an OUT parameter and should be passed in empty. It will
         *                          be populated with names for all data not yet applied
         * 
         * @return bool - This will return true if there are items that have had changes which have  not
         *                been applied.
         */
         bool areCurrentChangesPending(std::vector<std::string>& itemsNotApplied);

        
         /**
          * invalidate
          *
          * This will set m_isLoaded to false indicating that next time load is called all data should
          * be refreshed from the database.
          */
         void invalidateData()
         {
             m_isLoaded = false;
         }


        /**
         * getAllEventTypes
         *
         * This returns all event types and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the event type keys and names. This is all
         *                                      information needed to update data and to display to the user
         */
        std::map<unsigned long, std::string> getAllEventTypes();


        /**
         * getAllEntityTypes
         *
         * This returns all entity types and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the entity type keys and names. This is all
         *                                      information needed to update data and to display to the user
         */
        std::map<unsigned long, std::string> getAllEntityTypes();

    
    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        EventPlanAssocDatabaseAccessor( const EventPlanAssocDatabaseAccessor& theEventPlanAssocDatabaseAccessor){ };


        /**
         * Operator =
         *
         * Hidden as a private method so it is not used.
         */
        EventPlanAssocDatabaseAccessor& operator=(const EventPlanAssocDatabaseAccessor& pm);


        // This is a map of IConfigEventPlanAssoc* objects stored by their key (unsigned long)
        typedef std::map<unsigned long, TA_Base_Core::IConfigEventPlanAssocData*> LoadedAssociations;

        LoadedAssociations m_eventPlanAssocs;   // This is all the event plan associations loaded from the database

        bool m_isLoaded;          // This indicates if we have loaded the event plan associations before or not.
                                  // If we have never loaded the event plan associations then when we are told
                                  // to refresh we shouldn't load them.

    };
}

#endif // !defined(_EVENT_PLAN_ASSOC_DATABASE_ACCESSOR_H_)
