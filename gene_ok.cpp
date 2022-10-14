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
		int order[51];    //�L�k���ܤj�p 
		double path;
	};
	typedef struct d listorder;
	listorder route_20[route];      //20�����| 
void initialroute(listorder  route_20[],element data[] ,int *max_index,double *max_dis,int *min_index,double *min_dis);
void delete_max_distance(listorder  route_20[],int crossover[],int *index,double *dis,double changedis);
NODE* createList(int *arr,int len);
int checkrepete(int a,NODE *b);
void crossover(listorder route_20[],listorder []);     //listirder�^�ǥi�_�O�}�C? 
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
	out = fopen("outtime.txt","w");  //�M�Ÿ�ư� 
	fclose(out);
	out2 = fopen("outpath.txt","w");
	fclose(out2);
	data = readdata();

	srand(time(NULL));
	start_time = clock();
	
	initialroute(route_20,data,&keep_biggest_path_index,&keep_biggest_paht_distance,&keep_smallest_path_index,&keep_smallest_paht_distance);
	end_time = clock();
	printf("�ثe�䪺���ƬO:%d ,�̵u�Z���O:%f ,���ɶ��O:%f \n",keep_smallest_path_index+1, keep_smallest_paht_distance,(double)(end_time - start_time)/1000);
	findtime = 20;
	
	
	printf("�̪�䪺�̵u���|%f\n",keep_biggest_paht_distance);
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
	printf("�̵u�Z���O:");
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
		xdis= data[order[0]].x - data[order[totaldatanumber-1]].x;   //�Y����Z�� 
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
			if(ch == EOF)   //����|   ���M�̫�@��Ū���i�h 
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
				route_20[i].order[j] = order[j];               //�]�w�̪���|20�� 
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

void delete_max_distance(listorder  route_20[],int crossover[],int *index,double *dis,double changedis)    //�C��crossover����n���ѴN���� 
{
	int i = 0;
	double max_dis = 0;
	int max_index = 0;
	for(i = 0;i<totaldatanumber;i++)
		route_20[*index].order[i] = crossover[i];      //��̤jpath��route���� 
	route_20[*index].path = changedis;
	for(i = 0;i<route;i++)
		{
			if(route_20[i].path>max_dis)
			{
			max_dis = route_20[i].path;
			max_index = i;
			}
		}
	*index = max_index ;       //�����̤jpath��index 
		*dis = max_dis;			//�����̤jpath
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
				pick1 = (int)rand()%totaldatanumber;      //crossover�洫�I
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
		for(j = pick1;j<=pick2;j++)                                                                  //�T�w�ȥ��O�� 
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
		    crossover_data[i*2].order[(pick2+1+innercount)%totaldatanumber] = route_20[pickchromosome2].order[(pick2+k+1)%totaldatanumber];  //(pick2+k+1)%totaldatanumber�Mpick2+1+innercount���@�ˬO�]���t���]�t��crossover������ 
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
	         crossover_data[i*2+1].order[(pick2+1+innercount)%totaldatanumber] = route_20[pickchromosome1].order[(pick2+k+1)%totaldatanumber] ;  //(pick2+k+1)%totaldatanumber�Mpick2+1+innercount���@�ˬO�]���t���]�t��crossover������ 
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
	for(i = 0;i<route;i++)              //��mutation 
	{
		if(rand()%10<5)
		{
			do
			{
				mutationpick1 = (int)rand()%totaldatanumber;      //mutation�洫�I
				mutationpick2 = (int)rand()%totaldatanumber;
			}while(mutationpick1 == mutationpick2);
			swap(route_crossover[i].order,mutationpick1,mutationpick2);    //�i��|�� 
		}
	}
}

void evalution(listorder route_evalution[],listorder route_20[],element data[],int *max_index,double *max_dis,int *min_index,double *min_dis,int *findtime,double start_time)   //�̫�n��runtime���� 
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
				printf("�ثe�䪺���ƬO:%d ,�̵u�Z���O:%f ,���ɶ��O:%f \n",*findtime,*min_dis,(double)(end_time - start_time)/1000);
				/*printf("�̵u�Z���O:");
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
			if((*findtime)%20000 == 0)           //�C���d����J�@����� 
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
		return 1;                  //�����ƶǦ^1; 
		else
		c =  c->next;
	}
	return 0;
}





