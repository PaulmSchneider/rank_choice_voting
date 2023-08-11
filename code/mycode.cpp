#include "mycode.h" 

RankChoice::RankChoice() { 

}

RankChoice::~RankChoice() {

}

// Dynamically allocates a new ballot node to take in a ballot containing a voter ranked choices, the ballot number, 
// and a random priority. 

shared_ptr<ballot_node> RankChoice::FillBallot(vector<string> vec, int key) {
    shared_ptr<ballot_node> ret(new ballot_node);
    ret->first_preference = "";
    ret->left = shared_ptr<ballot_node>(NULL); 
    ret->right = shared_ptr<ballot_node>(NULL);
    ret->rank = vec; 
    ret->ballot_key = key; 
    ret->random_priority = 0 + rand() % 100;

    return ret; 

}

// Dynamically allocates a new candidate node to take in the candidates name and create a random priority. 

shared_ptr<candidate_node> RankChoice::FillCandidates(string name) {
    shared_ptr<candidate_node> ret(new candidate_node);
    ret->candidate_name = name;
    ret->left = shared_ptr<candidate_node>(NULL);
    ret->right = shared_ptr<candidate_node>(NULL);
    ret->random_priority = 0 + rand() % 100;
    ret->votes = 0;

    return ret;
}

// Recursively traverses the Ballot Treap to access each node, then send it to the PrintRank funtion. 
void RankChoice::PrintBallots(shared_ptr<ballot_node> ballot_treap) {
    if (ballot_treap == NULL) {
        return;
    }
    PrintBallots(ballot_treap->left);
    PrintRank(ballot_treap);
    PrintBallots(ballot_treap->right);
}

// Prints the ranked votes of each ballot in the Ballot Treap.
void RankChoice:: PrintRank(shared_ptr<ballot_node> ballot_treap) {
    cout << " " << endl;
    cout << "Read Ballot: ";
    for (int i = 0; i < ballot_treap->rank.size(); i++) {
        cout << " " << "[" << ballot_treap->rank.at(i) << "]"; 
        cout << " ";
    }
    cout << " " << endl;
    
}
// Recursively traverses the Candidate Treap to access each node, then send it to the Print function. 
void RankChoice::PrintCandidates(shared_ptr<candidate_node> candidate_treap) {
    if (candidate_treap == NULL) {
        return; 
    }
    PrintCandidates(candidate_treap->left);
    Print(candidate_treap);
    PrintCandidates(candidate_treap->right);
}
// Prints the names of the canidates and their vote percentages of each Canidate Node in the Candidate Treap.
void RankChoice::Print(shared_ptr<candidate_node> candidate_treap) {
    cout << " " << endl;
    cout << "Candidates: ";
    
    
    
    if (candidate_treap->votes > 0) {
        double percentage = (1.0 * candidate_treap->votes / num_votes);
    
        while(candidate_treap != NULL) {
        cout << " " << candidate_treap->candidate_name << " " << percentage * 100 << "%"; 
        return; 
        }  
    }
    else {
        
    
        while(candidate_treap != NULL) {
        cout << " " << candidate_treap->candidate_name; 
        return;
        }
    }
}

// Rotates right at the parent node because it's left priority was greater than itself or its right priority. 
void RankChoice::RightRotation(shared_ptr<ballot_node>& ball, shared_ptr<candidate_node>& can) {
    if (can == NULL) {
        shared_ptr<ballot_node> temp = ball->left;
        ball->left = temp->right;
        temp->right = ball; 

        ball = temp; 
    }
    else if (ball == NULL) {
        shared_ptr<candidate_node> temp = can->left;
        can->left = temp->right;
        temp->right = can;

        can = temp; 
    }
}
// Rotates left at the parent node because it's right priority was greater than itself or its left priority.
void RankChoice::LeftRotation(shared_ptr<ballot_node>& ball, shared_ptr<candidate_node>& can) {

    if (can == NULL) {
        shared_ptr<ballot_node> temp = ball->right;
        ball->right = temp->left;
        temp->left = ball;

        ball = temp;
    }

    else if (ball == NULL) {
        shared_ptr<candidate_node> temp = can->right;
        can->right = temp->left;
        temp->left = can; 

        can = temp; 
    }
}

