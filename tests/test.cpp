// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/mycode.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_RankChoice : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		
	}


	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
		
	}
	
	
};



/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////



std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

shared_ptr<ballot_node> TestBuildBallot ( )
{
	RankChoice myrace;
    vector<string> vec;

    vector<string> vec4 = {"Mike","Lisa","Bob", "Jane"};
    shared_ptr<ballot_node> top = myrace.FillBallot(vec4, 4); 

    vector<string> vec2 = {"Bob", "Mike", "Lisa", "Jane"};
    shared_ptr<ballot_node> two = myrace.FillBallot(vec2, 2);

    vector<string> vec1 = {"Mike","Bob","Lisa", "Jane"};
    shared_ptr<ballot_node> one = myrace.FillBallot(vec1, 1); 

    vector<string> vec3 = {"Jane","Bob","Lisa", "Mike"};
    shared_ptr<ballot_node> three = myrace.FillBallot(vec3, 3); 

    vector<string> vec5 = {"Bob","Lisa","Jane", "Mike"};
    shared_ptr<ballot_node> five = myrace.FillBallot(vec5, 5); 

    shared_ptr<ballot_node> test_treap (NULL);
    shared_ptr<candidate_node> null (NULL);
    shared_ptr<candidate_node> null_treap (NULL);

    myrace.Insert(top, null, test_treap, null_treap);
    myrace.Insert(three, null, test_treap, null_treap);
    myrace.Insert(one, null, test_treap, null_treap);
    myrace.Insert(two, null, test_treap, null_treap);
    myrace.Insert(five, null, test_treap, null_treap);
	
	return test_treap;
}
shared_ptr<candidate_node> TestBuildCandidate() {
    RankChoice myrace; 

    shared_ptr<candidate_node> Mike = myrace.FillCandidates("Mike");
    shared_ptr<candidate_node> Lisa = myrace.FillCandidates("Lisa");
    shared_ptr<candidate_node> Bob = myrace.FillCandidates("Bob");
    shared_ptr<candidate_node> Jane = myrace.FillCandidates("Jane");

    shared_ptr<candidate_node> test_candidate(NULL);
    shared_ptr<ballot_node> null(NULL);
    shared_ptr<ballot_node> null_treap(NULL);

    myrace.Insert(null, Mike, null_treap, test_candidate);
    myrace.Insert(null, Lisa, null_treap, test_candidate);
    myrace.Insert(null, Bob, null_treap, test_candidate);
    myrace.Insert(null, Jane, null_treap, test_candidate);

    return test_candidate; 

}
/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_RankChoice, TestFillBallot){
    RankChoice myrace; 
    vector<string> vec; 
    shared_ptr<ballot_node> nodeptr = myrace.FillBallot(vec, 1);
    ASSERT_EQ(vec, nodeptr->rank);
    ASSERT_EQ(1,nodeptr->ballot_key);

}

TEST_F(test_RankChoice, TestFillCandidates) {
    RankChoice myrace;
    shared_ptr<candidate_node> nodeptr = myrace.FillCandidates("Paul");
}

TEST_F(test_RankChoice, TestInsertBallots) {
    RankChoice myrace;
    vector<string> vec;

    vector<string> vec4 = {"Mike","Lisa","Bob", "Jane"};
    shared_ptr<ballot_node> top = myrace.FillBallot(vec4, 4); 

    vector<string> vec2 = {"Bob", "Mike", "Lisa", "Jane"};
    shared_ptr<ballot_node> two = myrace.FillBallot(vec2, 2);

    vector<string> vec1 = {"Mike","Bob","Lisa", "Jane"};
    shared_ptr<ballot_node> one = myrace.FillBallot(vec1, 1); 

    vector<string> vec3 = {"Jane","Bob","Lisa", "Mike"};
    shared_ptr<ballot_node> three = myrace.FillBallot(vec3, 3); 

    vector<string> vec5 = {"Bob","Lisa","Jane", "Mike"};
    shared_ptr<ballot_node> five = myrace.FillBallot(vec5, 5); 

    shared_ptr<ballot_node> test_treap (NULL);
    shared_ptr<candidate_node> null (NULL);
    shared_ptr<candidate_node> null_treap (NULL);

    myrace.Insert(top, null, test_treap, null_treap);
    myrace.Insert(three, null, test_treap, null_treap);
    myrace.Insert(one, null, test_treap, null_treap);
    myrace.Insert(two, null, test_treap, null_treap);
    myrace.Insert(five, null, test_treap, null_treap);
	

    
}

