/*  xbfile.h

    Xbase project source code
  
    This file conatains a header file for the xbLock virtual objects which
    is used for controlling file and record locking.  Record and file
    locking has been rewritten in version 3.

    Copyright (C) 1997,2003,2004  Gary A Kunkel
                                  Sergio Yakovin
    
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

/*! \file xblock.h
*/

#ifndef __XB_FILE_H__
#define __XB_FILE_H__

//#ifdef __GNU LesserG__
//#pragma interface
//#endif

class XBDLLEXPORT xbFile
{
  public:
    xbFile(){}
    virtual const char* GetExtWithDot(bool lower)=0;
    const xbString& GetFileName() {return fileName_;}
    xbString MakeFileName(const char* filename);

  protected:
    void SetFileName(const char *filename) 
    {
      fileName_=MakeFileName(filename);
    }
    
  private:
    xbString fileName_;
};

#endif   // XBFILE_H
