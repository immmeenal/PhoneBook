#include <string>
#include <vector>
using namespace std;

class MapNode{
	public:
		string key;
		vector<string> value;
		MapNode* next;
		MapNode(string key,vector<string> value){
			this->key = key;
			this->value = value;
			next = NULL;
		}

		~MapNode(){
			delete next;
		}
};


class OurMap{
	public:
		MapNode** buckets;
		int count;
		int numBuckets;

	public:
		OurMap(){
			count=0;
			numBuckets = 20;
			buckets = new MapNode*[numBuckets];
			for(int i=0;i<numBuckets;i++){
				buckets[i]= NULL;
			}
		}
		~OurMap(){
			for(int i=0;i<numBuckets;i++){
			delete buckets[i];
			}
			delete [] buckets;
		}

	private:
		int getBucketIndex(string key){
			int hashCode=0;

			int currentCoeff = 1; 
			for(int i=key.length();i>=0;i--){
				hashCode = key[i] * currentCoeff;
				hashCode = hashCode % numBuckets;
				currentCoeff *= 37;
				currentCoeff = currentCoeff % numBuckets;
			}

			return hashCode % numBuckets;
		}

	public:

		int size(){
			return count;
		}

		void insert(string key,vector<string> value){
			int bucketIndex = getBucketIndex(key);
			MapNode* head = buckets[bucketIndex];
			while(head!=NULL){
				if(head->key == key){
					head->value.push_back(value[0]);
					return;
				}
				head = head->next;
			}
			 head = buckets[bucketIndex];
			 MapNode* node = new MapNode(key,value);
			 node->next = head;
			 buckets[bucketIndex] = node;

			 count++;
		}

		vector<string> getValue(string key){
			int bucketIndex = getBucketIndex(key);
			MapNode* head = buckets[bucketIndex];
			while(head!=NULL){
				if(head->key == key){
					return head->value;
				}
				head = head->next;
			}
			return vector<string>(); 
		}

		vector<string> remove(string key){
			int bucketIndex = getBucketIndex(key);
			MapNode* head = buckets[bucketIndex];
			MapNode* prev = NULL;
			while(head!=NULL){
				if(head->key == key){
						if(prev==NULL){
						buckets[bucketIndex]= head->next;
						}
						else{
							prev->next = head->next;
						}
						vector<string> returnValue = head->value;
						head->next = NULL;
						delete head;
						count--;
						return returnValue;
				}
				prev = head;
				head=head->next;
			}
			return vector<string>();
		}

};














