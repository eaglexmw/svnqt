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
 
#ifndef SVNQT_INFO_ENTRY_H
#define SVNQT_INFO_ENTRY_H

#include "svnqt_global.h"
#include "lock_entry.h"
#include "datetime.h"
#include "revision.h"
#include "svnqttypes.h"

#include <qstring.h>

struct svn_info_t;

namespace svn {
  class SVNQT_EXPORT InfoEntry
  {
public:
    InfoEntry();
    InfoEntry(const svn_info_t*,const char*path);
    InfoEntry(const svn_info_t*,const QString&path);
    InfoEntry(const InfoEntry&);
    ~InfoEntry();

    void init(const svn_info_t*,const char*path);
    void init(const svn_info_t*,const QString&path);

    DateTime cmtDate()const;
    DateTime textTime()const;
    DateTime propTime()const;
    bool hasWc()const;
    /**
     * @return lock for that entry
     * @since subversion 1.2
     */
    const LockEntry&lockEntry()const;
    /**
     * @return last commit author of this file
     */
    const QString&cmtAuthor () const;
    const QString&Name()const;

    const QString& checksum()const;
    const QString& conflictNew()const;
    const QString& conflictOld()const;
    const QString& conflictWrk()const;
    const QString& copyfromUrl()const;
    const QString& prejfile()const;
    const QString& reposRoot()const;
    const QString& url()const;
    const QString& uuid()const;
    svn_node_kind_t kind()const;
    const Revision& cmtRev()const;
    const Revision& copyfromRev()const;
    const Revision& revision()const;
    svn_wc_schedule_t Schedule()const;

    qlonglong size()const;
    qlonglong working_size()const;
    const QByteArray&changeList()const;
    svn::Depth depth()const;

    const QString&prettyUrl()const;

    bool isDir()const;
    QString prettyUrl(const char*)const;

protected:
    DateTime m_last_changed_date;
    DateTime m_text_time;
    DateTime m_prop_time;
    bool m_hasWc;
    LockEntry m_Lock;
    QString m_name;
    QString m_checksum;
    QString m_conflict_new;
    QString m_conflict_old;
    QString m_conflict_wrk;
    QString m_copyfrom_url;
    QString m_last_author;
    QString m_prejfile;
    QString m_repos_root;
    QString m_url;
    QString m_pUrl;
    QString m_UUID;
    svn_node_kind_t m_kind;
    Revision m_copy_from_rev;
    Revision m_last_changed_rev;
    Revision m_revision;
    svn_wc_schedule_t m_schedule;

    qlonglong m_size;
    qlonglong m_working_size;
    QByteArray m_changeList;
    svn::Depth m_depth;

protected:
    void init();
  };
}
#endif
