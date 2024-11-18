#include<bits/stdc++.h> 
using namespace std; 

// C++ implementation of First - Fit algorithm 
// Function to allocate memory to blocks as per First fit algorithm 
void firstFit(int blockSize[], int m, int processSize[], int n) 
{ 
	// Stores block id of the block allocated to a process 
	vector<int>allocation(n,-1); 

	// pick each process and find suitable blocks according to its size ad assign to it 
	for (int i = 0; i < n; i++) 
	{ 
		for (int j = 0; j < m; j++) 
		{ 
			if (blockSize[j] >= processSize[i]) 
			{ 
				// allocate block j to p[i] process 
				allocation[i] = j; 
				// Reduce available memory in this block. 
				blockSize[j] -= processSize[i]; 
				break; 
			} 
		} 
	} 

	cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
	for (int i = 0; i < n; i++) 
	{ 
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		if (allocation[i] != -1) 
			cout << allocation[i] + 1; 
		else
			cout << "Not Allocated"; 
		cout << endl; 
	} 
} 

// C++ implementation of Best - Fit algorithm 
// Method to allocate memory to blocks as per Best fit algorithm 
void bestFit(int blockSize[], int m, int processSize[], int n) 
{ 
	// Stores block id of the block allocated to a process 
	vector<int>allocation(n,-1); 

	// pick each process and find suitable blocks according to its size ad assign to it 
	for (int i = 0; i < n; i++) 
	{ 
		// Find the best fit block for current process 
		int bestIdx = -1; 
		for (int j = 0; j < m; j++) 
		{ 
			if (blockSize[j] >= processSize[i]) 
			{ 
				if (bestIdx == -1) 
					bestIdx = j; 
				else if (blockSize[bestIdx] > blockSize[j]) 
					bestIdx = j; 
			} 
		} 

		// If we could find a block for current process 
		if (bestIdx != -1) 
		{ 
			// allocate block j to p[i] process 
			allocation[i] = bestIdx; 
			// Reduce available memory in this block. 
			blockSize[bestIdx] -= processSize[i]; 
		} 
	} 

	cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
	for (int i = 0; i < n; i++) 
	{ 
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		if (allocation[i] != -1) 
			cout << allocation[i] + 1; 
		else
			cout << "Not Allocated"; 
		cout << endl; 
	} 
} 

// C++ implementation of worst - Fit algorithm 
// Function to allocate memory to blocks as per worst fit algorithm 
void worstFit(int blockSize[], int m, int processSize[], int n) 
{ 
	// Stores block id of the block allocated to a process 
	vector<int>allocation(n,-1); 

	// pick each process and find suitable blocks according to its size ad assign to it 
	for (int i=0; i<n; i++) 
	{ 
		// Find the best fit block for current process 
		int wstIdx = -1; 
		for (int j=0; j<m; j++) 
		{ 
			if (blockSize[j] >= processSize[i]) 
			{ 
				if (wstIdx == -1) 
					wstIdx = j; 
				else if (blockSize[wstIdx] < blockSize[j]) 
					wstIdx = j; 
			} 
		} 

		// If we could find a block for current process 
		if (wstIdx != -1) 
		{ 
			// allocate block j to p[i] process 
			allocation[i] = wstIdx; 
			// Reduce available memory in this block. 
			blockSize[wstIdx] -= processSize[i]; 
		} 
	} 

	cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
	for (int i = 0; i < n; i++) 
	{ 
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		if (allocation[i] != -1) 
			cout << allocation[i] + 1; 
		else
			cout << "Not Allocated"; 
		cout << endl; 
	} 
} 

void nextFit(int blockSize[],int m,int processSize[],int n)
{
    // Stores block id of the block allocated to a process 
	vector<int>allocation(n,-1);

    //Pointer to keep track of where last allocation was made
    int j=0;
    //Counter to keep track of how many blocks have been visited

    //Fetching the process and allocating block
    for (int i = 0; i < n; i++) { 
  
        int count=0;
        // Do not start from beginning 
        while (count < m) 
        { 
            if (blockSize[j] >= processSize[i]) { 
  
                // allocate block j to p[i] process 
                allocation[i] = j; 
                // Reduce available memory in this block. 
                blockSize[j] -= processSize[i]; 
  
                break; 
            } 
  
            // mod m will help in traversing the blocks from starting block after we reach the end.  
            j = (j + 1) % m; 
            count++;
        } 
    } 
    
    cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
	for (int i = 0; i < n; i++) 
	{ 
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		if (allocation[i] != -1) 
			cout << allocation[i] + 1; 
		else
			cout << "Not Allocated"; 
		cout << endl; 
	} 
}

// Driver code 
int main() 
{ 
	// int blockSize[] = {100, 500, 200, 300, 600}; 
	// int processSize[] = {212, 417, 112, 426}; 
    
    int blockSize[] = {40, 10};
    int processSize[] = {10, 20, 30};
	
    int m = sizeof(blockSize) / sizeof(blockSize[0]); 
	int n = sizeof(processSize) / sizeof(processSize[0]); 

//     cout<<"--------------------------------First Fit--------------------------------"<<endl;
//	 firstFit(blockSize, m, processSize, n); 
//     cout<<endl<<endl;    

     cout<<"--------------------------------Best Fit--------------------------------"<<endl;
     bestFit(blockSize, m, processSize, n); 
     cout<<endl<<endl;  

    // cout<<"--------------------------------Worst Fit--------------------------------"<<endl;
    // worstFit(blockSize, m, processSize, n); 
    // cout<<endl<<endl;  

//    cout<<"--------------------------------Next Fit--------------------------------"<<endl;
//    nextFit(blockSize, m, processSize, n);
//    cout<<endl<<endl;  

	return 0 ; 
} 
