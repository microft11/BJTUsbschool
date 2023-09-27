#include <iostream>
using namespace std;

class HashTable {
	private:
		int *data;
		int size;
	public:
		HashTable(int n) {
			size = n;
			data = new int[size];
			for (int i = 0; i < size; i++) {
				data[i] = -1;
			}
		}
		int Hash(int n) {
			return n%11;
		}
		void insert(int n, int hash) {
			hash %= size; //循环判断直到找到NULL
			if(data[hash] == -1) {
				data[hash] = n;
			} else {
				if(data[hash + 1] == -1) {
					data[hash + 1] = n;
				} else {
					insert(n,hash+1);
				}
			}
		}
		void search(int find){
			int cnt = 0, index = 0;
			int hash = Hash(find);
			while(1){
				hash %= size;
				cnt++;
				if(data[hash] == find){
					cout<<"1 "<<cnt<<" "<<hash + 1<<"\n";
					return ;
				}
				if(data[hash] == -1){
					cout<<"0 "<<cnt<<"\n";
					return ;
				}
				hash++;
			}
		}
		void print(){
			for(int i = 0; i < size; i++){
				if(data[i] > 0){
					cout<<data[i]<<" ";
				}else{
					cout<<"NULL ";
				}
			}
			cout<<endl; 		
		}
		~HashTable() {
			delete[] data;
		}
};

int main() {
	int t;
	cin>>t;
	while(t--) {
		int size,n;
		cin>>size>>n;
		HashTable h(size);
		while(n--) {
			int data;
			cin>>data;
			h.insert(data,h.Hash(data));
		}
		h.print();
		int k;
		cin>>k;
		while(k--){
			int find;
			cin>>find;
			h.search(find);
		}
	}
	return 0;
}
