#include<iomanip>
#include<iostream>
#include<cmath>
#include<map>
#include<fstream>
#include<cstdlib>
#include<ctime>

#define rownum 150
#define rownum1 30
#define cloumnnum  4
using namespace std;

//ifstream in; 
//ofstream out;

class KNN{
	public:
		double dataSet[rownum][cloumnnum];
		double testData[rownum1][cloumnnum];
		double testset[cloumnnum];
		string test;
		string symbol[rownum];
		string symboltest[rownum];
		string symbolreal[rownum];
		map <int,double> map_index_dis;
		map <string,int> map_label_freq;
		int k;
		int errornum;
		double RMSE;
		double sym[rownum];
		double symtest[rownum]; 
		
		KNN();
		int read();
		virtual double get_distance(double *d1,double *d2);
		virtual void save_distance();
		void calculate_maxtimes();
		void calculate_errornum();
		void conclude();
		void show();
		virtual int out();
		int outreal();
		void reform();
};

double KNN::get_distance(double *d1,double *d2){
	
	double sum=0;
	for(int i=0;i<cloumnnum;i++)
	{
		sum+=pow(d1[i]-d2[i],2);
	}
	sum=sqrt(sum);
	return sum;
}


// 1111111111111111111111111111111111111111
class distance1: public KNN{
	public:
		
 double get_distance(double *d1,double *d2)
{
	double sum=0;
	for(int i=0;i<cloumnnum;i++)
	{
		sum+=abs(d1[i]-d2[i]);
	}
	sum=sqrt(sum);
	return sum;
}

 void save_distance()
{
	double distance;
	int i;
	for(i=1;i<=120;i++)//  because index>0,index=1;  120=150-30;
	{
		distance =get_distance(dataSet[i],testset);
		map_index_dis[i]=distance;
		
	}//cout<<map_index_dis[1]<<endl;
}

int out()
{
	ofstream out;
	out.open("D:/test2.txt");
    if(!out)
    {
        cout<<"could not open the file."<<endl;
        return false;
    }
    
     for(int i=0;i<30;i++)
    {	
      for(int j=0;j<4;j++)
        {
        out<<testData[i][j]<<"  ";
        
        }
        out<<"  "<<symboltest[i]<<endl;
    }
    	out<<"���������  "<<errornum<<" ��"<<endl;
    	out<<"RMSE  :"<<RMSE<<endl;
        out.close();
        return true;
}

};

//1111111111111111111111111111111


KNN::KNN()
{	errornum=-12;
	if(!read())
		exit(1);
	cout<<"����kֵ "<<endl;
	cin>>k;
}

void KNN::show()
{
	cout<<endl;
	cout<< fixed <<setprecision(1)<<setw(6)<<testset[0]<<setw(6)<<"  "<<setw(6)<<testset[1]<<setw(6)<<"  "<<setw(6)<<testset[2]<<"  "<<setw(6)<<testset[3]<<"  "<<test<<endl;
}

KNN::read()
{
	ifstream in;
	
	in.open("D:/data.txt");
    if(!in )
    {
        cout<<"could not open the file"<<endl;
        return false;
    }
    
    for(int i=0;i<150;i++)
    {
        for(int j = 0;j<=4;j++)
        {
        	if(j!= 4)
        	{	
			in>>dataSet[i][j]; 
			}
          else in>>symbol[i];
        }
    }
    
   
    in.close();    
    
    return true;
}




void KNN::save_distance()
{
	double distance;
	int i;
	for(i=1;i<=120;i++)//  because index>0,index=1;  120=150-30;
	{
		distance =get_distance(dataSet[i],testset);
		map_index_dis[i]=distance;
		//cout<<map_index_dis[i]<<endl;
	}
}

void KNN::calculate_maxtimes()
{
	double t1;
	string t2;
	int count=0;
	
	for(int i=0;i<rownum-1;i++)
	{
		for(int j=i+1;j<rownum;j++)
		{
			if(map_index_dis[i]>map_index_dis[j])
			{
			t1=map_index_dis[i];
			map_index_dis[i]=map_index_dis[j];
			map_index_dis[j]=t1;
			
			t2=symbol[i];
			symbol[i]=symbol[j];
			symbol[j]=t2;
			}
		}
	}
	for(int p=0;p<k;p++)
	{
		
		map_label_freq[ symbol[p] ]++;
		
		//cout<<map_label_freq[ symbol[p] ]<<symbol[p]<<endl;
	}	
}

