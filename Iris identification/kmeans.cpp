#include<ctime> 
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
using namespace std;
struct location{
   double x,y,z;
};
class Culser{
public:
    location centroid;
    vector<int> samples;
};
double distance(location a,location b){
    double val=pow(a.x-b.x,2);
    val+=pow(a.y-b.y,2);
    val+=pow(a.z-b.z,2);
    return pow(val,0.5);
}
vector<Culser> kmeans(vector<location>trainX,int k,int MAX){
    vector<Culser> culser(k);
    srand((unsigned)time(NULL));
    for(int i=0;i<k;i++){
        int x=rand()%trainX.size();
        location p=trainX[x];
        culser[i].centroid=p;
    }
    while(MAX--!=0){
        for(int i=0;i<k;i++){
            culser[i].samples.clear();
        }
        for(int i=0;i<trainX.size();i++){
            int c=0;
           double min_dis=distance(trainX[i],culser[0].centroid);
            for(int j=1;j<k;j++){
                double dis=distance(trainX[i],culser[j].centroid);
                if(dis<min_dis){
                    c=j;
                    min_dis=dis;
                }
            }
            culser[c].samples.push_back(i);
        }
        for(int i=0;i<k;i++){
            double valx=0,valy=0,valz=0;
            for(int j=0;j<culser[i].samples.size();j++){
                int sample=culser[i].samples[j];
                valx+=trainX[sample].x;      
                valy+=trainX[sample].y;
                valz+=trainX[sample].z;
                if(j==culser[i].samples.size()-1){
                    culser[i].centroid.x=valx/(culser[i].samples.size()+1);
                    culser[i].centroid.y=valy/(culser[i].samples.size()+1);
                    culser[i].centroid.z=valz/(culser[i].samples.size()+1);
                }
            }
        }
    }
    return culser;
}
int main(){
    vector<location>trainX(5);
    for(int i=0;i<5;i++){
        location p;
        p.x=p.y=p.z=1;
        cin>>p.x>>p.y>>p.z;
        trainX[i]=p;
    }
    vector<Culser>kmeans1=kmeans(trainX,3,100);
    for(int i=0;i<3;i++){
        cout<<"centroid"<<i<<":"<<kmeans1[i].centroid.x<<" "<<kmeans1[i].centroid.y<<" "<<kmeans1[i].centroid.z<<" "<<endl;
        for(int j=0;j<kmeans1[i].samples.size();j++){
            int k=kmeans1[i].samples[j];
            cout<<"Point"<<k<<":"<<trainX[k].x<<" "<<trainX[k].y<<" "<<trainX[k].z<<endl;
        }
        cout<<endl<<endl;
    }
    return 0;