// First recursively inserts node with the key, maintaining BST properties.
// Then percolates up using rotations until the random priority does not violates heap properties.
// Is capable of inserting both Ballot and Candidate nodes into seperate Treaps. (Saves Space)
void RankChoice::Insert(shared_ptr<ballot_node> ballot, shared_ptr<candidate_node> candidate,
                        shared_ptr<ballot_node>& ballot_treap, shared_ptr<candidate_node>& candidate_treap) {
    if (ballot_treap == NULL && candidate_treap == NULL) {
        ballot_treap = ballot; 
        candidate_treap = candidate; 
        return;
    }
    if (ballot_treap != NULL && candidate_treap == NULL) {
        if (ballot->ballot_key <= ballot_treap->ballot_key) {

            Insert(ballot, candidate, ballot_treap->left, candidate_treap);

            if (ballot_treap->left->random_priority > ballot_treap->random_priority) {

                RightRotation(ballot_treap, candidate_treap);
            }
            
        }
        else if (ballot->ballot_key >= ballot_treap->ballot_key) {

            Insert(ballot, candidate, ballot_treap->right, candidate_treap);

            if (ballot_treap->right->random_priority > ballot_treap->random_priority) {
                
                LeftRotation(ballot_treap, candidate_treap);
            }

        
        }
    }
    else if (ballot_treap == NULL && candidate_treap != NULL) {
        if (candidate->candidate_name <= candidate_treap->candidate_name) {

            Insert(ballot, candidate, ballot_treap, candidate_treap->left);

            if (candidate_treap->left->random_priority > candidate_treap->random_priority) {

                RightRotation(ballot_treap, candidate_treap);
            }
            
        }
        else if (candidate->candidate_name >= candidate_treap->candidate_name) {

            Insert(ballot, candidate, ballot_treap, candidate_treap->right);

            if (candidate_treap->right->random_priority > candidate_treap->random_priority) {
                
                LeftRotation(ballot_treap, candidate_treap);
            }
        
        }

    }

    return; 



}
// Sets the node_to_delete's priority to zero. Then percolates node down using rotations until it only has one child, or is a leaf. Then safely removes node. 
shared_ptr<candidate_node> RankChoice::Remove(string loser_name) {
  shared_ptr<candidate_node> parent(NULL);
    shared_ptr<candidate_node> cursor = root_ptr_;
    shared_ptr<ballot_node> test(NULL);
    shared_ptr<candidate_node> top(NULL);

    while (cursor != NULL) {
        if (cursor->candidate_name == loser_name) {
            cursor->random_priority = 0; 
            while (cursor->left != NULL || cursor->right != NULL) {
                if(cursor->left != NULL && cursor->right != NULL){
                    if (cursor->left->random_priority > cursor->right->random_priority) {
                        if (parent == NULL) {
                            RightRotation(test, cursor);
                            root_ptr_ = cursor;
                            parent = cursor;

                            cursor = cursor->right;
                        }
                        else {
                            RightRotation(test, cursor);
                            parent = cursor;
                            root_ptr_->right = parent;
                            cursor = cursor->right;
                        }
                    }
                    else if (cursor->left->random_priority < cursor->right->random_priority){
                        if (parent == NULL) { 
                            LeftRotation(test, cursor);
                            root_ptr_ = cursor;
                            parent = cursor;
                            cursor = cursor->left;
                        }
                        else {
                            LeftRotation(test, cursor);
                            parent = cursor;
                            root_ptr_->left = parent;

                            cursor = cursor->left;

                        }
        
                    }
                }
                else if (cursor->right == NULL) {
                    if(parent == NULL) {
                      root_ptr_ = cursor->left;
                      return root_ptr_;
                    }
                    else if (parent->left == cursor) {
                      parent->left = cursor->left;
                      return root_ptr_;
            
                    }
                    else {
                      parent->right = cursor->right;
                      return root_ptr_;
                    
                   }
                }
                else if (cursor->left == NULL) {
                    if (parent == NULL) {
                      root_ptr_ = cursor->right;
                      return root_ptr_;
                    }
                    else if (parent->left == cursor){
                      parent->left = cursor->right;
                      return root_ptr_; 
                    }
                    else {
                      parent->right = cursor->right;
                      return root_ptr_;
                    }
                }
            }
            if (cursor->left == NULL && cursor->right == NULL) {
                if(parent == NULL) {
                    root_ptr_ = NULL;
                    return root_ptr_;
                }
                else if (parent->left == cursor) {
                    parent->left = NULL;
                    return root_ptr_;
                }
                else {
                    parent->right = NULL;
                    return root_ptr_; 
                }
            }        
                
            

        }
        else if (cursor->candidate_name < loser_name) {
            parent = cursor;
            cursor = cursor->right; 
        }
        else if (cursor->candidate_name > loser_name) {
            parent = cursor;
            cursor = cursor->left;
        }
        
        
        
    }

    return root_ptr_;
}  
  
  
// Recursively traverses each Ballot Treap node (inorder) and sets their first candidate preference to the first element in their rank candidates list.  
void RankChoice::SetPref(shared_ptr<ballot_node>& ballot) {
    if (ballot == NULL) {
        return;
    }
    SetPref(ballot->left);
    ballot->first_preference = ballot->rank.at(0); 
    SetPref(ballot->right);
}
// Recursively traverses each Ballot Treap node (inorder), then pushes their first candidate preference to a private vector named "vote_tally". 
void RankChoice::GetPref(shared_ptr<ballot_node> ballot) {
    if (ballot == NULL) {
        return;
    }
    GetPref(ballot->left);
    vote_tally.push_back(ballot->first_preference);
    GetPref(ballot->right);
}
// Recursively traverses each Ballot Treap node (inorder) and sends it to the EditBallot function. 
void RankChoice::ResetPref(shared_ptr<ballot_node>& ballot, shared_ptr<candidate_node> lost) {
    if (ballot == NULL) {
        return;
    }
    ResetPref(ballot->left, lost);
    EditBallot(ballot, lost);
    ResetPref(ballot->right, lost);
}

