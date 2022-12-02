#include <iostream>
#include <fstream>
#include <vector>
// Add additional libraries you need here
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    }
    else {
		// Read input
		ifstream inFile(argv[1]);
		int T, B, R, cr;
		int fr, gr;
		inFile >> T >> B >> R;
		std::vector<int> f(R+1); // Allows indexing from 1 to R.
		std::vector<int> g(R+1); // Allows indexing from 1 to R.
		std::vector<int> c(R+1); // Allows indexing from 1 to R.
		for (int r = 1; r <= R; r++) {
			inFile >> fr >> gr >> cr;
			f[r] = fr;
			g[r] = gr;
			c[r] = cr;
		}
		inFile.close();

		bool solExists;
		int totCapEx; // Total capital expenditure.
		double maxExpectedRevenue; // Maximum expected annual revenue.
		vector<int> trucks(R+1);
		// Trucks to purchase on each route (1 to R)
		// 	to achieve max expected annual revenue.
		//  Store values in index 1 to R.

		// Place your algorithm here
		// If you need to create a function, place the function above the main function
		// If there's a solution (i.e., solExists == True), the results of your algorithm
		//		should be placed in variables totCapEx, maxExpedtedRevenue and trucks.
		// ****************************************************************************** //
		//check

		for(int i = 0; i < f.size();i++){
            if(f[i]!=0){
                solExists=true;
            }else{
                solExists=false;
            }
		}

		if(solExists){
            vector<int> val;
            vector<int> wt;
            for(int i = 0; i <= R; i++){
                int v = 50 * (g[i]-f[i]);
                for(int j = 0; j < T; j++){
                    val.push_back(v);
                    wt.push_back(c[i]);
                }
            }

            vector<vector<int>> dp(val.size()+1,vector<int>(B+1));
/*
            int dp[val.size()+1][B+1];
            */
            //Build table dp[][] for bottom up manner
            for(int i = 0; i <= val.size();i++){
                for(int j = 0; j <= B;j++){
                    if(i==0 || j==0){
                        dp[i][j] = 0;
                    }else if(wt[i-1]<=j){
                        dp[i][j] = max(val[i-1]+
                                       dp[i-1][j-wt[i-1]],
                                       dp[i-1][j]);
                    }else{
                        dp[i][j] = dp[i-1][j];
                    }
                }
            }
            maxExpectedRevenue = floor(dp[val.size()][B]/1000);
            int result = dp[val.size()][B];
            int temp = B;
            for(int i = val.size(); i>0 && result > 0;i--){
                if(result == dp[i-1][temp]){
                    continue;
                }else{
                    trucks[floor((i-1)/T)] += 1;
                    totCapEx += wt[i-1];
                    result = result - val[i-1];
                    temp = temp - wt[i-1];
                }
            }
		}

		// ****************************************************************************** //

		// Print output
		if (solExists) {
			cout << T << " " << B << " " << totCapEx << " " << maxExpectedRevenue << "\n";
			for (int r = 1; r <= R; r++) {
				cout << r << " ";
			}
			cout << "\n";
			for (int r = 1; r <= R; r++) {
				cout << trucks[r] << " ";
			}
		}
		else {
			cout << "No Solution";
		}
		cout << "\n";
    }

    return 0;
}
