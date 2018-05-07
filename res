#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

struct Resistance {
    vector<double> sp(int P, int S, vector<string> missions) {
        vector<double> freq(P, 0.0);
        int total=0;

        for (int mask=0; mask<(1<<P); ++mask) {
            if (__builtin_popcount(mask)==S) {
                bool valid=1;

                for (int i=0; i<(int)missions.size(); ++i) {
                    if (missions[i][0]=='F') {
                        bool has_spy=0;

                        for (int p=0; p<P; ++p) {
                            if (missions[i][p+1]=='1' && (mask&1<<p)!=0) {
                                has_spy=1;
                            }
                        }

                        if (!has_spy) {
                            valid=false;
                        }
                    }
                }
                if (valid) {
                    cout<<"Mask: "<<mask<<endl;
                    total++;
                    for (int p=0; p<P; ++p) {
                        if (mask & 1<<p) {
                            freq[p]++;
                        }
                    }
                }
            }
        }
        if (total==0) return vector<double>();
        for (int p=0; p<P; ++p) { cout<<"freq["<<p<<"]: "<<freq[p]<<endl; freq[p]/=total; }
        cout<<"Total: "<<total<<endl;
        return freq;
    }
};

int main() {
    int P=4;
    int S=2;
    vector<string> vs=
{"F0100",
 "S0101",
 "F1010",
 "S1011"};
    Resistance a;
    vector<double> res=a.sp(P, S, vs);
    for (auto e : res) cout<<e<<' ';
    cout<<endl;
    return 0;
}
/*
0)

    
4
1
{"S0110",
 "F1100",
 "S0011"}
Returns: {0.5, 0.5, 0.0, 0.0 }
There is only one spy. Players 2 and 3 cannot be the spy because neither of them went on the failed mission. Players 0 and 1 can be spies. As both scenarios are valid, each of these two players is a spy with probability 50%.
1)

    
4
2
{"F0100",
 "S0101",
 "F1010",
 "S1011"}
Returns: {0.5, 1.0, 0.5, 0.0 }
Now we have two spies. Only one player went to the first failed mission, so we can be certain that player 1 is a spy. Based on the second failed mission, one of players 0 and 2 must be a spy. Both possibilities match the rest of the input, so we assign each of them probability 50% of being a spy. Note that player 1 (a known spy) once voted for a success of a mission.
2)

    
3
1
{"F110",
 "F101",
 "F011"}
Returns: { }
There is supposed to be only one spy, but no player went on all three failed missions, so the mission history is invalid.
3)

    
5
2
{"F11000",
 "S00011",
 "F10100",
 "S01111"}
Returns: {0.8, 0.4, 0.4, 0.2, 0.2 }
One possibility is that the spies are players 1 and 2. Another possibility is that one of the spies is player 0 and the other spy can be any of the other four players.
4)

    
9
3
{"S100001100",
 "F011110000",
 "F001000010",
 "F100010101",
 "S010010001",
 "F100001010",
 "F000100100"}
Returns: {0.3, 0.1, 0.4, 0.5, 0.2, 0.1, 0.6, 0.7, 0.1 }
*/