// Finds the ranked choices of each ballot and begans iterating through the vector. 
// If an element in the list is the same as the eliminated candidate, the element is removed for the vector. 
// Slowest Part
void RankChoice::EditBallot(shared_ptr<ballot_node> ballot, shared_ptr<candidate_node> lost) {
    for (int i = 0; i < ballot->rank.size(); i++) {
        if (ballot->rank.at(i) == lost->candidate_name) {
            ballot->rank.erase(ballot->rank.begin() + i);
        }
    }
    return;
}

// Conducts a Treap Search on the Candidate Treap using candidate names as the key. 
// If candidate node is found, one vote is added. 
void RankChoice::AddVotes(shared_ptr<candidate_node> candidate_treap, string name) {

    while(candidate_treap != NULL) {
        if (candidate_treap->candidate_name >= name) { 
            if (candidate_treap->candidate_name == name){
                candidate_treap->votes += 1;
                return;
            }
            else {
                candidate_treap = candidate_treap->left;
            }
        }
        else if(candidate_treap->candidate_name <= name) {
            if (candidate_treap->candidate_name == name) {
                candidate_treap->votes += 1;
                return;
            }
            else {
                candidate_treap = candidate_treap->right; 
            }
        } 
    }
    return;
    

    
}
// Recursively traverses each Candidate Treap node and resets each Candidates vote total to zero. 
void RankChoice::ResetVotes(shared_ptr<candidate_node> candidate_treap) {
    if(candidate_treap == NULL) {
        return;
    }
    ResetVotes(candidate_treap->left);
    candidate_treap->votes = 0; 
    ResetVotes(candidate_treap->right);

}

// Iteratively traveres the private vector "vote_tally" and selects the first Candidate preference taken from the ballots. 
// Sends first Candidate preference to the function "AddVotes" to be counted.
// Add one to the private integer "num_votes", which keeps track of the number of votes. 
// Clears "vote_tally" for subsequent rounds.
void RankChoice::Count_Votes(shared_ptr<candidate_node>& candidates) {

    for (int i = 0; i < vote_tally.size(); i++) {
        AddVotes(candidates, vote_tally[i]);
        num_votes++;
    }

    vote_tally.clear();
}

