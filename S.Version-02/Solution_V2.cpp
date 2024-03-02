#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
using namespace std;

// Structure for site information
struct Site {
    int id;
    int score;
    int time;
};

// Structure for linked list node
struct Node {
    Site data;
    Node* next;
};

// Define list type
typedef Node* SiteList;

// Structure for result site information
struct ResultSite {
    int id;
    int score;
    int time;
    int departure_time;
    int arrival_time;
};

// Structure for linked list node of result sites
struct ResultNode {
    ResultSite data;
    ResultNode* next;
};

// Define list type for result sites
typedef ResultNode* ResultSiteList;

// Function to insert a new node into the list
void insertSite(SiteList* L, Site value) {
    Node* new_node = new Node;
    new_node->data = value;
    new_node->next = NULL;

    if (*L == NULL) {
        *L = new_node;
    } else {
        new_node->next = *L;
        *L = new_node;
    }
}

// Function to insert a new node into the result list
void insertResultSite(ResultSiteList* L, ResultSite value) {
    ResultNode* new_node = new ResultNode;
    new_node->data = value;
    new_node->next = NULL;

    if (*L == NULL) {
        *L = new_node;
    } else {
        new_node->next = *L;
        *L = new_node;
    }
}

// Function to display the list
void display(SiteList L) {
    Node* current = L;
    if (L == NULL) {
        cout << "The list is empty." << endl;
    } else {
        while (current != NULL) {
            cout << " " << current->data.id << " " << current->data.score << " " << current->data.time << endl;
            current = current->next;
        }
    }
}

// Function to calculate average score of sites
int averageScore(SiteList L) {
    Node* current = L;
    int count = 0;
    int sum = 0;

    if (L != NULL) {
        while (current != NULL) {
            sum += current->data.score;
            current = current->next;
            count++;
        }
    }

    return count > 0 ? sum / count : 0;
}

// Function to remove a site from the list
void removeSite(Node* L, Site value) {
    Node* temp;
    Node* p;

    if (L != NULL) {
        if (L->data.id == value.id) {
            *L = *L->next;
        } else {
            temp = L;
            while (temp->next != NULL && temp->next->data.id != value.id) {
                temp = temp->next;
            }
            if (temp->next != NULL) {
                p = temp->next;
                temp->next = temp->next->next;
                delete (p);
            }
        }
    }
}

// Function to calculate minutes from total minutes
int calculateMinutes(int value) {
    return value % 60;
}

// Function to calculate hours from total minutes
int calculateHours(int value) {
    return value / 60;
}

