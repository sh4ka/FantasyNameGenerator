#include "iostream"
using std::cout;
using std::cin;
#include "fstream"
using std::ifstream;
#include "vector"
using std::vector;
using std::string;
#include "iterator"
using std::istream_iterator;
#include "random"
using std::random_device;
using std::random_device;
using std::mt19937;
using std::default_random_engine;
#include "algorithm"
using std::transform;

vector<string> bdd;

random_device dev;
mt19937 rng(dev());
default_random_engine generator(dev());

struct NameParts {
	string nameOrigin;
	string nameSliced;
	string remain;
	bool isStart = false;
};

struct NameFull {
	string Name;
	string Surname;
};

void loadNames()
{
	ifstream myfile("names.txt");
	copy(istream_iterator<string>(myfile),
		 istream_iterator<string>(),
		 back_inserter(bdd));
}


bool containsOnlyASCII(const std::string& givenString) {
	for (auto c: givenString) {
		if (static_cast<unsigned char>(c) > 127) {
			return false;
		}
	}
	return true;
}


string getRandName(bool safe = true)
{
	std::uniform_int_distribution<mt19937::result_type> dist6(0, bdd.size());
	string name = bdd.at(dist6(rng));
	bool nameIsSafe = containsOnlyASCII(name);
	while (safe && !nameIsSafe) {
		name = getRandName();
		nameIsSafe = containsOnlyASCII(name);
	}

	return name;
}

NameParts getNameObj()
{
	NameParts nameParts;
	string _name = getRandName();
	string _nameFraction;

	nameParts.nameOrigin = _name;

	std::uniform_real_distribution<double> distribution(0,1);
	if (distribution(generator) < 0.5) {
		_nameFraction = _name.substr(0, round(_name.length()) / 2.0);
		transform(_nameFraction.begin(), _nameFraction.end(), _nameFraction.begin(),
			[](unsigned char c) { return std::tolower(c); });
		nameParts.remain = _name.substr(round(_name.length()) / 2.0);
		transform(nameParts.remain.begin(), nameParts.remain.end(), nameParts.remain.begin(),
			[](unsigned char c) { return std::tolower(c); });
		nameParts.isStart = true;
	} else {
		_nameFraction = _name.substr(round(_name.length()) / 2.0);
		transform(_nameFraction.begin(), _nameFraction.end(), _nameFraction.begin(),
			[](unsigned char c) { return std::tolower(c); });
		nameParts.remain = _name.substr(0, round(_name.length()) / 2.0);
		transform(nameParts.remain.begin(), nameParts.remain.end(), nameParts.remain.begin(),
			[](unsigned char c) { return std::tolower(c); });
		nameParts.isStart = false;
	}

	nameParts.nameSliced = _nameFraction;

	return nameParts;
}

vector<NameParts> generateNameArray() {
	vector<NameParts> result = {};

	for (int i = 0; i < 4; ++i) {
		result.push_back(getNameObj());
	}

	return result;
}

NameFull GetFirstName() {
	NameFull generated;
	vector<NameParts> names = generateNameArray();
	string FirstName = names.at(0).remain + names.at(1).remain;
	transform(FirstName.begin(), FirstName.begin() + 1, FirstName.begin(), ::toupper);
	generated.Name = FirstName;
	string LastName = names.at(2).remain + names.at(3).remain;
	transform(LastName.begin(), LastName.begin() + 1, LastName.begin(), ::toupper);
	generated.Surname = LastName;

	return generated;
}

int main(int argc, char** argv) {
	int toGenerate = 1;
	if (argc > 1) {
		string argument = argv[1];
		bool isNumber = !argument.empty() && find_if(argument.begin(),
														  argument.end(), [](unsigned char c) { return !isdigit(c); }) == argument.end();
		if (isNumber) {
			int argumentNumber = stoi(argument);
			if (argumentNumber > 0) {
				toGenerate = argumentNumber;
			}
		}
	}

	loadNames(); // initialize name db
	for (int i = 0; i < toGenerate; ++i) {
		NameFull generated = GetFirstName();
		cout << generated.Name << " " << generated.Surname << "\n";
	}

	return 0;
}
