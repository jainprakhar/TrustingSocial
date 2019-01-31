#include <bits/stdc++.h>
using namespace std;

void fillMatrix(int* mat[],int r,int c)
{
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			mat[i][j] = rand()%10 + 1;
		}
	}

}

void printMatrix(int* arr[],int r,int c)
{
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

bool isSafe(int tl,int tr,int bl,int br,int r,int c)
{
	bool inside = (tl>=0 && tl<r && bl>=0 && bl<r && tr>=0 && tr<c && br>=0 && br<c);
	bool valid = (tl <= bl && tr <= br);
	return (inside && valid);
}

int sumMatrix(int* arr[],int r,int c,int tl,int tr,int bl,int br)
{
	int sum = 0;
	for(int i=tl;i<=bl;i++)
	{	
		for(int j=tr;j<=br;j++)
			sum += arr[i][j];
	}
	return sum;
}

int main()
{
	ifstream fid;
	fid.open("input1.txt");
	int r,c;
	fid >> r >> c;
	srand(time(NULL));
	int *arr[r];
	
	for(int i=0;i<r;i++)
	{
		arr[i] = new int[c];
	}

	fillMatrix(arr,r,c);
	printMatrix(arr,r,c);

	int times;
	fid >> times;

	for(int i=0;i<times;i++)
	{
		int t_i,t_j,b_i,b_j;
		if(fid.peek()!=EOF)
		{
			fid >> t_i >> t_j >> b_i >> b_j;

			if(isSafe(t_i,t_j,b_i,b_j,r,c))
			{
				cout << sumMatrix(arr,r,c,t_i,t_j,b_i,b_j) << endl;
			}
			else cout << "Please enter valid indices" << endl;
		}
		
	}

	fid.close();	
	return 0;
}