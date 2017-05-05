#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int totalProfit;
int totalAds;
const int numberOfAds = 5000;

int start[numberOfAds], finish[numberOfAds], profit[numberOfAds];
bool channel1[numberOfAds], channel2[numberOfAds], channel3[numberOfAds], channel4[numberOfAds];

struct Advertisement {
    int start, finish, profit;
    bool channel[4];
};

Advertisement Ads[numberOfAds];

bool adCompare(Advertisement a1, Advertisement a2) {
    return (a1.finish < a2.finish);
}

void buildAds(Advertisement Ads[], int index) {
    Ads[index].start = start[index];
    Ads[index].finish = finish[index];
    Ads[index].profit = profit[index];
    Ads[index].channel[0] = channel1[index];
    Ads[index].channel[1] = channel2[index];
    Ads[index].channel[2] = channel3[index];
    Ads[index].channel[3] = channel4[index];
}

void compareAds(Advertisement Ads[], int original, int newAd, int chNumber) {
    Ads[original].start = start[newAd];
    Ads[original].finish = finish[newAd];
    Ads[original].profit = profit[newAd];
    Ads[original].channel[0] = channel1[newAd];
    Ads[original].channel[1] = channel2[newAd];
    Ads[original].channel[2] = channel3[newAd];
    Ads[original].channel[3] = channel4[newAd];

    for (int i = 0; i < original; i++) {
        if (Ads[original].finish < Ads[i].start) {
            swap(Ads[original],Ads[i]);
        }
        if (Ads[original].start < Ads[i].finish) {
                Ads[i] = Ads[original];
                Ads[original] = Ads[i + 1];
        }
    }

    //Last entry that will allow all results to be printed.
    if (newAd > 4997) {
        for (int i = 0; i < original+1; i++) {
            if (Ads[i].start != 0 && Ads[i].finish != 0) {
                if (Ads[i].start != Ads[i - 1].finish) {
                    totalProfit += Ads[i].profit;
                    totalAds ++;
                }
            }
        }
        if (chNumber == 1) {
            cout << "While reading the file: " << endl;
        }
        cout << "Channel: " << chNumber << endl;
        cout << "Total Profit: " << totalProfit << endl;
        totalProfit = 0;

        cout << "Number of Advertisements: " << totalAds << endl;
        totalAds = 0;

        cout << endl;
    }
}

void readAds(ifstream& inFile) {

    Advertisement ch1Ads[numberOfAds], ch2Ads[numberOfAds], ch3Ads[numberOfAds], ch4Ads[numberOfAds];

    int i = 0;
    int ch1Entries = 0, ch2Entries = 0, ch3Entries = 0, ch4Entries = 0;

    while (!inFile.eof()) {
        inFile >> start[i] >> finish[i] >> profit[i] >> channel1[i] >> channel2[i] >> channel3[i] >> channel4[i];

        if(channel1[i]) {
            compareAds(ch1Ads,ch1Entries, i, 1);
            ch1Entries++;
        }
        if(channel2[i]) {
            compareAds(ch2Ads,ch2Entries, i, 2);
            ch2Entries++;
        }
        if(channel3[i]) {
            compareAds(ch3Ads,ch3Entries, i, 3);
            ch3Entries++;
        }
        if(channel4[i]) {
            compareAds(ch4Ads,ch4Entries, i, 4);
            ch4Entries++;
        }
        i++;
    }

    //Remake Ads array for Activity Selection.
    for (int i = 0; i < numberOfAds; i++) {
        buildAds(Ads,i);
    }
}

void adActivitySelector(Advertisement Ads[], int size, int channelNumber) {

    sort(Ads,Ads+size,adCompare);

    int i = 0;

    for (int j = 1; j < size; j++) {

        if(Ads[j-1].channel[channelNumber-1]) {

            if (Ads[j].start > Ads[i].finish) {
                totalProfit += Ads[j].profit;
                totalAds++;
                i = j;
            }
            else if (Ads[j].start == Ads[i].finish || Ads[j].start == Ads[j].finish) {
                if (Ads[j].profit > Ads[i].profit) {
                    i = j;
                }
            }
        }
    }

    cout << endl << "Total Profit: " << totalProfit << endl;
    totalProfit = 0;

    cout << "Number of Advertisements: " << totalAds << endl;
    totalAds = 0;
}

int main() {

    ifstream inFile;

    inFile.open("input.txt"); // Open the file

    // Check if the file is opened or not
    // Exit if not
    if (inFile.fail()) {
        cout << "Fail to open the file" << endl;
        exit(1);
    }

    readAds(inFile); //Will create Ads object with information

    inFile.close(); // Close the file

    int size = numberOfAds;

    cout << "After reading whole file: " << endl;
    for (int i = 1; i < 5; i++) {
        cout << "Channel: " << i;
        adActivitySelector(Ads, size, i);
        cout << endl;
    }

    return 0;
}