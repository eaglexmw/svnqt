/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef SVNCOMMITITEM_H
#define SVNCOMMITITEM_H

#include "client.h"

#include "svnqt_global.h"
#include <subversion-1/svn_types.h>
#include <apr.h>

// forward declarations
struct svn_client_commit_item_t;
// only used if build against svn 1.3 api
struct svn_client_commit_item2_t;
// only used if build against svn 1.5 api
struct svn_client_commit_item3_t;

namespace svn {

/**
	@author Rajko Albrecht <ral@alwins-world.de>
*/
class SVNQT_EXPORT CommitItem{

private:
    void init();
    void convertprop(apr_array_header_t *);

protected:
    PropertiesMap m_CommitProperties;
    QString m_Path,m_Url,m_CopyFromUrl;
    svn_node_kind_t m_Kind;
    svn_revnum_t m_Revision,m_CopyFromRevision;
    apr_byte_t m_State;

public:
    //! constructor
    CommitItem(const svn_client_commit_item_t*aSource=0);
    //! constructor
    /*!
     * This one will only do something if build against subversion 1.3
     */
    CommitItem(const svn_client_commit_item2_t*);
    /*!
     * This one will only do something if build against subversion 1.5
     */
    CommitItem(const svn_client_commit_item3_t*);
    //! Destructor
    /*!
     * Not virtual 'cause no child class is needed
     */
    ~CommitItem();

    const QString& path()const;
    const QString& url()const;
    const QString& copyfromurl()const;
    const PropertiesMap& properties()const;
    svn_revnum_t revision()const;
    svn_revnum_t copyfromrevision()const;
    svn_node_kind_t kind()const;
    apr_byte_t state()const;
    //! Kind of action
    /*!
     * \return Char for type of action or 0 if unknown. Currently known is
     * <UL>
     * <LI>A - add</LI>
     * <LI>C - copy</LI>
     * <LI>D - deletion</LI>
     * <LI>M - Modify (content or property)</LI>
     * <LI>R - replaced</LI>
     * <LI>L - (un-)lock</LI>
     * </UL>
     */
    char actionType()const;
};

}

#endif
