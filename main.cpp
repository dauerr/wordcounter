   #include <iostream>
   #include <fstream>
   #include <map>
   #include <string>
   #include <array>
   #include <algorithm>
   #include <vector>


   typedef std::map<std::string, int> StrIntMap;

   std::string removeNonAlphNum(std::string inStr){
      std::string s = inStr;
      for(int i = 0; i < s.size(); ++i)
         {
            if (!((s[i] >= 'a' && s[i]<='z') || (s[i] >= '0' && s[i]<='9'))){
              if (s[i] >= 'A' && s[i]<='Z'){
                s[i] = s[i]-('A'-'a');
              } else {
                s.erase(i);
              }
            }
         }
      return s;
  }

   void countWords(std::istream& in, StrIntMap& words) {

      std::string s;

      while (in >> s) {
        s = removeNonAlphNum(s);
        s.shrink_to_fit();
        if (s.length() > 2){
           ++words[s];
        }

     }
  }

  int main(int argc, char** argv) {

    if (argc < 2) return(EXIT_FAILURE);

    std::ifstream in(argv[1]);

    if (!in) exit(EXIT_FAILURE);

    StrIntMap w;
    countWords(in, w);

    int topValue;
    std::cout << "\n\n" << w.size() << " distinct words found!\nHow many results should be shown (0 = all)?\n>";
    std::cin >> topValue;

    topValue = topValue == 0 ? w.size() : topValue > w.size() ? w.size() : topValue;

    std::cout << "\nTop " << topValue << ":\n";

    std::vector<std::pair<std::string, int>> top(topValue);
    std::partial_sort_copy(w.begin(),
                           w.end(),
                           top.begin(),
                           top.end(),
                           [](std::pair<const std::string, int> const& l,
                              std::pair<const std::string, int> const& r)
                           {
                               return l.second > r.second;
                           });
    int i = 1;
    std::ofstream outputFile;
    outputFile.open ("output.txt");
    outputFile << "Total unique words: " << w.size() << "\n";
    for (auto const& p: top)
    {
       if (p.first.length() > 0){
        std::cout << i << ". " << p.first << " -> " << p.second << " times\n";
        outputFile << i << ". " << p.first << " -> " << p.second << " times\n";
        i++;
        }
    }

    outputFile.close();
    std::cout << "\n### Wrote all data to output.txt ###\n";

    std::cout << "\n\nTotal unique words: " << w.size() << "\n";
  }
