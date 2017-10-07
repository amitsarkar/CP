//Author: Amit Sarkar
#include <iostream>

using namespace std;
//#define SAMPLE_INPUT
#define MAX_N 200001
#define MAX_DUE 10000

long due[MAX_N] = { 0, };
long out[MAX_N] = { 0, };
long balance[MAX_N] = { 0, };
long edge_list[MAX_N] = { 0, };
bool visited[MAX_N] = { false, };
long cycles[MAX_N] = { 0, };

int main()
{

#ifdef SAMPLE_INPUT
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	long u = 0, val = 0, N = 0;
	scanf("%ld",&N);
	for (long i = 1; i <= N; i++)
	{
		scanf("%ld %ld", &u, &val);
		edge_list[i] = u;
		due[i] = val;
		out[u] += val;
	}

	long result_sum = 0;

	for (long i = 1; i <= N; i++)
	{
		if (!out[i])
		{
			long repay = due[i];
			result_sum += repay; //money from town
			long j = edge_list[i];
			balance[j] += due[i];
			due[i] = 0;
			visited[i] = 1;

			//clear dues till reaching a multi-donor or cycle-node
			while (due[j] && out[j] == balance[j])
			{
				//need to clear dues if any
				if (balance[j] < due[j])
				{
					repay = due[j] - balance[j]; //money from town
					result_sum += repay;
				}
				repay = due[j]; //pay to lender node
				due[j] = 0;
				visited[j] = true;
				j = edge_list[j];
				balance[j] += repay;
			}
		}
	}

	long no_of_cycles = 0;
	//only cycles remaining now, find cycle count and minimum refund in each cycle
	for (long i = 1; i <= N; i++)
	{
		if (due[i] && !visited[i])
		{
			long min = MAX_DUE, min_i=0;
			long repay = due[i] - balance[i];
			if (repay < min)
			{
				min = repay;
				min_i = i;
			}
			visited[i] = true;
			long j = edge_list[i];
			while (j != i)
			{
				long repay = due[j] - balance[j];
				if (repay < min)
				{
					min = repay;
					min_i = j;
				}
				visited[j] = 1;
				j = edge_list[j];
			}
			cycles[no_of_cycles] = min_i;
			no_of_cycles++;
		}
	}

	//process cycles
	for (long i = 0; i < no_of_cycles; i++)
	{
		long j = cycles[i];
		long repay = 0;
		long k = 0;
		do
		{
			repay = due[j]>balance[j] ? (due[j] - balance[j]) : 0;
			result_sum += repay;
			k = edge_list[j];
			balance[k] += due[j];
			due[j] = 0;
			j = k;
		} while (due[j]);
	}

	printf("%ld\n", result_sum);
#ifdef SAMPLE_INPUT
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}
