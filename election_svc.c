/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "election.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static char **
_register_voter_1 (register_voter_1_argument *argp, struct svc_req *rqstp)
{
	return (register_voter_1_svc(argp->arg1, argp->arg2, rqstp));
}

static bool_t *
_verify_voter_1 (char * *argp, struct svc_req *rqstp)
{
	return (verify_voter_1_svc(*argp, rqstp));
}

static bool_t *
_cast_vote_1 (cast_vote_1_argument *argp, struct svc_req *rqstp)
{
	return (cast_vote_1_svc(argp->arg1, argp->arg2, rqstp));
}

static candidate_list *
_tally_results_1 (void  *argp, struct svc_req *rqstp)
{
	return (tally_results_1_svc(rqstp));
}

static char **
_announce_winner_1 (void  *argp, struct svc_req *rqstp)
{
	return (announce_winner_1_svc(rqstp));
}

static bool_t *
_add_candidate_1 (char * *argp, struct svc_req *rqstp)
{
	return (add_candidate_1_svc(*argp, rqstp));
}

static bool_t *
_remove_candidate_1 (char * *argp, struct svc_req *rqstp)
{
	return (remove_candidate_1_svc(*argp, rqstp));
}

static bool_t *
_invalidate_candidate_1 (char * *argp, struct svc_req *rqstp)
{
	return (invalidate_candidate_1_svc(*argp, rqstp));
}

static stats *
_calc_statistics_1 (void  *argp, struct svc_req *rqstp)
{
	return (calc_statistics_1_svc(rqstp));
}

static void
election_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		register_voter_1_argument register_voter_1_arg;
		char *verify_voter_1_arg;
		cast_vote_1_argument cast_vote_1_arg;
		char *add_candidate_1_arg;
		char *remove_candidate_1_arg;
		char *invalidate_candidate_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case register_voter:
		_xdr_argument = (xdrproc_t) xdr_register_voter_1_argument;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _register_voter_1;
		break;

	case verify_voter:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _verify_voter_1;
		break;

	case cast_vote:
		_xdr_argument = (xdrproc_t) xdr_cast_vote_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _cast_vote_1;
		break;

	case tally_results:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_candidate_list;
		local = (char *(*)(char *, struct svc_req *)) _tally_results_1;
		break;

	case announce_winner:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _announce_winner_1;
		break;

	case add_candidate:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _add_candidate_1;
		break;

	case remove_candidate:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _remove_candidate_1;
		break;

	case invalidate_candidate:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _invalidate_candidate_1;
		break;

	case calc_statistics:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_stats;
		local = (char *(*)(char *, struct svc_req *)) _calc_statistics_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (ELECTION, ELECTIONVERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, ELECTION, ELECTIONVERS, election_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (ELECTION, ELECTIONVERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, ELECTION, ELECTIONVERS, election_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (ELECTION, ELECTIONVERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
