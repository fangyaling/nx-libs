/**************************************************************************/
/*                                                                        */
/* Copyright (c) 2001, 2011 NoMachine (http://www.nomachine.com)          */
/* Copyright (c) 2008-2014 Oleksandr Shneyder <o.shneyder@phoca-gmbh.de>  */
/* Copyright (c) 2014-2016 Ulrich Sibiller <uli42@gmx.de>                 */
/* Copyright (c) 2014-2016 Mihai Moldovan <ionic@ionic.de>                */
/* Copyright (c) 2011-2016 Mike Gabriel <mike.gabriel@das-netzwerkteam.de>*/
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

#ifndef PolyLine_H
#define PolyLine_H

#include "Message.h"

//
// Set the verbosity level.
//

#define PANIC
#define WARNING
#undef  TEST
#undef  DEBUG
#undef  DUMP

//
// Set default values.
//

#define POLYLINE_ENABLE_CACHE               1
#define POLYLINE_ENABLE_DATA                0
#define POLYLINE_ENABLE_SPLIT               0
#define POLYLINE_ENABLE_COMPRESS            0

#define POLYLINE_DATA_LIMIT                 144
#define POLYLINE_DATA_OFFSET                12

#define POLYLINE_CACHE_SLOTS                3000
#define POLYLINE_CACHE_THRESHOLD            3
#define POLYLINE_CACHE_LOWER_THRESHOLD      1

//
// The message class.
//

class PolyLineMessage : public Message
{
  friend class PolyLineStore;

  public:

  PolyLineMessage()
  {
  }

  ~PolyLineMessage()
  {
  }

  //
  // Put here the fields which constitute
  // the 'identity' part of the message.
  //

  private:

  unsigned char mode;
  unsigned int  drawable;
  unsigned int  gcontext;
};

class PolyLineStore : public MessageStore
{
  //
  // Constructors and destructors.
  //

  public:

  PolyLineStore() : MessageStore()
  {
    enableCache    = POLYLINE_ENABLE_CACHE;
    enableData     = POLYLINE_ENABLE_DATA;
    enableSplit    = POLYLINE_ENABLE_SPLIT;
    enableCompress = POLYLINE_ENABLE_COMPRESS;

    dataLimit  = POLYLINE_DATA_LIMIT;
    dataOffset = POLYLINE_DATA_OFFSET;

    cacheSlots          = POLYLINE_CACHE_SLOTS;
    cacheThreshold      = POLYLINE_CACHE_THRESHOLD;
    cacheLowerThreshold = POLYLINE_CACHE_LOWER_THRESHOLD;

    messages_ -> resize(cacheSlots);

    for (T_messages::iterator i = messages_ -> begin();
             i < messages_ -> end(); i++)
    {
      *i = NULL;
    }

    temporary_ = NULL;
  }

  virtual ~PolyLineStore()
  {
    for (T_messages::iterator i = messages_ -> begin();
             i < messages_ -> end(); i++)
    {
      destroy(*i);
    }

    destroy(temporary_);
  }

  virtual const char *name() const
  {
    return "PolyLine";
  }

  virtual unsigned char opcode() const
  {
    return X_PolyLine;
  }

  virtual unsigned int storage() const
  {
    return sizeof(PolyLineMessage);
  }

  //
  // Message handling methods.
  //

  public:

  virtual Message *create() const
  {
    return new PolyLineMessage();
  }

  virtual Message *create(const Message &message) const
  {
    return new PolyLineMessage((const PolyLineMessage &) message);
  }

  virtual void destroy(Message *message) const
  {
    delete (PolyLineMessage *) message;
  }

  virtual int parseIdentity(Message *message, const unsigned char *buffer,
                                unsigned int size, int bigEndian) const;

  virtual int unparseIdentity(const Message *message, unsigned char *buffer,
                                  unsigned int size, int bigEndian) const;

  virtual void updateIdentity(EncodeBuffer &encodeBuffer, const Message *message,
                                  const Message *cachedMessage,
                                      ChannelCache *channelCache) const;

  virtual void updateIdentity(DecodeBuffer &decodeBuffer, const Message *message,
                                  ChannelCache *channelCache) const;

  virtual void identityChecksum(const Message *message, const unsigned char *buffer,
                                    unsigned int size, int bigEndian) const;

  virtual void dumpIdentity(const Message *message) const;
};

#endif /* PolyLine_H */
