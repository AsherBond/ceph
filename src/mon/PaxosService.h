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

#ifndef CEPH_PAXOSSERVICE_H
#define CEPH_PAXOSSERVICE_H

#include "messages/PaxosServiceMessage.h"
#include "include/Context.h"
#include "Paxos.h"

class Monitor;
class Paxos;

class PaxosService {
public:
  Monitor *mon;
  Paxos *paxos;
  
protected:
  class C_RetryMessage : public Context {
    PaxosService *svc;
    PaxosServiceMessage *m;
  public:
    C_RetryMessage(PaxosService *s, PaxosServiceMessage *m_) : svc(s), m(m_) {}
    void finish(int r) {
      svc->dispatch(m);
    }
  };
  class C_Active : public Context {
    PaxosService *svc;
  public:
    C_Active(PaxosService *s) : svc(s) {}
    void finish(int r) {
      if (r >= 0) 
	svc->_active();
    }
  };

  class C_Propose : public Context {
    PaxosService *ps;
  public:
    C_Propose(PaxosService *p) : ps(p) { }
    void finish(int r) { 
      ps->proposal_timer = 0;
      ps->propose_pending(); 
    }
  };	
  friend class C_Propose;
  

private:
  Context *proposal_timer;
  bool have_pending;

public:
  PaxosService(Monitor *mn, Paxos *p) : mon(mn), paxos(p),
					proposal_timer(0),
					have_pending(false) { }
  virtual ~PaxosService() {}

  const char *get_machine_name();
  
  // i implement and you ignore
  void restart();
  void election_finished();
  void shutdown();

private:
  void _active();

public:
  // i implement and you use
  void propose_pending();     // propose current pending as new paxos state
  bool dispatch(PaxosServiceMessage *m);

  // you implement
  /*
   * Create the initial state for your system.
   * In some of ours the state is actually set up
   * elsewhere so this does nothing.
   */
  virtual void create_initial() = 0;

  /*
   * Query the Paxos system for the latest state and apply it if
   * it's newer than the current Monitor state.
   * Return true on success.
   */
  virtual void update_from_paxos() = 0;

  /*
   * This function is only called on a leader. Create the pending state.
   * (this created state is then modified by incoming messages).
   * Called at startup and after every Paxos ratification round.
   */
  virtual void create_pending() = 0;

  /*
   * This function is only called on a leader. Encode the pending state
   * into a bufferlist for ratification and transmission
   * as the next state.
   */
  virtual void encode_pending(bufferlist& bl) = 0;

  /*
   * As this function is NOT overridden in any of our code,
   * but it is called in election_finished if have_pending.
   */
  virtual void discard_pending() { }       // [leader] discard pending

  /*
   * Look at the query; if the query can be handled without changing
   * state, do so.
   * Return true if the query was handled (ie, was a read that got answered,
   * was a state change that has no effect), false otherwise.
   */
  virtual bool preprocess_query(PaxosServiceMessage *m) = 0;

  /*
   * This function is only called on the leader. Apply the message
   * to the pending state.
   */
  virtual bool prepare_update(PaxosServiceMessage *m) = 0;

  /*
   * Determine if the Paxos system should vote on pending, and
   * if so how long it should wait to vote.
   * Returns true if the Paxos system should propose,
   * and fills in the delay paramater with the wait time
   * (so you can limit update traffic spamming).
   */
  virtual bool should_propose(double &delay);

  /*
   * This is called when the Paxos state goes to active.
   * It's a courtesy method if you have things you want/need
   * to do at that time.
   *
   * Note that is may get called twice in certain recovery cases.
   */
  virtual void on_active() { }

  /*
   * Another courtesy method. Called when the Paxos
   * system enters a leader election.
   */
  virtual void on_restart() { }

  virtual void tick() {}

  /**
   * get health information
   *
   * @param summary list of summary strings and associated severity
   * @param detail optional list of detailed problem reports; may be NULL
   */
  virtual void get_health(list<pair<health_status_t,string> >& summary,
			  list<pair<health_status_t,string> > *detail) const { }

 protected:

  /**
   * Get our version.
   *
   * @remarks currently we simply defer to Paxos
   *
   * @returns Our version.
   */
  version_t get_version() { return paxos->get_version(); }

  /**
   * @defgroup PaxosService_h_store_funcs Back storage interface functions
   * @{
   */
  /**
   * @defgroup PaxosService_h_store_funcs_write Write
   * @{
   */
  int put(string dir, string name, bufferlist& bl);
  int put(string dir, version_t ver, bufferlist& bl);
  int put(string dir, string name, version_t ver);
  int append(string dir, string name, bufferlist& bl);
  int erase(string dir, string name);
  int erase(string dir, version_t ver);
  /**
   * @}
   */
  /**
   * @defgroup PaxosService_h_store_funcs_read Read
   * @{
   */
  int get(string dir, string name, bufferlist& bl);
  int get(string dir, version_t ver, bufferlist& bl);
  version_t get(string dir, string name);
  /**
   * @}
   */
  /**
   * @}
   */
};

#endif

