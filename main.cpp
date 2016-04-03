#include <iostream>
#include <fstream> 
#include <cstring>
#include <string>
#include <vector>

using namespace std;

//input params
int rec_size1,rec_size2, page_size, avail_pages, max_h_rounds;

//created pseudo params 
int no_of_buckets,rec_per_page1,rec_per_page2;

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

//set derived parameters
void set_derived_params()
{
	no_of_buckets = avail_pages - 1;
	rec_per_page1 = page_size/rec_size1;
	rec_per_page2 = page_size/rec_size2;
}


//return no. of records in a file
int get_no_of_rec(int cur_round, string cur_bucket,int relation_no)
{
	ifstream ifs;

	string s=to_string(relation_no);
	char *ss=new char[s.size()+1];
	ss[s.size()]=0;
	memcpy(ss,s.c_str(),s.size());

	char str[]="relation";
	if(cur_round==1)
	{
		strcat(str,ss);
		strcat(str,".txt");
	}
	else
	{
		strcat(str,ss);

		string s1=to_string(cur_round);
		char *rd=new char[s1.size()+1];
		rd[s1.size()]=0;
		memcpy(rd,s1.c_str(),s1.size());

		string s2=cur_bucket;
		char *buck=new char[s2.size()+1];
		buck[s2.size()]=0;
		memcpy(buck,s2.c_str(),s2.size());

		strcat(str,".round");
		strcat(str,rd);
		strcat(str,".bucket");
		strcat(str,buck);
		strcat(str,".txt");
	}
	ifs.open(str);

	int count=0,val;
	while (ifs.good()) 
	{
	    ifs>>val;
	    count++;
  	}

  	ifs.close();
  	return count;
}

//returns size in pages
int get_size(int cur_round, string cur_bucket,int relation_no)
{
	int no_of_records,size_in_pages;
	
	no_of_records=get_no_of_rec(cur_round,cur_bucket,relation_no);
	
	if(no_of_records%rec_per_page1==0)
	{
		size_in_pages=no_of_records/rec_per_page1;	
	}
	else
	{
		size_in_pages=no_of_records/rec_per_page1;
		size_in_pages++;
	}
	
	return size_in_pages;
}

//get file data in a vector.
vector<int> get_data(int cur_round, string cur_bucket,int relation_no)
{
	ifstream ifs;

	string s=to_string(relation_no);
	char *ss=new char[s.size()+1];
	ss[s.size()]=0;
	memcpy(ss,s.c_str(),s.size());

	char str[]="relation";
	if(cur_round==1)
	{
		strcat(str,ss);
		strcat(str,".txt");
	}
	else
	{
		strcat(str,ss);

		string s1=to_string(cur_round);
		char *rd=new char[s1.size()+1];
		rd[s1.size()]=0;
		memcpy(rd,s1.c_str(),s1.size());

		string s2=cur_bucket;
		char *buck=new char[s2.size()+1];
		buck[s2.size()]=0;
		memcpy(buck,s2.c_str(),s2.size());

		strcat(str,".round");
		strcat(str,rd);
		strcat(str,".bucket");
		strcat(str,buck);
		strcat(str,".txt");
	}
	ifs.open(str);
	std::vector<int> v;
	int val;
	while(ifs.good())
	{
		ifs>>val;
		v.push_back(val);
	}

	return v;

}

void update_log(int cur_round,string cur_bucket)
{
	/*
		Size of relation 1: 3 pages
		Size of relation 2: 4 pages
		Total number of available pages: 5
		Number of buckets in hash table: 4

		Hashing round and bucket no --
	*/
	int size_in_pages;
	size_in_pages=get_size(cur_round,cur_bucket,1);
	f_log<<"Size of relation 1: "<<size_in_pages<<" pages\n";

	size_in_pages=get_size(cur_round,cur_bucket,2);
	f_log<<"Size of relation 2: "<<size_in_pages<<" pages\n";

	f_log<<"Total number of available pages: "<<avail_pages<<endl;
	f_log<<"\nHashing round no: "<<cur_round<<" , Hashing bucket no: "<<cur_bucket<<endl;
	f_log<<"\n\n";
}

void update_result(int cur_round, string cur_bucket)
{

	int size1=get_size(cur_round,cur_bucket,1);
	int size2=get_size(cur_round,cur_bucket,2);

	int tot_size=size1+size2;
	f_result<<"\nHashing round no: "<<cur_round<<"\nHashing bucket no: "<<cur_bucket<<endl;
	f_result<<"Total size is "<<tot_size<<" pages.\n";
	f_result<<"Total available pages are"<<avail_pages<<" pages.\n";
}

//find if 2 files can be joined in the main memory
bool can_be_joined(int cur_round, string cur_bucket)
{
	int size1=get_size(cur_round,cur_bucket,1);
	int size2=get_size(cur_round,cur_bucket,2);

	if((size1+size2)<avail_pages)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

//join 2 files in main memory - needs to checked if possible before by calling can_be_joined
void join_them(int cur_round, string cur_bucket,vector<int> vec1, vector<int> vec2)
{
	int i,j,len1=vec1.size();
	int len2=vec2.size();

	update_result(cur_round,cur_bucket);
	f_result<<"Performing in memory join:\nMatching pairs are: \n";

	int ff=0;

	for(i=1;i<len1;i++)
	{
		for(j=1;j<len2;j++)
		{
			if(vec1[i]==vec2[j])
			{
				ff=1;
				f_result<<vec1[i]<<" , "<<vec1[i]<<endl;
				break;
			}
		}
	}
	if(ff==0)
	{
		f_result<<"..No matching tuples found!..\n";
	}

}

//create buckets for both the files and fill it into corresponding files  
void create_buckets(int cur_round, string cur_bucket)
{

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
	update_log(cur_round,cur_bucket);
	
	std::vector<int> vec1;
	std::vector<int> vec2;

	vec1=get_data(cur_round,cur_bucket,1);
	vec2=get_data(cur_round,cur_bucket,2);

	int size1=vec1.size();
	int size2=vec2.size();

	if(size1==0 || size2==0)
	{
		update_result(cur_round,cur_bucket);
		f_result<<"No matching tuple. No further processing required!\n";
		return;
	}
	if(can_be_joined(cur_round,cur_bucket))
	{
		join_them(cur_round,cur_bucket,vec1,vec2);
	}
	else
	{
		if(cur_round==max_h_rounds)
		{
			final_flag=0;
			cout<<"Maximum rounds reached! Cannot perform join at bucket : "<<cur_bucket<<endl;
			f_log<<"Maximum rounds reached! Cannot perform join at bucket : "<<cur_bucket<<endl;
			return;
		}
		//create buckets for both files having a file corresponding to each bucket!
		create_buckets(cur_round,cur_bucket);
		
		//call recursively for each bucket
		int i;
		for(i=1;i<=no_of_buckets;i++)
		{
			string i2s=to_string(i);
			solver(cur_round+1,cur_bucket+i2s);
		}	
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

	//set other derived parameters;
	set_derived_params();

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

	f_log.close();
	f_result.close();

    return 0;
}