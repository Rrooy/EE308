#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
void collatFile(string file_content);
vector <string> judge; 
string collated_words[1000];
string collated_keywords[1000];
int words_count = 0;
int keyword_num = 0;
int main()
{
	string filename,content;
	char buffer[1];
	cout<<"File path:";	
	cin>>filename;	
	ifstream fin(filename.c_str());   
	if ( ! fin){
        cout << "Failed to open file." <<endl;
    }
    //Read the code content.
	else{
        while (getline(fin,content)){
            collatFile(content);			  
        }
        fin.close();
    }
}

void collatFile(string file_content)
{
	int n = file_content.length();
	string collated_str;
	int brace = 0;
    //Turn the string into an array and do the following split.
	const char* arr_content = file_content.data();  
    //To identify and recombine characters one by one.
	for(int i = 0;i <= n;i++){
		if(arr_content[i] == '{'){
			brace=1;
		}
		if(arr_content[i] == '}'){
			brace=2;
		}		
		if((arr_content[i] >= 'a'&&arr_content[i] <= 'z'||arr_content[i] >= 'A'&&arr_content[i] <= 'Z')){
			collated_str += arr_content[i];
		}
        //According to the "if", "else" and the position of the brackets, the element is pushed into the vector used to determine the number of i_e and i_e_e.
		else{
			if(collated_str == ""){
			 	if(brace == 1){
                    judge.push_back("{");
                }
			 	if(brace == 2){
                    judge.push_back("}");
                }
			 	brace = 0;
			 	continue;
			}
			collated_words[words_count++] = collated_str;  
            //Remove the space after the else, if it is followed by an if, it is an i_e_e statement.
			if(collated_str == "else"){
				int j = i;
				while(arr_content[j] == ' '&& j <= n){
                    j++;
                }
				if(arr_content[j] == 'i'&&arr_content[j+1] == 'f'){
					judge.push_back("else_if");
					i = j+2;
					keyword_num++;
				}
				else{
                    judge.push_back("else");
                }

			}
			if(collated_str == "if"){
			 	if(judge.back() != "else"){
                    judge.push_back("if");
                }
			}
            //Push the curly braces into the vector.
			if(brace == 1){
                judge.push_back("{");
            }
			if(brace == 2){
                judge.push_back("}");
            }
			brace = 0;
			collated_str = "";
			continue;
		}
	}
}