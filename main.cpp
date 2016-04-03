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
	//WF
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
	//WF
	no_of_buckets = avail_pages - 1;
	rec_per_page1 = page_size/rec_size1;
	rec_per_page2 = page_size/rec_size2;
}


//return no. of records in a file
int get_no_of_rec(int cur_round, string cur_bucket,int relation_no)
{
	//WF
	//cout<<"here - "<<cur_round<<" "<<cur_bucket<<" "<<relation_no<<endl;
	cur_round--;
	ifstream ifs;

	string s=to_string(relation_no);
	char *ss=new char[s.size()+1];
	ss[s.size()]=0;
	memcpy(ss,s.c_str(),s.size());

	
	if(cur_round==0)
	{
		char str[1000]="relation";
		strcat(str,ss);
		strcat(str,".txt");
		ifs.open(str);
	}
	else
	{
		char str[1000]="files/relation";
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
		ifs.open(str);
	}

	

	int count=0,val;
	while (ifs.good()) 
	{
	    ifs>>val;
	    if(!ifs.fail())
	    {
	    	count++;
	    }
  	}

  	ifs.close();
  	return count;
}

//returns size in pages
int get_size(int cur_round, string cur_bucket,int relation_no)
{
	//WF
	int no_of_records,size_in_pages;
	
	no_of_records=get_no_of_rec(cur_round,cur_bucket,relation_no);
	if(relation_no==1)
	{
		int kk=no_of_records*rec_size1;
		if(kk%page_size==0)
		{
			size_in_pages=kk/page_size;	
		}
		else
		{
			size_in_pages=kk/page_size;
			size_in_pages++;
		}

	}
	else
	{
		int kk=no_of_records*rec_size2;
		if(kk%page_size==0)
		{
			size_in_pages=kk/page_size;	
		}
		else
		{
			size_in_pages=kk/page_size;
			size_in_pages++;
		}
	}
	
	return size_in_pages;
}

//get file data in a vector.
vector<int> get_data(int cur_round, string cur_bucket,int relation_no)
{
	//WF
	cur_round--;
	//cout<<cur_round<<" "<<cur_bucket<<" "<<relation_no<<endl;
	ifstream ifs;

	string s=to_string(relation_no);
	char *ss=new char[s.size()+1];
	ss[s.size()]=0;
	memcpy(ss,s.c_str(),s.size());

	
	if(cur_round==0)
	{
		char str[1000]="relation";
		strcat(str,ss);
		strcat(str,".txt");
		ifs.open(str);
	}
	else
	{
		char str[1000]="files/relation";
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
		ifs.open(str);
	}
	
	std::vector<int> v;
	int val;
	while(ifs.good())
	{
		ifs>>val;
		if(!ifs.fail())
	    {
	    	v.push_back(val);
	    }
		
	}
	ifs.close();
	return v;

}

void update_log(int cur_round,string cur_bucket)
{
	//WF
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
	f_log<<"\nHashing round no: "<<cur_round<<endl;
	f_log<<"\n\n";
}

void update_result(int cur_round, string cur_bucket)
{
	//WF
	int size1=get_size(cur_round,cur_bucket,1);
	int size2=get_size(cur_round,cur_bucket,2);

	int tot_size=size1+size2;
	f_result<<"Hashing round no: "<<cur_round<<"\nHashing bucket no: "<<cur_bucket<<endl;
	f_result<<"Total size is "<<tot_size<<" pages.\n";
	f_result<<"Total available pages are "<<avail_pages<<" pages.\n\n";
}

