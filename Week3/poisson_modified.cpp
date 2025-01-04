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


// Function to construct Laplacian matrix in CSR format
void make_laplacian_csr(vector<double> &data, vector<int> &indices, vector<int> &row_ptr, int n) {
    int N = n * n;
    row_ptr.resize(N + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j;
            // Add diagonal element
            data.push_back(-4.0);
            indices.push_back(idx);
            row_ptr[idx + 1]++;

            
            // Add neighbor elements
            if (i > 0) { // up
                data.push_back(1.0);
                indices.push_back((i - 1) * n + j);
                row_ptr[idx + 1]++;
            }
            if (i < n - 1) { // down
                data.push_back(1.0);
                indices.push_back((i + 1) * n + j);
                row_ptr[idx + 1]++;
            }
            if (j > 0) { // left
                data.push_back(1.0);
                indices.push_back(i * n + j - 1);
                row_ptr[idx + 1]++;
            }
            if (j < n - 1) { // right
                data.push_back(1.0);
                indices.push_back(i * n + j + 1);
                row_ptr[idx + 1]++;
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        row_ptr[i] += row_ptr[i - 1];
    }
}

// Sparse matrix-vector multiplication
void sparse_dot_vec(vector<double> &data,vector<int> &indices, vector<int> &row_ptr, vector<double> &vec, vector<double> &result) {
    int N = vec.size();
    result.assign(N, 0.0);
    for (int i = 0; i < N; ++i) {
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; ++j) {
            result[i] += data[j] * vec[indices[j]];
        }
    }
}

// Solver using CSR Laplacian
void solve_system_lineq_csr(vector<double> &data, vector<int> &indices,vector<int> &row_ptr, vector<double> &rhs, vector<double> &solution, int max_iters = 10000, double tol = 1e-6) {
    int N = rhs.size();
    solution.assign(N, 0.0);
    vector<double> temp(N, 0.0);

    for (int iter = 0; iter < max_iters; ++iter) {
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = row_ptr[i]; j < row_ptr[i + 1]; ++j) {
                if (indices[j] != i) {
                    sum += data[j] * solution[indices[j]];
                }
            }
            temp[i] = (rhs[i] - sum) / -4.0; // Diagonal is always -4 in Laplacian
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
    int n = 100; // Grid size
    vector<vector<double>> cd_grid(n, vector<double>(n, 0.0));
    cd_grid[n/2+10][n/2] = 1.0;
    cd_grid[n/2- 10][n/2] = -1.0;

    for (int j = 0; j < n; ++j) {
        cd_grid[0][j] = 1.0;
        cd_grid[n - 1][j] = -1.0;
    }

    vector<double> cd_flat;
    flatten(cd_grid, cd_flat);

    vector<double> laplacian_data;
    vector<int> laplacian_indices;
    vector<int> laplacian_row_ptr;
    make_laplacian_csr(laplacian_data, laplacian_indices, laplacian_row_ptr, n);

    vector<double> rhs = cd_flat;
    for (auto &val : rhs) val *= -1.0; // Adjust RHS

    vector<double> u_flat;
    solve_system_lineq_csr(laplacian_data, laplacian_indices, laplacian_row_ptr, rhs, u_flat);

    vector<vector<double>> u_grid(n, vector<double>(n));
    flat2grid(u_flat, u_grid);

    ofstream field_file("field_sparse.txt");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            field_file << i << " " << j << " " << u_grid[i][j] << endl;
        }
    }
    field_file.close();

}
