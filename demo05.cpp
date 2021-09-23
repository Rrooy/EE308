void showData(int level)
{
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