#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include <omp.h>

////#define min(a,b) (((a)<(b))?(a):(b))
//#define max(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
//#define floord(n,d) floor(((double)(n))/((double)(d)))
#define ceild(n,d) ceil(((double)(n))/((double)(d)))

using namespace std;

const int N = 8;
int C[N][N];



char SEQi[8] = {' ', 'G','G','U','C','C','A','C'};
char SEQj[8] = {'G','G','U','C','C','A','C', ' '};
string seq = "GGUCCAC";
string seqq = "GUACGUACGUACGUACGUACGUACGUACGUAC";
std::string large_string(10000, ' ');
vector<vector<int>> S(seqq.length(), vector<int>(seqq.length()));
vector<vector<int>> B(seqq.length(), vector<int>(seqq.length()));

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
            B[i][j] = INT_MIN;
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

    /*
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
       */
    cout << "Uday loop" << endl;
    int N = seqq.length();

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++){
            S[i][j] = INT_MIN;
            B[i][j] = INT_MIN;
        }
    }

    for(i=0; i<N; i++){
        S[i][i] = 0;
        B[i][i] = 0;
        if(i+1 < N) {
            S[i][i + 1] = 0;
            S[i+1][i] = 0;
            B[i][i + 1] = 0;
            B[i+1][i] = 0;
        }
    }
    for (i = N-1; i >= 0; i--) {
        for (j = i+1; j < N; j++) {
            for (k = 0; k < j-i; k++) {
                S[i][j] = max(S[i][k+i] + S[k+i+1][j], S[i][j]);
            }

            S[i][j] = max(S[i][j], S[i+1][j-1] + paired(seqq[i],seqq[j]));

          //  cout << i << "|" << j << "|" << seqq[i] << seqq[j] << "|" << S[i][j] << " , " << paired(seqq[i],seqq[j])  << "| " << S[i+1][j-1]<< endl;

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



cout << "barvinok" << endl;
    /*
S :=  [N] -> { [jj,ii,j,i,k] -> [ii-jj,ii,i-j,i,k] : 0 <= k < i-j and  0 <= jj <= N/4 and 0 <= ii <= N/4 and
0 <= i < N and 0 <= j <=N and ii*4 <= i < (ii+1)*4 and jj*4 <= j < (jj+1)*4 and ((ii=jj and i>j) or ii>jj)};
codegen S;
     */
    omp_set_nested(1);
    for (int c0 = 0; c0 <= (N - 1)/16; c0 += 1)  // serial loop
 //    #pragma omp parallel for
        for (int c1 = c0; c1 <= min((N - 1) / 16, (N + c0 - 2 )/ 16); c1 += 1) // parallel loop  blocks
        {
            int i = c1*16;
            int j = i-c0*16;
            cout << "\n -------- NEW BLOCK CORNER " << j << "," << i << endl;

            for (int c2 = max(1, 16 * c0 - 15);
                 c2 <= min(16 * c0 + 15, N + 16 * c0 - 16 * c1 - 1); c2 += 1) { // serial loop
                if (c0 >= 1) {
                    //    #pragma omp parallel for
                    for (int c3 = max(16 * c1, -16 * c0 + 16 * c1 + c2); c3 <= min(min(N - 1, 16 * c1 + 15),
                                                                                   -16 * c0 + 16 * c1 + c2 +
                                                                                   15); c3 += 1) {   // parallel loop threads
                        for (int c4 = 0; c4 < c2; c4 += 1) // serial
                            B[-c2 + c3][c3] = max(B[-c2 + c3][-c2 + c3 + c4] + B[-c2 + c3 + c4 + 1][c3],
                                                  B[-c2 + c3][c3]);
                        B[-c2 + c3][c3] = max(B[-c2 + c3][c3],
                                              B[-c2 + c3 + 1][c3 - 1] + paired(seqq[-c2 + c3], seqq[c3]));
                        cout << c0 << " " << c1 << " " << c2 << " " << c3 << ": " << -c2 + c3 << " " << c3 << endl;
                    }
                } else {
                    //  #pragma omp parallel for
                    for (int c3 = 16 * c1 + c2; c3 <= min(N - 1, 16 * c1 + 15); c3 += 1) {   // parallel loop threads
                        for (int c4 = 0; c4 < c2; c4 += 1) {  // serial
                            B[-c2 + c3][c3] = max(B[-c2 + c3][-c2 + c3 + c4] + B[-c2 + c3 + c4 + 1][c3],
                                                  B[-c2 + c3][c3]);
                        }
                        B[-c2 + c3][c3] = max(B[-c2 + c3][c3],
                                              B[-c2 + c3 + 1][c3 - 1] + paired(seqq[-c2 + c3], seqq[c3]));
                        cout << c0 << " " << c1 << " " << c2 << " " << c3 << ": " << -c2 + c3 << " " << c3 << endl;
                    }
                }
            }
        }




    cout << endl << endl;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(B[i][j] < 0)
                cout << "";
            else
                cout << B[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
    cout << endl;

    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            if(S[i][j] != B[i][j]){
                cout << "error" << endl;
                exit(0);
            }



    return 0;
}
