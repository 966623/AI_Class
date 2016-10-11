#ifndef SOMECLASS_HPP
#define SOMECLASS_HPP

#include <tuple>
#include <vector>
#include <sstream>

using namespace std;

class ImgSettings {
	public:
		ImgSettings(){}

		//Get vector of data given a name
		vector<string> getData(string name){
			for(int i = 0; i < data.size(); i++){
				if( get<0>(data[i]).compare(name) == 0){
					return get<1>(data[i]);
				}
			}
			vector<string> empty;
			return empty;
		}

		//jump to index give a name
		int seek(string name){
			for(int i = 0; i < data.size(); i++){
				if( get<0>(data[i]).compare(name) == 0){
					index = i;
					return i;
				}
			}
			return -1;
		}

		// get current index
		tuple<string, vector<string>> getCurrent(){
			return data[index];
		}

		// set index to start
		void seekStart(){
			index = 0;
		}

		// delete and return
		vector<string> remove(string name){
			for(int i = 0; i < data.size(); i++){
				if( get<0>(data[i]).compare(name) == 0){
					vector<string> returnData = get<1>(data[i]);
					data.erase(data.begin() + i);
					return get<1>(data[i]);
				}
			}
			vector<string> empty;
			return empty;
		}

		// return next tuple and increment index
		tuple<string, vector<string>> next(){
			index++;
			if(index >= data.size()){
				vector<string> empty;
				return make_tuple("eof", empty);
			}
			else{
				return data[index];
			}
			
		}

		// Get all data with given name
		vector<vector<string>> getAll(string name){
			vector<vector<string>> allData;
			for(int i = 0; i < data.size(); i++){
				if( get<0>(data[i]).compare(name) == 0){
					allData.push_back(get<1>(data[i]));
				}
			}
			return allData;
		}

		//Add tuple of a name and a vector of data
		void setData(string name, vector<string> newData){
			tuple<string, vector<string>> dataTuple = make_tuple(name, newData);
			data.push_back(dataTuple);
		}

		string to_str(){
			stringstream ss;
			for(int i = 0; i < data.size(); i++){
				ss << get<0>(data[i]) << " : ";
				vector<string> d = get<1>(data[i]);
				for(int j = 0; j < d.size(); j++){
					ss << d[j] << " ";
				}
				ss << "\n";
			}
			return ss.str();
		}
	private:
		vector<tuple<string, vector<string>>> data;
		int index = 0;

}; // end SomeClass

#endif
