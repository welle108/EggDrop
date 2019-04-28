#include <sstream>
#include <iostream>
#include <climits>

using namespace std;

int max(int n, int m){
  if(n > m){
    return n;
  }
  return m;
}

int eggDrop(int floors, int eggs){
    int i, j, k, cur;
    int eggTries[floors + 1][eggs + 1];
    for(i = 0; i <= floors; i++){
      for(j = 0; j <= eggs; j++){
        eggTries[i][j] = 0;
      }
    }

    /*
      Every time there is 1 egg left we need
      i tries for the number of floors remaining
    */

    for(i = 1; i <= floors; i++){
      eggTries[i][1] = i;
    }

    /*
      When 0 floors left 0 tries and when
      1 floor left 1 try
    */

    for(j = 1; j <= eggs; j++){
      eggTries[0][j] = 0;
      eggTries[1][j] = 1;
    }

    /*
      Fill rest of values with INT_MAX value as placeholder
    */

    for(i = 2; i <= floors; i++){
      for(j = 2; j <= eggs; j++){
        eggTries[i][j] = INT_MAX;
        // Compute values for each floor
        for(k = 1; k <= i; k++){
          /*
              Two possibilities:
              1: Egg Cracks
                  - eggTries[current_floor - 1][current_eggs -1]
              2: Egg Doesn't Crack
                  - eggTries[total_floors-current_floor][current_eggs]

              Take max value between these two and add 1 to account
              for the try you used on the floor you're currently at.
          */
          cur = 1 + max(eggTries[k-1][j-1], eggTries[i-k][j]);

          //Replace placeholder INT_MAX value with caluclated value
          if(cur < eggTries[i][j]){
            eggTries[i][j] = cur;
          }
        }
      }
    }
    return eggTries[floors][eggs];
}

int main (int argc, char* argv[]) {
  istringstream f_stream(argv[1]);
  istringstream e_stream(argv[2]);
  int floors;
  int eggs;
  if(f_stream >> floors && e_stream >> eggs){
    int result = eggDrop(floors,eggs);
    cout << endl;
    cout << "Given " << floors << " floors and " << eggs
    << " eggs, the minimum number of tries required in the worst case to \n" <<
    "find the highest possible floor from which the egg can fall without breaking is: \n" << result;
    cout << endl;
  }
}
