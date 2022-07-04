#include <iostream> // used for input and output
#include <iomanip> // used for alignment
#include <string> // used for std::string 
#include <cctype> // used for the purpose of toupper()
#include <fstream> // used for file io operation
#include <ctime> // get current time
#include <chrono> // used in the sleep_for function to convert value given in second
#include <thread> // used for sleep_for function to pause the execution with the given time

using namespace std;

struct moviesData {

    char m_name[41] = "";
    char date[20] = "";
    char time[20] = "";
    char day_week[15] = "";
    int all_seats = 0;
    int seat_sold_1 = 0;
    int seat_sold_2 = 0;
    int seat_sold_3 = 0;
    int total = 0;
    int total_sold = 0;
    int ac_seats[6] = {};
    double all_prices = 0;
    double seat_percent_1 = 0;
    double seat_percent_2 = 0;
    double seat_percent_3 = 0;
    double total_percent = 0;
    double total_price_seats[6] = {};

};

void menu(string info[], string layout_1[], string layout_2[], string layout_3[]);
void ticket_sale(int r_seats, int option, string info[], string classes, int classes_seat[], string layout_1[], string layout_2[], string layout_3[]);
void second_menu(string info[], int classes_seats[], string layout_1[], string layout_2[], string layout_3[]);
bool valid_date(int day, int month, int year);
void sleep();

void ini_seats(string info[]) { // initialize seats

    string layout_1[30], layout_2[30], layout_3[30]; // used to store the seats layout of each class

    for (int i = 0; i < 30; i++) {
        layout_1[i] = to_string(101 + i); // saves the seats into arrays by looping the numbers in string data type
    }
    for (int i = 0; i < 30; i++) {
        layout_2[i] = to_string(201 + i);
    }
    for (int i = 0; i < 30; i++) {
        layout_3[i] = to_string(301 + i);
    }

    menu(info, layout_1, layout_2, layout_3); // proceed to the first menu
    return;
}

string uppercase(string m_name) { // trim both side of the string and convert the string into uppercase

    m_name.erase(0, m_name.find_first_not_of(" ")); // erase the left spaces by erasing from the first position 0 until first index that found not spaces (left trim)
    m_name.erase(m_name.find_last_not_of(" ") + 1); // erase the right spaces at the last position + 1 (right trim)

    for (unsigned int i = 0; i < m_name.length(); i++) { // convert whole string input to uppercase
        m_name[i] = toupper(m_name[i]);
    }

    return m_name;
}

void display_seats(string layout_1[], string layout_2[], string layout_3[], int option) { // display selected class seat

    switch (option) {
    case 1:
        for (int i = 0; i < 30; i++) {
            if ((i % 5 == 0) && (i != 0)) {
                cout << endl;
            }
            cout << layout_1[i] << " ";
        }
        break;
    case 2:
        for (int i = 0; i < 30; i++) {
            if ((i % 5 == 0) && (i != 0)) {
                cout << endl;
            }
            cout << layout_2[i] << " ";
        }
        break;
    case 3:
        for (int i = 0; i < 30; i++) {
            if ((i % 5 == 0) && (i != 0)) {
                cout << endl;
            }
            cout << layout_3[i] << " ";
        }
        break;
    }

    return;
}

void display_logo() { // display cinema title

    string title = "|TAR StarMax Ticketing System|";
    int title_size = title.size();
    string dashes = string(title_size, '-');
    int padding = 80 - (title_size / 2);
    cout << setw(padding) << dashes << endl;
    cout << setw(padding) << title << endl;
    cout << setw(padding) << dashes << endl;

    return;

}

string* select_seats(int total_seats, string layout_1[], string layout_2[], string layout_3[], int option, int r_seats) { // select seats

    int count = 0;
    static string choose[30]; // including seats number of layout_1,layout_2 or layout_3
    string* new_layout = layout_1; // initialize the pointer

    switch (option) // point to the desired array with pointer
    {
    case 1:
        new_layout = layout_1;
        break;
    case 2:
        new_layout = layout_2;
        break;
    case 3:
        new_layout = layout_3;
        break;
    }

    if (total_seats == r_seats) {
        cout << "You have purchased the maximum seats available for this class. Redirecting to the payment session." << endl;
        for (int i = 0; i < 30; i++) {
            if (*(new_layout + i) != "X") {
                choose[count] = *(new_layout + i);
                count += 1;
            }
        }
        sleep();
    }

    else {
        while (count < total_seats) { // select seat based on the total seats select
            int found = 0; // counter to validate whether the result found or not

            cout << endl << endl << "Please select your seats (" << (total_seats - count) << " remaining): ";
            getline(cin, choose[count]);

            for (int i = 0; i < 30; i++) {
                if (choose[count] == *(new_layout + i)) { // if the input matches the value in the array
                    *(new_layout + i) = 'X'; // turns selected seat into 'X' to indicate no longer available
                    count += 1;
                    found += 1;
                    display_seats(layout_1, layout_2, layout_3, option);
                }
            }

            if (found == 0) {
                cout << "The seat you chosen is not available." << endl << endl;
                display_seats(layout_1, layout_2, layout_3, option);
            }
        }
    }


    return choose; // return selected seat array

}

void sleep() { // function to pause a program

    int time = 2; // to store sleep time

    this_thread::sleep_for(chrono::seconds(time)); // sleep with the time given

}

void file_check() {

    ifstream inData, readIndex;
    ofstream outData, outIndex;
    int index[2] = { 0,9 };


    /*Save information on the sales report*/
    inData.open("sales_report.bin");
    readIndex.open("index.bin");

    if (!inData || !readIndex) { //check if sales report file exists
        cout << "File Not Found. Creating New File..." << endl;
        outData.open("sales_report.bin", ios::out | ios::binary);
        outIndex.open("index.bin", ios::out | ios::binary);
        outIndex.write(reinterpret_cast<char*> (&index), sizeof(index));
    }


    /*Close Files*/
    inData.close();
    outData.close();
    readIndex.close();
    outIndex.close();
    return;
}

bool is_digit(string day, string month, string year) {

    for (unsigned i = 0; i < day.length(); i++) {
        if (!isdigit(day[i])) {
            return false;
        }
    }
    for (unsigned i = 0; i < month.length(); i++) {
        if (!isdigit(month[i])) {
            return false;
        }
    }
    for (unsigned i = 0; i < year.length(); i++) {
        if (!isdigit(year[i])) {
            return false;
        }
    }
    return true;
}

