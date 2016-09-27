#include<iostream>
#include<fstream>
#include<utility>
#include<string>
#include<map>
#include<set>
#include<vector> 
#include<algorithm>
#include<iterator>
using namespace std;

//flight.txt ��λ 
set<int> guojiset;
set<int> guoneiset;
map<char,set<int> > taskmap;//����-����λ 
map<string,set<int> > companymap;//��˾-����λ 
map<string,set<int> > typemap;//�ɻ�����-����λ 
map<int,bool> yuanjinmap;//false yuan����λ-��Զ�� 
map<int,string> huadaomap;//��λ-������
map<string,set<int> > huadaoset;//����-����λ 


class mytime{
	public:
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		mytime()
		{
			year=0;
			month=0;
			day=0;
			hour=0;
			minute=0;
			second=0;
		}
		mytime(string s)
		{
			int size=0;
			char*p=new char[50];
			//year
			int yearend = 3;
			for(int i=0;i<s.length();i++)
			    p[i]=s[i];
			year=helper(p,0,yearend);
			//month
			int monthend = yearend+3;
			if(s[monthend]=='-')
			    monthend--;
			month = helper(p,yearend+2,monthend);
			//day
			int dayend = monthend + 3;
			if(s[dayend]=='-')
			    dayend--;
			day = helper(p,monthend + 2,dayend);
			//hour
			int hourend = dayend + 3;
			if(s[hourend]==':')
			    hourend--;
			hour = helper(p,dayend+2,hourend);
			//minute
			int minend = hourend +3;
			if(s[minend]==':')
			    minend--;
			minute = helper(p,hourend+2,minend);
			
			second = helper(p,minend+2,s.length()-1);
			
			
			delete p;
		}
		
		int helper(char *p,int start,int end)//�����ַ������죬תһ���Ӵ�Ϊ���� 
		{
			int tmp=1;
			int re=0;
			for(int i=end;i>=start;i--)
			{
				re+=(p[i]-'0')*tmp;
				tmp*=10;
			}
			return re;
		}
		
		bool operator < (const mytime mt)
		{
			if(year > mt.year) return false;
			else if(year < mt.year) return true;
			else{
				if(month > mt.month) return false;
		 	    else if(month < mt.month) return true;
		    	else{
				    if(day > mt.day) return false;
		 	        else if(day < mt.day) return true;
		    	    else{
				        if(hour > mt.hour) return false;
		 	            else if(hour < mt.hour) return true;
		    	        else{
				            if(minute > mt.minute) return false;
		 	                else if(minute < mt.minute) return true;
		    	            else{
				                if(second > mt.second) return false;
		 	                    else if(second < mt.second) return true;
		    	                else{
				                    return false;
			                    } 
			                } 
			            } 
			        } 
			    } 
			} 
		}
		
		bool operator == (const mytime mt)
		{
			if(year==mt.year&&month==mt.month&&day==mt.day&&hour==mt.hour&&minute==mt.minute&&second==mt.second)
			    return true;
			return false;
		}
		
		bool operator > (const mytime mt)
		{
			if (*this <mt || *this ==mt)
			    return false;
			return true;
		}
		
		bool operator >= (const mytime mt)
		{
			if(*this < mt)
			    return false;
			return true;
		}
		
		bool operator <=(const mytime mt)
		{
			if(*this > mt)
			    return false;
			return true;
		}
		
		mytime operator + (const int min)//�ӷ��ӣ�δ�����·ݽ�λ 
		{
			mytime re=mytime();
			re.day=day;re.year=year;re.month=month;
			re.hour=hour;re.minute=minute;re.second=second;
			re.minute+=min;
			if(re.minute>=60)
			{
				re.minute-=60;
				re.hour+=1;
				if(re.hour>=24)
				{
					re.hour -=24;
					re.day +=1;
				}
			}
			return re; 
		}
		
		
};

//flight1.txt ���� �ĸ������� 
map<int,string> mapcompany;//����-����˾ 
map<int,bool> mapguoji;//guoji true ����-�����ʹ��� 
map<int,char> maptask;//����-������ 
map<int,string> maptype;//����-������ 
map<int,int> mappeople;//����-������ 
map<int,mytime> mapin;//����ʱ�� 
map<int,mytime> mapout;//�뿪ʱ�� 
vector<int> flightNO;//������˳�򱣴�ĺ���� 


