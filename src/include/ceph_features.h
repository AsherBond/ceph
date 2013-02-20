#ifndef __CEPH_FEATURES
#define __CEPH_FEATURES

/*
 * feature bits
 */
#define CEPH_FEATURE_UID            (1<<0)
#define CEPH_FEATURE_NOSRCADDR      (1<<1)
#define CEPH_FEATURE_MONCLOCKCHECK  (1<<2)
#define CEPH_FEATURE_FLOCK          (1<<3)
#define CEPH_FEATURE_SUBSCRIBE2     (1<<4)
#define CEPH_FEATURE_MONNAMES       (1<<5)
#define CEPH_FEATURE_RECONNECT_SEQ  (1<<6)
#define CEPH_FEATURE_DIRLAYOUTHASH  (1<<7)
#define CEPH_FEATURE_OBJECTLOCATOR  (1<<8)
#define CEPH_FEATURE_PGID64         (1<<9)
#define CEPH_FEATURE_INCSUBOSDMAP   (1<<10)
#define CEPH_FEATURE_PGPOOL3        (1<<11)
#define CEPH_FEATURE_OSDREPLYMUX    (1<<12)
#define CEPH_FEATURE_OSDENC         (1<<13)
#define CEPH_FEATURE_OMAP           (1<<14)
#define CEPH_FEATURE_MONENC         (1<<15)
#define CEPH_FEATURE_QUERY_T        (1<<16)
#define CEPH_FEATURE_INDEP_PG_MAP   (1<<17)
#define CEPH_FEATURE_CRUSH_TUNABLES (1<<18)
#define CEPH_FEATURE_CHUNKY_SCRUB   (1<<19)
#define CEPH_FEATURE_MON_NULLROUTE  (1<<20)
#define CEPH_FEATURE_MON_GV         (1<<21)
#define CEPH_FEATURE_BACKFILL_RESERVATION (1<<22)
#define CEPH_FEATURE_MSG_AUTH	    (1<<23)
#define CEPH_FEATURE_RECOVERY_RESERVATION (1<<24)
#define CEPH_FEATURE_CRUSH_TUNABLES2 (1<<25)
#define CEPH_FEATURE_CREATEPOOLID   (1<<26)
#define CEPH_FEATURE_REPLY_CREATE_INODE   (1<<27)
#define CEPH_FEATURE_OSD_HBMSGS     (1<<28)
#define CEPH_FEATURE_MDSENC         (1<<29)
#define CEPH_FEATURE_OSDHASHPSPOOL  (1<<30)

/*
 * Features supported.  Should be everything above.
 */
#define CEPH_FEATURES_ALL		 \
	(CEPH_FEATURE_UID |		 \
	 CEPH_FEATURE_NOSRCADDR |	 \
	 CEPH_FEATURE_MONCLOCKCHECK |	 \
	 CEPH_FEATURE_FLOCK |		 \
	 CEPH_FEATURE_SUBSCRIBE2 |	 \
	 CEPH_FEATURE_MONNAMES |	 \
	 CEPH_FEATURE_RECONNECT_SEQ |	 \
	 CEPH_FEATURE_DIRLAYOUTHASH |	 \
	 CEPH_FEATURE_OBJECTLOCATOR |	 \
	 CEPH_FEATURE_PGID64 |		 \
	 CEPH_FEATURE_INCSUBOSDMAP |	 \
	 CEPH_FEATURE_PGPOOL3 |		 \
	 CEPH_FEATURE_OSDREPLYMUX |	 \
	 CEPH_FEATURE_OSDENC |		 \
	 CEPH_FEATURE_OMAP |		 \
	 CEPH_FEATURE_QUERY_T |		 \
	 CEPH_FEATURE_MONENC |		 \
	 CEPH_FEATURE_INDEP_PG_MAP |	 \
	 CEPH_FEATURE_CRUSH_TUNABLES |	 \
	 CEPH_FEATURE_CHUNKY_SCRUB |	 \
	 CEPH_FEATURE_MON_NULLROUTE |	 \
	 CEPH_FEATURE_MON_GV |		 \
	 CEPH_FEATURE_BACKFILL_RESERVATION | \
	 CEPH_FEATURE_MSG_AUTH |	     \
	 CEPH_FEATURE_RECOVERY_RESERVATION | \
	 CEPH_FEATURE_CRUSH_TUNABLES2 |	     \
	 CEPH_FEATURE_CREATEPOOLID |	     \
	 CEPH_FEATURE_REPLY_CREATE_INODE |   \
	 CEPH_FEATURE_OSD_HBMSGS |		\
	 CEPH_FEATURE_MDSENC |			\
	 CEPH_FEATURE_OSDHASHPSPOOL)

#define CEPH_FEATURES_SUPPORTED_DEFAULT  CEPH_FEATURES_ALL

/*
 * crush related features
 */
#define CEPH_FEATURES_CRUSH			\
	(CEPH_FEATURE_CRUSH_TUNABLES |		\
	 CEPH_FEATURE_CRUSH_TUNABLES2)

#endif
