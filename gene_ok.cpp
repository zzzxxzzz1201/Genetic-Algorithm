#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define PI 3.14
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#define  route  20 
#include <float.h>
struct node
{
	int data;
	struct node *next;
};
	typedef struct node NODE;
	typedef struct a element;
int totaldatanumber;
struct a
	{
		int x;
		int y;
	};
typedef struct a element;
void shuffle(int[] ,int);
void swap(int[],int,int );
double finddistance(int[],element[]);
void writedata(int a,int b);
element* readdata(); 
struct d
	{
		int order[51];    //無法改變大小 
		double path;
	};
	typedef struct d listorder;
	listorder route_20[route];      //20筆路徑 
void initialroute(listorder  route_20[],element data[] ,int *max_index,double *max_dis,int *min_index,double *min_dis);
void delete_max_distance(listorder  route_20[],int crossover[],int *index,double *dis,double changedis);
NODE* createList(int *arr,int len);
int checkrepete(int a,NODE *b);
void crossover(listorder route_20[],listorder []);     //listirder回傳可否是陣列? 
void mutation(listorder route_crossover[]);
void evalution(listorder route_evalution[],listorder route_20[],element data[],int *max_index,double *max_dis,int *min_index,double *min_dis,int *findtime,double start_time);
int main(void)
{
	
	
double start_time;
	double end_time;
	double totalpath;
	int findtime = 0,pick1,pick2;
	double distance;
	double replace_dis;
	double smallest_dis;
	double ice = 1;
	double lava = 10;
	double rate = 0.00001; 
	int i,change,j;
	int order[totaldatanumber];
	int innerfindtime,innerdistance,sel_distance;
	int minpick1,minpick2;
	int keep_biggest_path_index; 
	double keep_biggest_paht_distance;
	int keep_smallest_path_index; 
	double keep_smallest_paht_distance;
	listorder crossoverdata[route];
	element *data;
	int writedistance;
	FILE *out,*out2;
	out = fopen("outtime.txt","w");  //清空資料區 
	fclose(out);
	out2 = fopen("outpath.txt","w");
	fclose(out2);
	data = readdata();

	srand(time(NULL));
	start_time = clock();
	
	initialroute(route_20,data,&keep_biggest_path_index,&keep_biggest_paht_distance,&keep_smallest_path_index,&keep_smallest_paht_distance);
	end_time = clock();
	printf("目前找的次數是:%d ,最短距離是:%f ,找到時間是:%f \n",keep_smallest_path_index+1, keep_smallest_paht_distance,(double)(end_time - start_time)/1000);
	findtime = 20;
	
	
	printf("最初找的最短路徑%f\n",keep_biggest_paht_distance);
	while(findtime<=1000000)
	{ 
      crossover(route_20,crossoverdata);
/*	j=0;
while(j<20) 
	{
		for(i = 0;i<51;i++)
		{
			if(i == 50)
			printf("%d\n",crossoverdata[j].order[i]);
			else
			printf("%d->",crossoverdata[j].order[i]);
		}
		j++;
	}*/
	mutation(crossoverdata);
	evalution(crossoverdata,route_20,data,&keep_biggest_path_index,&keep_biggest_paht_distance,&keep_smallest_path_index,&keep_smallest_paht_distance,&findtime,start_time);
	}
	printf("最短距離是:");
	for(j = 0;j<totaldatanumber;j++)
	{
		if(j == 50)
			printf("%d\n",route_20[keep_smallest_path_index].order[j]);
			else
			printf("%d->",crossoverdata[keep_smallest_path_index].order[j]);
	}
system("pause");
return 0;
}
void shuffle(int a[],int totalnum)
{
	int i;
	int randnum;
	for(i = 0 ;i<totalnum;i++)
	{
		randnum = (int)(rand()%(i+1));
		swap(a,i,randnum);
	}
	
}

void swap(int a[],int b,int c)
{
	int temp;
	if(b == c)
	return;
	else
	{
		temp = a[b];
		a[b] = a[c];
		a[c] = temp;
		return;
	}
	
}

double finddistance(int order[],element data[])
{
	int i;
	double xdis;
	double ydis;
	double tempdis;
	double totaldis = 0;
	for(i = 0;i<totaldatanumber-1;i++)
	{
		xdis= data[order[i+1]].x - data[order[i]].x;
		ydis= data[order[i+1]].y - data[order[i]].y;
		tempdis = sqrt((pow(xdis,2)+pow(ydis,2)));
		totaldis += tempdis; 
	}
		xdis= data[order[0]].x - data[order[totaldatanumber-1]].x;   //頭到尾距離 
		ydis= data[order[0]].y - data[order[totaldatanumber-1]].y;
		tempdis = sqrt((pow(xdis,2)+pow(ydis,2)));
		totaldis += tempdis; 
		return (double)totaldis;
}