vector<int> solution;
double obj(vector<int> s)//Ŀ�꺯�� 
{
	int total=s.size();
	int allocated=0;
	int near = 0;
	int collision = 0;
	
	map<string,vector<mytime> >huadaotime;
	
	for(int i=0;i<s.size();i++)
	{
		if(s[i]==0)//δ�������� 
		    continue;
		allocated++;//������+1 
		if(yuanjinmap[s[i]])
		    near++;//����λ��+1 
		string huadao = huadaomap[s[i]];//��λ�Ļ��� 
		if(huadaotime.find(huadao)==huadaotime.end())//�״���ӵ�����ʱ��� 
		    huadaotime.insert(pair<string,vector<mytime> >(huadao,vector<mytime>()));
		bool find = false;
		for(int j=0;j<huadaotime[huadao].size();j++)//���һ���ʱ����Ƿ��ͻ 
		{
			if((huadaotime[huadao][j]+5) >= mapin[flightNO[i]] && huadaotime[huadao][j] <= (mapin[flightNO[i]] +5))//time-5<=mapin<=time+5,��time+5>=mapin,time<=mapin+5 
	        {
	        	find=true;break;
			}
			if((huadaotime[huadao][j]+5) >= mapout[flightNO[i]] && huadaotime[huadao][j] <= (mapout[flightNO[i]] +5))//time-5<=mapout<=time+5��ͬ�� 
	        {
	        	find=true;break;
			}
		}
		if(find)
		    collision++;
		huadaotime[huadao].push_back(mapin[flightNO[i]]);
		huadaotime[huadao].push_back(mapout[flightNO[i]]);
	}
	return 3.0*allocated / total + 2.0*near / total + 1.0*(1- collision / (double)total) ;
}

set<int> operator < (const set<int> s1,const set<int> s2)
{
	set<int> re;
	set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(re,re.begin()));
	return re;
 } 
set<int> operator > (const set<int> s1,const set<int> s2)
{
	set<int> re;
	set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(re,re.begin()));
	return re;
 } 
 set<int> operator - (const set<int> s1,const set<int> s2)
{
	set<int> re;
	set_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(re,re.begin()));
	return re;
 } 

struct GatePositionInfo
{
	bool empty;
	mytime leaving_time;
};

vector<int> checkSolution(vector<int> s)
{
	map<string,GatePositionInfo > positionInfo;
	vector<int> re;
	for(int i=0;i<s.size();i++)
	{
		int flight = flightNO[i];
		int gate = s[i];
		string company = mapcompany[flight];
		mytime in = mapin[flight];
		mytime out = mapout[flight];
		bool guoji = mapguoji[flight];
		char task = maptask[flight];
		string type = maptype[flight];
		set<int> candidate;
		if(guoji)
		{
			candidate = companymap[company] < guojiset < taskmap[task] < typemap[type];
		}
	}
	
}

