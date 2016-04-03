#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

int rec_size1,rec_size2, page_size, avail_pages, max_h_rounds;

ofstream f_log,f_result;

bool final_flag=1;

//take input params from std in.
void take_input_params()
{
	
	cout<<"Enter record size of first file:\n";
	cin>>rec_size1;
	
	cout<<"Enter record size of second file:\n";
	cin>>rec_size2;

	cout<<"Enter the page size:\n";
	cin>>page_size;

	cout<<"Enter the number of available pages in the memory:\n";
	cin>>avail_pages;

	cout<<"Enter maximum number of hashing rounds which can be performed.\n";
	cin>>max_h_rounds;
}

void update_log()
{
	/*
		Size of relation 1: 3 pages
		Size of relation 2: 4 pages
		Total number of available pages: 5
		Number of buckets in hash table: 4

		Hashing round and bucket no --
	*/

}



/*
	solve the work	
	input params - round no.- WHICH IS TO BE USED TO CREATE FILES , bucket no. string. 
	file names can be found from round no and bucket number string, except for round 1
	file names correspond to (round no - 1) files. 
	work-
		check if max. rounds is reached.
		if join is possible, 
			join 2 files, write output and return.
		else
			divide each file into buckets with appropriate names 
			and call the function for each bucket, with next round, and return.
		
*/
void solver(int cur_round, string cur_bucket)
{
	if(final_flag=0)
	{
		return;
	}

	update_log(cur_round,cur_bucket);
	
	if(cur_round>max_h_rounds)
	{
		final_flag=0;
		cout<<"Maximum rounds reached! Cannot perform join at bucket : "<<cur_bucket<<endl;
		f_log<<"Maximum rounds reached! Cannot perform join at bucket : "<<cur_bucket<<endl;
		return;
	}

	if(can_be_joined(cur_round,cur_bucket))
	{
		join_them(cur_round,cur_bucket);
	}
	else
	{
		//create buckets for both files having a file corresponding to each bucket!
		create_buckets(cur_round,cur_bucket);

		//call recursively for each bucket	
	}

}



int main()
{
	//open output files
	f_log.open("output_log.txt");
	f_result.open("output_result");

	//taking input
	cout<<"Please enter the input parameters one by one!\n";
	take_input_params();

	//solving
	cout<<"Input taken successfully!\nLets perform the hash based join.\nSpecifications can be found in README.md file.\n";

	string ini_bucket="";
	
	//round no, string for bucket number
	solver(1,ini_bucket);
	
	//final message
	if(final_flag=0)
	{
		cout<<"Hash based join is unsuccessful !"<<endl;
	}
	cout<<"Hash based join is successfully done !"<<endl;
    return 0;
}