//find if 2 files can be joined in the main memory
bool can_be_joined(int cur_round, string cur_bucket)
{
	//WF
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
	//WF
	int i,j,len1=vec1.size();
	int len2=vec2.size();

	update_result(cur_round,cur_bucket);
	f_result<<"Performing in memory join:\nMatching pairs are:\n";

	int ff=0;

	for(i=0;i<len1;i++)
	{
		for(j=0;j<len2;j++)
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

int get_sum_of_digits(int val)
{
	int sum=0,n=val;
	while(n%10>0)
	{
		sum=sum + n%10;
		n=n/10;
	}
	return sum;
}

//find bucket using hashing
int find_bucket(int val,int cur_round)
{
	int bucket;
	int sum=get_sum_of_digits(val);
	bucket=((val + (sum*sum*cur_round))%no_of_buckets) + 1;
	return bucket;
}

//transfer contents to a secondary storage file
void transfer(vector<int> vec, int cur_round, string cur_bucket, int relation_no)
{
	//cout<<vec.size()<<" "<<cur_round<<" "<<cur_bucket<<" "<<relation_no<<endl;
	
	ofstream ofs;
	
	string s=to_string(relation_no);
	char *ss=new char[s.size()+1];
	ss[s.size()]=0;
	memcpy(ss,s.c_str(),s.size());

	char str[1000]="files/relation";

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
	
	ofs.open(str,ios::app);
	
	int len=vec.size();
	//cout<<"len is "<<len<<endl;
	
	for(int i=0;i<len;i++)
	{
		ofs<<vec[i]<<endl;
	}
	
	ofs.close();
	
}


//create buckets for both the files and fill it into corresponding files  
void create_buckets(int cur_round, string cur_bucket,int relation_no)
{
	ifstream ifs;
	cur_round--;
	string s=to_string(relation_no);
	char *ss=new char[s.size()+1];
	ss[s.size()]=0;
	memcpy(ss,s.c_str(),s.size());

	
	if(cur_round==0)
	{
		char str[1000]="relation";
		strcat(str,ss);
		strcat(str,".txt");
		ifs.open(str);
	}
	else
	{
		char str[1000]="files/relation";
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
		ifs.open(str);
	}
	
	cur_round++;
	int val;
	vector< vector<int> > buckets(no_of_buckets+1);

	f_log<<"Reading relation "<<relation_no<<" , bucket "<<cur_bucket<<endl;
	int tup=1;
	
	while(ifs.good())
	{
		ifs>>val;
		//cout<<"---------"<<endl;
		if(!ifs.fail())
		{	
			//cout<<"1";
			int buck=find_bucket(val,cur_round);
			buckets[buck].push_back(val);
			f_log<<"Tuple "<<tup<<": "<<val<<" Mapped to bucket: "<<cur_bucket+to_string(buck)<<endl;
			
			if(relation_no==1)
			{
				//cout<<"2"<<endl;
				if(buckets[buck].size()>=rec_per_page1)
				{
					//cout<<"here"<<endl;
					transfer(buckets[buck], cur_round, cur_bucket+to_string(buck), relation_no);
						//cout<<"there"<<endl;
					buckets[buck].clear();
					f_log<<"Page for bucket "<<cur_bucket+to_string(buck)<<" full. Flushed to secondary storage.\n";
				}
			}
			else
			{
				//cout<<"3"<<endl;
				if(buckets[buck].size()>=rec_per_page2)
				{
					transfer(buckets[buck], cur_round, cur_bucket+to_string(buck), relation_no);
					buckets[buck].clear();
					f_log<<"Page for bucket "<<cur_bucket+to_string(buck)<<" full. Flushed to secondary storage.\n";
				}
			}
			
			tup++;	
		}
		
	}
	int pp;
	for(int pp=1;pp<=no_of_buckets;pp++)
	{
		transfer(buckets[pp], cur_round, cur_bucket+to_string(pp), relation_no);
		buckets[pp].clear();
	}

	f_log<<"Leftover data written to secondary storage\n";

	f_log<<"\nDone with relation"<<relation_no<<endl;
	f_log<<"Created following files.\n";
	int kk;
	//cout<<"hhhhhhhhhhhhh\n";
	for(kk=1;kk<=no_of_buckets;kk++)
	{
		int size_in_pages=0;
		size_in_pages=get_size(cur_round+1,cur_bucket+to_string(kk),relation_no);
		
		//int aa=get_no_of_rec(cur_round+1,cur_bucket+to_string(kk),relation_no);
		//f_log<<"aa is "<<aa<<endl;
		f_log<<"relation"<<relation_no<<".round"<<cur_round<<".bucket"<<cur_bucket+to_string(kk)<<": "<<size_in_pages<<" pages\n";
	}

	f_log<<"\n\n";
	ifs.close();
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
	f_log<<"cur round is "<<cur_round<<endl;
	update_log(cur_round,cur_bucket);
	
	int size1=get_no_of_rec(cur_round,cur_bucket,1);
	int size2=get_no_of_rec(cur_round,cur_bucket,2);
	//cout<<"----"<<size1<<" "<<size2<<endl;
	
	if(size1==0 || size2==0)
	{
		//cout<<"size1size2"<<endl;
		
		update_result(cur_round,cur_bucket);
		f_result<<"No matching tuple. No further processing required!\n";
		
		return;
	}
	
	if(can_be_joined(cur_round,cur_bucket))
	{
		//cout<<"can_be_joined is true"<<endl;
		std::vector<int> vec1;
		std::vector<int> vec2;

		vec1=get_data(cur_round,cur_bucket,1);
		vec2=get_data(cur_round,cur_bucket,2);

		join_them(cur_round,cur_bucket,vec1,vec2);
		
	}
	else
	{
		//cout<<"can_be_joined is false "<<cur_bucket<<endl;
		
		if(cur_round>max_h_rounds)
		{
			final_flag=0;
			cout<<"Maximum rounds reached! Cannot perform join at bucket : "<<cur_bucket<<endl;
			f_log<<"Maximum rounds reached! Cannot perform join at bucket : "<<cur_bucket<<endl;
			return;
		}
		//create buckets for both files having a file corresponding to each bucket!
		f_log<<"Hashing round "<<cur_round<<":"<<endl;
		create_buckets(cur_round,cur_bucket,1);
		
		create_buckets(cur_round,cur_bucket,2);
		
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
	else
	{
		cout<<"Hash based join is successfully done !"<<endl;	
	}
	f_log.close();
	f_result.close();

    return 0;
}