TEST_F(test_RankChoice, TestSetPref) {
    RankChoice myrace;
    shared_ptr<ballot_node> top = TestBuildBallot();

    myrace.SetPref(top);

}

TEST_F(test_RankChoice, TestGetPref) {
    RankChoice myrace;
     

    shared_ptr<ballot_node> top = TestBuildBallot();
    myrace.SetPref(top);
    myrace.GetPref(top);
}

TEST_F(test_RankChoice, TestInsertCanidates) {
    RankChoice myrace; 

    shared_ptr<candidate_node> Mike = myrace.FillCandidates("Mike");
    shared_ptr<candidate_node> Lisa = myrace.FillCandidates("Lisa");
    shared_ptr<candidate_node> Bob = myrace.FillCandidates("Bob");
    shared_ptr<candidate_node> Jane = myrace.FillCandidates("Jane");

    shared_ptr<candidate_node> test_candidate(NULL);
    shared_ptr<ballot_node> null(NULL);
    shared_ptr<ballot_node> null_treap(NULL);

    myrace.Insert(null, Mike, null_treap, test_candidate);
    myrace.Insert(null, Lisa, null_treap, test_candidate);
    myrace.Insert(null, Bob, null_treap, test_candidate);
    myrace.Insert(null, Jane, null_treap, test_candidate);



} 

TEST_F(test_RankChoice, TestAdd) {
    RankChoice myrace;
    shared_ptr<candidate_node> top = TestBuildCandidate(); 

    myrace.AddVotes(top, "Mike");
    myrace.AddVotes(top, "Lisa");
    myrace.AddVotes(top, "Bob");
    myrace.AddVotes(top, "Jane");



}

TEST_F(test_RankChoice, TestCount) {
    RankChoice myrace;
    shared_ptr<ballot_node> ballot = TestBuildBallot();
    shared_ptr<candidate_node> candidate = TestBuildCandidate(); 

    myrace.SetPref(ballot);
    myrace.GetPref(ballot);
    myrace.Count_Votes(candidate); 
}

TEST_F(test_RankChoice, TestMin) {
    RankChoice myrace;
    shared_ptr<ballot_node> ballot = TestBuildBallot();
    shared_ptr<candidate_node> candidate = TestBuildCandidate(); 

    myrace.SetPref(ballot);
    myrace.GetPref(ballot);
    myrace.Count_Votes(candidate); 
    
    shared_ptr<candidate_node> eliminated = myrace.FillCandidates("");

    myrace.Findmin(candidate, eliminated, candidate->votes, candidate->candidate_name); 
}

TEST_F(test_RankChoice, TestMax) {
    RankChoice myrace;
    shared_ptr<ballot_node> ballot = TestBuildBallot();
    shared_ptr<candidate_node> candidate = TestBuildCandidate(); 

    myrace.SetPref(ballot);
    myrace.GetPref(ballot);
    myrace.Count_Votes(candidate);

    shared_ptr<candidate_node> winner = myrace.FillCandidates("");

    myrace.FindWinner(candidate, winner, candidate->votes, candidate->candidate_name);
}