void previous_sales(int index, char option) {
    const int ori_seats[3] = { 30,30,30 }; // fixed seats for each classes

    ifstream inData;

    struct moviesData record[10];

    /*padding for the title to be aligned*/
    string title = "PREVIOUS TICKET SALES REPORT";
    int title_size = title.size();
    int padding = 80 - (title_size / 2); // set padding value to print lines

    if (option == 'y' || option == 'Y') {
        inData.open("sales_report_old.bin", ios::in | ios::binary);
    }

    else {
        inData.open("sales_report.bin", ios::in | ios::binary);
    }

    if (!inData) {
        cout << "An error occurred while opening the file. Terminating Program... " << endl << endl;
        sleep();
    }

    else {
        inData.read(reinterpret_cast<char*>(&record), sizeof(record)); // read file

        for (int i = 0; i < padding; i++) { cout << "="; }; // print line
        cout << endl << setw(46) << title << endl << endl; // display title
        cout << "Movie Title:   " << record[index].m_name << endl;
        cout << "Date / Time:   " << record[index].day_week << " " << record[index].date << " (" << record[index].time << ")" << endl << endl;
        cout << "SEAT OCCUPANCY FOR EACH CLASS:" << endl << endl;

        /*Display seat occupancy for each class*/
        cout << fixed << setprecision(2); // set the number of decimal points to 2 
        cout << setw(22) << "Total Seats" << setw(17) << "Quantity Sold" << setw(10) << "Sold %" << endl << endl;
        cout << "Class 1" << setw(9) << ori_seats[0] << setw(17) << record[index].seat_sold_1 << setw(16) << record[index].seat_percent_1 << endl << endl;
        cout << "Class 2" << setw(9) << ori_seats[1] << setw(17) << record[index].seat_sold_2 << setw(16) << record[index].seat_percent_2 << endl << endl;
        cout << "Class 3" << setw(9) << ori_seats[2] << setw(17) << record[index].seat_sold_3 << setw(16) << record[index].seat_percent_3 << endl << endl;
        cout << setw(22) << string(12, '=') << setw(17) << string(14, '=') << setw(10) << string(7, '=') << endl << endl; // print lines
        cout << "OVERALL" << setw(9) << record[index].total << setw(17) << record[index].total_sold << setw(16) << record[index].total_percent << endl << endl;
        /*End for display*/

        /*Seats for each category type*/
        cout << "SEAT FOR EACH CATEGORY TYPE:" << endl << endl;
        cout << fixed << setprecision(2); // set the number of decimal points to 2 
        cout << setw(22) << "Category" << setw(10) << "Seats" << setw(15) << "Sales(RM)" << endl << endl;
        cout << setw(22) << "ADULT" << setw(10) << record[index].ac_seats[0] << setw(15) << record[index].total_price_seats[0] << endl << endl;
        cout << setw(22) << "CHILD" << setw(10) << record[index].ac_seats[1] << setw(15) << record[index].total_price_seats[1] << endl << endl;
        cout << setw(22) << "SENIOR CITIZEN" << setw(10) << record[index].ac_seats[2] << setw(15) << record[index].total_price_seats[2] << endl << endl;
        cout << setw(22) << "STUDENT(F/D)" << setw(10) << record[index].ac_seats[3] << setw(15) << record[index].total_price_seats[3] << endl << endl;
        cout << setw(22) << "STUDENT(DEGREE)" << setw(10) << record[index].ac_seats[4] << setw(15) << record[index].total_price_seats[4] << endl << endl;
        cout << setw(22) << "STUDENT(PhD)" << setw(10) << record[index].ac_seats[5] << setw(15) << record[index].total_price_seats[5] << endl << endl;
        cout << setw(22) << string(9, '=') << setw(10) << string(6, '=') << setw(15) << string(20, '=') << endl << endl; // print lines
        cout << setw(22) << "TOTAL" << setw(10) << record[index].all_seats << setw(15) << record[index].all_prices << endl << endl;
        /*End for display*/

        inData.close();
    }
    return;
}

int previous_sales_file() { //check the file and put the desire data into an array

    ifstream inData, readIndex;

    int index[2];
    int count = 0;
    string m_name, day, month, year, date;
    char option = 'n';
    struct moviesData record[10];

    readIndex.open("index.bin", ios::in | ios::binary);
    inData.open("sales_report_old.bin", ios::in | ios::binary);

    if (!readIndex) {
        cout << "Index File not found. Returning to main menu..." << endl;
        sleep();
        return 0;
    }

    else if (!inData) {
        cout << "Old file not found. Opening current file." << endl;
        inData.open("sales_report.bin", ios::in | ios::binary);
        if (!inData) {
            cout << "Sales report file not found. Returning to main menu..." << endl;
            sleep();
            return 0;
        }
        else {
            readIndex.read(reinterpret_cast<char*>(&index), sizeof(index));
            inData.read(reinterpret_cast<char*>(&record), sizeof(record));
            cout << "These are the movie sales report available : " << endl << endl;
            cout << left;
            cout << setw(41) << "Movies name" << "Date" << endl << endl;

            for (int i = 0; i <= index[1]; i++) { // display movie details
                cout << setw(41) << record[i].m_name << record[i].date << endl;
            }

            cout << right;

            while (count == 0) {
                cout << endl << "Please enter the movie name. (0 to exit) : ";
                getline(cin, m_name);
                if (m_name.find_first_not_of(' ') == string::npos) {     /*using find_first_not_of(' ') to find the first character that doesn't match the parameter given which is the ' ' empty spaces
                                                                            if such character not found, it will return string::npos which is maximum size of the string data type*/
                    cout << "Please Don't Leave It Blank." << endl << endl;

                }

                else if (m_name == "0") {
                    cout << "Returning to the main menu" << endl << endl;
                    sleep();
                    return 0;
                }

                else {
                    count += 1;
                    m_name = uppercase(m_name);

                    while (count == 1) {

                        cout << "Please enter a date with the format (DD MM YYYY) : ";
                        cin >> day >> month >> year;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                               by giving the maximum size of the I/O buffer to be cleared completely
                                                                                to prevent cin reading unnecessary extra input*/
                        if (is_digit(day, month, year) && valid_date(stoi(day), stoi(month), stoi(year))) {
                            date = day + '-' + month + '-' + year; // construct date format

                            for (int i = 0; i <= index[1]; i++) {
                                inData.read(reinterpret_cast<char*>(&record[i]), sizeof(record[i])); //read struct file

                                if (m_name == record[i].m_name) { // if input matches name member in struct
                                    if (date == record[i].date) { // if input matches date member in struct
                                        count += 1;
                                        previous_sales(i, option); // proceed to display sales report
                                        break;
                                    }
                                }
                            }
                            if (count == 1) {
                                cout << "Record not found." << endl << endl; // if both record not found
                                count -= 1; // loop back to name input
                            }
                        }

                        else {
                            cout << "Invalid Date. Please try again." << endl << endl;

                        }
                    }
                }
            }
        }
    }

    else {

        while (count == 0) {

            cout << "Do you wish to view back the oldest file? (y = yes , n = no) : ";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                        by giving the maximum size of the I/O buffer to be cleared completely
                                                                         to prevent cin reading unnecessary extra input*/

            if (option == 'y' || option == 'Y') {
                count += 1;
            }
            else if (option == 'n' || option == 'N') {
                inData.close();
                count += 1;
                inData.open("sales_report.bin", ios::in | ios::binary);
            }
            else {
                cout << "Invalid Input" << endl << endl;

            }
        }

        if (inData && readIndex) {

            readIndex.read(reinterpret_cast<char*>(&index), sizeof(index));
            inData.read(reinterpret_cast<char*>(&record), sizeof(record));
            cout << "These are the movie sales report available : " << endl << endl;
            cout << left;
            cout << setw(41) << "Movies name" << "Date" << endl << endl;

            for (int i = 0; i <= index[1]; i++) {
                cout << setw(41) << record[i].m_name << record[i].date << endl;
            }

            cout << right;

            while (count == 1) {
                cout << endl << "Please enter the movie name. (0 to exit) : ";
                getline(cin, m_name);

                if (m_name.find_first_not_of(' ') == string::npos) { /*using find_first_not_of(' ') to find the first character that doesn't match the parameter given which is the ' ' empty spaces
                                                                       if such character not found, it will return string::npos which is maximum size of the string data type*/

                    cout << "Please Don't Enter An Empty String." << endl << endl;
                }


                else if (m_name == "0") {
                    cout << "Returning to the main menu..." << endl;
                    sleep();
                    return 0;
                }

                else {
                    count += 1;
                    m_name = uppercase(m_name);

                    while (count == 2) {
                        cout << "Please enter a date with the format (DD MM YYYY) : ";
                        cin >> day >> month >> year;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                               by giving the maximum size of the I/O buffer to be cleared completely
                                                                                to prevent cin reading unnecessary extra input*/
                        if (is_digit(day, month, year) && valid_date(stoi(day), stoi(month), stoi(year))) {
                            date = day + '-' + month + '-' + year;

                            for (int i = 0; i <= index[1]; i++) {
                                inData.read(reinterpret_cast<char*>(&record[i]), sizeof(record[i]));

                                if (m_name == record[i].m_name) {
                                    if (date == record[i].date) {
                                        count += 1;
                                        previous_sales(i, option);
                                        break;
                                    }
                                }
                            }
                            if (count == 2) {
                                cout << "Record not found." << endl << endl;
                                count -= 1; // looping back to name input
                            }
                        }

                        else {

                            cout << "Invalid Date. Please try again." << endl << endl;

                        }
                    }
                }
            }
        }
        else {
            cout << "An error occurred while opening the file. Returning to main menu" << endl;
            inData.close();
            readIndex.close();
            sleep();
            return 0;
        }
    }

    /*Close File*/
    inData.close();
    readIndex.close();
    return 1;
}

