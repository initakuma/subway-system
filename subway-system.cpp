#include <iostream>
#include<queue>
#include <fstream>
#include<math.h>

using namespace std;

vector<vector <int> > graph(20);
vector<bool> v(20);

void addedge(int u,int v){
	graph[u].push_back(v);
	graph[v].push_back(u);
}

int bfs(int src,int dest){
	queue<int> q;
	int dist[20];
	int pred[20];
	for(int i=0;i<20;i++){
		dist[i]=177013;//a big value
		pred[i]=-1;
		v[i]=false;
	}
	v[src]=true;
	dist[src]=0;
	q.push(src);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=0;i<graph[u].size();i++){


			if(v[graph[u][i]]==false){
				v[graph[u][i]]=true;
				dist[graph[u][i]]=dist[u]+1;
				pred[graph[u][i]]=u;
				q.push(graph[u][i]);
				
			
			}

		}
	}
return dist[dest];
}



class account{
private:
	int amt;
	int lastdep;
	int lastarr;
public:
	int id;

	account(int id){
		amt=lastdep=lastarr=0;
		this->id = id;

	}
	int getamt(){
	return this->amt;
	}
	void updateamt(int x){
		this -> amt += x;
	}
	int getlastdep(){
	return this -> lastdep;
	}
	int getlastarr(){
	return this -> lastarr;
	}
	void payamt(int x){
	this -> amt -=x;
	}
	void updateloc(int x,int y){
		this -> lastdep = x;
	        this -> lastarr = y;	
	}
} acc(0);

void balance(){
	cout<<"Your curent SmartCard balance is: "<<acc.getamt()<<endl;
}

void topup(){
	cout<<"Enter Topup Amount: ";
	int x;
	cin>>x;
	acc.updateamt(x);
	balance();
}

void lastjourney(){
	cout<<"Your Last Journey was from "<<acc.getlastdep()<<" to "<<acc.getlastarr()<<"."<<endl;
}

void pay(){
	if(acc.getamt()<0) cout<<"Insufficient Balance!"<<endl;
	else{
		int d,c;
		cout<<"Enter Check-In Station: ";
		cin>>c;
		cout<<"Enter Destination Station: ";
		cin>>d;

		acc.updateloc(c,d);

		acc.payamt(((bfs(c,d)/2)*5) +10);
		cout<<((bfs(c,d)/2)*5)+10<<" Rs. have been deducted from the SmartCard."<<endl; 
		}
}


void quit(){
	ofstream ofs;
	ofs.open(to_string(acc.id), ios :: out);
	ofs.write((char*) &acc, sizeof(acc));
	ofs.close();
	exit(0);
}

void graphinit(){
addedge(0,1);
addedge(1,2);
addedge(2,3);
addedge(3,4);
addedge(4,5);
addedge(5,6);
addedge(6,7);
addedge(7,8);
addedge(8,9);
addedge(9,10);
addedge(5,11);
addedge(11,12);
addedge(12,13);
addedge(13,14);
addedge(14,15);
addedge(5,16);
addedge(16,17);
addedge(17,18);
addedge(18,19);

}
int main(){
	graphinit();
	bool ctrl=true;
	cout<<"Welcome to the Subway"<<endl;
		
		cout<<"Do you already have a SmartCard(Y/N)? ";
		char ch;
	       	cin>>ch;
		if(ch=='N'){
			cout<<"Enter your new SmartCard id: ";
			int tmpid;
			cin>>tmpid;
			string tempid = to_string(tmpid);
			ofstream of;
			of.open(tempid,ios :: out);
			::acc.id=tmpid;
			of.write((char*) &acc, sizeof(acc));
			
		}
		else{
			cout<<"Enter your SmartCard id: ";
			int tmpid;
			cin>>tmpid;
			string tempid = to_string(tmpid);
			ifstream in;
			in.open(tempid,ios::in);

			::acc.id=tmpid;

			in.read((char*) &acc, sizeof(acc));
			in.close();
		}	
		
	while(ctrl){
		cout<<"1) Check Current SmartCard Balance"<<endl;
		cout<<"2) Topup SmartCard"<<endl;
		cout<<"3) View Last Journey Details"<<endl;
		cout<<"4) Pay for a ticket"<<endl;
		cout<<"5) Exit"<<endl;
		cout<<"Select an option to continue: ";
		int opt;
		cin>>opt;
		switch(opt) {
			case 1: 
			balance();
			break;

			case 2:
			topup();
			break;

			case 3:
			lastjourney();
			break;

			case 4:
			pay();
			break;


			case 5:
			quit();
			break;

			default:
			cout<<"Wrong Option"<<endl;
		}

		cout<<"Do you want to continue(Y/N)? ";
		char tmp;
		cin>>tmp;
		if(tmp=='N') ctrl=false;
	}

quit();
return 0;
}

