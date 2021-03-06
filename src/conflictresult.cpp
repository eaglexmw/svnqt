/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA 02110-1301 USA
 */
 

#include "conflictresult.h"


#include <subversion-1/svn_wc.h>

namespace svn
{
    ConflictResult::ConflictResult()
    :m_choice(ChooseMerged),m_MergedFile()
    {
    }

    ConflictResult::ConflictResult(const svn_wc_conflict_result_t*aResult)
    {
        if (!aResult){
            return;
        }
#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
        switch (aResult->choice){
            case svn_wc_conflict_choose_base:
                m_choice=ChooseBase;
                break;
            case svn_wc_conflict_choose_theirs_full:
                m_choice=ChooseTheirsFull;
                break;
            case svn_wc_conflict_choose_mine_full:
                m_choice=ChooseMineFull;
                break;
            case svn_wc_conflict_choose_theirs_conflict:
                m_choice=ChooseTheirsConflict;
                break;
            case svn_wc_conflict_choose_mine_conflict:
                m_choice=ChooseMineConflict;
                break;
            case svn_wc_conflict_choose_merged:
                m_choice=ChooseMerged;
                break;
            case svn_wc_conflict_choose_postpone:
            default:
                m_choice=ChoosePostpone;
                break;
        }
        if (aResult->merged_file) {
            m_MergedFile=QString::fromUtf8(aResult->merged_file);
        } else {
            m_MergedFile.clear();
        }
#else
        Q_UNUSED(aResult);
#endif
    }

    void ConflictResult::setMergedFile(const QString&aMergedfile) {
        m_MergedFile=aMergedfile;
    }

    void ConflictResult::setChoice(ConflictChoice aValue)
    {
        m_choice=aValue;
    }

    void ConflictResult::assignResult(svn_wc_conflict_result_t**aResult,const Pool&pool)const
    {
#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
        svn_wc_conflict_choice_t _choice;
        switch (choice()) {
            case ConflictResult::ChooseBase:
                _choice=svn_wc_conflict_choose_base;
                break;
            case ConflictResult::ChooseTheirsFull:
                _choice=svn_wc_conflict_choose_theirs_full;
                break;
            case ConflictResult::ChooseMineFull:
                _choice=svn_wc_conflict_choose_mine_full;
                break;
            case ConflictResult::ChooseTheirsConflict:
                _choice=svn_wc_conflict_choose_theirs_conflict;
                break;
            case ConflictResult::ChooseMineConflict:
                _choice=svn_wc_conflict_choose_mine_conflict;
                break;
            case ConflictResult::ChooseMerged:
                _choice=svn_wc_conflict_choose_merged;
                break;
            case ConflictResult::ChoosePostpone:
            default:
                _choice=svn_wc_conflict_choose_postpone;
                break;

        }
        const char* _merged_file = mergedFile().isNull()?0:apr_pstrdup (pool,mergedFile().toUtf8());
        if ((*aResult)==0) {
            (*aResult) = svn_wc_create_conflict_result(_choice,_merged_file,pool);
        } else {
            (*aResult)->choice=_choice;
            (*aResult)->merged_file=_merged_file;
        }
#else
        Q_UNUSED(aResult);
        Q_UNUSED(pool);
#endif
    }

    const svn_wc_conflict_result_t*ConflictResult::result(const Pool&pool)const
    {
        svn_wc_conflict_result_t*result=0;
        assignResult(&result,pool);
        return result;
    }
}