void class_update(int option, int total_seats, string info[], int classes_seats[], int ac_seats[]) { // update class seats
    int* remain_1 = &classes_seats[0]; // initialize remaining seats with pointers 
    int* remain_2 = &classes_seats[1];
    int* remain_3 = &classes_seats[2];

    switch (option) { // deducts number of remaining seats
    case 1:
        *remain_1 -= total_seats;
        break;
    case 2:
        *remain_2 -= total_seats;
        break;
    case 3:
        *remain_3 -= total_seats;
        break;
    }

    cout << "Number of seats has been updated." << endl << endl << endl;
    return;
}

void sales_report(string info[], int seats[], int classes_seats[], int ac_seats[], double total_price_seats[]) { //function to display sales report

    const int ori_seats[3] = { 30,30,30 }; // fixed seats for each classes

    ifstream inData, readIndex, inOld;
    ofstream outData, outIndex;

    int all_seats = 0; // store number of all of the seats sold
    double all_prices = 0;  // store total of the prices earned

    for (int i = 0; i < 6; i++) { // sum up all the seats and prices
        all_seats += ac_seats[i];
        all_prices += total_price_seats[i];
    }

    /*Seats sold*/
    int seat_sold_1 = ori_seats[0] - classes_seats[0];
    int seat_sold_2 = ori_seats[1] - classes_seats[1];
    int seat_sold_3 = ori_seats[2] - classes_seats[2];

    /*Seats sold percentage*/
    double seat_percent_1 = ((double)seat_sold_1 / ori_seats[0]) * 100;
    double seat_percent_2 = ((double)seat_sold_2 / ori_seats[1]) * 100;
    double seat_percent_3 = ((double)seat_sold_3 / ori_seats[2]) * 100;

    /*Total Seats*/
    int total = ori_seats[0] + ori_seats[1] + ori_seats[2];
    int total_sold = seat_sold_1 + seat_sold_2 + seat_sold_3;
    double total_percent = ((double)total_sold / total) * 100;

    /*padding for the title to be aligned*/
    string title = "TICKET SALES REPORT";
    int title_size = title.size();
    int padding = 80 - (title_size / 2); // set padding value to print lines



    for (int i = 0; i < padding; i++) { cout << "="; }; // print line
    cout << endl << setw(46) << title << endl << endl; // display title
    cout << "Movie Title:   " << info[0] << endl;
    cout << "Date / Time:   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl << endl;
    cout << "SEAT OCCUPANCY FOR EACH CLASS:" << endl << endl;

    /*Display seat occupancy for each class*/
    cout << fixed << setprecision(2); // set the number of decimal points to 2 
    cout << setw(22) << "Total Seats" << setw(17) << "Quantity Sold" << setw(10) << "Sold %" << endl << endl;
    cout << "Class 1" << setw(9) << ori_seats[0] << setw(17) << seat_sold_1 << setw(16) << seat_percent_1 << endl << endl;
    cout << "Class 2" << setw(9) << ori_seats[1] << setw(17) << seat_sold_2 << setw(16) << seat_percent_2 << endl << endl;
    cout << "Class 3" << setw(9) << ori_seats[2] << setw(17) << seat_sold_3 << setw(16) << seat_percent_3 << endl << endl;
    cout << setw(22) << string(12, '=') << setw(17) << string(14, '=') << setw(10) << string(7, '=') << endl << endl; // print lines
    cout << "OVERALL" << setw(9) << total << setw(17) << total_sold << setw(16) << total_percent << endl << endl;
    /*End for display*/

    /*Seats for each category type*/
    cout << "SEAT FOR EACH CATEGORY TYPE:" << endl << endl;
    cout << fixed << setprecision(2); // set the number of decimal points to 2 
    cout << setw(22) << "Category" << setw(10) << "Seats" << setw(15) << "Sales(RM)" << endl << endl;
    cout << setw(22) << "ADULT" << setw(10) << ac_seats[0] << setw(15) << total_price_seats[0] << endl << endl;
    cout << setw(22) << "CHILD" << setw(10) << ac_seats[1] << setw(15) << total_price_seats[1] << endl << endl;
    cout << setw(22) << "SENIOR CITIZEN" << setw(10) << ac_seats[2] << setw(15) << total_price_seats[2] << endl << endl;
    cout << setw(22) << "STUDENT(F/D)" << setw(10) << ac_seats[3] << setw(15) << total_price_seats[3] << endl << endl;
    cout << setw(22) << "STUDENT(DEGREE)" << setw(10) << ac_seats[4] << setw(15) << total_price_seats[4] << endl << endl;
    cout << setw(22) << "STUDENT(PhD)" << setw(10) << ac_seats[5] << setw(15) << total_price_seats[5] << endl << endl;
    cout << setw(22) << string(9, '=') << setw(10) << string(6, '=') << setw(15) << string(10, '=') << endl << endl; // print lines
    cout << setw(22) << "TOTAL" << setw(10) << all_seats << setw(15) << all_prices << endl << endl;
    /*End for display*/

    /*Save data*/
    int new_index[2] = { 0,9 }; // the index of the structure array

    readIndex.open("index.bin", ios::in | ios::binary);
    inData.open("sales_report.bin", ios::in | ios::binary);

    if (!inData || !readIndex) { // if can't open file
        cout << "Error occurred while opening the file. This record data will not be saved" << endl << endl;
        readIndex.close();
        inData.close();
    }
    else {
        readIndex.read(reinterpret_cast<char*> (&new_index), sizeof(new_index)); // read the latest index in file
        outIndex.open("index.bin", ios::out | ios::binary);
        outData.open("sales_report.bin", ios::out | ios::binary | ios::app);

        struct moviesData record[10]; // declare struct array with 10 sale records

        /*Convert string into char array to prevent read violation in struct*/
        char* new_movie = &info[0][0]; //pointers point to the address of the first index of the string
        char* new_date = &info[1][0];
        char* new_time = &info[2][0];
        char* new_day = &info[3][0];

        /*Assign values to struct members by copying the content of the address from the source*/
        strcpy_s(record[new_index[0]].m_name, sizeof(record[new_index[0]].m_name), new_movie);
        strcpy_s(record[new_index[0]].date, sizeof(record[new_index[0]].date), new_date);
        strcpy_s(record[new_index[0]].time, sizeof(record[new_index[0]].time), new_time);
        strcpy_s(record[new_index[0]].day_week, sizeof(record[new_index[0]].day_week), new_day);

        record[new_index[0]].seat_sold_1 = seat_sold_1;
        record[new_index[0]].seat_sold_2 = seat_sold_2;
        record[new_index[0]].seat_sold_3 = seat_sold_3;
        record[new_index[0]].seat_percent_1 = seat_percent_1;
        record[new_index[0]].seat_percent_2 = seat_percent_2;
        record[new_index[0]].seat_percent_3 = seat_percent_3;
        record[new_index[0]].total = total;
        record[new_index[0]].total_sold = total_sold;
        record[new_index[0]].total_percent = total_percent;
        record[new_index[0]].all_prices = all_prices;
        record[new_index[0]].all_seats = all_seats;

        for (int i = 0; i < 6; i++) {
            record[new_index[0]].ac_seats[i] = ac_seats[i];
            record[new_index[0]].total_price_seats[i] = total_price_seats[i];
        }

        /*Write data to sales_report.bin file*/
        outData.write(reinterpret_cast<char*>(&record[new_index[0]]), sizeof(record[new_index[0]]));
        inData.close();// close files
        outData.close();

        if (new_index[0] >= 9 && new_index[1] >= 9) { // if both index reach or exceed number limit for struct, reset the first index and start to perform rename action
            new_index[0] = 0; // the first index is for write file purpose
            new_index[1] = 9; // the second index is for read file purpose

            if (rename("sales_report.bin", "sales_report_old.bin") == 0) { //if old file name does not exist rename current file and create a new file
                outData.open("sales_report.bin"); // create new file after renaming the old file
                inData.open("sales_report.bin", ios::in | ios::binary);
                if (inData) {
                    cout << "New file has been created successfully." << endl;
                    inData.close();
                }
                else {
                    cout << "An error occurred while creating the file." << endl;
                    inData.close();
                    return;
                }
            }
            else { // if old file name exists delete the old file name and rename the current one
                if (remove("sales_report_old.bin") == 0) {// first remove the old file
                    cout << "Old file has been removed" << endl;

                    if (rename("sales_report.bin", "sales_report_old.bin") == 0) { // check if the new file has renamed successfully
                        outData.open("sales_report.bin"); // create a new file
                        inData.open("sales_report.bin", ios::in | ios::binary);
                        if (inData) {
                            cout << "New file has been created successfully." << endl;
                            inData.close();
                        }
                        else {
                            cout << "An error occurred while creating the file." << endl;
                            inData.close();
                            return;
                        }
                    }
                }

                else {
                    cout << "There's an error while renaming the file." << endl;
                    return;
                }


            }
        }

        else { // if second index reaches the number limit and the first one doesn't, update the first index
            new_index[0] += 1;
        }

        /*Write new index into index.bin file*/
        outIndex.write(reinterpret_cast<char*> (&new_index), sizeof(new_index));



        if (new_index[1] - new_index[0] == 0) {
            inOld.open("sales_report_old.bin", ios::in | ios::binary);

            if (!inOld) {
                cout << "Saving Data... The next saving process will create a new file" << endl;
                sleep();
            }

            else {
                cout << "Saving Data... The next saving process will delete the old file to create a new one." << endl;
                cout << "Make sure to change your old file name to preserve the data..." << endl;
                sleep();
            }

        }
        else {
            cout << "Saving Data... (" << new_index[1] - new_index[0] + 1 << " reports remaining to create a new file)" << endl;
            sleep();
        }


        /*Close Files*/
        inOld.close();
        outIndex.close();
        readIndex.close();
    }


    /*Print ending message and exit*/
    cout << "Thanks for using our services. See you next time ~~" << endl;
    cout << "Press Enter Key To Exit" << endl;
    if (cin.get()) {
        return;
    }

}

