/*
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
* Copyright (C) Gao Peng, 2015

* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.

* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.

* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the Free
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

* ---------------------------------------------------------------------
* ECDictionary.h
*
* define a Dictionary which can store any type of data.
*
* [Note:] Key class type, must have the == opration implementation
*
* Eamil:  epengao@126.com
* Author: Gao Peng
* Version: First initinal version.
* --------------------------------------------------------------------
*/

#ifndef EC_DICTIONARY_H
#define EC_DICTIONARY_H

#include "ECMutableArray.h"


template<typename KeyT, typename ValT>
class ECDictionary
{
public:
    ECDictionary();
    ~ECDictionary();

public:
    EC_U32 AddItem(const KeyT key, const ValT value);
    EC_U32 DeleteItem(const KeyT key);
    EC_U32 GetItem(const KeyT key, ValT* value) const;
    EC_BOOL IsEmpty() const;
    EC_U32  GetItemsCount() const;
    EC_VOID DeleteAllItems();

private:
    EC_U32 FindItemPos(const KeyT key) const;

private:
    ECMutableArray<ECPairNode<KeyT,ValT>>*  m_pContainer;
};

template<typename KeyT, typename ValT>
ECDictionary<KeyT,ValT>::ECDictionary()
{
    m_pContainer = new ECMutableArray<ECPairNode<KeyT,ValT>>();
}

template<typename KeyT, typename ValT>
ECDictionary<KeyT,ValT>::~ECDictionary()
{
    if(m_pContainer) delete m_pContainer;
}


template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::AddItem(const KeyT key, const ValT value)
{
    return m_pContainer->InsertToTail(ECPairNode<KeyT,ValT>(key,value));
}

template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::DeleteItem(const KeyT key)
{
    EC_U32 nPos = FindObjectPos(key);
    return m_pContainer->DeleteAtIndex(nPos);
}

template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::GetItem(const KeyT key, ValT* pValue) const
{
    EC_U32 nPos = FindObjectPos(key);

    ECPairNode<KeyT,ValT> pare;
    EC_U32 nRet = m_pContainer->GetItemAtIndex(&pare, nPos);
    if(EC_Err_None == nRet)
    {
        *pValue = pare.m_sVal;
    }
    return nRet;
}

template<typename KeyT, typename ValT>
EC_BOOL ECDictionary<KeyT,ValT>::IsEmpty() const
{
    return (0 == m_pContainer->GetItemsCount());
}

template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::GetItemsCount() const
{
    return m_pContainer->GetItemsCount();
}

template<typename KeyT, typename ValT>
EC_VOID ECDictionary<KeyT,ValT>::DeleteAllItems()
{
    if(m_pContainer) delete m_pContainer;
    m_pContainer = new ECMutableArray<ECPairNode<KeyT,ValT>>();
}

/* privare function */
template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::FindItemPos(const KeyT key) const
{
    EC_U32 nPos = EC_U32_MAX;

    EC_U32 nCount = m_pContainer->GetItemsCount();
    ECPairNode<KeyT,ValT> pare;
    for(EC_U32 i=0; i<nCount; ++i)
    {
        EC_U32 nRet = m_pContainer->GetItemAtIndex(&pare, i);
        if((EC_Err_None == nRet) && (key == pare.m_sKey))
        {
            nPos = i;
            break;
        }
    }

    return nPos;
}


#endif /* EC_DICTIONARY_H */
