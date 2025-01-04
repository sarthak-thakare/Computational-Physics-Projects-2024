#include<bits/stdc++.h>
using namespace std;

void flatten(vector<vector<double>> &grid, vector<double> &flat) {
    int n = grid.size();
    flat.resize(n*n);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            flat[i*n + j] = grid[i][j];
        }
    }
}

void flat2grid(vector<double> &flat, vector<vector<double>> &grid) {
    int n = grid.size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            grid[i][j] = flat[i * n + j];
        }
    }
}


void make_laplacian_operator(vector<vector<double>> &op, int n) {
    int N = n * n;
    op.assign(N, vector<double>(N, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j;
            op[idx][idx] = -4.0;
            if (i > 0) op[idx][(i - 1) * n + j] = 1.0; // up
            if (i < n - 1) op[idx][(i + 1) * n + j] = 1.0; // down
            if (j > 0) op[idx][i * n + j - 1] = 1.0; // left
            if (j < n - 1) op[idx][i * n + j + 1] = 1.0; // right
        }
    }
}

void solve_system_lineq(const vector<vector<double>> &op, const vector<double> &rhs, vector<double> &solution, int max_iters = 10000, double tol = 1e-6) {
    int N = rhs.size();
    solution.assign(N, 0.0);
    vector<double> temp(N, 0.0);

    for (int iter = 0; iter < max_iters; ++iter) {
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j) {
                if (j != i) sum += op[i][j] * solution[j];
            }
            temp[i] = (rhs[i] - sum) / op[i][i];
        }
        double diff = 0.0;
        for (int i = 0; i < N; ++i) {
            diff = max(diff, fabs(temp[i] - solution[i]));
            solution[i] = temp[i];
        }
        if (diff < tol) break;
    }
}

int main() {
    int n = 50; // Grid size
    vector<vector<double>> cd_grid(n, vector<double>(n, 0.0));
    cd_grid[n / 2 + 10][n / 2] = 1.0;
    cd_grid[n / 2 - 10][n / 2] = -1.0;

    for (int j = 0; j < n; ++j) {
        cd_grid[0][j] = 1.0;
        cd_grid[n - 1][j] = -1.0;
    }

    vector<double> cd_flat;
    flatten(cd_grid, cd_flat);

    vector<vector<double>> laplacian;
    make_laplacian_operator(laplacian, n);

    vector<double> rhs = cd_flat;
    for (auto &val : rhs) val *= -1.0; // Adjust RHS

    vector<double> u_flat;
    solve_system_lineq(laplacian, rhs, u_flat);

    vector<vector<double>> u_grid(n, vector<double>(n));
    flat2grid(u_flat, u_grid);

    ofstream field_file("field.txt");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            field_file <<i<<" "<<j<<" "<<u_grid[i][j]<<endl;
        }
        // field_file << "\n";
    }
    field_file.close();

    cout << "Results saved to field.txt. Use gnuplot to visualize." << endl;
    return 0;
}