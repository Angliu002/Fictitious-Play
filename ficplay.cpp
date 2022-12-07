#include <bits/stdc++.h>
using namespace std;

#define N 2         // number of players
#define M 2         // number of actions
#define WIDTH 20

static int MAXRD = 10000;
static double THRESHOLD = 1e-3;
static bool INDETAIL = false;

static string action[M] = {"S", "B"};
static double matrice[N][M][M];         // Player p's payoff when he doing action a_1 and others doing action a_2
static double belief[N][M];          // record[Player p][Action a] = times that player p choose action a
static double payoff[N][M];

int main(int argc, char** argv) {

    if (argc == 3) {
        MAXRD = atoi(argv[1]);
        THRESHOLD = stod(argv[2]); 
    } else if (argc ==4) {
        MAXRD = atoi(argv[1]);
        THRESHOLD = stod(argv[2]); 
        INDETAIL = (argv[3] == "true" ? true : false);
    } else if (argc != 1) {
        cerr << "usage: ./ficplay <number of rounds> <threshold> [output in detail]\n";     // example: ./ficplay 1000 0.05 true
        return -1;
    }
    cout << "Maximum number of rounds: " << MAXRD << '\n' << "Threshold: " << THRESHOLD << '\n';

    /* Initial */
    srand(time(NULL));
    memset(matrice, 0, sizeof(matrice));
    memset(belief, 0, sizeof(belief));
    memset(payoff, 0, sizeof(payoff));

    /* Actions' name */
    for (int i = 0; i < M; i++) {
        cin >> action[i];
    }

    /* Set belief */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> belief[i][j];
        }
    }

    /* Set game matrice */
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                cin >> ( k == 0 ? matrice[k][i][j] : matrice[k][j][i]);
            }
        }
    }

    /* Print game matrice */
    cout << "Game matrix:\n";
    cout << "P1\\P2"
        << setw(WIDTH) << "c1"
        << setw(WIDTH) << "c2"
        << '\n';
    for (int i = 0; i < M; i++) {
        cout << setw(5) << left << (i == 0 ? "r1" : "r2");
        for (int j = 0; j < M; j++) {
            char u[WIDTH];
            sprintf(u, "%.1f,%.1f", matrice[0][i][j], matrice[1][j][i]);
            cout << setw(WIDTH) << right << u;
        }
        cout << '\n';
    }

    /* Fictitious */
    if (INDETAIL) {
        cout << "Round"
            << setw(WIDTH) << "1's action"
            << setw(WIDTH) << "2's action"
            << setw(WIDTH) << "1's belief"
            << setw(WIDTH) << "2's belief"
            << setw(WIDTH) << "1's payoff"
            << setw(WIDTH) << "2's payoff"
            << '\n';
    }
    
    
    double utility[N][M];
    int BR[N];
    queue<pair<int, int>> pure_strategies;
    queue<pair<double, double>> mixed_strategies;
    for (int round = 0; round <= MAXRD; round++) {

        /* Response */
        for (int i = 0; i < N; i++) {
            int a;
            for (int j = 0; j < M; j++) {
                double count = 0;
                for (int k = 0; k < M; k++) {
                    utility[i][j] += belief[i][k] * matrice[i][j][k];
                    count += belief[i][k];
                }
                if (count != 0) utility[i][j] /= count;
                else utility[i][j] = 0;
            }
            BR[i] = (utility[i][0] > utility[i][1] ? 0 : 1) ;
            BR[i] = (utility[i][0] == utility[i][1] ? rand()%2 : BR[i]);
        }

        /* Recalculate payoff */
        memset(payoff, 0, sizeof(payoff));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < M; k++) {
                    payoff[i][j] += belief[i][k] * matrice[i][j][k];
                }
            }
        }

        /* Output round info */
        if (INDETAIL) {
            char belief1[WIDTH], belief2[WIDTH];
            sprintf(belief1, "(%.2f, %.2f)", belief[0][0], belief[0][1]);
            sprintf(belief2, "(%.2f, %.2f)", belief[1][0], belief[1][1]);

            char payoff1[WIDTH], payoff2[WIDTH];
            sprintf(payoff1, "%.2f %.2f", payoff[0][0], payoff[0][1]);
            sprintf(payoff2, "%.2f %.2f", payoff[1][0], payoff[1][1]);

            cout << right << setw(5) << round
                << right << setw(WIDTH) << (round == 0 ? "-" : action[BR[0]])
                << right << setw(WIDTH) << (round == 0 ? "-" : action[BR[1]])
                << right << setw(WIDTH) << string(belief1)
                << right << setw(WIDTH) << string(belief2)
                << right << setw(WIDTH) << string(payoff1)
                << right << setw(WIDTH) << string(payoff2)
                << '\n';
        }

        /* Determine the convergence */
        pure_strategies.push({BR[0], BR[1]});
        if (round >= 10 && pure_strategies.size() >= round/2) {

            while (!pure_strategies.empty()) {
                pair<int, int> temp = pure_strategies.front();
                pure_strategies.pop();
                if (temp.first != BR[0] || temp.second != BR[1]) break;
            }

            if (pure_strategies.empty()) {
                cout << "#rounds = " << round << '\n';
                cout << "Converge, the Nash Equilibrium (pure strategy) is (" << action[BR[0]] << ',' << action[BR[1]] << ")\n";
                return 0;
            }

        }

        mixed_strategies.push({belief[0][0]/(belief[0][0]+belief[0][1]), belief[1][0]/(belief[1][0]+belief[1][1])});
        if (round >= 10 && mixed_strategies.size() >= round/10) {
            pair<double, double> temp = mixed_strategies.front();
            mixed_strategies.pop();
            
            if (temp.first <= mixed_strategies.back().first + THRESHOLD && 
                temp.first >= mixed_strategies.back().first - THRESHOLD &&
                temp.second <= mixed_strategies.back().second + THRESHOLD && 
                temp.second >= mixed_strategies.back().second - THRESHOLD) {

                cout << "#rounds = " << round << '\n';
                cout << "Converge, the Nash Equilibrium (mixed strategy) is (" << mixed_strategies.back().first << ',' << mixed_strategies.back().second << ")\n";
                return 0;
            }
        }

        /* Record */
        belief[0][BR[1]] += 1;
        belief[1][BR[0]] += 1;
        
    }

    cout << "#rounds = " << MAXRD << '\n';
    cout << "No Nash Equilibrium found\n";
    return 0;
    
}