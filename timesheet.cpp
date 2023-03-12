#include<bits/stdc++.h>
using namespace std;

string convertSecToTime(long long int t)
    {
        int hours = t / 3600;
        string hh = hours < 10 ? "0" + to_string(hours)
                               : to_string(hours);
        int min = (t % 3600) / 60;
        string mm = min < 10 ? "0" + to_string(min)
                             : to_string(min);
        int sec = ((t % 3600) % 60);
        string ss = sec < 10 ? "0" + to_string(sec)
                             : to_string(sec);
        string ans = hh + ":" + mm + ":" + ss;
        return ans;
    }

    long long int getTimeInSeconds(string str)
    {
        vector<int> curr_time;
        istringstream ss(str);
        string token;
        while (getline(ss, token, ':')) {
            curr_time.push_back(stoi(token));
        }
        long long int t = curr_time[0] * 60 * 60
                          + curr_time[1] * 60
                          + curr_time[2];
        return t;
    }

    string timeGap(string st, string et)
    {
        long long int t1 = getTimeInSeconds(st);
        long long int t2 = getTimeInSeconds(et);
        long long int time_diff
            = (t1 - t2 < 0) ? t2 - t1 : t1 - t2;
        return convertSecToTime(time_diff);
    }

    string timeAdd(string st, string et)
    {
        long long int t1 = getTimeInSeconds(st);
        long long int t2 = getTimeInSeconds(et);
        long long int time_diff = t1+t2;
        return convertSecToTime(time_diff);
    }


class Employee {

    public:
    string name;
    string clockIn;
    string clockOut;
    string breakStart;
    string breakStop;


    string getOfficeHour() {
        string s1 = timeGap(this->clockIn , this->clockOut);
        string s2 = timeGap(this->breakStart,this->breakStop);

        string ans = timeGap(s1,s2);

        return ans;
    }
};

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    Employee v[11][32];
    int l;
    cin >> l;
    int mon = 1;
    string officeOutTime = "19:30:00";
    while(l) {
        string s1,s2,s3,s4;
        int empNo;
        while(l) {
            cin >> s1 >> s2 >> s3 >> s4;
            int empId = s1[s1.length()-1]-'0';
            empNo = max(empNo,empId);
            int date = stoi(s2.substr(8,2));
            // int month = stoi(s2.substr(5,2));
            // if(month != mon) break;
            v[empId][date].name = s1;
            if(s4 == "clock-in") {
                v[empId][date].clockIn = s3;
            }
            else if(s4 == "clock-out") {
                v[empId][date].clockOut = s3;
            }
            else if(s4 == "break-start") {
                v[empId][date].breakStart = s3;
            }
            else{
                v[empId][date].breakStop = s3;
            }
            l--;
        }
    
        vector<string> totalTime(empNo+1,"00:00:00");
        for(int i=1;i<=empNo;i++) {
            for(int j=1;j<32;j++) {
                if(v[i][j].name == "") continue;
                if(v[i][j].clockOut == "") {
                    v[i][j].clockOut = min(officeOutTime , timeAdd("06:00:00",v[i][j].clockIn));
                }
                totalTime[i] = timeAdd(totalTime[i],v[i][j].getOfficeHour());
            }
        }
        sort(totalTime.begin(),totalTime.end());
        string worst = totalTime[1];
        string best = totalTime[empNo];
        string avg;
        long long int t = 0;
        for(int i=1;i<=empNo;i++) {
            t += getTimeInSeconds(totalTime[i]);
        }
        t /= empNo;
        avg = convertSecToTime(t);
        cout << best << " " << worst << " " << avg << "\n";
    }
    return 0;
}