#ifndef RANKCHOICE_H__
#define RANKCHOICE_H__

#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector> 
#include <cstdlib>
#include <algorithm>  
#include <iomanip>

using namespace std;

    struct ballot_node {
        string first_preference; 
        shared_ptr<ballot_node> left;
        shared_ptr<ballot_node> right;
        vector<string> rank;
        int ballot_key;
        int random_priority;


};

    struct candidate_node {
        int votes;
        int random_priority;
        shared_ptr<candidate_node> left;
        shared_ptr<candidate_node> right;
        string candidate_name; 

};


class RankChoice {
public:
  RankChoice();

  ~RankChoice();

  shared_ptr<ballot_node> FillBallot(vector<string> vec, int key);

  shared_ptr<candidate_node> FillCandidates(string canidate_name);

  void PrintBallots(shared_ptr<ballot_node> ballot_treap);

  void PrintRank(shared_ptr<ballot_node> ballot_treap);

  void PrintCandidates(shared_ptr<candidate_node> candidate_treap);   

  void Print(shared_ptr<candidate_node> candidate_treap); 

  void RightRotation(shared_ptr<ballot_node>& ball, shared_ptr<candidate_node>& can);
  
  void LeftRotation(shared_ptr<ballot_node>& ball, shared_ptr<candidate_node>& can);
    
  void Insert(shared_ptr<ballot_node> ballot, shared_ptr<candidate_node> candidate, 
              shared_ptr<ballot_node>& ballot_treap, shared_ptr<candidate_node>& canidate_treap);
    
  shared_ptr<candidate_node> Remove(string loser_name);

  void SetPref(shared_ptr<ballot_node>& ballot); 

  void GetPref(shared_ptr<ballot_node> ballot);

  void ResetPref(shared_ptr<ballot_node>& ballot, shared_ptr<candidate_node> lost);

  void EditBallot(shared_ptr<ballot_node> ballot, shared_ptr<candidate_node> lost); 

  void AddVotes(shared_ptr<candidate_node> candidate_treap, string name);

  void ResetVotes(shared_ptr<candidate_node> candidate_treap);

  void Count_Votes(shared_ptr<candidate_node>& candidates);

  void Findmin(shared_ptr<candidate_node> candidate_treap, shared_ptr<candidate_node>& last, int& min_vote, string& loser_name);

  void FindWinner(shared_ptr<candidate_node> candidate_treap, shared_ptr<candidate_node>& first, int& max_vote, string& winner_name);

  void Election_Day(shared_ptr<candidate_node> candidate_treap, shared_ptr<ballot_node> ballot_treap);

  shared_ptr<candidate_node> GetRoot();

  void SetRoot(shared_ptr<candidate_node> root_ptr);

 private:
    
    vector<string> vote_tally;  

    shared_ptr<candidate_node> root_ptr_;

    int num_votes = 0;

    int round = 0; 
};










#endif // RANKCHOICE_H__