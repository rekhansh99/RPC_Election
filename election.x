struct voter {
  char id[9];
  char name[32];
  char gender;
  int vote;
};

struct candidate {
  char name[32];
  int votes;
  bool valid;
};

struct candidate_stats {
  double total_vote_percent;
  double male_vote_percent;
  double female_vote_percent;
};

struct stats {
  double total_vote_percent;
  double male_vote_percent;
  double female_vote_percent;
  candidate_stats candidate<>;
};

typedef voter *voter_ptr;
typedef candidate candidate_list<>;

program ELECTION {
  version ELECTIONVERS {
    string register_voter(string, char) = 1;

    bool verify_voter(string) = 2;

    bool cast_vote(string, string) = 3;

    candidate_list tally_results(void) = 4;

    string announce_winner(void) = 5;

    bool add_candidate(string) = 6;

    bool remove_candidate(string) = 7;

    bool invalidate_candidate(string) = 8;

    stats calc_statistics() = 9;
 	} = 1;
} = 0x20000001;