void ticket_printing(string info[], int seats[], int option, double prices[], int classes_seats[], int ac_seats[], double total_price_seats[], string layout_1[], string layout_2[], string layout_3[], string* choose) { // print tickets for the customers

    string class_name = ""; // initialize class name with a empty string
    string title = "TAR StarMax Ticketing System";
    int title_size = title.size();
    int padding = 80 - (title_size / 2); // set padding value to print lines
    char confirm; // to store the user input for next user confirmation.
    int counter = 1; // use to break the loop by changing its value


    switch (option) //determine the class chosen by user and assign the address of the variables to the pointer
    {
    case 1:
        class_name = "Class 1";
        break;
    case 2:
        class_name = "Class 2";
        break;
    case 3:
        class_name = "Class 3";
        break;
    }

    string seat_num = "Seats " + *choose; //format string with the selected seat

    /*Start to print tickets*/
    for (int i = 0; i < seats[0]; i++) { // print tickets for adult seats with the numbers of the seats

        seat_num = "Seats " + *choose; // use to update seat number 

        for (int i = 0; i < padding; i++) { cout << '='; };
        cout << endl << title << setw(20) << "ADULT - " << class_name << endl << endl;
        cout << left;
        cout << "This Friday Movie :   " << info[0] << endl;
        cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
        cout << setw(22) << left << seat_num << "Price : RM" << prices[0] << endl << endl;
        cout.unsetf(ios::left);
        choose += 1; // address of pointer +1 after printing each of the tickets

    }

    for (int i = 0; i < seats[1]; i++) {  // print tickets for children seats with the numbers of the seats

        seat_num = "Seats " + *choose;

        for (int i = 0; i < padding; i++) { cout << '='; }; // print line
        cout << endl << title << setw(20) << "CHILDREN - " << class_name << endl << endl;
        cout << left;
        cout << "This Friday Movie :   " << info[0] << endl;
        cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
        cout << setw(22) << left << seat_num << "Price : RM" << prices[1] << endl << endl;
        cout.unsetf(ios::left);
        choose += 1;

    }

    for (int i = 0; i < seats[2]; i++) { // print tickets for senior seats with the numbers of the seats

        seat_num = "Seats " + *choose;

        for (int i = 0; i < padding; i++) { cout << '='; }; //print line
        cout << endl << title << setw(20) << "SENIOR CITIZEN - " << class_name << endl << endl;
        cout << left;
        cout << "This Friday Movie :   " << info[0] << endl;
        cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
        cout << setw(22) << left << seat_num << "Price : RM" << prices[2] << endl << endl;
        cout.unsetf(ios::left);
        choose += 1;
    }
    for (int i = 0; i < seats[3]; i++) { // print tickets for foundation/diploma student seats with the numbers of the seats

        seat_num = "Seats " + *choose;

        for (int i = 0; i < padding; i++) { cout << '='; };//print line 
        cout << endl << title << setw(35) << "STUDENT (FOUNDATION/DIPLOMA) - " << class_name << endl << endl;
        cout << left;
        cout << "This Friday Movie :   " << info[0] << endl;
        cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
        cout << setw(22) << left << seat_num << "Price : RM" << prices[3] << endl << endl;
        cout.unsetf(ios::left);
        choose += 1;
    }

    for (int i = 0; i < seats[4]; i++) { // print tickets for degree student seats with the numbers of the seats

        seat_num = "Seats " + *choose;

        for (int i = 0; i < padding; i++) { cout << '='; }; // print line
        cout << endl << title << setw(22) << "STUDENT (DEGREE) - " << class_name << endl << endl;
        cout << left;
        cout << "This Friday Movie :   " << info[0] << endl;
        cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
        cout << setw(22) << left << seat_num << "Price : RM" << prices[4] << endl << endl;
        cout.unsetf(ios::left);
        choose += 1;
    }

    for (int i = 0; i < seats[5]; i++) { // print tickets for degree student seats with the numbers of the seats

        seat_num = "Seats " + *choose;

        for (int i = 0; i < padding; i++) { cout << '='; }; //print line
        cout << endl << title << setw(20) << "STUDENT (PhD) - " << class_name << endl << endl;
        cout << left;
        cout << "This Friday Movie :   " << info[0] << endl;
        cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
        cout << setw(22) << left << seat_num << "Price : RM" << prices[5] << endl << endl;
        cout.unsetf(ios::left);
        choose += 1;
    }

    /*End of print tickets*/

    cout << "Seats Still Available:" << endl; //shows remaining seats
    cout << setw(16) << right << "Class 1 = " << classes_seats[0] << endl;
    cout << setw(16) << right << "Class 2 = " << classes_seats[1] << endl;
    cout << setw(16) << right << "Class 3 = " << classes_seats[2] << endl << endl;

    if (classes_seats[0] == 0 && classes_seats[1] == 0 && classes_seats[2] == 0) {
        cout << "All of the tickets has been sold out. Redirecting to sales report..." << endl;
        sleep(); // make it pause to simulate the loading session
        sales_report(info, seats, classes_seats, ac_seats, total_price_seats);
    }

    else {
        do {
            cout << "Next Customer? (Y = Yes , N = No) ";
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                    by giving the maximum size of the I/O buffer to be cleared completely
                                                                    to prevent cin reading unnecessary extra input*/

            if (!cin.fail()) { //if the user input data type is not wrong
                if (confirm == 'Y' || confirm == 'y') {
                    counter += 1; // change value to break the loop
                    second_menu(info, classes_seats, layout_1, layout_2, layout_3); // go to the second menu
                }
                else if (confirm == 'N' || confirm == 'n') {
                    counter += 1;// change value to break the loop
                    sales_report(info, seats, classes_seats, ac_seats, total_price_seats);
                }
                else {
                    cout << "Please Select A Valid Option" << endl << endl; // error message
                }
            }
            else {
                cout << "Invalid Input. Only single character is accepted" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                    by giving the maximum size of the I/O buffer to be cleared completely
                                                                    to prevent cin reading unnecessary extra input*/
            }
        } while (counter == 1);
    }
    return;

}

