/**************************************************************************/
/*                                                                        */
/* Copyright (c) 2001, 2011 NoMachine (http://www.nomachine.com)          */
/* Copyright (c) 2008-2017 Oleksandr Shneyder <o.shneyder@phoca-gmbh.de>  */
/* Copyright (c) 2014-2022 Ulrich Sibiller <uli42@gmx.de>                 */
/* Copyright (c) 2014-2019 Mihai Moldovan <ionic@ionic.de>                */
/* Copyright (c) 2011-2022 Mike Gabriel <mike.gabriel@das-netzwerkteam.de>*/
/* Copyright (c) 2015-2016 Qindel Group (http://www.qindel.com)           */
/*                                                                        */
/* NXCOMP, NX protocol compression and NX extensions to this software     */
/* are copyright of the aforementioned persons and companies.             */
/*                                                                        */
/* Redistribution and use of the present software is allowed according    */
/* to terms specified in the file LICENSE.nxcomp which comes in the       */
/* source distribution.                                                   */
/*                                                                        */
/* All rights reserved.                                                   */
/*                                                                        */
/* NOTE: This software has received contributions from various other      */
/* contributors, only the core maintainers and supporters are listed as   */
/* copyright holders. Please contact us, if you feel you should be listed */
/* as copyright holder, as well.                                          */
/*                                                                        */
/**************************************************************************/

#ifndef List_H
#define List_H

#include "Misc.h"
#include "Types.h"

//
// Set the verbosity level.
//

#define PANIC
#define WARNING
#undef  TEST
#undef  DEBUG

//
// Define this to log when lists are
// allocated and deallocated.
//

#undef  REFERENCES

class List
{
  public:

  List();

  ~List();

  int getSize()
  {
    return list_.size();
  }

  T_list &getList()
  {
    return list_;
  }

  T_list copyList()
  {
    return list_;
  }

  void add(int value)
  {
    list_.push_back(value);
  }

  void remove(int value);

  void rotate();

  private:

  //
  // The list container.
  //

  T_list list_;

  #ifdef REFERENCES

  static int references_;

  #endif
};

#endif /* List_H */