// Main function
int main() {
    int current_line = 0, word, site_count, i = 0, j = 0;
    istringstream c;
    string line;
    SiteList L;
    L = NULL;

    ifstream file("AAC-instance.txt", ios::in);

    if (file) {
        Site value;
        while (!file.eof() && current_line <= 2) {
            current_line++;
            getline(file, line);
            if (current_line == 2) {
                c.str(line);
                c >> site_count;
                c.clear();
            }
        }
    } else {
        cerr << "Unable to open the file!" << endl;
        exit(1);
    }

    file.close();

    int MatTmp[site_count][site_count];

    ifstream matrix_file("AAC-instance-151.txt", ios::in);
    current_line = 0;

    if (matrix_file) {
        Site value;
        while (!matrix_file.eof()) {
            current_line++;
            getline(matrix_file, line);
            if (current_line > 4 && current_line <= site_count + 4) {
                c.str(line);
                int sum = 0;
                while (c.good()) {
                    sum++;
                    if (sum == 1) {
                        c >> value.id;
                    }
                    if (sum == 2) {
                        c >> value.score;
                    }
                    if (sum == 3) {
                        c >> value.time;
                    }
                    if (sum == 3) {
                        insertSite(&L, value);
                    }
                }
                sum = 0;
                c.clear();
            }
            if (current_line >= site_count + 6) {
                c.str(line);
                if (c.good()) {
                    for (int i = 0; c.good(); i++) {
                        c >> MatTmp[j][i];
                    }
                }
                j++;
                c.clear();
            }
        }
    } else {
        cerr << "Unable to open the file!" << endl;
        exit(1);
    }

    matrix_file.close();

    ResultSiteList result_list;
    result_list = NULL;
    ResultSite result_value;
    result_value.id = 0;
    result_value.score = 0;
    result_value.time = 0;
    result_value.departure_time = 0;
    result_value.arrival_time = 0;
    insertResultSite(&result_list, result_value);

    SiteList LN;
    LN = L;
    while (LN != NULL) {
        for (int i = 0; i < site_count; i++) {
            if (i != LN->data.id && LN->data.id != 0) {
                MatTmp[i][LN->data.id] = MatTmp[i][LN->data.id] + LN->data.time;
            }
        }
        LN = LN->next;
    }

    int test_time = 0, total_time = 720;
    bool zero_test = true;

    while (test_time <= total_time && zero_test) {
        zero_test = false;
        SiteList test_list, test_list1;
        test_list1 = L;
        test_list = NULL;
        Site new_site;
        ResultSite best_site;
        int count = 0, calculated_time = 0, calculated_score = 0, best_time, best_id;

        for (int i = 0; i < site_count; i++) {
            if (MatTmp[result_list->data.id][i] != 0) {
                calculated_time = calculated_time + MatTmp[result_list->data.id][i];
                count++;
            }
        }

        calculated_time = count > 0 ? calculated_time / count : 0;
        calculated_score = averageScore(L);

        for (int i = 0; i < site_count; i++) {
            if (MatTmp[result_list->data.id][i] != 0 && MatTmp[result_list->data.id][i] < calculated_time && i != 0) {
                zero_test = true;
                test_list1 = L;
                while (test_list1 != NULL) {
                    if (i == test_list1->data.id) {
                        if (test_list1->data.score > calculated_score) {
                            new_site.id = test_list1->data.id;
                            new_site.score = test_list1->data.score;
                            new_site.time = test_list1->data.time;
                            best_time = MatTmp[result_list->data.id][i];
                            best_id = i;
                            insertSite(&test_list, new_site);
                        }
                    }
                    test_list1 = test_list1->next;
                }
            }
        }

        if (test_list == NULL) {
            for (int i = 0; i < site_count; i++) {
                if (MatTmp[result_list->data.id][i] != 0 && MatTmp[result_list->data.id][i] < calculated_time && i != 0) {
                    test_list1 = L;
                    zero_test = true;
                    while (test_list1 != NULL) {
                        if (i == test_list1->data.id) {
                            new_site.id = test_list1->data.id;
                            new_site.score = test_list1->data.score;
                            new_site.time = test_list1->data.time;
                            best_time = MatTmp[result_list->data.id][i];
                            best_id = i;
                            insertSite(&test_list, new_site);
                        }
                        test_list1 = test_list1->next;
                    }
                }
            }
        }

        if (zero_test) {
            for (int i = 0; i < site_count; i++) {
                if (MatTmp[result_list->data.id][i] <= best_time && MatTmp[result_list->data.id][i] != 0) {
                    test_list1 = test_list;
                    while (test_list1 != NULL) {
                        if (test_list1->data.id == i) {
                            best_time = MatTmp[result_list->data.id][i];
                            best_id = i;
                        }
                        test_list1 = test_list1->next;
                    }
                }
            }

            while (test_list != NULL) {
                if (test_list->data.id == best_id) {
                    best_site.id = test_list->data.id;
                    best_site.score = test_list->data.score;
                    best_site.time = test_list->data.time;
                    best_site.arrival_time = test_time + MatTmp[result_list->data.id][best_site.id] - best_site.time;
                    best_site.departure_time = best_site.arrival_time + best_site.time;
                }
                test_list = test_list->next;
            }

            test_time = test_time + MatTmp[result_list->data.id][best_site.id] + MatTmp[best_site.id][0];

            if (test_time <= total_time) {
                insertResultSite(&result_list, best_site);
                Site best_site_val;
                best_site_val.id = best_site.id;
                best_site_val.score = best_site.score;
                best_site_val.time = best_site.time;
                removeSite(L, best_site_val);
                for (int i = 0; i < site_count; i++) {
                    for (int j = 0; j < site_count; j++) {
                        if (j == best_site.id) {
                            MatTmp[i][j] = 0;
                        }
                    }
                }
                test_time = test_time - MatTmp[best_site.id][0];
            } else {
                test_time = test_time - MatTmp[result_list->data.id][best_site.id] - MatTmp[best_site.id][0];
                for (int i = 0; i < site_count; i++) {
                    for (int j = 0; j < site_count; j++) {
                        if (j == best_site.id) {
                            MatTmp[i][j] = 0;
                        }
                    }
                }
                Site best_site_val;
                best_site_val.id = best_site.id;
                best_site_val.score = best_site.score;
                best_site_val.time = best_site.time;
                removeSite(L, best_site_val);
            }
        }
    }

    ResultSite final_site;
    final_site.id = 0;
    final_site.score = 0;
    final_site.time = 0;
    test_time = test_time + MatTmp[result_list->data.id][0];
    final_site.arrival_time = test_time;
    final_site.departure_time = 0;
    insertResultSite(&result_list, final_site);

    ofstream output_file("Result2.txt");

    if (output_file.good()) {
        int final_score = 0, site_count = 0, zero = 1;
        output_file << "Total travel time is: " << calculateHours(test_time) << " hours and " << calculateMinutes(test_time) << " minutes" << endl;
        output_file << "-------------------------------------------------------------------" << endl;
        while (result_list != NULL) {
            final_score = final_score + result_list->data.score;
            if (result_list->data.id == 0 && zero == 2) {
                output_file << "id = " << result_list->data.id << " , departure time = " << 8 + calculateHours(result_list->data.departure_time) << ":" << calculateMinutes(result_list->data.departure_time) << endl;
                zero++;
            } else if (result_list->data.id == 0 && zero == 1) {
                output_file << "id = " << result_list->data.id << " , arrival time = " << 8 + calculateHours(result_list->data.arrival_time) << ":" << calculateMinutes(result_list->data.arrival_time) << endl;
                zero++;
            } else {
                output_file << "id = " << result_list->data.id << " , arrival time = " << 8 + calculateHours(result_list->data.arrival_time) << ":" << calculateMinutes(result_list->data.arrival_time) << " , departure time = " << 8 + calculateHours(result_list->data.departure_time) << ":" << calculateMinutes(result_list->data.departure_time) << endl;
            }
            site_count++;
            result_list = result_list->next;
        }
        output_file << "-------------------------------------------------------------------" << endl;
        output_file << "Total score is: " << final_score << endl;
        output_file << "Number of visited sites: " << site_count << endl;
    } else {
        cerr << "ERROR!" << endl;
        exit(1);
    }

    output_file.close();
    return 0;
}
