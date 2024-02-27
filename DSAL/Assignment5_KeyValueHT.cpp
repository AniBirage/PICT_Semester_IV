#include <iostream>
using namespace std;
#include<string>
int hashfunc(string n){
	int sum = 0;
	int size = n.size();
	for(int i=0;i<size;i++){
		sum += int(n[i]);
	}
	return sum%10;
}
class Node{
	string key;
	int value;
	Node* next;
public:
	Node(){
		key = "";
		value = 0;
		next = NULL;
	}
	Node(string n){
		key = n;
		value = hashfunc(n);
		next = NULL;
	}
	int returnvalue(){
		return value;
	}
	friend class HashTable;
};

class HashTable{
private:
	Node* HT[10];
public:
	HashTable(){
		for(int i=0;i<10;i++){
			HT[i] = NULL;
		}
	}
	void insert(string n){
		Node* nn = new Node(n);
		int a = nn->returnvalue();
		if(HT[a] == NULL){
			HT[a] = nn;
		}
		else{
			Node* temp = HT[a];
			while(temp->next != NULL){
				if(temp->key == n){
					cout<<"Element is already present\n";
				}
				temp = temp->next;
			}
			temp->next = nn;
		}
	}
	void search(string n){
		int a = hashfunc(n);
		if(HT[a]->key == n){
			cout<<"Key is present"<<endl;
		}
		else{
			Node* temp = HT[a];
			while(temp != NULL){
				if(temp->key == n){
					cout<<"Key is present"<<endl;
					return;
				}
				temp = temp->next;
			}
			cout<<"Key is not present :("<<endl;
		}
	}
	void del_element(string n){
		int a = hashfunc(n);
		if(HT[a] == NULL){
			cout<<"Key not present"<<endl;
		}
		else if(HT[a]->key == n){
			cout<<"Key is deleted"<<endl;
			Node* temp = HT[a];
			HT[a] = temp->next;
			delete(temp);
		}
		else{
			Node* temp = HT[a];
			Node* prev = NULL;
			while(temp != NULL){
				if(temp->key == n){
					cout<<"Key is deleted"<<endl;
					prev->next = temp->next;
					delete(temp);
					return;
				}
				prev = temp;
				temp = temp->next;
			}
			cout<<"Key is not present"<<endl;
		}
	}
	void display(){
		cout << endl;
		for(int i = 0;i<10;i++){
			if(i<9){
				cout<<i+1<<"  ";
			}
			else{
				cout<<i+1<<" ";
			}
			Node* temp = HT[i];
			while(temp != NULL){
				cout<<temp->key<<" -> ";
				temp = temp->next;
			}
			cout<<"\n";
		}
	}
};
int main(){
	HashTable ht;
	char ch;
	while(1){
		int choice;
		cout<<"1.Insert"<<endl;
		cout<<"2.Search\n";
		cout<<"3.Delete\n";
		cout<<"4.Display\n";
		cout<<"5.Exit\n";
		cout<<"Enter your choice\n";
		cin>>choice;
		if(choice == 1){
			string n;
			cout<<"Enter the string you want to insert\n";
			cin>>n;
			ht.insert(n);
		}
		else if(choice == 2){
			string n;
			cout<<"Enter the string you want to search\n";
			cin>>n;
			ht.search(n);
		}
		else if(choice == 3){
			string n;
			cout<<"Enter the string you want to delete\n";
			cin>>n;
			ht.del_element(n);
		}
		else if(choice == 4){
			ht.display();
		}
		else if(choice == 5){
			return 0;
		}
		else{
			cout<<"Enter a valid choice\n";
		}
	}
	return 0;
}