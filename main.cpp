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
           // for (k = 0; k < j-i; k++) {
           //     S[i][j] = max(S[i][k+i] + S[k+i+1][j], S[i][j]);
           // }
            S[i][j] = max(S[i][j], max(S[i+1][j], S[i][j-1]));  /// ?????
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


cout << "barvinok" << endl;
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

cout << "parallel dapt" << endl;
    for (int w0 = 1; w0 < N; w0++) {
        cout << "synch" << endl;
        for (int h0 = -N + w0 + 1; h0 <= 0; h0++) {
            for (int i3 = 0; i3 < w0; i3++) {
              //  cpu_S[-h0][w0 - h0] = MAX(cpu_S[-h0][-h0 + i3] + cpu_S[-h0 + i3 + 1][w0 - h0], cpu_S[-h0][w0 - h0]);
            }
            //cpu_S[-h0][w0 - h0] = MAX(cpu_S[-h0][w0 - h0], cpu_S[-h0 + 1][w0 - h0 - 1] + isPair_host(-h0, w0 - h0));
          cout << -h0 << " " << w0 - h0 << endl;
        }
    }
    cout << endl;
    cout << "parallel pluto" << endl;
    int t1, t2, t3, t4, t5, t6, t7, t9;
    int lb, ub, lbp, ubp, lb2, ub2;
    register int lbv, ubv;
/* Start of CLooG code */
    for (t2=1;t2<=6;t2++) {
        lbp=t2;
        ubp=6;
        cout << "synch" << endl;
//#pragma omp parallel for private(lbv,ubv,t5,t6,t7)
        for (t4=lbp;t4<=ubp;t4++) {
            for (t6=0;t6<=t2-1;t6++) {
              //  S[(-t2+t4)][t4] = S[(-t2+t4)][t6+(-t2+t4)] + S[t6+(-t2+t4)+1][t4] + S[(-t2+t4)][t4];;
            }
            //S[(-t2+t4)][t4] = S[(-t2+t4)][t4] + S[(-t2+t4)+1][t4-1];;
            cout << -t2+t4 << " " << t4 << endl;
        }
    }

    for (t2=0;t2<=3;t2++) {
        lbp=t2;
        ubp=3;
#pragma omp parallel for private(lbv,ubv,t5,t6,t7,t8,t9,t10)
        for (t4=lbp;t4<=ubp;t4++) {
            for (t5=max(-5,2*t2-2*t4);t5<=min(0,2*t2-2*t4+1);t5++) {
                for (t7=max(2*t4,-t5+1);t7<=min(6,2*t4+1);t7++) {
                    for (t9=0;t9<=t5+t7-1;t9++) {
                        S[-t5][t7] = S[-t5][t9+-t5] + S[t9+-t5+1][t7] + S[-t5][t7];;
                    }
                    S[-t5][t7] = S[-t5][t7] + S[-t5+1][t7-1];;
                }
            }
        }
    }
/*
    cout << "parallel tile pluto" << endl;
    for (t2=-1;t2<=1;t2++) {
        lbp=max(0,t2);
        ubp=1;
        cout << "synch" << endl;
//#pragma omp parallel for private(lbv,ubv,t5,t6,t7,t8,t9,t10)
        for (t4=lbp;t4<=ubp;t4++) {
            for (t5=max(max(-5,4*t2-4*t4),-4*t4-2);t5<=min(0,4*t2-4*t4+3);t5++) {
                for (t7=max(4*t4,-t5+1);t7<=min(6,4*t4+3);t7++) {
                    for (t9=0;t9<=t5+t7-1;t9++) {
                     //   S[-t5][t7] = S[-t5][t9+-t5] + S[t9+-t5+1][t7] + S[-t5][t7];;
                    }
                   // S[-t5][t7] = S[-t5][t7] + S[-t5+1][t7-1];;
                   cout << t2 << " " << t4 << ":" << -t5 << " " << t7 << endl;
                }
            }
        }
    }*/
    cout << "parallel tile pluto" << endl;
    for (t2=0;t2<=3;t2++) {
        lbp=t2;
        ubp=3;
        cout << "synch" << endl;
//#pragma omp parallel for private(lbv,ubv,t5,t6,t7,t8,t9,t10)
        for (t4=lbp;t4<=ubp;t4++) {
            for (t5=max(-5,2*t2-2*t4);t5<=min(0,2*t2-2*t4+1);t5++) {
                for (t7=max(2*t4,-t5+1);t7<=min(6,2*t4+1);t7++) {
                    for (t9=0;t9<=t5+t7-1;t9++) {
                      //  S[-t5][t7] = S[-t5][t9+-t5] + S[t9+-t5+1][t7] + S[-t5][t7];;
                    }
                 //   S[-t5][t7] = S[-t5][t7] + S[-t5+1][t7-1];;
                    cout << t2 << " " << t4 << ":" << -t5 << " " << t7 << " uses " << -t5+1 << "|" << t7-1 << endl;
                }
            }
        }
    }

    return 0;
}
