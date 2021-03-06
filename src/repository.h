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
 
#ifndef SVNREPOSITORY_H
#define SVNREPOSITORY_H

// Ignore MSVC 7, 2005 & 2008 compiler warning: C++ exception specification
#if defined (_MSC_VER) && _MSC_VER > 1200 && _MSC_VER <= 1550
#pragma warning (disable: 4290)
#endif

#include "svnqt_global.h"
#include "exception.h"
#include "revision.h"

#include <qstring.h>

namespace svn {

namespace repository {

class RepositoryData;
class RepositoryListener;
class CreateRepoParameter;

//! wrapper class for subversions administrative repository functions
/*!
    \author Rajko Albrecht <ral@alwins-world.de>
*/
class SVNQT_EXPORT Repository{
public:
    enum LOAD_UUID {
        UUID_DEFAULT_ACTION = 0,
        UUID_IGNORE_ACTION = 1,
        UUID_FORCE_ACTION = 2
    };
    //! constructor
    /*!
     * \param aListener callback object, the object will NOT take the ownership.
     */
    Repository(svn::repository::RepositoryListener*aListener);
    //! destructor
    virtual ~Repository();

    //! open a local repository path for maintenance
    /*!
        Assigns a repository with that object. If a path was opened before it will closed.
        \param path Path to a local repository, must not be an url
        \exception ClientException will be thrown in case of an error
     */
    void Open(const QString&path) throw (ClientException);
    //! Creates and open a new repository
    /*!
     * Creates a new repository in path with type fstype. If create succeeded open and assigns with the object.
     * If a repository was opened before it will closed.
     * @param params All values needed
     */
    void CreateOpen(const CreateRepoParameter&params) throw (ClientException);
    //! dump content of repository to a file
    /*!
        The repository must opened before. Progress message go trough the assigned svn::repository::RepositoryListener object.
        The revision parameter must be numbers, no constant values like svn::Revision::HEAD.
        \param output where to output the content
        \param start Begin on revision. If revision == -1 than start with first entry.
        \param end End with revision.  If revision == -1 than end with current head.
        \param incremental dump incrementally
        \param use_deltas use deltas in dump output
        \exception ClientException will be thrown in case of an error
     */
    void dump(const QString&output,const svn::Revision&start,const svn::Revision&end, bool incremental, bool use_deltas)throw (ClientException);
    //! load a dump into repository
    /*!
        The repository must opened before. Progress message go trough the assigned svn::repository::RepositoryListener object.
        \param dump Dumpfile to load
        \param uuida what to do with UUIDs
        \param parentFolder put content of dumpstream within folder in repository, if empty put into root-folder.
        \param usePre use pre-commit-hook
        \param usePost use post-commit-hook
        \exception ClientException will be thrown in case of an error
     */
    void loaddump(const QString&dump,LOAD_UUID uuida, const QString&parentFolder, bool usePre, bool usePost)throw (ClientException);
    //! copy a repository to a new location
    /*!
        \param src the repository path to copy
        \param dest where to copy
        \param cleanlogs remove redundand log files from source
        \exception ClientException will be thrown in case of an error
     */
    static void hotcopy(const QString&src,const QString&dest,bool cleanlogs)throw (ClientException);

private:
    RepositoryData*m_Data;
};

}

}

#endif
