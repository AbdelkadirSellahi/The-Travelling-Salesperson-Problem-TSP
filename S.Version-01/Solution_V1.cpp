#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Function to transform minutes into hours
int Transform_minutes(int value) {
    int minutes = value % 60;
    return minutes;
}

// Function to transform hours
int Transform_hours(int value) {
    int hours = value / 60;
    return hours;
}

int main() {
    int site_count, time = 720;
    string line;
    istringstream word;
    ifstream instance("AAC-instance.txt", ios::in); // Read the instance for the number of sites
    if (instance.good()) {
        if (!instance.eof()) {
            getline(instance, line); // The number of sites
            getline(instance, line); // 151
            word.str(line);
            word >> site_count;
            word.clear();
        }
    } else {
        cerr << "Unable to open file!" << endl;
        exit(1);
    }
    instance.close();

    int mat_time[site_count][site_count], mat_site[site_count][3], mat_result[site_count][3], mat_test[site_count][3];

    ifstream instance1("AAC-instance.txt", ios::in);
    if (instance1.good()) {
        if (!instance1.eof()) {
            getline(instance1, line); // The number of sites
            getline(instance1, line); // 151
            getline(instance1, line); // The sites
            getline(instance1, line); // siteId score time
            for (int k = 0; k < site_count; k++) {
                getline(instance1, line); // 1st matrix
                word.str(line);
                for (int i = 0; word.good(); i++) {
                    word >> mat_site[k][i];
                }
                word.clear();
            }
            getline(instance1, line); // The time matrix
            for (int k = 0; k < site_count; k++) {
                getline(instance1, line); // 2nd matrix
                word.str(line);
                for (int i = 0; word.good(); i++) {
                    word >> mat_time[k][i];
                }
                word.clear();
            }
        }
    } else {
        cerr << "Unable to open file!" << endl;
        exit(1);
    }
    instance1.close();

    for (int w = 0; w < site_count; w++) {
        for (int z = 0; z < 3; z++) {
            mat_result[w][z] = mat_site[w][z];
            mat_test[w][z] = mat_site[w][z];
        }
    }

    int max_return = 0;
    for (int w = 0; w < site_count; w++) {
        if (mat_time[w][0] > max_return) {
            max_return = mat_time[w][0];
        }
    }

    int average = 0;
    for (int w = 0; w < site_count; w++) {
        average += mat_site[w][2];
    }
    average = average / site_count;
    for (int w = 0; w < site_count; w++) {
        if (mat_site[w][2] * 0.8 >= average) {
            mat_site[w][1] = -1;
        }
    }

    int max_results[site_count];
    max_results[0] = 0;
    bool check = true;
    int check2 = 0;
    while (check) {
        int max_val = 0, pos2 = 0;
        check2++;
        check = false;
        for (int w = 0; w < site_count; w++) {
            if (mat_site[w][1] >= max_val) {
                max_val = mat_site[w][1];
                pos2 = w;
                check = true;
            }
        }
        if (check) {
            mat_site[pos2][1] = -1;
            max_results[check2] = pos2;
        }
    }

    bool check1 = true;
    int p = 0, pos1, pos2, check_time = 0, end_pos, score_result = 0;
    while (check1) {
        pos1 = max_results[p];
        int l = p + 1;
        pos2 = max_results[l];
        check_time = check_time + mat_time[pos1][pos2] + mat_site[pos2][2];
        if (check_time > time - max_return) {
            check_time = check_time - mat_time[pos1][pos2] - mat_site[pos2][2];
            check1 = false;
            check_time = check_time + mat_time[pos1][0];
        } else {
            p++;
            end_pos = p;
        }
    }

    for (int n = 0; n <= end_pos; n++) {
        score_result = score_result + mat_result[max_results[n]][1];
    }

    ofstream File("Result.txt");
    if (File.good()) {
        int hr = 0;
        File << "Visited sites:" << endl;
        File << "id: " << 0 << " , Departure time: " << 8 + Transform_hours(0) << " h " << Transform_minutes(0) << " min " << endl;
        for (int n = 1; n <= end_pos; n++) {
            hr = hr + mat_time[max_results[n - 1]][max_results[n]];
            File << "id: " << max_results[n] << " , Arrival time: " << 8 + Transform_hours(hr) << " h " << Transform_minutes(hr) << " min ";
            hr = hr + mat_site[max_results[n]][2];
            File << " , Departure time: " << 8 + Transform_hours(hr) << " h " << Transform_minutes(hr) << " min " << endl;
        }
        hr = hr + mat_time[max_results[end_pos]][0];
        File << "id: " << 0 << " , Arrival time: " << 8 + Transform_hours(hr) << " h " << Transform_minutes(hr) << " min " << endl;
        File << "Number of visited sites: " << end_pos << endl;
        File << "Final score: " << score_result << endl;
        File << "Time consumed: " << check_time << " minutes" << endl;
        File << "Time: " << 8 + Transform_hours(check_time) << " h " << Transform_minutes(check_time) << " min " << endl;
    } else {
        cerr << "ERROR!";
        exit(1);
    }
    File.close();
    return 0;
}
