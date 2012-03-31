#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

namespace {

bool ReadVocab(const char* filename, map<string, string>& voc) {
  ifstream ifs(filename);
  if (!ifs) {
    cerr << "Vocabulary does not exist.\n";
    return false;
  }

  voc.clear();

  string line, s1, s2;
  voc["1"] = "UNK";

  while (getline(ifs, line)) {
    istringstream eingabe(line);
    if (!(eingabe >> s1 >> s2)) {
      cerr << "ERROR in vocabulary '" << line << "'\n";
      return false;
    }
    voc[s1] = s2;
  }
  return true;
}

bool ConvertSnt(const char* filename, int max_elements, bool counts,
                const map<string, string>& voc) {
  ifstream ifs(filename);
  if (!ifs) {
    cerr << "No such file or directory: " << filename << endl;
    return false;
  }

  string line1, line2, line3;
  vector<map<int,int> > vsi(voc.size() + 1000);

  int line_num = 0;
  int total_elements = 0;

  while (getline(ifs, line1) && getline(ifs, line2) && getline(ifs, line3)) {
    istringstream eingabe1(line1), eingabe2(line2), eingabe3(line3);
    double count;
    string word;

    eingabe1 >> count;
    vector<int>l1,l2;

    while (eingabe2 >> word) {
      l1.push_back(atoi(word.c_str()));
    }
    while (eingabe3 >> word) {
      l2.push_back(atoi(word.c_str()));
    }

    if (((++line_num) % 1000) == 0) {
      cerr << "line " << line_num << '\n';
    }

    total_elements -= vsi[0].size();
    for (unsigned int j=0;j<l2.size();++j) {
      vsi[0][l2[j]]++;
    }
    total_elements += vsi[0].size();

    for (unsigned int i = 0; i < l1.size(); ++i) {
      if (l1[i]>=int(vsi.size())) {
        cerr << "I have to resize: " << l1[i] << endl;
        vsi.resize(static_cast<size_t>(l1[i] + 1));
      }
      map<int,int>& theset = vsi[static_cast<size_t>(l1[i])];
      total_elements -= theset.size();
      for (unsigned int j = 0; j < l2.size(); ++j) {
        theset[l2[j]]++;
      }
      total_elements += theset.size();
    }
    if (total_elements > max_elements && max_elements) {
      cerr << "INFO: print out " << total_elements << " entries.\n";
      for (unsigned int i=0;i<vsi.size();++i) {
        for (map<int,int>::const_iterator j=vsi[i].begin();j!=vsi[i].end();++j) {
          if (counts) {
            cout << j->second << " " << i << " " << j->first << '\n';
          } else {
            cout << i << " " << j->first << '\n';
          }
        }
      }
      total_elements = 0;
      vsi.clear();
      vsi.resize(voc.size()+1000);
    }
  }
  cerr << "END.\n";
  for (unsigned int i = 0; i < vsi.size(); ++i) {
    for (map<int,int>::const_iterator j= vsi[i].begin();
         j != vsi[i].end(); ++j) {
      if (counts) {
        cout << j->second << " " << i << " " << j->first << '\n';
      } else {
        cout << i << " " << j->first << '\n';
      }
    }
  }
  return true;
}

} // namespace

int main(int argc, char **argv) {
  if (argc != 4 && argc != 5) {
    cerr << "Usage: " << argv[0] << " vcb1 vcb2 snt12 \n";
    cerr << "Converts GIZA++ snt-format into plain text.\n";
    exit(1);
  }

  int max_elements = 0;
  bool counts = false;

  if (argc == 5) {
    if (string(argv[4]) != "-counts") {
      cerr << "ERROR: wrong option " << argv[5] << endl;
    }
    counts = true;
    max_elements = 10000000;
  }

  map<string, string> voc1, voc2;

  if (!ReadVocab(argv[1], voc1)) {
    cerr << "Failed to read vocabulary." << endl;
    exit(1);
  }

  if (!ReadVocab(argv[2], voc2)) {
    cerr << "Failed to read vocabulary." << endl;
    exit(1);
  }

  if (!ConvertSnt(argv[3], max_elements, counts, voc1)) {
    cerr << "Failed to convert." << endl;
    exit(1);
  }

  return 0;
}
