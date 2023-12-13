#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_V = 10005;
const int INF = 1e9;



// Solves the problem using Floyd-Warshall algorithm
int maximumWater(vector<vector<int>>& travel_time, vector<int>& pumping_rate, int t) {
    int v = travel_time.size();

    // Initialize the dp matrix
    vector<vector<int>> dp(v, vector<int>(t + 1, 0));

    // Floyd-Warshall Algorithm
    for (int k = 1; k <= v; ++k) {
        for (int i = 1; i < v; ++i) {  // Corrected index, starting from 1
            for (int j = 1; j <= t; ++j) {
                if (j >= travel_time[i][k] && k != i) {
                    dp[i][j] = max(dp[i][j], dp[k][j - travel_time[i][k]] + pumping_rate[k]);  // Corrected index
                }
            }
        }
    }

    // Find the maximum water at the end of time limit
    int max_water = 0;
    for (int i = 1; i < v; ++i) {  // Corrected index
        for (int j = 1; j <= t; ++j) {
            max_water = max(max_water, dp[i][j]);
        }
    }

    return max_water;
}

int main() {
    int v, w, e, t;
    cin >> v >> w >> e >> t;

    vector<vector<int>> travel_time(v + 1, vector<int>(v + 1, INF));
    vector<int> pumping_rate(v + 1, 0);

    for (int i = 0; i < w; ++i) {
        int station;
        cin >> station;
        pumping_rate[station] = 200; // Assuming 200m3 water per minute for each pumping station
    }

    for (int i = 0; i < e; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        travel_time[a][b] = travel_time[b][a] = d;
    }

    int result = maximumWater(travel_time, pumping_rate, t);

    cout << result << endl;

    return 0;
}
