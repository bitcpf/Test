#include <iostream>

bool inc( int *indexes, int *limit, int n  )
{
	if( ++indexes[n] <= limit[n]  )
		return true;
	if( n == 0 ) return false;
	if( inc( indexes, limit, n-1  )  ) {
		indexes[n] = 0;
		return true;

	}
	return false;


}

int main()
{
	const size_t N=3;
	int indexes[N];
	int limits[] = {2,2,1};
	for( size_t i = 0; i < N; ++i  ) indexes[i] = 0;

	do {
		for( size_t i = 0; i < N; ++i  ) std::cout << indexes[i] << ' ';
		std::cout << std::endl;

	} while( inc( indexes, limits, N-1  )  );
	return 0;

}