void calculation(int total_seats, int seats[], int option, string info[], int classes_seats[], int ac_seats[], string layout_1[], string layout_2[], string layout_3[], string* choose) { // function for tickets price calculation and payment

    string class_name = ""; // store class name
    int index = 0; // to determine the price of the class based on index
    int count = 0; // counter to break loop
    double prices[6] = {}; // to store prices of each category
    static double total_price_seats[6] = {}; // store total price of each seat

    // price of tickets

    const double senior[3] = { 14,16,20 };
    const double adult[3] = { 18,20,26 };
    const double child[3] = { 9,10,13 };

    // student tickets price multiplier

    const double diploma_foundation = 0.95;
    const double degree = 0.93;
    const double phd = 0.91;

    switch (option) { // determine the price of the class based on index
    case 1:
        class_name = "Class 1";
        index = 0;
        break;
    case 2:
        class_name = "Class 2";
        index = 1;
        break;
    case 3:
        class_name = "Class 3";
        index = 2;
        break;
    }

    /*Price Calculation*/
    double total_adult = adult[index] * seats[0];
    double total_child = child[index] * seats[1];
    double total_senior = senior[index] * seats[2];

    double f_student_price = adult[index] * diploma_foundation; // Foundation / Diploma Student
    double total_f_student_price = f_student_price * seats[3];

    double d_student_price = adult[index] * degree; // Degree Student
    double total_d_student_price = d_student_price * seats[4];

    double p_student_price = adult[index] * phd; // PHD Student
    double total_p_student_price = p_student_price * seats[5];

    double total_price = total_adult + total_child + total_senior + total_f_student_price + total_d_student_price + total_p_student_price; // calculate total price
    double payment = 0; // Initialize payment

    prices[0] = adult[index];
    prices[1] = child[index];
    prices[2] = senior[index];
    prices[3] = f_student_price;
    prices[4] = d_student_price;
    prices[5] = p_student_price;


    cout << endl << endl << endl << "Bill calculation - " << class_name << endl << endl << endl;
    cout << fixed << setprecision(2);
    cout << "Number of Adults                     = " << setw(5) << seats[0] << "@RM" << adult[index] << setw(11) << "= RM" << total_adult << endl;
    cout << "Number of Child                      = " << setw(5) << seats[1] << "@RM" << child[index] << setw(11) << "= RM" << total_child << endl;
    cout << "Number of Senior                     = " << setw(5) << seats[2] << "@RM" << senior[index] << setw(11) << "= RM" << total_senior << endl;

    cout << "Number of Diploma/Foundation Student = " << setw(5) << seats[3] << "@RM" << f_student_price << "(5%)" << setw(7) << "= RM" << total_f_student_price << endl;
    cout << "Number of Degree Student             = " << setw(5) << seats[4] << "@RM" << d_student_price << "(7%)" << setw(7) << "= RM" << total_d_student_price << endl;
    cout << "Number of PhD Student                = " << setw(5) << seats[5] << "@RM" << p_student_price << "(9%)" << setw(7) << "= RM" << total_p_student_price << endl;

    cout << setw(15) << "Total to pay" << setw(48) << "= RM" << total_price << endl;

    while (count == 0) {
        cout << setw(15) << "Cash Payment" << setw(48) << "= RM";
        cin >> payment;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

        if (cin.fail()) {
            cout << "Invalid Input. Please try again" << endl << endl;
            cin.clear(); // Used to clear error flag in user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                 by giving the maximum size of the I/O buffer to be cleared completely
                                                                 to prevent infinity loops*/
        }

        else if (payment - total_price < 0) {
            cout << "Insufficient Payment. Please try again." << endl << endl;
        }

        else {
            count += 1;
        }

    }

    double change_due = payment - total_price;
    cout << setw(15) << "Change Due" << setw(48) << "= RM" << change_due << endl;

    // accumulate total price value
    total_price_seats[0] += total_adult;
    total_price_seats[1] += total_child;
    total_price_seats[2] += total_senior;
    total_price_seats[3] += total_f_student_price;
    total_price_seats[4] += total_d_student_price;
    total_price_seats[5] += total_p_student_price;

    class_update(option, total_seats, info, classes_seats, ac_seats); // updates class seats
    cout << "Updating class seats...." << endl;
    sleep();
    cout << "Here are your tickets :" << endl;
    ticket_printing(info, seats, option, prices, classes_seats, ac_seats, total_price_seats, layout_1, layout_2, layout_3, choose); // prints tickets
    return;
}

