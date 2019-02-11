#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

int get_input(int& dim_x, int& dim_y, int& n) {
    cout << "dimensions(x y)?";
    cin >> dim_x >> dim_y;
    cout << "mines(n)?";
    cin >> n;
    if (dim_x <= 0 || dim_y <= 0 || n < 0) {
        cerr << "Invalid input." <<endl;
        return 1;
    }
    return 0;
}

void generate_mines(int n, vector<vector<int> >& board) {
    int dim_x = board.size();
    int dim_y = board[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, dim_x - 1);
    std::uniform_int_distribution<> dis_y(0, dim_y - 1);

    int mines = 0;
    while (mines < n) {
        int x, y;
        x = dis_x(gen);
        y = dis_y(gen);
        if (! board[x][y]) {
            board[x][y] = -1;
            ++mines;
        }
    }
}

void calculate_numbers(vector<vector<int> >& board) {
    int dim_x = board.size();
    int dim_y = board[0].size();

    for (int i = 0; i < dim_x; ++i) {
        for (int j = 0; j < dim_y; ++j) {
            if (board[i][j] == -1) continue;
            int count = 0;
            vector<int> range{-1, 0, 1};
            for (int di : range) {
                for (int dj : range) {
                    if (! di && ! dj) continue;
                    if (board[i + di][j + dj] == -1) ++count;
                }
            }
            board[i][j] = count;
        }
    }
}

void output(vector<vector<int> >& board) {
    int dim_x = board.size();
    int dim_y = board[0].size();

    for (int i = 0; i < dim_x; ++i) {
        for (int j = 0; j < dim_y; ++j) {
            switch (board[i][j]) {
            case -1:
                cout << "{{:boom:}}";
                break;
            case 0:
                cout << "{{:zero:}}";
                break;
            case 1:
                cout << "{{:one:}}";
                break;
            case 2:
                cout << "{{:two:}}";
                break;
            case 3:
                cout << "{{:three:}}";
                break;
            case 4:
                cout << "{{:four:}}";
                break;
            case 5:
                cout << "{{:five:}}";
                break;
            case 6:
                cout << "{{:six:}}";
                break;
            case 7:
                cout << "{{:seven:}}";
                break;
            case 8:
                cout << "{{:eight:}}";
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
}

int main() {
    int dim_x, dim_y, n;
    if (get_input(dim_x, dim_y, n)) return 1;

    vector<vector<int> > board(dim_x, vector<int>(dim_y, 0));

    generate_mines(n, board);
    calculate_numbers(board);

    output(board);

    return 0;
}
