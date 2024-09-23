#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

const int N = 8;
int C[N][N];
int S[N][N];

char SEQi[8] = {' ', 'G','G','U','C','C','A','C'};
char SEQj[8] = {'G','G','U','C','C','A','C', ' '};
string seq = "GGUCCAC";

int paired(char a1, char a2)
{
    if(a1 == 'A' && a2 == 'U')
        return 1;
    if(a1 == 'U' && a2 == 'A')
        return 1;
    if(a1 == 'G' && a2 == 'C')
        return 1;
    if(a1 == 'C' && a2 == 'G')
        return 1;

    return 0;
}

int BS = 4;

void showMatrix(int D[N][N]){
    int i,j;
    cout << endl;
    cout << endl << "\t\t";
    for(i = 0; i< N-1; i++)
        cout << seq[i] << "\t";
    cout << endl;
    for(i = 0; i< N-1; i++) {
        cout << "\t" << seq[i] << "\t";
        for (j = 1; j < N; j++) {
            if (D[i][j] < 0)
                cout << "";
            else
                cout << D[i][j];
            cout << "\t";
        }
        cout << "\n";
    }

}

int main() {
    int i,j,ii,jj,D,t,k;
    int BLOCKS = ceil(N/BS);

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++){
            C[i][j] = INT_MIN;
            S[i][j] = INT_MIN;
        }
    }

    for(i=0; i<N; i++){
         C[i][i] = 0;
         S[i][i] = 0;
         if(i+1 < N) {
             C[i][i + 1] = 0;
             S[i][i + 1] = 0;
         }
    }


int _i;
        // Wypisuje elementy na przekątnej d
      for (k = -BS+1; k < BS; k++) {
            for (i = k; i < BS; i++) {
                j = i - k;
                if(i>= 0 && j < BS)
                  cout << i << "," << j << " ";
            }
            cout << endl;
        }



    for(D=0; D<BLOCKS; D++) // diagonal only N  (UR triangle)
    // parallel
    for(t=D; t<BLOCKS; t++) {
        int BLOCKI = t;
        int BLOCKJ = t - D;
        cout << BLOCKI << "  " << BLOCKJ << endl;

        int start = (BLOCKI != BLOCKJ);


         for (k = (-BS+1)*start; k < BS; k++)
             // parallel
            for (i =k; i < BS; i++) {
                j = i - k;
                if (i >= 0 && j < BS) {
                    int _i = BLOCKI * BS + i;
                    int _j = BLOCKJ * BS + j;
                    cout << BLOCKI << "  " << BLOCKJ << "   : " << _j << "," << _i << "| " << SEQj[_j] << SEQi[_i] << " |b " << paired(SEQj[_j], SEQi[_i]);

                    if(_i > _j + 1) {
                        cout << "| " << C[_j + 1][_i] << "," << C[_j][_i - 1] <<"," <<  C[_j + 1][_i - 1] << " | ";
                        C[_j][_i] = max(max(C[_j + 1][_i], C[_j][_i - 1]), C[_j + 1][_i - 1] + paired(SEQj[_j], SEQi[_i]));
                        cout << "| " << C[_j][_i] << " | ";
                    }
                    cout << endl;
                }
            }
    }
    showMatrix(C);
    cout << "Uday loop" << endl;
    int N = 7;
    for (i = N-1; i >= 0; i--) {
        for (j = i+1; j < N; j++) {
            for (k = 0; k < j-i; k++) {
                S[i][j] = max(S[i][k+i] + S[k+i+1][j], S[i][j]);
            }
            S[i][j] = max(S[i][j], S[i+1][j-1] + paired(seq[i],seq[j]));

           // cout << i << "|" << j << "|" << seq[i] << seq[j] << "|" << S[i][j] << endl;

        }
    }
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(S[i][j] < 0)
                cout << "";
            else
                cout << S[i][j];
            cout << "\t";
        }
        cout << "\n";
    }


/*
    for (int c0 = 0; c0 <= N; c0 += 1){
        cout << "synch" << endl;
        for (int c1 = c0; c1 < N; c1 += 1)
            cout << -c0 + c1 << " " << c1 << endl;
    }
    */



   /* for (int c0 = 0; c0 < 2; c0 += 1){
        cout << "synch" << endl;
        for (int c1 = c0; c1 < 2; c1 += 1)
            for (int c2 = max(0, 5 * c0 - c1 + 1); c2 < min(4 * c0 + c1, N + 4 * c0 - 4 * c1); c2 += 1)
                for (int c3 = max(4 * c1, -4 * c0 + 4 * c1 + c2); c3 < min(min(N, 5 * c1), -5 * c0 + 5 * c1 + c2); c3 += 1)
                    //   (-c0 + c1, c1, -c2 + c3, c3);
                    cout << -c0 + c1 << " " << c1 << ":" << -c2 + c3 << " " << c3 << endl;
    }*/
    for (int c0 = 0; c0 <= N/4; c0 += 1) {
        cout << "synch tile" << endl;
        for (int c1 = c0; c1 <= N / 4; c1 += 1)
            for (int c2 = max(0, 4 * c0 - 3); c2 <= min(4 * c0 + 3, N + 4 * c0 - 4 * c1 - 1); c2 += 1) {
                cout << "synch statement" << endl;
                for (int c3 = max(-4 * c0 + 4 * c1, 4 * c1 - c2);
                     c3 <= min(min(-4 * c0 + 4 * c1 + 3, N - c2 - 1), 4 * c1 - c2 + 3); c3 += 1)
                    cout << -c0 + c1 << " " << c1 << ":" << c2 + c3 << " " << c3 << endl;
            }
    }





    return 0;
}
