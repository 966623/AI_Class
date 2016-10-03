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

}; // end SomeClass

#endif
