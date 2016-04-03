# HashBasedJoin
Equi Join between 2 relations using hashing technique to fit buckets in main memory

Assumptions and specifications of hash based join code - 

- Lanugage used - C++11
- input files -	relation1.txt, relation2.txt
- input parameters - 
record size- int rec_size1,rec_size2
page size- int page_size
# available pages - int avail_pages
maximum no. of hashing rounds - int max_h_rounds

Hash function format for different rounds. (for now) 
no_of_buckets are from 1 to ( page_size-1 ).

H_i : hash function for round i 
H_i(val) = (val + ((sum of digits)^2)*i) mod no_of_buckets

- Only 1 column in input relation files, which contains integer values (int)
- Type of join - Equi join , where for an input A, a matching pair means A,A
- Output files - output_log.txt, output_result.txt

- intermediate files naming format --

format example - relation1.round2.bucket12.txt - splitting bucket 1 of round 1 in relation 1 to bucket 2 in round 2 creates this file.
Note that round i file is created as an output after round 2.
i.e. First time splitting gives round 1 files. 

- This is only a simulation. 

Protocol.. create all files for all buckets even if they are empty!!!