void KNN::conclude()
{
	if(map_label_freq["Iris-setosa"]>=map_label_freq["Iris-versicolor"]&&map_label_freq["Iris-setosa"]>=map_label_freq["Iris-virginica"])
		test="Iris-setosa";
	if(map_label_freq["Iris-versicolor"]>=map_label_freq["Iris-setosa"]&&map_label_freq["Iris-versicolor"]>=map_label_freq["Iris-virginica"])
		test="Iris-versicolor";
	if(map_label_freq["Iris-virginica"]>=map_label_freq["Iris-versicolor"]&&map_label_freq["Iris-virginica"]>=map_label_freq["Iris-setosa"])
		test="Iris-virginica";
}

void KNN::calculate_errornum()
{
	for(int i=0;i<30;i++)
    {
    	if(symboltest[i]!=symbolreal[i])
    	{errornum++;
		RMSE+=pow(sym[i]-symtest[i],2);
		}
    	RMSE=sqrt(RMSE);
	}
}

int KNN::out()
{
	ofstream out;
	out.open("D:/test1.txt");
    if(!out)
    {
        cout<<"could not open the file."<<endl;
        return false;
    }
    
     for(int i=0;i<30;i++)
    {	
      for(int j=0;j<4;j++)
        {
        out<<testData[i][j]<<"  ";
        }

        out<<"  "<<symboltest[i]<<endl;
    }
    	out<<"���������  "<<errornum<<" ��"<<endl;
    	out<<"RMSE  :"<<RMSE<<endl;
        out.close();
        return true;
}


int KNN::outreal()
{
	ofstream outreal;
	outreal.open("D:/testreal.txt");
    if(!outreal)
    {
        cout<<"could not open the file."<<endl;
        return false;
    }
    
     for(int i=0;i<30;i++)
    {	
      for(int j=0;j<4;j++)
        {
        outreal<<testData[i][j]<<"  ";
        }

        outreal<<"  "<<symbolreal[i]<<endl;
    }
        outreal.close();
        return true;
}

void KNN::reform()
{
	for(int i=0;i<30;i++)
    {
    	if(symbolreal[i]=="Iris-setosa")
    	sym[i]=1;
    	if(symbolreal[i]=="Iris-versicolor")
    	sym[i]=1.5;
    	if(symbolreal[i]=="Iris-virginica")
    	sym[i]=2;
    	
    	if(symboltest[i]=="Iris-setosa")
    	symtest[i]=1;
    	if(symboltest[i]=="Iris-versicolor")
    	symtest[i]=1.5;
    	if(symboltest[i]=="Iris-virginica")
    	symtest[i]=2;
	}
}


int main()
{	cout<<fixed<<setprecision(3);
	srand(time(NULL));
	cout<<"ŷ�Ͼ���/"; 
      KNN k;
      cout<<"�����پ���/"; 
      distance1 k1;

      
	 for(int count=0;count<30;count++)
      {
      	
      	int p;
		  p=rand()%30+120;
      	k.testset[0]=k.dataSet[p][0];
      	k.testset[1]=k.dataSet[p][1];
      	k.testset[2]=k.dataSet[p][2];
      	k.testset[3]=k.dataSet[p][3];
      	
      	k.testData[count][0]=k.dataSet[p][0];
      	k.testData[count][1]=k.dataSet[p][1];
      	k.testData[count][2]=k.dataSet[p][2];
      	k.testData[count][3]=k.dataSet[p][3];
      	
      	k1.testset[0]=k1.dataSet[p][0];
      	k1.testset[1]=k1.dataSet[p][1];
      	k1.testset[2]=k1.dataSet[p][2];
      	k1.testset[3]=k1.dataSet[p][3];
      	
      	k1.testData[count][0]=k1.dataSet[p][0];
      	k1.testData[count][1]=k1.dataSet[p][1];
      	k1.testData[count][2]=k1.dataSet[p][2];
      	k1.testData[count][3]=k1.dataSet[p][3];
      	
      	k.symbolreal[count]=k.symbol[p];
      	k1.symbolreal[count]=k1.symbol[p];
      	
      	k1.save_distance();
      	
      	k1.calculate_maxtimes();
      	k1.conclude();
		k1.symboltest[count]=k1.test;

      	
      	k.save_distance();
      	k.calculate_maxtimes();
      	k.conclude();
		k.symboltest[count]=k.test; 
		
		k.map_label_freq["Iris-setosa"]=0;
		k.map_label_freq["Iris-versicolor"]=0;
		k.map_label_freq["Iris-virginica"]=0;
		
		k1.map_label_freq["Iris-setosa"]=0;
		k1.map_label_freq["Iris-versicolor"]=0;
		k1.map_label_freq["Iris-virginica"]=0;
		
	  }
		k1.reform();
		k.reform();
	    k1.calculate_errornum(); 
	    k.calculate_errornum();
	  	k.out();
		k.outreal();
		k1.out();
		

      
    return 0; 
}