int main()
{
	ifstream fin("flight.txt");
	char* p = new char[100];
	fin.getline(p,100);
	int count=0;
	string lasthuadao;
	while(!fin.eof())//��flight.txt 
	{
		if(count >10)break;//���Կ��ƴ����ã�ע����ѭ��β��ע�� 
		int gate;
	    string guoji;
	    string yuanjin;
	    string huadao;
	    string task;
	    string company;
	    string type;
	    fin>>gate;
	    fin>>guoji;
	    if(guoji == "����")
	        guojiset.insert(gate);
	    else if (guoji == "����")
	    guoneiset.insert(gate);
	    else
	    {
	    	guojiset.insert(gate);
	    	guoneiset.insert(gate);
		}
	    fin>>yuanjin;
	    if(yuanjin=="Զ��λ")
	    yuanjinmap.insert(pair<int,bool>(gate,false));
	    else
	    yuanjinmap.insert(pair<int,bool>(gate,true));
	    //���봦���� 
	    char c;int cnt=0;
	    char *cc = new char[50];
	    int index=0;
	    
	    while(fin.get(c))
	    {
	    	
	    	if(c == '\t')
	    	{
	    		if(cnt==1)
	    		break;
	    		cnt++;
			}
			else
	    	{
	    		cc[index]=c;
	    		index++;
	    	}
		}
		cc[index]=0;
		huadao=string(cc);
	    if(huadao.length()>0)
	    {
	    	lasthuadao =huadao;
		}
		else
		{
			huadao = lasthuadao;
		}
		delete cc;
		huadaomap.insert(pair<int,string>(gate,huadao));
		if(huadaoset.find(huadao)==huadaoset.end())
		    huadaoset.insert(pair<string,set<int> >(huadao,set<int>()));
		huadaoset[huadao].insert(gate);
		
		
	    fin>>task>>company>>type;
	    //��������
		for(int i=0;i<task.length();i++)
		{
			if(task[i]=='"'|| task[i]==',')
			continue;
			if(taskmap.find(task[i])==taskmap.end())
			taskmap.insert(pair<char,set<int> >(task[i],set<int>()));
			taskmap[task[i]].insert(gate);
		}
		 //����˾
		 string name;
		 cnt=0;
		 for(int i=0;i<company.length();i++)
		{
			if(company[i]=='"')
			{
				if(cnt==1)
				{
					if(companymap.find(name)==companymap.end())
			            companymap.insert(pair<string,set<int> >(name,set<int>()));
			        companymap[name].insert(gate);
			        name="";
				}
				cnt++;
				continue; 
			}
			if(company[i]==',')
			{
				if(companymap.find(name)==companymap.end())
			        companymap.insert(pair<string,set<int> >(name,set<int>()));
			    companymap[name].insert(gate);
			    name="";
			 } 
			 else
			name+=company[i];
		}
		
		//�������
		  cnt=0;
		 for(int i=0;i<type.length();i++)
		{
			if(type[i]=='"')
			{
				if(cnt==1)
				{
					if(typemap.find(name)==typemap.end())
			            typemap.insert(pair<string,set<int> >(name,set<int>()));
			        typemap[name].insert(gate);
			        name="";
				}
				cnt++;
				continue; 
			}
			if(type[i]==',')
			{
				if(typemap.find(name)==typemap.end())
			        typemap.insert(pair<string,set<int> >(name,set<int>()));
			    typemap[name].insert(gate);
			    name="";
			 } 
			 else
			name+=type[i];
		}

	   // count++;

	}
	fin.close();
	fin.open("flight1.txt");
	fin.getline(p,100);
	count=0;
	while(!fin.eof())//��flight1.txt 
	{
		if(count>10)break;//���Կ��ƴ����ã�ע����ѭ��β��ע�� 
		string company,in,intime,out,outtime,guoji,type;
		char task;
		int flight,people;
		
		fin>>company>>flight>>in>>intime>>out>>outtime>>guoji>>task>>type>>people;
		flightNO.push_back(flight); 
		mapcompany.insert(pair<int,string>(flight,company));
		mapin.insert(pair<int,mytime>(flight,mytime(in+' '+intime)));
		mapout.insert(pair<int,mytime>(flight,mytime(out+' '+outtime)));
		if(guoji=="����")
		mapguoji.insert(pair<int,bool>(flight,true));
		else
		mapguoji.insert(pair<int,bool>(flight,false));
		
		maptask.insert(pair<int,char>(flight,task));
		maptype.insert(pair<int,string>(flight,type));
		mappeople.insert(pair<int,int>(flight,people));
	//	count++;
	}
	/*
	set<int> a,b,c,d;
	a.insert(5);a.insert(6);a.insert(7);
	b.insert(5);b.insert(8);
	d.insert(9);
	c = a>b>d; 
	copy(c.begin(), c.end(), ostream_iterator <int> (cout, " "));  */
		
	
    mytime leaving_time[713];//when the airplane is leaving.
	
	//initialise leaving_time
	for(int i=0; i< 714; i++)
	{
        leaving_time.day = 0;
        leaving_time.hour = 0;
        leaving_time.minute = 0;
        leaving_time.month = 0;
        leaving_time.second = 0;
        leaving_time.year = 0;
	}
	
	
	//liminglong, TODO: use greedy algorithm to calculate the result of the "obj" function.
    for(int flight_index = 1001; flight_index < 1700; flight_index++)//The flight number is from 1011 to 1699.
    {
    	for(int position_index = 101; position_index < 713; position_index++)//The gate position number of the airport is from 101 to 712.
    	{
		    if(  ( (leaving_time[position_index]+8) < mapin[flight_index] )
	           &&( == maptype[flight_index])		  
			  )
			{
				leaving_time[position_index] = mapout[flight_index]//use a new leaving time of this flight to update the leaving_time
			}
		      
		}
	}
	
 } 