void second_menu(string info[], int classes_seats[], string layout_1[], string layout_2[], string layout_3[]) { // menu that pops up while seats sold out or second loop
    int remain_1 = classes_seats[0];
    int remain_2 = classes_seats[1];
    int remain_3 = classes_seats[2];

    int option = 0; // for class selection
    int count = 0;
    int r_seats = 0; // Used to store the selected number of  class seats. 
    string classes = ""; // to store class name


    while (count == 0) {
        cout << "Class Required? (1,2,3) : ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                    by giving the maximum size of the I/O buffer to be cleared completely
                                                                    to prevent cin reading unnecessary extra input*/
        if (cin.fail()) {
            cout << "Please Enter An Integer" << endl << endl;
            cin.clear(); // Used to clear error flag in user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                   by giving the maximum size of the I/O buffer to be cleared completely
                                                                   to prevent cin reading unnecessary extra input*/
        }

        else if (option < 1 || option > 3) {
            cout << "Please Enter A Valid Option" << endl << endl;
        }

        else {

            switch (option) {

            case 1: // Assign seats numbers and class name based on option
                r_seats = remain_1;
                classes = "Class 1";
                break;
            case 2:
                r_seats = remain_2;
                classes = "Class 2";
                break;
            case 3:
                r_seats = remain_3;
                classes = "Class 3";
                break;
            }
            count += 1;
        }
    }
    ticket_sale(r_seats, option, info, classes, classes_seats, layout_1, layout_2, layout_3);
    return;
}

void ticket_sale(int r_seats, int option, string info[], string classes, int classes_seats[], string layout_1[], string layout_2[], string layout_3[]) { // function to sell tickets

    int a_seats, s_seats, c_seats, stf_seats, std_seats, stp_seats; // variables for adult,child,senior citizen, and students.
    int seats[6] = {}; // array to store number of seats for each categories (adult,child,senior citizen, and students)
    static int ac_seats[6] = {}; // array to store number of total seats for each categories (adult,child,senior citizen, and students)
    int total_seats = 0;
    int count = 0;

    if (r_seats <= 0) {
        cout << "There are no remaining seats for this class, please choose another class instead." << endl << endl;
        cout << "Seats Still Available:" << endl; //shows remaining seats
        cout << setw(16) << right << "Class 1 = " << classes_seats[0] << endl;
        cout << setw(16) << right << "Class 2 = " << classes_seats[1] << endl;
        cout << setw(16) << right << "Class 3 = " << classes_seats[2] << endl << endl;
        second_menu(info, classes_seats, layout_1, layout_2, layout_3);
    }

    else {

        cout << "These are the seats available for this class" << endl << endl;
        display_seats(layout_1, layout_2, layout_3, option);

        while (count == 0) {
            cout << endl << endl << "Number of Adult seats required :" << setw(10);
            cin >> a_seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

            if (cin.fail()) {
                cout << "Please Enter An Integer" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/
            }

            else if (a_seats < 0) {
                cout << "Number of seats cannot be negative" << endl << endl;
            }

            else {
                total_seats += a_seats;
                count += 1;
            }
        }
        while (count == 1) {
            cout << "Number of Children seats required :" << setw(10);
            cin >> c_seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

            if (cin.fail()) {
                cout << "Please Enter An Integer" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                     by giving the maximum size of the I/O buffer to be cleared completely
                                                                     to prevent infinity loops*/
            }

            else if (c_seats < 0) {
                cout << "Number of seats cannot be negative" << endl << endl;
            }

            else {
                total_seats += c_seats;
                count += 1;
            }
        }

        while (count == 2) {
            cout << "Number of Senior Citizens seats required :" << setw(10);
            cin >> s_seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

            if (cin.fail()) {
                cout << "Please Enter An Integer" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                     by giving the maximum size of the I/O buffer to be cleared completely
                                                                     to prevent infinity loops*/
            }

            else if (s_seats < 0) {
                cout << "Number of seats cannot be negative" << endl << endl;
            }

            else {
                total_seats += s_seats;
                count += 1;
            }
        }

        while (count == 3) {
            cout << "Number of Foundation/Diploma Students seats required :" << setw(10);
            cin >> stf_seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

            if (cin.fail()) { // If users input is not an integer
                cout << "Please Enter An Integer" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                     by giving the maximum size of the I/O buffer to be cleared completely
                                                                     to prevent infinity loops*/
            }

            else if (stf_seats < 0) { // if the user input is a negative number
                cout << "Number of seats cannot be negative" << endl << endl;
            }

            else { // accumulate the total seats for updating the number of seats
                total_seats += stf_seats;
                count += 1;
            }
        }

        while (count == 4) {
            cout << "Number of Degree Students seats required :" << setw(10);
            cin >> std_seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

            if (cin.fail()) { // If users input is not an integer
                cout << "Please Enter An Integer" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                     by giving the maximum size of the I/O buffer to be cleared completely
                                                                     to prevent infinity loops*/
            }

            else if (std_seats < 0) { // if the user input is a negative number
                cout << "Number of seats cannot be negative" << endl << endl;
            }

            else { // accumulate the total seats for updating the number of seats
                total_seats += std_seats;
                count += 1;
            }
        }

        while (count == 5) {
            cout << "Number of PhD Students seats required :" << setw(10);
            cin >> stp_seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

            if (cin.fail()) { // If users input is not an integer
                cout << "Please Enter An Integer" << endl << endl;
                cin.clear(); // Used to clear error flag in user input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                     by giving the maximum size of the I/O buffer to be cleared completely
                                                                     to prevent infinity loops*/
            }

            else if (stp_seats < 0) { // if the user input is a negative number
                cout << "Number of seats cannot be negative" << endl << endl;
            }

            else { // accumulate the total seats for updating the number of seats
                total_seats += stp_seats;
                count += 1;
            }
        }

        if (r_seats - total_seats < 0) { // if the tickets number exceeds the number of remaining seats
            cout << endl << "The total seats that you have chosen has exceeded the limit of the seats, please select another class or reduce the number of seats chosen." << endl;
            for (int i = 0; i < 140; ++i) { cout << '-'; } // print line
            cout << endl << endl;
            cout << "Seats Still Available:" << endl; //shows remaining seats
            cout << setw(16) << right << "Class 1 = " << classes_seats[0] << endl;
            cout << setw(16) << right << "Class 2 = " << classes_seats[1] << endl;
            cout << setw(16) << right << "Class 3 = " << classes_seats[2] << endl << endl;
            second_menu(info, classes_seats, layout_1, layout_2, layout_3);
        }

        else if (total_seats == 0) { // if user doesn't purchase any tickets
            cout << "You did not purchase any tickets. Redirecting back to the menu." << endl << endl;
            sleep();
            cout << "Seats Still Available:" << endl; //shows remaining seats
            cout << setw(16) << right << "Class 1 = " << classes_seats[0] << endl;
            cout << setw(16) << right << "Class 2 = " << classes_seats[1] << endl;
            cout << setw(16) << right << "Class 3 = " << classes_seats[2] << endl << endl;
            second_menu(info, classes_seats, layout_1, layout_2, layout_3);
        }
        else {

            string* choose = select_seats(total_seats, layout_1, layout_2, layout_3, option, r_seats);
            /*store values of the current number of seats bought */
            seats[0] = a_seats;
            seats[1] = c_seats;
            seats[2] = s_seats;
            seats[3] = stf_seats;
            seats[4] = std_seats;
            seats[5] = stp_seats;

            /*store value of total number of seats for each category use for sales report calculation*/
            for (int i = 0; i < 6; i++) {
                ac_seats[i] += seats[i];
            }

            calculation(total_seats, seats, option, info, classes_seats, ac_seats, layout_1, layout_2, layout_3, choose);
        }
    }
    return;
}

