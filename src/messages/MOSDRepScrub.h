// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */


#ifndef CEPH_MOSDREPSCRUB_H
#define CEPH_MOSDREPSCRUB_H

#include "msg/Message.h"

/*
 * instruct an OSD initiate a replica scrub on a specific PG
 */

struct MOSDRepScrub : public Message {
  pg_t pgid;             // PG to scrub
  eversion_t scrub_from; // only scrub log entries after scrub_from
  eversion_t scrub_to;   // last_update_applied when message sent
  epoch_t map_epoch;

  MOSDRepScrub() {}
  MOSDRepScrub(pg_t pgid, eversion_t scrub_from, eversion_t scrub_to,
	       epoch_t map_epoch) :
    Message(MSG_OSD_REP_SCRUB),
    pgid(pgid),
    scrub_from(scrub_from),
    scrub_to(scrub_to),
    map_epoch(map_epoch) {}
  
private:
  ~MOSDRepScrub() {}

public:
  const char *get_type_name() { return "replica scrub"; }
  void print(ostream& out) {
    out << "replica scrub(pg: ";
    out << pgid << ",from:" << scrub_from << ",to:" << scrub_to
	<< "epoch:" << map_epoch;
    out << ")";
  }

  void encode_payload(CephContext *cct) {
    __u8 v = 0;
    ::encode(v, payload);
    ::encode(pgid, payload);
    ::encode(scrub_from, payload);
    ::encode(scrub_to, payload);
    ::encode(map_epoch, payload);
  }
  void decode_payload(CephContext *cct) {
    __u8 v = -1;
    bufferlist::iterator p = payload.begin();
    ::decode(v, p);
    assert(v == 0);
    ::decode(pgid, p);
    ::decode(scrub_from, p);
    ::decode(scrub_to, p);
    ::decode(map_epoch, p);
  }
};

#endif