void writedata(int a,int b)
{
	
	char time[10] = {0},path[10] = {0},copy[10] = {0};
	FILE *ptr,*ptr2;
	int c;
	int bit;
	int i;
	int j ;
	ptr = fopen("outtime.txt","a");
	ptr2 = fopen("outpath.txt","a");
	bit = 0;
	do
	{
		c = a%10;
		copy[bit] = c+48;
		a = a/10; 
		if(a != 0 )
		bit++;
	}while(a!=0);
	j = 0;
	for(i = bit;i>=0;i--)
	{
	 time[j] = copy[i];
	j++;
	}
	bit = 0;
	copy[10] = {0};
	do
	{
		c = b%10;
		copy[bit] = c+48;
		b = b/10;
		if(b != 0 ) 
		bit++;
	}while(b!=0);
	j = 0;
	for(i = bit;i>=0;i--)
	{
	 path[j] = copy[i];
	j++;
	}
	fputs(time,ptr);
	putc('\n',ptr);
	fputs(path,ptr2);
	putc('\n',ptr2);
	printf("time:%s ,path:%s\n",time,path);
	fclose(ptr);
	fclose(ptr2);
	
}


element* readdata(void)
{
	int i = 0;
	char number[10] = {0},xais[10]= {0},yais[10]= {0},ch;
	int intnumber,intxais,intyais;
	FILE *input;
	element *data;
	input = fopen("inputdata.txt","r");
	data = (element *) malloc(1*sizeof(element));
	while(feof(input)==0)
	{
		i = 0;
		while((ch = getc(input))!=' ')
		{
			number[i] = ch;
			i++;
		}
		intnumber = atoi(number);
		data = (element *)realloc(data,sizeof(element)*intnumber) ;
		for(i = 0;i<10;i++)
		number[i] = 0; 
		i = 0;
		while((ch = getc(input))!=' ')
		{
			xais[i] = ch;
			i++;
		}
		intxais = atoi(xais);
	    (data+intnumber-1)->x = intxais; 
	    for(i = 0;i<10;i++)
		xais[i] = 0;
		i = 0;
		while((ch = getc(input))!='\n')
		{
			if(ch == EOF)   //不能漏   不然最後一行讀不進去 
			break;
			yais[i] = ch;
			i++;
		}
		intyais = atoi(yais);
	    (data+intnumber-1)->y = intyais; 
	    for(i = 0;i<10;i++)
		yais[i] = 0;
		i = 0;    
	    printf("%d ,%d ,%d\n",intnumber,(data+intnumber-1)->x,(data+intnumber-1)->y);
	}
	totaldatanumber = intnumber;
	fclose(input);
return data;
}
void initialroute(listorder  route_20[],element data[],int *max_index,double *max_dis,int *min_index,double *min_dis)
{
	int order[totaldatanumber];
	int i,j;
	double local_max_dis = 0;
	int local_max_index = 0;
	double local_min_dis = FLT_MAX;
	int local_min_index = 0;
	for(i = 0;i<totaldatanumber;i++)
		order[i] = i;
		
		for(i = 0;i<route;i++)
		{
			shuffle(order,totaldatanumber);
			for(j = 0;j<totaldatanumber;j++)
			{
				route_20[i].order[j] = order[j];               //設定最初路徑20條 
			}
			 route_20[i].path = finddistance(route_20[i].order,data);
		}
		for(i = 0;i<route;i++)
		{
			if(route_20[i].path>local_max_dis)
			{
			local_max_dis = route_20[i].path;
			local_max_index = i;
			}
			if(route_20[i].path<local_min_dis)
			{
			local_min_dis = route_20[i].path;
			local_min_index = i;	
			}
			if(i == 0)
			{
				writedata(0,route_20[0].path);
			}
		}
		
		*max_index = local_max_index ;
		*max_dis = local_max_dis;
		*min_index = local_min_index ;
		*min_dis = local_min_dis;
	
}