void menu(string info[], string layout_1[], string layout_2[], string layout_3[]) { // first menu to obtain user data input

    int option = 0; // class option
    int count = 0; // counter to break loop

    // number of seats for each class
    int classes_seats[3] = { 30,30,30 };

    int r_seats = 0;
    string classes = "";

    display_logo();

    cout << left;
    cout << "This Friday Movie :   " << info[0] << endl;
    cout << "Date / Time       :   " << info[3] << " " << info[1] << " (" << info[2] << ")" << endl;
    cout << "Counter is now Open for Selling of Tickets " << endl << endl;
    cout << "Seats Available:" << endl;

    cout << setw(16) << right << "Class 1 = " << classes_seats[0] << endl;
    cout << setw(16) << right << "Class 2 = " << classes_seats[1] << endl;
    cout << setw(16) << right << "Class 3 = " << classes_seats[2] << endl << endl;



    while (count == 0) {
        cout << "Class Required? (1,2,3) 0 to exit: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

        if (cin.fail()) {
            cout << "Please Enter An Integer" << endl << endl;
            cin.clear(); // Used to clear error flag in user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/
        }

        else if (option < 0 || option > 3) {
            cout << "Please Enter A Valid Option" << endl << endl;
        }

        else {

            switch (option) {
            case 0: // exit program
                cout << "Thanks for using our service. See you next time." << endl;
                cout << "Press Enter Key To Exit." << endl;

                if (cin.get()) {
                    return;
                }
                break;
            case 1:
                r_seats = classes_seats[0];
                classes = "Class 1";
                break;
            case 2:
                r_seats = classes_seats[1];
                classes = "Class 2";
                break;
            case 3:
                r_seats = classes_seats[2];
                classes = "Class 3";
                break;
            }
            count += 1;
        }
    }

    ticket_sale(r_seats, option, info, classes, classes_seats, layout_1, layout_2, layout_3);
    return;
}

string chk_day(int day, int month, int year) { // to check the weekday based on the given date

    string day_week[7] = { "Saturday","Sunday","Monday","Tuesday", "Wednesday","Thursday","Friday" };
    int change_month = month;

    if (month <= 2) {
        change_month = 12 + month; //for Jan and Feb, month code will be 13 and 14
        year -= 1; //decrease year for month Jan and Feb
    }

    /*(year % 100) is to obtain the last two digits of the year and (year / 100) is to obtain the first two digits of the year*/

    int index = (day + int((13 * (change_month + 1)) / 5) + year % 100 + int((year % 100) / 4) + int((year / 100) / 4) + int(5 * (year / 100))) % 7;
    return day_week[index];
}

bool leap(int year) { // to determine whether the year given is a leap year
    if ((((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))) {
        return true;
    }
    else {
        return false;
    }
}

bool valid_date(int day, int month, int year) { // date validation

    if (year < 1800 || year > 9999) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }

    if (month == 2) {
        if (leap(year)) {
            if (day <= 29) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            if (day <= 28) {
                return true;
            }
            else {
                return false;
            }
        }
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day <= 30) {
            return true;
        }
        else {
            return false;
        }
    }

    return true;
}

