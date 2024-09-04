#include <vector>
#include <iostream>
#include<iomanip>
using namespace std;
class Taxi{
    public:
    static int id;
    int taxiId;
    int startTime;
    char currentLocation;
    int totalEarning;
    Taxi(){
        this->taxiId = id++;
        this->startTime=0;
        this->currentLocation ='A';
        this->totalEarning =0;
    }
};
int Taxi :: id = 0;
class Booking{
    public:
    int customerId;
    int taxiId;
    char pickupPoint;
    char dropPoint;
    int pickupTime;
    int bookingId;
    int amount;
    Booking(int customerId, int taxiId,  int bookingId ,char pickupPoint, char dropPoint , int pickupTime, int amount){
        this-> customerId;
        this->taxiId;
        this->pickupPoint;
        this->dropPoint;
        this->pickupTime;
        this->bookingId;
        this->amount; 
    }
};
class BookingDetails : public Taxi{
    public:
    vector<Taxi> taxis;
    vector<Booking> bookings;
    int bookingId;
    BookingDetails(){
        for(int i=0; i<6; i++){
            Taxi t;
            taxis.push_back(t);
        }
        bookingId=0;
    }

    int findtaxi(char pickupPoint, int pickupTime){
        int nearestTaxi= -1;
        for(int i=0; i<6; i++){
            if(taxis[i].startTime <= pickupTime && (pickupTime- taxis[i].startTime)>= (abs(pickupPoint - taxis[i].currentLocation)) ){
                if( taxis[nearestTaxi].currentLocation == taxis[i].currentLocation){
                    if(taxis[i].totalEarning < taxis[nearestTaxi].totalEarning){
                        nearestTaxi=i;
                    }
                }
                else if((abs(pickupPoint - taxis[i].currentLocation)) < (abs(pickupPoint - taxis[nearestTaxi].currentLocation))){
                    nearestTaxi=i;
                }
            }
        }
        return nearestTaxi;
    }

    int findAmount(char pickupPoint, char dropPoint){
        int amount;
        int distance = abs(pickupPoint - dropPoint);
        distance*=15;
        amount = 100 + (distance-5)*10;
        return amount;
    }
    void bookticket(){
        int customerId;
        char pickupPoint;
        char dropPoint;
        int pickupTime;
        int amount;
        cout<<"Enter booking details:"<<endl;

        cout<<"Customer ID:";
        
        cin>>customerId;
        
        cout<<"Enter Pickup Point:";
        cin>>pickupPoint;
        
        cout<<"Enter Drop Point:";
        cin>>dropPoint;
        
        cout<<"Enter pickup Time:";
        cin>>pickupTime;

        int taxi = findtaxi(pickupPoint,pickupTime);
        if(taxi==-1){
            "Taxi not available";
            return;
        }
        amount = findAmount(pickupPoint,dropPoint);
        int travelTime = abs(pickupPoint - dropPoint);
        Booking book(customerId,taxi,++bookingId, pickupPoint, dropPoint, pickupTime, amount);
        bookings.push_back(book);
        taxis[taxi].currentLocation = dropPoint;
        taxis[taxi].startTime += travelTime;
        taxis[taxi].totalEarning+=amount;
        cout<<"Taxi booked successfully"<<endl;
        cout<<"Taxi - "<<taxis[taxi].taxiId<<" is allocated"<<endl;
    }

    void printDetails(){
        cout<<"\n------------------------------------------------------------------------------------\n";
        cout<<endl<<setw(20)<<"Taxi ID"<<setw(20)<<"Total Earnings"<<setw(20)<<"Current Point"<<setw(20)<<"Available Time\n";
        for(int i=0; i<6; i++){
            cout<<"\n------------------------------------------------------------------------------------\n";
            cout<<setw(20)<<taxis[i].taxiId;
            cout<<setw(20)<<taxis[i].totalEarning;
            cout<<setw(20)<<taxis[i].currentLocation;
            cout<<setw(20)<<taxis[i].startTime;
            cout<<endl;
        }
        cout<<"\n------------------------------------------------------------------------------------\n";
    }

    void book(){
        while(1){
            cout<<"Enter option:"<<'\n'<<"1.Call Taxi Booking"<<'\n'<<"2. Display the Taxi details"<<'\n';
            int n;
            cin>>n;
            switch(n){
                case 1:
                    bookticket();
                    break;
                case 2:
                    printDetails();
                default:
                    return;
            }
        }
    }
};
int main(){
    BookingDetails b;
    b.book();

}
