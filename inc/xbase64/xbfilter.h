/*  xbfilter.h

    Xbase project source code
  
    This file conatains a header file for the xbFilter object which
    is used for filtering data.

    Copyright (C) 1997,2003  Gary A Kunkel
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    Contact:
    
     Email:
    
      xdb-devel@lists.sourceforge.net
      xdb-users@lists.sourceforge.net
      
      
     Regular Mail:
     
       XBase Support
       149C South Main St
       Keller Texas, 76248     
       USA
*/

/*! \file xbfilter.h
*/

#ifndef __XB_FILTER_H__
#define __XB_FILTER_H__

//#ifdef __GNU LesserG__
//#pragma interface
//#endif

//! xbFilter class
/*!
*/

class XBDLLEXPORT xbFilter
{
public:
  xbFilter( xbDbf * dbf, xbIndex * index, char * expression );
  virtual ~xbFilter();

  xbShort GetFirstFilterRec();
  xbShort GetLastFilterRec();
  xbShort GetNextFilterRec();
  xbShort GetPrevFilterRec();
  xbShort GetStatus() { return Status; }

protected:
  xbULong CurFilterRecNo;
  xbShort Status;
  xbExpn * flExpn;
  xbDbf *d;
  xbIndex *i;
};

#endif