void input() {

    string m_name, day_week, choice; // store user input of movie name, day of the week, and the time choice
    string clock[2] = { "AM","PM" }; // save AM and PM use for string format
    string info[4]; // save info of movie name, date , time , and day of the week.
    string date; // save date as char for sprintf string formatting
    string time_string;// save time 
    int day, month, year, hour, minute; // save user input
    int day_option = 1;
    int count = 1;

    struct tm tm;// initialize tm structure in c_time
    time_t now = std::time(0); // get current time
    localtime_s(&tm, &now);  // convert given time since epoch into calender time

    /*get current year, month , and day*/

    int current_year = 1900 + tm.tm_year;
    int current_month = tm.tm_mon + 1;
    int current_day = tm.tm_mday;

    // file streams initialization
    ifstream inData, inOldData, readIndex;

    while (count == 1) {

        cout << endl << "Please Enter A Movie Name : ";
        getline(cin, m_name); // get movie name

        if (m_name.find_first_not_of(' ') == string::npos) {     /*using find_first_not_of(' ') to find the first character that doesn't match the parameter given which is the ' ' empty spaces
                                                                   if such character not found, it will return string::npos which is maximum size of the string data type*/
            cout << "Please Don't Leave It Blank." << endl << endl;
        }
        else if (m_name.length() > 40) { // if the movie name input is too long
            cout << "The movie name input is too long. Please try a different name" << endl << endl;
        }
        else {
            m_name = uppercase(m_name);
            count += 1;
        }
    }

    /*Date and Time Input Session*/

    while (count == 2) {

        cout << "Please Enter The Date With The Format (DD MM YYYY).\nThe date must be today or after. : ";
        cin >> day >> month >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/


        if (!cin.fail()) { // Input validation

            if (valid_date(day, month, year)) {
                if (year < current_year) {
                    cout << endl << "Invalid date. Please Try Again. The date should be today of after. " << endl << endl;
                }

                else if (((day < current_day) || month < current_month) && year == current_year) {
                    cout << endl << "Invalid date. Please Try Again. The date should be today of after." << endl << endl;

                }

                else {
                    day_week = chk_day(day, month, year);
                    count += 1; // break loop
                }
            }
            else {
                cout << endl << "Invalid date. Please Try Again." << endl << endl;
            }
        }

        else { //If input data type error
            cout << endl << "Please Enter Integers" << endl << endl;
            cin.clear(); // Used to clear error flag in user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                 by giving the maximum size of the I/O buffer to be cleared completely
                                                                 to prevent cin reading unnecessary extra input*/
        }

    }

    while (count == 3) {

        cout << "Please Enter The Time Of The Show With The 24 Hours Format (HH MM): ";
        cin >> hour >> minute;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/

        if (!cin.fail()) { // Input validation
            time_t now = std::time(0); // refresh time
            localtime_s(&tm, &now);// convert given time since epoch into calendar time

            if (day == tm.tm_mday && (month == tm.tm_mon + 1) && year == 1900 + tm.tm_year) { // if the time saved not equal to the current time
                if (hour == tm.tm_hour) { // if hour input less or equal than current hour
                    if (minute <= tm.tm_min) { // if minute input less or equal than current minute
                        cout << "The time input should be after the current time. " << endl << endl;
                        continue;
                    }
                }
                if (hour < tm.tm_hour) {
                    cout << "The time input should be after the current time." << endl << endl;
                    continue;

                }
            }

            else if (current_day != tm.tm_mday || (current_month != tm.tm_mon + 1) || current_year != 1900 + tm.tm_year) {
                cout << "The date has changed. Terminating program... (Press Enter Key To Exit.)" << endl;
                if (cin.get()) {
                    return;
                }
            }
            if (hour >= 0 && hour < 24 && minute >= 0 && minute < 59) {
                if (hour < 1 || hour >= 12) {
                    if (hour >= 13) {
                        hour = abs(hour - 12); // convert time to 12 hour clock system
                        choice = clock[1]; // choose PM
                        count += 1; // break loop
                    }
                    else if (hour == 0) {
                        hour = abs(hour - 12); // convert time to 12 hour clock system
                        choice = clock[0]; // choose AM
                        count += 1; // break loop
                    }

                    else if (hour == 12) {
                        choice = clock[1]; // choose PM
                        count += 1; // break loop
                    }
                }
                else {
                    choice = clock[0]; // choose AM
                    count += 1; // break loop
                }

            }


            if (hour < 0 || hour > 23) {
                cout << endl << "Invalid Hour Input. Please Try Again." << endl << endl;
            }

            if (minute < 0 || minute > 59) {
                cout << endl << "Invalid Minute Input. Please Try Again." << endl << endl;
            }
        }

        else { // if input data type error

            cout << "Please Enter Integer " << endl << endl;
            cin.clear(); // Used to clear error flag in user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                                by giving the maximum size of the I/O buffer to be cleared completely
                                                                to prevent cin reading unnecessary extra input*/
        }
    }

    if (minute >= 0 && minute < 9) { // format time and date and add a 0 before the minute for time display purpose for the menu
        if (choice == "AM") {
            time_string = to_string(hour) + ":0" + to_string(minute) + " AM";
            date = to_string(day) + '-' + to_string(month) + '-' + to_string(year);
        }
        else {
            time_string = to_string(hour) + ":0" + to_string(minute) + " PM";
            date = to_string(day) + '-' + to_string(month) + '-' + to_string(year);
        }
    }

    else { // format time and date for minute > 9

        if (choice == "AM") {
            time_string = to_string(hour) + ":" + to_string(minute) + " AM";
            date = to_string(day) + '-' + to_string(month) + '-' + to_string(year);
        }
        else {
            time_string = to_string(hour) + ":" + to_string(minute) + " PM";
            date = to_string(day) + '-' + to_string(month) + '-' + to_string(year);
        }
    }



    inData.open("sales_report.bin", ios::in | ios::binary);
    inOldData.open("sales_report_old.bin", ios::in | ios::binary);
    readIndex.open("index.bin", ios::in | ios::binary);

    struct moviesData record[10], record_2[10];
    int index[2];

    if (readIndex || inData || inOldData) {

        readIndex.read(reinterpret_cast<char*>(&index), sizeof(index));
        inData.read(reinterpret_cast<char*>(&record), sizeof(record));
        inOldData.read(reinterpret_cast<char*>(&record_2), sizeof(record_2));

        for (int i = 0; i <= index[1]; i++) {
            if (m_name == record[i].m_name || m_name == record_2[i].m_name) { // to check whether the movie session match the data in the file to prevent redundancy
                if (date == record[i].date || date == record_2[i].date) {
                    if (time_string == record[i].time || time_string == record_2[i].time) { // if all three inputs (movie name, date, time) matches the record in the file, terminate the program
                        cout << "This movie session has been sold. Please come again next time. (Press Enter Key To Exit)" << endl << endl;
                        if (cin.get()) {
                            return;
                        }
                    }
                }
            }
        }
    }
    else {
        cout << endl << "An error occurred while opening file... The sales data will not be saved afterward." << endl;
        cout << "If you want to save the sales record, please restart the program by entering 0 in the menu session or click the x button on the right corner of the console." << endl;
    }


    /*Save movie info*/

    info[0] = m_name;
    info[1] = date;
    info[2] = time_string;
    info[3] = day_week;

    /*Close files*/
    readIndex.close();
    inData.close();
    inOldData.close();

    ini_seats(info);
}

int main() // main function to get the user input for movie name, date and time then proceeds to another session
{

    int m_option; // for user option
    int count = 0; // for breaking loop

    while (count == 0) { // option selection

        file_check(); // check whether files exist
        display_logo(); // Display decorated cinema title

        cout << "Select an option " << endl;
        cout << "0. Exit " << endl;
        cout << "1. Buy Tickets" << endl;
        cout << "2. View Previous Sale Report" << endl;
        cout << ">> ";

        cin >> m_option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                             by giving the maximum size of the I/O buffer to be cleared completely
                                                             to prevent cin reading unnecessary extra input*/

        if (cin.fail()) { // if user input didn't match the data type
            cout << "Please Enter Integer." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Used to clear input buffer before entering the new line
                                                             by giving the maximum size of the I/O buffer to be cleared completely
                                                             to prevent cin reading unnecessary extra input*/

        }
        else {
            if (m_option < 0 || m_option > 2) {
                cout << "Invalid Input." << endl << endl;
            }
            else if (m_option == 2) {
                count = previous_sales_file();
            }
            else {
                count += 1;
            }
        }
    }

    if (m_option == 0 || m_option == 2) {
        cout << "Thank you for using our service. Press Enter Key To Exit" << endl;
        if (cin.get()) {
            return 0;
        }
    }
    else {
        input();
    }

    return 0;
}