TEST_F(test_RankChoice, TestDeleteLoser) {
    RankChoice myrace;
    shared_ptr<ballot_node> ballot = TestBuildBallot();
    shared_ptr<candidate_node> candidate = TestBuildCandidate(); 

    myrace.SetPref(ballot);
    myrace.GetPref(ballot);
    myrace.Count_Votes(candidate); 
    myrace.SetRoot(candidate);
    shared_ptr<candidate_node> eliminated = myrace.FillCandidates("");

    myrace.Findmin(candidate, eliminated, candidate->votes, candidate->candidate_name); 

    myrace.Remove(eliminated->candidate_name);
}

TEST_F(test_RankChoice, TestResetPref) {
    RankChoice myrace;
    shared_ptr<ballot_node> ballot = TestBuildBallot();
    shared_ptr<candidate_node> candidate = TestBuildCandidate(); 

    myrace.SetPref(ballot);
    myrace.GetPref(ballot);
    myrace.Count_Votes(candidate); 
    
    shared_ptr<candidate_node> eliminated = myrace.FillCandidates("");

    eliminated->candidate_name = "Bob";

    myrace.ResetPref(ballot, eliminated);

}

TEST_F(test_RankChoice, TestPetElection) {

    RankChoice myrace;
 
    // Candidate Treap
    shared_ptr<candidate_node> Lizard = myrace.FillCandidates("Lizard");
    shared_ptr<candidate_node> Bunny = myrace.FillCandidates("Bunny");
    shared_ptr<candidate_node> Pariot = myrace.FillCandidates("Pariot");
    shared_ptr<candidate_node> Snake = myrace.FillCandidates("Snake");
    shared_ptr<candidate_node> Turtle = myrace.FillCandidates("Turtle");
    shared_ptr<candidate_node> Mouse = myrace.FillCandidates("Mouse");


    shared_ptr<candidate_node> candidate3(NULL);
    shared_ptr<ballot_node> null_bal3(NULL);
    shared_ptr<ballot_node> null_btreap3(NULL);

    myrace.Insert(null_bal3, Lizard, null_btreap3, candidate3);
    myrace.Insert(null_bal3, Bunny, null_btreap3, candidate3);
    myrace.Insert(null_bal3, Pariot, null_btreap3, candidate3);
    myrace.Insert(null_bal3, Snake, null_btreap3, candidate3);
    myrace.Insert(null_bal3, Turtle, null_btreap3, candidate3);
    myrace.Insert(null_bal3, Mouse, null_btreap3, candidate3);



    // Ballot Treap
    vector<string> vec_election3;

    vector<string> vector_1 = {"Snake","Turtle","Bunny", "Lizard", "Mouse", "Pariot"};
    shared_ptr<ballot_node> one_class = myrace.FillBallot(vector_1, 1); 

    vector<string> vector_2 = {"Lizard","Snake","Turtle", "Pariot", "Bunny", "Mouse"};
    shared_ptr<ballot_node> two_class = myrace.FillBallot(vector_2, 2);

    vector<string> vector_3 = {"Mouse","Turtle","Snake", "Pariot", "Bunny", "Lizard"};
    shared_ptr<ballot_node> three_class = myrace.FillBallot(vector_3, 3); 

    vector<string> vector_4 = {"Bunny","Snake","Pariot", "Mouse", "Lizard", "Turtle"};
    shared_ptr<ballot_node> four_class = myrace.FillBallot(vector_4, 4); 

    vector<string> vector_5 = {"Mouse","Pariot","Lizard", "Bunny", "Turtle", "Snake"};
    shared_ptr<ballot_node> five_class = myrace.FillBallot(vector_5, 5); 
    
    vector<string> vector_6 = {"Snake","Bunny","Mouse", "Pariot", "Lizard", "Turtle"};
    shared_ptr<ballot_node> six_class = myrace.FillBallot(vector_6, 6); 

    vector<string> vector_7 = {"Pariot","Bunny","Snake", "Mouse", "Lizard", "Turtle"};
    shared_ptr<ballot_node> seven_class = myrace.FillBallot(vector_7, 7);

    vector<string> vector_8 = {"Bunny","Lizard","Snake", "Pariot", "Turtle", "Mouse"};
    shared_ptr<ballot_node> eight_class = myrace.FillBallot(vector_8, 8); 

    vector<string> vector_9 = {"Turtle","Mouse","Pariot", "Bunny", "Lizard", "Snake"};
    shared_ptr<ballot_node> nine_class = myrace.FillBallot(vector_9, 9); 

    vector<string> vector_10 = {"Lizard","Mouse","Pariot", "Snake", "Turtle", "Bunny"};
    shared_ptr<ballot_node> ten_class = myrace.FillBallot(vector_10, 10); 

    vector<string> vector_11 = {"Bunny","Pariot","Turtle", "Lizard", "Snake", "Mouse"};
    shared_ptr<ballot_node> eleven_class = myrace.FillBallot(vector_11, 11); 

    vector<string> vector_12 = {"Turtle","Bunny","Mouse", "Lizard", "Snake", "Pariot"};
    shared_ptr<ballot_node> twelve_class = myrace.FillBallot(vector_12, 12);

    vector<string> vector_13 = {"Bunny","Mouse","Pariot", "Snake", "Lizard", "Turtle"};
    shared_ptr<ballot_node> thirteen_class = myrace.FillBallot(vector_13, 13); 

    vector<string> vector_14 = {"Lizard","Bunny","Pariot", "Turtle", "Snake", "Mouse"};
    shared_ptr<ballot_node> fourteen_class = myrace.FillBallot(vector_14, 14); 

    vector<string> vector_15 = {"Snake","Mouse","Pariot", "Bunny", "Lizard", "Turtle"};
    shared_ptr<ballot_node> fifteen_class = myrace.FillBallot(vector_15, 15); 
    
    vector<string> vector_16 = {"Turtle","Mouse","Pariot", "Bunny", "Snake", "Lizard"};
    shared_ptr<ballot_node> sixteen_class = myrace.FillBallot(vector_16, 16); 

    vector<string> vector_17 = {"Bunny","Snake","Mouse", "Pariot", "Lizard", "Turtle"};
    shared_ptr<ballot_node> seventeen_class = myrace.FillBallot(vector_17, 17);

    vector<string> vector_18 = {"Turtle","Bunny","Pariot", "Snake", "Lizard", "Mouse"};
    shared_ptr<ballot_node> eighteen_class = myrace.FillBallot(vector_18, 18); 

    vector<string> vector_19 = {"Mouse","Pariot","Snake", "Turtle", "Bunny", "Lizard"};
    shared_ptr<ballot_node> nineteen_class = myrace.FillBallot(vector_19, 19); 

    vector<string> vector_20 = {"Bunny","Lizard","Pariot", "Mouse", "Turtle", "Snake"};
    shared_ptr<ballot_node> twenty_class = myrace.FillBallot(vector_20, 20); 

    shared_ptr<ballot_node> ballot3 (NULL);
    shared_ptr<candidate_node> null_can3 (NULL);
    shared_ptr<candidate_node> null_ctreap3 (NULL);

    myrace.Insert(one_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(two_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(three_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(four_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(five_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(six_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(seven_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(eight_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(nine_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(ten_class, null_can3, ballot3, null_ctreap3);    
    myrace.Insert(eleven_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(twelve_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(thirteen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(fourteen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(fifteen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(sixteen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(seventeen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(eighteen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(nineteen_class, null_can3, ballot3, null_ctreap3);
    myrace.Insert(twenty_class, null_can3, ballot3, null_ctreap3);

    cout << "##################################" << endl;
    cout << "Mr Lester's Classroom Pet Election" << endl;
    cout << "##################################" << endl; 

    myrace.Election_Day(candidate3, ballot3); 
}

TEST_F(test_RankChoice, TestTripElection) {

    RankChoice myrace;
 
    // Candidate Treap
    shared_ptr<candidate_node> Italy = myrace.FillCandidates("Italy");
    shared_ptr<candidate_node> Australia = myrace.FillCandidates("Australia");
    shared_ptr<candidate_node> Japan = myrace.FillCandidates("Japan");
    shared_ptr<candidate_node> South_Africa = myrace.FillCandidates("South Africa");
    shared_ptr<candidate_node> Peru = myrace.FillCandidates("Peru");

    shared_ptr<candidate_node> candidate2(NULL);
    shared_ptr<ballot_node> null_bal2(NULL);
    shared_ptr<ballot_node> null_btreap2(NULL);

    myrace.Insert(null_bal2, Italy, null_btreap2, candidate2);
    myrace.Insert(null_bal2, Australia, null_btreap2, candidate2);
    myrace.Insert(null_bal2, Japan, null_btreap2, candidate2);
    myrace.Insert(null_bal2, South_Africa, null_btreap2, candidate2);
    myrace.Insert(null_bal2, Peru, null_btreap2, candidate2);



    // Ballot Treap
    vector<string> vec_election2;

    vector<string> vector1 = {"Italy","Peru","Japan", "Australia", "South Africa"};
    shared_ptr<ballot_node> one_elect = myrace.FillBallot(vector1, 1); 

    vector<string> vector2 = {"South Africa","Italy","Australia", "Japan", "Peru"};
    shared_ptr<ballot_node> two_elect = myrace.FillBallot(vector2, 2);

    vector<string> vector3 = {"Japan","Australia","South Africa", "Peru", "Italy"};
    shared_ptr<ballot_node> three_elect = myrace.FillBallot(vector3, 3); 

    vector<string> vector4 = {"South Africa","Japan","Australia", "Peru", "Italy"};
    shared_ptr<ballot_node> four_elect = myrace.FillBallot(vector4, 4); 

    vector<string> vector5 = {"Italy","Japan","Peru", "South Africa", "Australia"};
    shared_ptr<ballot_node> five_elect = myrace.FillBallot(vector5, 5); 
    
    vector<string> vector6 = {"Peru","Italy","South Africa", "Australia", "Japan"};
    shared_ptr<ballot_node> six_elect = myrace.FillBallot(vector6, 6); 

    vector<string> vector7 = {"Japan","Peru","South Africa", "Italy", "Australia"};
    shared_ptr<ballot_node> seven_elect = myrace.FillBallot(vector7, 7);

    vector<string> vector8 = {"Italy","South Africa","Japan", "Australia", "Peru"};
    shared_ptr<ballot_node> eight_elect = myrace.FillBallot(vector8, 8); 

    vector<string> vector9 = {"Australia","Japan","South Africa", "Peru", "Italy"};
    shared_ptr<ballot_node> nine_elect = myrace.FillBallot(vector9, 9); 

    vector<string> vector10 = {"Peru","Australia","Italy", "South Africa", "Japan"};
    shared_ptr<ballot_node> ten_elect = myrace.FillBallot(vector10, 10); 

    shared_ptr<ballot_node> ballot2 (NULL);
    shared_ptr<candidate_node> null_can2 (NULL);
    shared_ptr<candidate_node> null_ctreap2 (NULL);

    myrace.Insert(one_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(two_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(three_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(four_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(five_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(six_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(seven_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(eight_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(nine_elect, null_can2, ballot2, null_ctreap2);
    myrace.Insert(ten_elect, null_can2, ballot2, null_ctreap2);

    cout << "***************************************" << endl;
    cout << "Senior Class of 2023 Overseas Trip Vote" << endl;
    cout << "_________Where Should We Go?___________" << endl;
    cout << "***************************************" << endl; 

    myrace.Election_Day(candidate2, ballot2); 

}

TEST_F(test_RankChoice, TestElection_Day) {
    // First Election 
    RankChoice myrace;
    shared_ptr<ballot_node> ballot = TestBuildBallot();
    shared_ptr<candidate_node> candidate = TestBuildCandidate(); 
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Ms.Frizzle's Line Leader Election" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    myrace.Election_Day(candidate, ballot); 
    

} 



