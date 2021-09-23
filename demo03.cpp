#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stack>
using namespace std;
string keyword_sheet[] = {
	"auto","break","case","char","const","continue","default",
	"double","do","else","enum","extern","float","for","goto","if",
	"int","long","register","return","short","signed","sizeof","static",
	"struct","switch","typedef","union","unsigned","void","volatile","while"};
void collatFile(string file_content);
void countKeywords(string content[]);
void countSwitchCase(string content[]);
void countIfElse();
vector <string> judge; 
string collated_words[2000];
int words_num = 0;
int words_count = 0;
int keywords_count = 0;
int switch_count = 0;
int case_count = 0;
int switch_case_arr[1000] = {0};
int i_e_e_count = 0;
int i_e_count = 0;
int main()
{
	string filename,content;
	char buffer[1];
	cout<<"File path:";	
	cin>>filename;	
	int level;
	cout<<"Please enter the level:";
	cin>>level;
	ifstream ifs(filename.c_str());   
	if ( ! ifs){
        cout << "Failed to open file." <<endl;
    }
    //Read the code content.
	else{
        while (getline(ifs,content)){
            collatFile(content);			  
        }
        ifs.close();
    }
	countKeywords(collated_words);
	countSwitchCase(collated_words);
	countIfElse();
	if(level==1){
		cout<<"total num: "<<keywords_count<<endl;
	}
	if(level==2){
		cout<<"total num: "<<keywords_count<<endl;
		cout<<"switch num: "<<switch_count<<endl;
		cout<<"case num: ";
		for(int i = 1;i <= case_count;i++){
			cout<<switch_case_arr[i]<<" ";
		}
		cout<<endl;
	}
	if(level==3){
		cout<<"total num: "<<keywords_count<<endl;
		cout<<"switch num: "<<switch_count<<endl;
		cout<<"case num: ";
		for(int i = 1;i <= case_count;i++){
			cout<<switch_case_arr[i]<<" ";
		}
		cout<<endl;
		cout<<"if-else num: "<<i_e_count<<endl;
	}
	if(level==4){
		cout<<"total num: "<<keywords_count<<endl;
		cout<<"switch num: "<<switch_count<<endl;
		cout<<"case num: ";
		for(int i = 1;i <= case_count;i++){
			cout<<switch_case_arr[i]<<" ";
		}
		cout<<endl;
		cout<<"if-else num: "<<i_e_count<<endl;
		cout<<"if-elseif-else num: "<<i_e_e_count<<endl;
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
			collated_words[words_num++] = collated_str;  
            //Remove the space after the else, if it is followed by an if, it is an i_e_e statement.
			if(collated_str == "else"){
				int j = i;
				while(arr_content[j] == ' '&& j <= n){
                    j++;
                }
				if(arr_content[j] == 'i'&&arr_content[j+1] == 'f'){
					judge.push_back("else_if");
					i = j+2;
					keywords_count++;
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
/*
	Count how many keywords there are.
*/
void countKeywords(string content[])
{
	for(int i = 0;i < words_num;i++){
		for(int j = 0;j <= 31;j++){
		    if(content[i] == keyword_sheet[j]){
			  	keywords_count++;
		    }
		}
	}
}
/*
	Count the number of switches and cases.
*/
void countSwitchCase(string content[])
{
	for(int i = 0;i < words_count;i++){
		if(content[i] == "switch"){ 
			switch_count++;
			case_count++; 
		}
		if(content[i] == "case"){
			switch_case_arr[case_count]++;
	    }
	}
}
/*
	Count the number of if-else and if-elseif statements.
*/
void countIfElse() 
{
	stack <string> pocket;  
	stack <int> i_e_e; 
	for (int i = 0;i < judge.size();i++){
		if (judge[i] == "{"){
			pocket.push("{");
			i_e_e.push(0);
		}
		else if (judge[i] == "}") {  
			while (pocket.top() != "{"){
				pocket.pop();
			}
			pocket.pop();
			i_e_e.pop();
		}
		else if (judge[i] == "if"){  
			pocket.push("if");
			i_e_e.pop();
			i_e_e.push(0);
		}
		else if (judge[i] == "else"){  
			if (i_e_e.top()) {
				i_e_e_count++;
			}
			else{
				i_e_count++;
			}
			i_e_e.pop();
			i_e_e.push(0);
			while (pocket.top() != "if"){ 
				pocket.pop();
			}
			pocket.pop();
		}
		else if (judge[i] == "else_if"){
			i_e_e.pop();
			i_e_e.push(1);
		}
	}
}