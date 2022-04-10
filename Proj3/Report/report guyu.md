#Introduction of algorithm
When the test data is randomly generated, it is stored in structure array first, and then the structure array is arranged from small to large by bubble sort, and then written into the file and saved

##algorithm Detailed introduction
1. Enter relation number m and fruit number n
2. Read m group relation, if the newly generated relation already exists (here using a while loop, when the new relation is not repeated break, otherwise infinite loop), then regenerate and save into the array
3. Bubble sort according to the number size of the first fruit in the relational structure
4. Read the rearranged structure array into the created file
5. Read n random numbers not more than 1000 and save them in the file in descending order
6. Perform data tests with the data in the file
