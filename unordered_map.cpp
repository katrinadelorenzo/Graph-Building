#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	unordered_map<string,int> wordsCount;
	char filename[256];
	ifstream input; //declare an ifstream object, which represents a disk file from which
	  //we will read info. 
	string word;

	cout <<"Enter the file you want to analyze:";
	cin >> filename;

	//Open the disk file 
	input.open (filename);

	if (input.is_open())
	{
		//reading from the file is similar to reading from standard input (cin)
		while (input >> word){ //as long as we successfully read a word 
			wordsCount[word]++;
			//when a word is first encounted, and wordsCount[word] is first
			//accessed, the value will be initialzied to 0 automatically 
			//Increment the count for the word 
		} //continue until we reached the end of file 

		//Close the file 
		input.close();

	} else
	{
		cout <<"Failed to open file " << filename<<endl;
		exit(1);
	}


	//Search a map 
	char cont;
	do{ 
		cout <<"Enter a word:";
		cin >> word;
		unordered_map<string,int>::iterator it;

		it = wordsCount.find(word);
		if (it==wordsCount.end())
		{
			cout <<" does not appear\n";
			//if accessed (as below), it will be initialized to 
			// default value, for int, it's 0 
			cout <<"if accessed?"<<wordsCount[word]<<endl;
		}
		else 
			cout <<" appears "<<wordsCount[word]<<" times\n";

		cout <<"Continue (y/n)?";
		cin >> cont;
	} while (cont=='y');

	//iterate through a map
	cout <<"Display the words and count\n";
	unordered_map<string,int>::iterator it;
	cout <<"word   count\n";
	for (it=wordsCount.begin();it!=wordsCount.end();it++)
	{
		cout <<it->first<<" "<<it->second<<endl;
	}
}
