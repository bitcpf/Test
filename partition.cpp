#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


// Recurive condition check
bool inc( int *indexes, vector<int> &limit, int n  )
{
	if( ++indexes[n] < limit[n]  )
		return true;
	if( n == 0  ) return false;
	if( inc( indexes, limit, n-1  )  ) {
		indexes[n] = 0;
		return true;

	}
	return false;
}


int helper(vector<float> &work, int m_num, int N, vector<int> &part_num, vector<vector<int> > &a, float epi){
	int ret_val = 0;

	cout << "Trace: Enter helper" << endl;
	// Calculate average load
	float sum_of_work = accumulate(work.begin(),work.end(),0);
	float avg_work = sum_of_work/N;


	//Could be a Backpack problem,O(V*Σn[i])
	//
	// Generate perm of all partitions qualify
	int idxs[work.size()];
	for(int i = 0; i < work.size(); i++){
		idxs[i] = 0;
	}
	vector<vector<int> > exe_comb;
	do {
		float m_load = 0;
		vector<int> tmp_assign;
		int over_flag = 0;
		for( int i = 0; i < work.size(); ++i  ) {
						//cout << idxs[i] << ' ';
			tmp_assign.push_back(idxs[i]);
			m_load += idxs[i]*work[i]/part_num[i];
			if(m_load > avg_work * (1+epi)) {
				over_flag = 1;
				break;
			}

		}
		//		cout <<"Work Load: " << m_load;
				//cout << endl;


		if(over_flag){
			over_flag = 0;
			continue;
		}
		if(m_load > avg_work*(1-epi) && m_load < avg_work*(1+epi)){
						//cout << "Qualify" << endl;
			exe_comb.push_back(tmp_assign);
		}
		tmp_assign.clear();
	}while( inc(idxs, part_num, work.size()-1));

	cout << "Executable combination: " << exe_comb.size() << endl;

	//No available combination, no solution
	if(exe_comb.size() == 0) return 0;

	vector<int> comb_limit;
	comb_limit.assign(N,exe_comb.size());


	for(int i = 0; i < N; i++){
		idxs[i] = 0;
	}

	do {
		vector<int> tmp_m_comb;
		tmp_m_comb.clear();
		vector<int> occu_part;
		occu_part.assign(work.size(),0);
		int part_flag = 0;
		for( int i = 0; i < N; ++i  ) {
			//cout << idxs[i] << ' ';
			tmp_m_comb.push_back(idxs[i]);
			for(int ii = 0; ii < work.size(); ii ++){
				cout << "Execomb: " << exe_comb[idxs[i]][ii] << ",";
				occu_part[ii] += exe_comb[idxs[i]][ii];
				if(occu_part[ii] > part_num[ii]){
					part_flag = i;
					++idxs[i];
					break;
				}
			}
			cout << endl;
			if(part_flag) break;
		
		}
		cout << endl;

			for(int i = 0; i < tmp_m_comb.size(); i ++){
				cout << tmp_m_comb[i] <<":";
				/*for(int ii = 0 ; ii < work.size(); ii++){
					cout << exe_comb[tmp_m_comb[i]][ii];
				}*/
				//cout << endl;

			}	
			cout << endl;




		if(part_flag){
			cout << "Prune at: " << part_flag << endl;
			part_flag = 0;
			continue;
		}

		int ret_flag = 0;
		for(int i = 0; i < work.size(); i ++){
			if(!(occu_part[i] == part_num[i])) {
				ret_flag = 0;
				break;
			}
			ret_flag = 1;
		}

		if(ret_flag){
			/*for(int i = 0; i < tmp_m_comb.size(); i ++){
				cout << tmp_m_comb[i] <<":";
				for(int ii = 0 ; ii < work.size(); ii++){
					cout << exe_comb[tmp_m_comb[i]][ii];
				}
				cout << endl;

			}	
			cout << endl;
			*/
			return 1;
		}


	}while( inc(idxs, comb_limit, N-1));

	//	Could be a N sum problem




	return ret_val;
}


bool existSolution(int N, float epi, vector<float> &work){

	// If N is power of 2, true
	if((N&(N-1)) == 0)
		return true;

	int max_p = 1;
	int d_N = N;
	while(N > 1){
		max_p =max_p << 1;
		N = N >> 1;
	}


	// Calculate the max epi needed for solution

	//float min_epi = (float(d_N - max_p))/max_p;
	//if(epi >= min_epi) return true;

	N = d_N;
	// Backtrace to find the solution exist
	vector<int> part_num;
	part_num.assign(work.size(),max_p);

	// Assign matrix
	vector<vector<int> > a(work.size(),vector<int>(N));

	return helper(work, 0, N, part_num, a, epi);

	//return false;

}

int main(){
	cout << "Enter main..." << endl;

	// Test cases:
	int N = 3;
	static const float arr[] = {2,3,5,7};
	vector<float> work (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	float epi = 0.3;



	// Calculate average load
	float sum_of_work = accumulate(work.begin(),work.end(),0);
	float avg_work = sum_of_work/N;

	if(existSolution(N,epi,work)){
		cout << "Exist Solution." << endl;
	}
	else{
		cout << "No Solution." << endl;
	}


}

