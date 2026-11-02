#include<iostream>
#include<cmath>
#include<string>
using namespace std;

float battery_status(float distance, float battery)
{
    return battery - distance/100;
}

float distance_moved(float Xf,float Xi,float Yf,float Yi,float Zf,float Zi)
{
    return sqrt(pow(Xf-Xi,2)+pow(Yf-Yi,2)+pow(Zf-Zi,2));
}

class Component
{
public:
    string name,status;
    float power;

    void add()
    {
        cout<<"Enter component name: ";
        cin>>name;

        cout<<"Enter status (ON/OFF): ";
        cin>>status;

        cout<<"Enter power consumed: ";
        cin>>power;
    }

    void display()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Status: "<<status<<endl;
        cout<<"Power: "<<power<<" W"<<endl;
    }
};

class Propeller: public Component
{
public:
    int rpm;

    void add()
    {
        Component::add();

        cout<<"Enter RPM: ";
        cin>>rpm;
    }

    void display()
    {
        Component::display();
        cout<<"RPM: "<<rpm<<endl;
    }
};

class Sensor
{
public:
    void reading(float depth)
    {
        float time;

        cout<<"Enter running time in minutes: ";
        cin>>time;

        cout<<"Pressure: "<<(9.8*depth/100)+1<<" atm"<<endl;
        cout<<"Temperature: "<<300+time*0.01<<" K"<<endl;
        cout<<"Signal strength: "<<100000/(1000+depth)<<endl;
    }
};

class AUV
{
public:
    float Xi=0,Yi=0,Zi=0;
    float battery;
    float max_depth;

    float total_distance=0;
    float energy=0;

    int waypoints=0;
    int readings=0;

    bool sensor_status=true;

    Component c;
    Propeller p;

    void movement()
    {
        float X,Y,Z;

        cout<<"Enter X, Y and depth: ";
        cin>>X>>Y>>Z;

        if(Z<0 || Z>max_depth)
        {
            cout<<"Invalid depth!"<<endl;
            return;
        }

        float d=distance_moved(X,Xi,Y,Yi,Z,Zi);

        if(d/100>battery)
        {
            cout<<"Insufficient battery!"<<endl;
            return;
        }

        battery=battery_status(d,battery);

        total_distance+=d;
        energy+=d/100;

        Xi=X;
        Yi=Y;
        Zi=Z;

        waypoints++;

        cout<<"Movement successful!"<<endl;
        cout<<"Distance travelled: "<<d<<" m"<<endl;
        cout<<"Remaining battery: "<<battery<<"%"<<endl;
    }

    void status()
    {
        cout<<"\nPosition: "<<Xi<<" "<<Yi<<" "<<Zi<<endl;
        cout<<"Battery: "<<battery<<"%"<<endl;
        cout<<"Total distance: "<<total_distance<<" m"<<endl;
        cout<<"Sensor: "<<(sensor_status?"Working":"Failed")<<endl;
    }

    void sensor_reading()
    {
        if(sensor_status)
        {
            Sensor s;
            s.reading(Zi);
            readings++;
        }
        else
        {
            cout<<"Sensor is not working!"<<endl;
        }
    }

    void add_component()
    {
        int choice;

        cout<<"1. General Component\n2. Propeller\n";
        cin>>choice;

        if(choice==1)
            c.add();

        else if(choice==2)
            p.add();

        else
            cout<<"Invalid choice!"<<endl;
    }

    void exploration()
    {
        int n;

        cout<<"Enter number of waypoints: ";
        cin>>n;

        for(int i=0;i<n;i++)
        {
            cout<<"\nWaypoint "<<i+1<<endl;

            movement();

            if(sensor_status)
                readings++;
        }
    }

    void inspection()
    {
        cout<<"Enter inspection location:"<<endl;
        movement();

        if(sensor_status)
            readings++;
    }

    void fault()
    {
        int choice;

        cout<<"1. Sensor failure\n";
        cout<<"2. Low battery\n";
        cout<<"3. Restore sensor\n";

        cin>>choice;

        if(choice==1)
            sensor_status=false;

        else if(choice==2)
        {
            battery=10;
            cout<<"Battery reduced to 10%!"<<endl;
        }

        else if(choice==3)
            sensor_status=true;

        else
            cout<<"Invalid choice!"<<endl;
    }

    void report()
    {
        cout<<"\n----- MISSION REPORT -----"<<endl;

        cout<<"Waypoints visited: "<<waypoints<<endl;
        cout<<"Readings collected: "<<readings<<endl;
        cout<<"Total distance: "<<total_distance<<" m"<<endl;
        cout<<"Energy consumed: "<<energy<<"%"<<endl;
        cout<<"Remaining battery: "<<battery<<"%"<<endl;
    }
};

int main()
{
    AUV Matsya;

    cout<<"Enter initial battery level: ";
    cin>>Matsya.battery;

    cout<<"Enter maximum depth: ";
    cin>>Matsya.max_depth;

    int n;

    while(true)
    {
        cout<<"\n======= MATSYA AUV =======\n";

        cout<<"1. View AUV Status\n";
        cout<<"2. View Sensor Readings\n";
        cout<<"3. Add a Component\n";
        cout<<"4. Exploration Mission\n";
        cout<<"5. Inspection Mission\n";
        cout<<"6. Simulate a Fault\n";
        cout<<"7. Mission Report\n";
        cout<<"8. Exit\n";

        cout<<"Enter choice: ";
        cin>>n;

        if(n==1)
            Matsya.status();

        else if(n==2)
            Matsya.sensor_reading();

        else if(n==3)
            Matsya.add_component();

        else if(n==4)
            Matsya.exploration();

        else if(n==5)
            Matsya.inspection();

        else if(n==6)
            Matsya.fault();

        else if(n==7)
            Matsya.report();

        else if(n==8)
            break;

        else
            cout<<"Invalid choice!"<<endl;
    }

    return 0;
}
