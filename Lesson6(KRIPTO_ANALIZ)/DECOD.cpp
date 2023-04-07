#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <regex>
using namespace std;
string ABC = "��������������������������������";

void countLetter(string &text) {
	unordered_map<int, int> freq;
	for (int i = 2; i <= 40; i++)
	{
		int count = 0;
		for (int j = 0;j< text.length() - i;j++) {
			if (text[j] == text[j + i])
				freq[i] ++;
		}
		
	}

	vector<pair<int, int>> vec(freq.begin(), freq.end());//������� ������ ������� ������ ���� � �������� 
	sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {//��� �������� ��������� �� �������� //GITH
		return a.second > b.second;
	});

	for (auto& pair : vec)
		cout << '{' << pair.first << ": " << pair.second << '}\t' ; //
	cout << endl;


}

void symbolFrequencies(string& text) {
	unordered_map<char, int> freq;
	for (char& c : text) {
		freq[c]++;
	}

	vector<pair<char, int>> vec(freq.begin(), freq.end());//������� ������ ������� ������ ���� � �������� 
	sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {//��� �������� ��������� �� �������� //GITH
		return a.second > b.second;
		});

	/*for (const auto& pair : vec) {
		
		cout << "{" << pair.first << ": " << pair.second << "}" << endl;
	}*/
}
double indexOfCoincidence(string& text) {
	unordered_map<char, int> freqs; // unordered_map ��� �������� ������ ������ �����
	long long int total = 0; // ����� ���������� ���� � ������
	long double ic = 0.0; // ������ ����������

	// ������� ������ ������ �����
	for (char c : text) {
		if (c >= '�' && c <= '�') {
			freqs[c]++; // ����������� ������� ������� �� 1
			total++; // ����������� ������� �������� �� 1
		}
	}

	// ������ ������� ����������
	for (auto& pair : freqs) {
		ic += pair.second * (pair.second - 1);
	}
	long long int f = (total * (total - 1));
	ic /= f;

	return ic;
}

vector<pair<char, int>> charValue(string block) {
	vector<pair<char, int>> b_stats;
	for (char c : block) {
		auto it = find_if(b_stats.begin(), b_stats.end(), [&](const pair<char, int>& p) {
			return p.first == c;
			});
		if (it != b_stats.end()) {
			it->second++;
		}
		else {
			b_stats.emplace_back(c, 1);
		}
	}
	return b_stats;
}


void bloc(string plaintext) { //����� ��� �������� ������ �� ����� ��� ����������� � ������� unit
	unordered_map<int, string> freq;//��� ��� �������� ������ ������ � ����������� ������ 
	string key;
	int r = 16; // ����� ����� 
	for (int i = 0; i <r; i++)//�� 0 �������� �� 16 
	{
		for (int j = 0 + i; j < plaintext.length(); j += r) {//���� ��� �������� �������� � ������� ����� ������ ������� �� ������� �� �������� ������� ����� ����� 
				freq[i] += plaintext[j];//���������� � ������ 
		}
	}
	for (const auto& pair1 : freq) {//����� 
		cout << "{" << pair1.first << ": " << pair1.second << "}" << endl;// ����� ����� � �������� 
		string r = pair1.second;
		vector<string> blocks ;
		blocks.push_back(r);
		for (string block : blocks) {
			vector<pair<char, int>> b_stats = charValue(block);
			char o = max_element(b_stats.begin(), b_stats.end(), [](const pair<char, int>& p1, const pair<char, int>& p2) {
				return p1.second < p2.second;
				})->first;
			int decodL = (ABC.find(o) - ABC.find('�') + ABC.size()) % ABC.size();
			key += ABC[decodL];
		}
		cout <<key<<endl;
		symbolFrequencies(r);
		cout << "index" << indexOfCoincidence(r)<<endl;
	}
}
string Text() {
	//string str1 = " ���� � ����� ����� ������ ,����� � ����� ������ �������  ";
	string path = "..\\file.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "������ ������ ����� " << endl;
	}
	else
	{
		cout << "���� ������" << endl;
		//char ch;
		//fin.get(ch) ������� ������ �� ��������� 

		string str;
		while (!fin.eof()) // ���������� ����� ����� 
		{
			str = ""; //��� ����������� ������	
			getline(fin, str);
			res += str;
		}
	}

	//cout << res << endl;

	fin.close();

	return res;
}


int main() {
	setlocale(LC_ALL, "ru");

	string text = Text();
	symbolFrequencies(text);
	//countLetter(text);
	bloc(text);

	
	return 0;
}