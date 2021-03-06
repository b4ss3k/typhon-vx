//TODO: this file shouldn't be part of the GSM Receiver
#ifndef __GSMSTACK_H__
#define __GSMSTACK_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

//#include <linux/if_ether.h>
#include "interleave.h"

#include <osmocom/bb/common/osmocom_data.h>
#include <l1ctl_proto.h>

enum BURST_TYPE {
        UNKNOWN = 0,
        FCCH,
        PARTIAL_SCH,            //successful correlation, but missing data ^
        SCH,
        CTS_SCH,
        COMPACT_SCH,
        NORMAL,
        DUMMY,
        ACCESS
};

enum TIMESLOT_TYPE {
	TST_UNKNOWN = 0,
	TST_OFF, /* timeslot is not decoded */
	TST_FCCH_SCH_BCCH_CCCH_SDCCH4,
	TST_FCCH_SCH_BCCH_CCCH,
	TST_SDCCH8,
	TST_TCHF
};

struct gs_ts_ctx {
	/* FIXME: later do this per each ts per each arfcn */
	unsigned char burst[4 * 58 * 2];
	unsigned char burst2[8 * 58 * 2]; /* buffer for FACCH on TCH */
	int burst_count;
	int burst_count2; /* counter for FACCH on TCH */
	enum TIMESLOT_TYPE type;
};

typedef struct
{
	int flags;
	int fn;
	int bsic;
	char msg[23];	/* last decoded message */

	INTERLEAVE_CTX interleave_ctx;
	INTERLEAVE_CTX interleave_facch_f1_ctx;
	INTERLEAVE_CTX interleave_facch_f2_ctx;

	struct gs_ts_ctx ts_ctx[8];

	int gsmtap_fd;
} GS_CTX;

int GS_new(GS_CTX *ctx);
int GS_process(GS_CTX *ctx, struct l1ctl_burst_ind *bi, unsigned char d_KC[8], int first_burst, unsigned char print_frames);

#ifdef __cplusplus
}
#endif

#endif
