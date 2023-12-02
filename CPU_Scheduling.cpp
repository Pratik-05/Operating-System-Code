#include <iostream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <queue>

using namespace std;
/*
    
    By -  Ayush Nandanwar
*/
class Process{ // Process Object Template
    public:
    int n; // process id
    int AT;
    int BT;
    int WT;
    int TAT;
    int CT;
    int PR;// Priority - higher number higher priority.
    int RT;  // burst remaining time
    Process(){}

    void findTATandWT(){
        TAT = CT - AT;
        WT = TAT - BT;
    }
};
void print(Process p[],int n){
    cout << "Prc \t AT \t BT \t CT \t TAT \t WT \t"<< endl;
    for(int i = 0;i < n;i++){
            p[i].findTATandWT();
            cout << p[i].n <<" \t ";
            cout << p[i].AT <<" \t ";
            cout << p[i].BT <<" \t ";
            cout << p[i].CT <<" \t ";
            cout << p[i].TAT<<" \t ";
            cout << p[i].WT <<" \t ";
            cout << "\n";
        }
}

void FCFSwithoutAT(){ // done
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process p[n];
    cout << "Enter Burst Time for every processes: \n";
    for (int i = 0; i < n; i++)
    { 
        cin >> p[i].BT;
        p[i].n = i + 1;
        p[i].AT = 0;  // without AT means at time 0 all processes has been arrived in ready queue.
    }

    int currTime = 0;
    for (int i = 0; i < n; i++)
    {
        currTime += p[i].BT;
        p[i].CT = currTime;
    }
    print(p,n);  
    float avgWT = 0;
    float avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;  
}

void sortFCFS(Process p[],int n){ // sort according to FCFS Algo i.e sort wrt AT
    for(int i = 0;i < n-1;i++){
        for(int j = 0;j < n - i - 1;j++){
            if(p[j].AT > p[j+1].AT){
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void FCFSwithAT(){ // done
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process p[n];
    cout << "Enter Arrival Time and Burst Time for every processes: \n";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].AT;
        cin >> p[i].BT;
        p[i].n = i + 1;
    }
    int currTime = 0;
    sortFCFS(p,n);  // sorting according to AT
    int complete = 0; // how many process completed
    int i = 0;
    while(complete != n){
        if(p[i].AT <= currTime){
            currTime += p[i].BT;
            p[i].CT = currTime;
            complete++;
            i++;
        }else{
            currTime++;
        } 
    }
    print(p,n);  
    float avgWT = 0;
    float avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;  
}

void SJFNonPreemptive(){
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process p[n];
    for(int i = 0;i < n;i++)
	{
		p[i].n = i + 1;
    }
    cout <<"Enter Arrival Time and Burst Time: \n";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].AT;
        cin >> p[i].BT;
        p[i].RT = p[i].BT;
    }
    int currTime = 0,complete = 0;
    while(complete != n){
        int idx = -1;
        int min = INT_MAX;
        for(int i = 0; i < n; i++) {  // finding the process with small burst time in ready queue.
            if(p[i].AT <= currTime && p[i].RT != 0) {
                if(p[i].BT < min) {
                    min = p[i].BT; 
                    idx = i;
                }
                if(p[i].BT == min) {
                    if(p[i].AT < p[idx].AT) {
                        min = p[i].BT;
                        idx = i;
                    }
                }
            }
        }
        if(idx != - 1){ // process found in ready queue with short burst time
            currTime += p[idx].RT;
            p[idx].CT = currTime;
            p[idx].RT = 0;
            complete++;
        }
        else currTime++;
    }
    print(p,n);

    float avgWT = 0;
    float avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;
}

void SJFPreemptive(){
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process p[n];
    for(int i = 0;i < n;i++)
	{
    	p[i].n = i + 1;
    }
    cout <<"Enter Arrival Time and Burst Time: \n";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].AT;
        cin >> p[i].BT;
        p[i].RT = p[i].BT;
    }
    int currTime = 0,complete = 0;
    // print(p,n); 
    while(complete != n){
        int idx = -1;
        int min = INT_MAX;
        for(int i = 0; i < n; i++) {  // finding the process with small burst time in ready queue.
            if(p[i].AT <= currTime && p[i].RT != 0) {
                if(p[i].RT < min) {
                    min = p[i].RT; 
                    idx = i;
                }
                if(p[i].RT == min) {
                    if(p[i].AT < p[idx].AT) {
                        min = p[i].RT;
                        idx = i;
                    }
                }
            }
        }
        if(idx != - 1){ // process found in ready queue with short burst time
            currTime++;
            p[idx].RT--;
            if(p[idx].RT == 0){
                p[idx].CT = currTime;
                complete++;
            }
           
        }
        else currTime++;
    }
    print(p,n);
    float avgWT = 0;
    float avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;
    
}