void delete_max_distance(listorder  route_20[],int crossover[],int *index,double *dis,double changedis)    //每次crossover有更好的解就替換 
{
	int i = 0;
	double max_dis = 0;
	int max_index = 0;
	for(i = 0;i<totaldatanumber;i++)
		route_20[*index].order[i] = crossover[i];      //把最大path的route換掉 
	route_20[*index].path = changedis;
	for(i = 0;i<route;i++)
		{
			if(route_20[i].path>max_dis)
			{
			max_dis = route_20[i].path;
			max_index = i;
			}
		}
	*index = max_index ;       //紀錄最大path的index 
		*dis = max_dis;			//紀錄最大path
}
void crossover(listorder route_20[],listorder crossover_data[])
{
	int pick1,pick2,i,j,temp,k;     
	NODE *trans1;
	NODE *trans2;
	NODE *trans3;
	int *begin1;
	int *begin2;
	int innercount = 0;
	int chromosomeorder[route];
	int pickchromosome1,pickchromosome2;
	
	for(i = 0;i<route;i++)
	 	chromosomeorder[i] = i;
	 	
	 	shuffle(chromosomeorder,route);
	 	
	/*j=0;
	while(j<20) 
	{
		for(i = 0;i<51;i++)
		{
			if(i == 50)
			printf("%d\n",route_20[j].order[i]);
			else
			printf("%d->",route_20[j].order[i]);
		}
		j++;
	}
	printf("------------------------------------\n");*/
	for(i = 0;i<route/2;i++)
	{
		do
			{
				pick1 = (int)rand()%totaldatanumber;      //crossover交換點
				pick2 = (int)rand()%totaldatanumber;
			}while(pick1 == pick2);
			
			if(pick1>pick2)
			{
			temp = pick1;
			pick1=  pick2;
			pick2 = temp;
			}
		
			
			if(pick1>pick2)
			{
			temp = pick1;
			pick1=  pick2;
			pick2 = temp;
			}
			
			pickchromosome1 = chromosomeorder[i*2];
			pickchromosome2 = chromosomeorder[i*2+1];
			begin1 = &route_20[pickchromosome1].order[pick1];
			begin2 = &route_20[pickchromosome2].order[pick1];
		for(j = pick1;j<=pick2;j++)                                                                  //固定值先記錄 
		{
			crossover_data[i*2].order[j] = route_20[pickchromosome1].order[j];
			crossover_data[i*2+1].order[j] = route_20[pickchromosome2].order[j];
		} 
		trans1 = createList(begin1,pick2-pick1+1);
		trans2 = createList(begin2,pick2-pick1+1);

		innercount = 0;
		for(k = 0;k<totaldatanumber;k++)     
		{
			if(checkrepete(route_20[pickchromosome2].order[(pick2+k+1)%totaldatanumber],trans1) == 1)
			continue;
			else
			{		
		    crossover_data[i*2].order[(pick2+1+innercount)%totaldatanumber] = route_20[pickchromosome2].order[(pick2+k+1)%totaldatanumber];  //(pick2+k+1)%totaldatanumber和pick2+1+innercount不一樣是因為含有包含不crossover的部分 
			innercount++;
			}
		}
		
	
		innercount = 0;
		for(k = 0;k<totaldatanumber;k++)     
		{
			if(checkrepete(route_20[pickchromosome1].order[(pick2+k+1)%totaldatanumber],trans2) == 1)
			continue;
			else
			{
	         crossover_data[i*2+1].order[(pick2+1+innercount)%totaldatanumber] = route_20[pickchromosome1].order[(pick2+k+1)%totaldatanumber] ;  //(pick2+k+1)%totaldatanumber和pick2+1+innercount不一樣是因為含有包含不crossover的部分 
			innercount++;
			}
		}
	}
	/*j=0;
	while(j<20) 
	{
		for(i = 0;i<51;i++)
		{
			if(i == 50)
			printf("%d\n",crossover_data[j].order[i]);
			else
			printf("%d->",crossover_data[j].order[i]);
		}
		j++;
	}
	printf("------------------------------------\n");*/
}



void mutation(listorder route_crossover[])
{
	int i;
	int mutationpick1,mutationpick2;
	for(i = 0;i<route;i++)              //做mutation 
	{
		if(rand()%10<5)
		{
			do
			{
				mutationpick1 = (int)rand()%totaldatanumber;      //mutation交換點
				mutationpick2 = (int)rand()%totaldatanumber;
			}while(mutationpick1 == mutationpick2);
			swap(route_crossover[i].order,mutationpick1,mutationpick2);    //可能會錯 
		}
	}
}

void evalution(listorder route_evalution[],listorder route_20[],element data[],int *max_index,double *max_dis,int *min_index,double *min_dis,int *findtime,double start_time)   //最後要傳runtime次數 
{
	int i,j;
	double end_time;
	double nowpath;
	for(i = 0;i<route;i++)
	{
		nowpath = finddistance(route_evalution[i].order,data);
		if(nowpath<*max_dis)
		{
			delete_max_distance(route_20,route_evalution[i].order,max_index,max_dis,nowpath);
			if(nowpath<*min_dis)
			{
				*min_index = i;
				*min_dis = nowpath;	
				end_time = clock();
				printf("目前找的次數是:%d ,最短距離是:%f ,找到時間是:%f \n",*findtime,*min_dis,(double)(end_time - start_time)/1000);
				/*printf("最短距離是:");
				for(j = 0;j<totaldatanumber;j++)
				{
					if(j == 50)
					printf("%d\n",route_20[*min_index].order[j]);
					else
					printf("%d->",route_20[*min_index].order[j]);
				}*/ 
			}	
		}
		*findtime = (*findtime)+1;
			if((*findtime)%20000 == 0)           //每找兩千次輸入一次資料 
 			{
			writedata(*findtime,nowpath);
			//printf("%d,%d\n",*findtime,nowpath); 
			}				
	} 
}

NODE* createList(int *arr,int len)
{
	
	int i;
	NODE *first,*current ,*previous;
	for(i = 0;i<len;i++)
	{
		current  = (NODE *) malloc(sizeof(NODE));
		current-> data = arr[i];
		if(i == 0)
		first = current;
		else 
		previous->next = current;
		current->next = NULL;
		previous = current;  
	}
	
	return first;
}

int checkrepete(int a,NODE *b)
{
	NODE *c;
	c = b;
	while(c != NULL)
	{
		if(c->data == a)
		return 1;                  //有重複傳回1; 
		else
		c =  c->next;
	}
	return 0;
}





