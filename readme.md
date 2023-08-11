# CSPB 2270 – Data Structures - Term Project

## What is Rank Choice Voting and How Does it Work? 

I dare not sound like a broken record when I say that our political voting system is flawed. How are the majority of Americans supposed to feel represented when there are only two parties to choose from? Although multiple parties can run for office, our electoral process almost always comes down to a choice between Republicans and Democrats. Why? To greatly oversimplify, it has to do with the rules of voting. The United States implements a “First-past the post” voting system for most national legislative elections. This means that the candidate with the most votes wins, even if they haven’t received a majority. ( 50% plus one) Thus, multiple parties must consolidate together if they want any chance of winning an election, and the end result is two main parties. But what if it didn’t have to be this way? What if our voting system was designed to allow multiple parties to enter the race and have a chance to win? Rank-Choice voting allows just that.    

Let's say we have four candidates running for office. In the first round, voters will rank the candidates based on preference. Once the votes are tabulated, we look for a candidate with over 50% (plus one) of the vote. If they obtain a majority, they win and the election is over. If no candidate obtains a majority the election enters into round two. In round two, the candidate with the lowest percentage of votes is eliminated. Now, this is where it gets tricky, all voters who ranked their first choice as the now-eliminated candidate will have their votes redistributed. Their votes will now go to whomever they ranked as their second choice in the election. The percentage of the voters is now redistributed. This algorithm continues until a candidate in the race reaches a majority. 


## Data Stucture Implemented: TREAP 

The purpose of this project is to implement a Rank-Choice voting system that simplifies the process and can be used as an educational tool for voters to learn about the advantages over our current system. This project can be implemented through a tree, however, a Treap is preferred over a regular Binary Search Tree given its structural advantages. A Treap uses two keys, a main key used to maintain binary search tree ordering, and a priority key, created randomly, to maintain heap properties.  While operations like search, delete and insert have a worst-case complexity of O(n) in a Binary Search Tree, a Treap is expected to maintain a complexity of O(Log n) for those same operations. This is because a Treap utilizes randomization and Binary Heap properties to maintain a high probability of balance in addition to a near-minimum height. Given these reasons, this complex algorithm will benefit from the structure of a Treap


## How To Compile and Run Code:

First run "cmake" within the build directory. Then run "make" within the same directory. And finally, run "./run_tests" to see the results of the elections. 