void PriorityNonPreemptive(){
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process p[n];
    cout << "Enter AT,BT and Priority(0 - highest priority) of each processes: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "P"<< i + 1 << ": ";
        cin >> p[i].AT >> p[i].BT >> p[i].PR;
        p[i].RT = p[i].BT;
        p[i].n = i + 1;
    }
    int complete = 0;
    int currTime = 0;
    while(complete != n){
       int idx = -1;
        int max = -1; // as higher number higher priority
        for(int i = 0; i < n; i++) { // finding the process in ready queue with highest priority
            if(p[i].AT <= currTime && p[i].RT != 0) {
                if(p[i].PR > max) {
                    max = p[i].PR;
                    idx = i;
                }
                if(p[i].PR == max) {
                    if(p[i].AT < p[idx].AT) {
                        max = p[i].PR;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1){  // process found in ready queue with highest priority.
            currTime += p[idx].RT;
            p[idx].CT = currTime;
            p[idx].RT = 0;
            complete++;
        }
        else currTime++;
    }
    print(p,n);  
    int avgWT = 0;
    int avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;  
}

void PriorityPreemptive(){
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process p[n];
    cout << "Enter AT,BT and Priority(0 - highest priority) of each processes: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "P"<< i + 1 << ": ";
        cin >> p[i].AT >> p[i].BT >> p[i].PR; 
        p[i].RT = p[i].BT;
        p[i].n = i + 1;
    }
    int complete = 0;
    int currTime = 0;
    int i = 0;
    while (complete != n)
    {
        int idx = -1;
        int max = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].AT <= currTime && p[i].RT != 0) {
                if(p[i].PR > max) {
                    max = p[i].PR;
                    idx = i;
                }
                if(p[i].PR == max) {
                    if(p[i].AT < p[idx].AT) {
                        max = p[i].PR;
                        idx = i;
                    }
                }
            }
        }
        if(idx != - 1){ // process found in ready queue with highest priority
            currTime++;
            p[idx].RT--;
            if(p[idx].RT == 0){
                p[idx].CT = currTime;
                complete++;
            }
           
        }
        else currTime++;
    }
    print(p,n);  
    int avgWT = 0;
    int avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;  
}

// round robin
bool compare1(Process p1, Process p2) 
{ 
    return p1.AT < p2.AT;
}

bool compare2(Process p1, Process p2) 
{  
    return p1.n < p2.n;
}

