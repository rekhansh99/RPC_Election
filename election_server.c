/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <string.h>
#include <stdlib.h>
#include "election.h"

candidate candidates[10];
voter voters[1000];
int voters_len = 0;
int candidates_len = 0;

char **register_voter_1_svc(char *arg1, char arg2, struct svc_req *rqstp) {
  static char *result;

  if(voters_len == 1000)
    result = "";
  else {
    voter *v = &voters[voters_len];
    v->gender = arg2;
    strcpy(v->name, arg1);
    sprintf(v->id, "%d", rand() % 100000 * 1000 + voters_len);
    v->vote = -1;
    result = v->id;
    voters_len++;

    // printf("Name: %s\nGender: %c\nid: %s\n", v->name, v->gender, v->id);
  }

  return &result;
}

bool_t *verify_voter_1_svc(char *arg1, struct svc_req *rqstp) {
  static bool_t result;

  result = FALSE;

  for (int i = 0; i < voters_len; i++)
    if (strcmp(voters[i].id, arg1) == 0)
      result = TRUE;

  return &result;
}

bool_t *cast_vote_1_svc(char *arg1, char *arg2, struct svc_req *rqstp) {
  static bool_t result;

  result = FALSE;
  for (int i = 0; i < voters_len; i++)
    if (strcmp(voters[i].id, arg1) == 0) {
      if (voters[i].vote == -1)
        for (int j = 0; j < candidates_len; j++)
          if(strcmp(candidates[j].name, arg2) == 0) {
            voters[i].vote = j;
            candidates[j].votes++;
            result = TRUE;
          }
      break;
    }

  return &result;
}

candidate_list *tally_results_1_svc(struct svc_req *rqstp) {
  static candidate_list result;

  result.candidate_list_len = candidates_len;
  result.candidate_list_val = candidates;

  return &result;
}

char **announce_winner_1_svc(struct svc_req *rqstp) {
  static char *result;

  result = "";
  int max_votes = 0;
  for (int i = 0; i < candidates_len; i++)
    if (candidates[i].valid && candidates[i].votes > max_votes) {
      max_votes = candidates[i].votes;
      result = candidates[i].name;
    }

  return &result;
}

bool_t *add_candidate_1_svc(char *arg1, struct svc_req *rqstp) {
  static bool_t result;

  if (candidates_len == 10)
    result = FALSE;
  else {
    candidate *c = &candidates[candidates_len];
    strcpy(c->name, arg1);
    c->votes = 0;
    c->valid = TRUE;

    candidates_len++;
    result = TRUE;
  }

  return &result;
}

bool_t *remove_candidate_1_svc(char *arg1, struct svc_req *rqstp) {
  static bool_t result;

  result = FALSE;
  for (int i = 0; i < candidates_len; i++) {
    if (strcmp(candidates[i].name, arg1) == 0) {
      for (int j = i + 1; j < candidates_len; j++)
        candidates[j - 1] = candidates[j];
      candidates_len--;
      result = TRUE;
    }
  }

  return &result;
}

bool_t *invalidate_candidate_1_svc(char *arg1, struct svc_req *rqstp) {
  static bool_t result;

  result = FALSE;
  for (int i = 0; i < candidates_len; i++) {
    if (strcmp(candidates[i].name, arg1) == 0) {
      candidates[i].valid = FALSE;
      result = TRUE;
    }
  }

  return &result;
}

stats *calc_statistics_1_svc(struct svc_req *rqstp) {
  static stats result;

  int total_votes = 0, male_voters = 0, female_voters = 0;
  int c_total_votes[candidates_len], c_male_voters[candidates_len], c_female_voters[candidates_len];

  memset(c_total_votes, 0, candidates_len * sizeof(int));
  memset(c_male_voters, 0, candidates_len * sizeof(int));
  memset(c_female_voters, 0, candidates_len * sizeof(int));

  result.candidate.candidate_len = candidates_len;
  for(int i = 0; i < voters_len; i++) {
    voter *v = &voters[i];

    if(v->vote != -1) {
      total_votes++;
      c_total_votes[v->vote]++;

      if(v->gender == 'M') {
        male_voters++;
        c_male_voters[v->vote]++;
      }
      else {
        female_voters++;
        c_female_voters[v->vote]++;
      }
    }
  }

  result.total_vote_percent = voters_len ? (double)total_votes / voters_len : 0;
  result.male_vote_percent = total_votes ? (double)male_voters / total_votes : 0;
  result.female_vote_percent = total_votes ? (double)female_voters / total_votes : 0;

  for (int i = 0; i < candidates_len; i++) {
    result.candidate.candidate_val[i].total_vote_percent = total_votes ? (double)c_total_votes[i] / total_votes : 0;
    result.candidate.candidate_val[i].male_vote_percent = total_votes ? (double)c_male_voters[i] / total_votes : 0;
    result.candidate.candidate_val[i].female_vote_percent = total_votes ? (double)c_female_voters[i] / total_votes : 0;
  }

  return &result;
}