// Recursively traverses Candidate Treap to find Candidate with the lowest number of votes. 
// Once found, copies node into a newly created 'last" node. 
void RankChoice::Findmin(shared_ptr<candidate_node> candidate_treap, shared_ptr<candidate_node>& last,
                 int& min_vote, string& loser_name) {
    

    if (candidate_treap == NULL) {
        return; 
    }
   
    Findmin(candidate_treap->left, last, min_vote, loser_name);
    if (candidate_treap->votes <= min_vote) {
        min_vote = candidate_treap->votes;
        loser_name = candidate_treap->candidate_name; 
        last->candidate_name = loser_name;
        last->votes = min_vote;
    }
    Findmin(candidate_treap->right, last, min_vote, loser_name); 
    
    
}

// Recursively traverses Canidate Treap to find the Candidate with the highest number of votes.
// Once found, copies node into a newly created "winner" node.
void RankChoice::FindWinner(shared_ptr<candidate_node> candidate_treap, shared_ptr<candidate_node>& first, int& max_vote, string& winner_name) {

    if (candidate_treap == NULL) {
        return; 
    }
   
    FindWinner(candidate_treap->left, first, max_vote, winner_name);
    if (candidate_treap->votes >= max_vote) {
        max_vote = candidate_treap->votes;
        winner_name = candidate_treap->candidate_name; 
        first->candidate_name = winner_name;
        first->votes = max_vote;
    }
    FindWinner(candidate_treap->right, first, max_vote, winner_name); 
    

}

// Calls previous functions.
// Starts by printing the Canidates and Voter Ballots. Sets and Gets first voter preferences. Counts and distributes out the votes. 
// Finds the candidate with the lowest and highest number of votes.
// If the candidate with the highest number of votes has a percentage over 50%, the election is called for that candidate.
// If no one is over the 50% threshold, removes the Candidate with the lowest vote total, resets preferences, and calls the function to restart with new information.  
void RankChoice::Election_Day(shared_ptr<candidate_node> candidate_treap, shared_ptr<ballot_node> ballot_treap) {
    round++;
    cout << " " << endl;
    cout << "ROUND #" << round << endl;

   
    PrintCandidates(candidate_treap);
    ResetVotes(candidate_treap);
    num_votes = 0; 
    cout << " " << endl;
    PrintBallots(ballot_treap);

    SetPref(ballot_treap);
    GetPref(ballot_treap);
    Count_Votes(candidate_treap);
    shared_ptr<candidate_node> Winner = FillCandidates("");
    shared_ptr<candidate_node> Loser = FillCandidates("");
    int votes = candidate_treap->votes;
    string names = candidate_treap->candidate_name;

    FindWinner(candidate_treap, Winner, votes, names);
   
    Findmin(candidate_treap, Loser, votes, names);

    float winner_percent = (Winner->votes * 1.0) / (num_votes* 1.0); 

    if (winner_percent >= .51) {
        cout << " " << endl; 
        PrintCandidates(candidate_treap);
        cout << " " << endl;
        cout << " " << endl;
        cout << "The Winner is: " << Winner->candidate_name << "!!!!" << endl; 
        cout << " " << endl; 
        return;
    }
    else {
        cout << " " << endl;
        cout << " " << endl;
        cout << "Round End: No Winner Declared" << endl;
        cout << "<<<" << Loser->candidate_name << ">>>" << " has been eliminated" << endl;
        cout << "Moving on to the next round..." << endl;
        SetRoot(candidate_treap);
        shared_ptr<candidate_node> new_treap = Remove(Loser->candidate_name);
        ResetPref(ballot_treap, Loser); 

        Election_Day(new_treap, ballot_treap);
    }
    return;
}

shared_ptr<candidate_node> RankChoice::GetRoot(){
  return root_ptr_;
}


void RankChoice::SetRoot(shared_ptr<candidate_node> root_ptr){
  root_ptr_ = root_ptr;
}