void roundRobin(){
    int n;
    cout <<"Enter the number of process: ";
    cin >> n;
    Process p[n];
    cout << "Enter the AT and BT for each process \b";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].AT >> p[i].BT;
        p[i].n = i + 1;
        p[i].RT = p[i].BT;
    }
    cout << "Enter the time quantum/slice: ";
    int tq;
    cin >> tq;
    sort(p,p+n,compare1);
    queue<int> q;
    int currTime = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    //memset(mark,0,sizeof(mark));
    mark[0] = 1;
    
    while(completed != n){
        int idx = q.front();
        q.pop();
        if(p[idx].RT - tq > 0) {
            p[idx].RT -= tq;
            currTime += tq;
        }else{
            currTime += p[idx].RT;
            p[idx].RT = 0;
            p[idx].CT = currTime;
            completed++;
        }

        for(int i = 1; i < n; i++) {
            if(p[i].RT > 0 && p[i].AT <= currTime && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if(p[idx].RT > 0) {
            q.push(idx);
        }
        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(p[i].RT > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    print(p,n);  
    int avgWT = 0;
    int avgTAT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
    }
    cout << "\n";
    cout << "Average Waiting Time is : "<< avgWT/n;
    cout << "\nAverage Waiting Time is : "<< avgTAT/n;  
    
}

int main(){

    while(true){
        cout << "--- CPU Scheduling Algorithm \n";
        cout <<" 1. FCFS Non-Preemptive \n";
        cout <<" 2. FCFS Preemptive \n";
        cout <<" 3. SJF Non Preemptive \n";
        cout <<" 4. SJF Preemptive \n";
        cout <<" 5. Priority Non-Preemptive \n";
        cout <<" 6. Priority Preemptive \n";
        cout <<" 7. Round Robin \n";
        cout <<"\nEnter your choice: ";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            FCFSwithoutAT();
            break;
        case 2:
            FCFSwithAT();
            break;
        case 3:
            SJFNonPreemptive();
            break;
        case 4:
            SJFPreemptive();
            break;
        case 5:
            PriorityNonPreemptive();
            break;
        case 6:
            PriorityPreemptive();
            break;
        case 7:
            roundRobin();
            break;
        default:
            cout << "Invalid Choice \n";
            break;
        }

        cout << "\nDo you want to continue? (Y/N): ";
        char cn = 'N';
        cin >> cn;
        if(cn != 'Y'){
            break;
        }
    }
}

/*

--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 

Enter your choice: 1
Enter number of processes: 4
Enter Burst Time for every processes: 
5
3
8
6
Prc      AT      BT      CT      TAT     WT 
1        0       5       5       5       0       
2        0       3       8       8       5       
3        0       8       16      16      8       
4        0       6       22      22      16      

Average Waiting Time is : 7
Average Waiting Time is : 12
Do you want to continue? (Y/N): Y
--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 

Enter your choice: 2
Enter number of processes: 4
Enter Arrival Time and Burst Time for every processes: 
0 5
1 3
2 8
3 6
Prc      AT      BT      CT      TAT     WT 
1        0       5       5       5       0       
2        1       3       8       7       4       
3        2       8       16      14      6       
4        3       6       22      19      13      

Average Waiting Time is : 5.75
Average Waiting Time is : 11.25
Do you want to continue? (Y/N): Y
--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 

Enter your choice: 3
Enter the number of processes: 4
Enter Arrival Time and Burst Time: 
0 1
1 4
2 9
3 5
Prc      AT      BT      CT      TAT     WT 
1        0       1       1       1       0       
2        1       4       5       4       0       
3        2       9       19      17      8       
4        3       5       10      7       2       

Average Waiting Time is : 2.5
Average Waiting Time is : 7.25
Do you want to continue? (Y/N): Y
--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 

Enter your choice: 4
Enter the number of processes: 4
Enter Arrival Time and Burst Time: 
0 7
2 4
4 2
7 1
Prc      AT      BT      CT      TAT     WT 
1        0       7       14      14      7       
2        2       4       6       4       0       
3        4       2       8       4       2       
4        7       1       9       2       1       

Average Waiting Time is : 2.5
Average Waiting Time is : 6
Do you want to continue? (Y/N): Y
--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 

Enter your choice: 5
Enter number of processes: 4
Enter AT,BT and Priority(0 - highest priority) of each processes: 
P1: 0 5 1
P2: 1 3 2
P3: 2 8 1
P4: 3 6 3
Prc      AT      BT      CT      TAT     WT 
1        0       5       5       5       0       
2        1       3       14      13      10      
3        2       8       22      20      12      
4        3       6       11      8       2       

Average Waiting Time is : 6
Average Waiting Time is : 11
Do you want to continue? (Y/N): Y
--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 

Enter your choice: 6
Enter number of processes: 4
Enter AT,BT and Priority(0 - highest priority) of each processes: 
P1: 0 5 1
P2: 1 3 2
P3: 2 8 1
P4: 3 6 2
Prc      AT      BT      CT      TAT     WT 
1        0       5       14      14      9       
2        1       3       4       3       0       
3        2       8       22      20      12      
4        3       6       10      7       1       

Average Waiting Time is : 5
Average Waiting Time is : 11
Do you want to continue? (Y/N): Y
--- CPU Scheduling Algorithm 
 1. FCFS Non-Preemptive 
 2. FCFS Preemptive 
 3. SJF Non Preemptive 
 4. SJF Preemptive 
 5. Priority Non-Preemptive 
 6. Priority Preemptive 
 7. Round Robin 
 
Enter your choice: 7
Enter the number of process: 3
Enter the AT and BT for each process0 24
0 3
0 3
Enter the time quantum/slice: 4
Prc      AT      BT      CT      TAT     WT 
1        0       24      30      30      6       
2        0       3       7       7       4       
3        0       3       10      10      7       

Average Waiting Time is : 5
Average Waiting Time is : 15
Do you want to continue? (Y/N): N

*/
