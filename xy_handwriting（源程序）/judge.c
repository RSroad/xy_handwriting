#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "external_call.h"

/*判断几个笔画是否为一个汉字的标志*/
int m_FLAG = 0;

char chinese_result[M_ROW][M_COL];

/*
	更改日期: 1st 2011.11.2
			  2nd 2011.11.3
			  3th 2011.11.8
			  4th 2011.11.21
			  5th 2011.11.24
 */


int Judge(Coor data[], int index)
{
        /*X与Y数据流返回的方程代码*/
        int X_stream = 0;
        int Y_stream = 0;
        int sharp_1 = 0; 	//笔画的主形
		int sharp_2 = -1;	//笔画的次形
		double k_x = 0.0;
		double k_y = 0.0;
		double x_aver = 0.0;
		double y_aver = 0.0;
		int *x_array = NULL;
		int *y_array = NULL;
		int i = 0;
       
		
		/*只有一个点，则不对此次输入进行判断*/
		if (2 > index)
		{
			return FALSE_;
		}

        Pretreatment(data, &index);
		
		/*申请两个index*int 大小的数组，分别用来保存Coor数组中的x和y*/
		if (!(x_array = (int *)malloc(index * sizeof(int))))
		{
			return FALSE_;
		}
		if (!(y_array = (int *)malloc(index * sizeof(int))))
		{
			return FALSE_;
		}

		/*将Coor data[]中的x,y,解析成两个数组*/
		for (i = 0; i < index; i++)
		{
			x_array[i] = data[i].x;
			y_array[i] = data[i].y;
		}
		
		fit( x_array, index, &k_x, &x_aver);
		fit( y_array, index, &k_y, &y_aver);	

        slope(k_x, &X_stream);
		slope(k_y, &Y_stream);
		

        sharp_1 = OtherJudge(data, index);


        if (OTHER == sharp_1)
        {
				/*对于"其它"笔画的模糊*/
                sharp_2 = Dim(k_x, k_y, x_aver, y_aver, X_stream, Y_stream, index, sharp_1);
				
                Seek(sharp_1, sharp_2);
                return TRUE_;
        }
		
        else
        {
                sharp_1 = SharpJudge(X_stream, Y_stream, index);
                sharp_2 = Dim(k_x, k_y, x_aver, y_aver, X_stream, Y_stream, index, sharp_1);
                
                Seek(sharp_1, sharp_2);
        }


        return TRUE_;
}



/*坐标值预处理*/
int Pretreatment(Coor data[], int *index)
{
        int i = 0;

        /*将Y坐标转置*/
        for (i = 0; i < *index; i++)
        {
                data[i].y = OVER - data[i].y;
        }

        /*去噪处理*/
        Denoising(data, index);

        return TRUE_;
}



/*去噪*/
int Denoising(Coor Data[MAXSIZE], int *index)
{
	int i, j;
	for(i = 1 ; i < (*index) ; i++){
		if(i + 1 > (*index)){
			if(Data[i - 1].x == Data[i].x){
				for(j = i ; j < (*index) ; j++){
					Data[j - 1] = Data[j];
				}
				(*index)--;
			continue;
			}
		}
		if(Data[i - 1].x == Data[i].x && Data[i - 1].x != Data[i + 1].x){
			for(j = i ; j < (*index) ; j++){
				Data[j - 1] = Data[j];
			}
			(*index)--;
		}
	}
	for(i = 1 ; i < (*index) ; i++){
		if(i + 1 > (*index)){
			if(Data[i - 1].x == Data[i].x){
				for(j = i ; j < (*index) ; j++){
					Data[j - 1] = Data[j];
				}
				(*index)--;
			continue;
			}			
		}
		if(Data[i - 1].y == Data[i].y && Data[i - 1].y != Data[i + 1].y){
			for(j = i ; j < (*index) ; j++){
				Data[j - 1] = Data[j];
			}
			(*index)--;
		}
	}
	i = 0;

	return 0;
}


/*先进行其它笔画的判断*/
int OtherJudge(Coor data[], int index)
{
        int i = 0;
        int j = 0;
        /*tag_ 用来判断X or Y 数据流是否在不同的n值下拥有相同的值*/
        int tag_y = 0;
        int tag_x = 0;
        int n_flag_x = 0; /*记录出现重复点数的次数*/
        int n_flag_y = 0;



        for (i = 0; i < index; i++)
        {
		 		for (j = 0; j < index; j++)
				{
                        /*若果X数据流中对于不同的n值有相同的X值，则跳出循环*/
                       if ( (data[i].x == data[j].x) && (i != j)) 
                       {
                               n_flag_x++;
                       }
                       if (2 < n_flag_x)
                       {
                       		 tag_x = 1;
                         	 break;
                       }
                }
        }

        for (i = 0; i < index; i++)
        {
			for (j = 0; j < index; j++)
			{
                        /*若果Y数据流中对于不同的n值有相同的Y值，则跳出循环*/
                        if ( (data[i].y == data[j].y) && (i != j) )
						{
                            n_flag_y++;
                        }
                       if (2 < n_flag_y)
                       {
                            tag_y = 1;
                          break;
                      }
                }
        }

        /*当X和Y的数据流同时满足为其他结构返回真*/
        if ( (1 == tag_x) && (1 == tag_y) )
        {
                return OTHER;
        }
        else 
        {
                return FALSE_;
        }
}


/*笔画模糊*/
int Dim(double k_x, double k_y, double x_aver, double y_aver, int X_stream, int Y_stream, int index, int sharp_1)
{
	
	int sharp_2 = -1;
		
		/*sharp_1为“其它”笔画时 且 X,Y的数据流的斜率判断为撇时，将PIE的值返回给sharp_2*/
		if (OTHER == sharp_1)
		{
			/*求方差，判断*/
			if ( (3 == X_stream) && (3 == Y_stream))
			{
				sharp_2 = PIE;	
			}
			if ( (2 == X_stream) && (3 == Y_stream) )
			{
				sharp_2 = NA;
			}
		}
       // else   /*点模糊成竖，丿拟合成竖， 捺拟合成竖, 丿模糊成点*/
		//{
		else if ( (DIAN == sharp_1) && (8 > index) && (2 <= index) )	
		{
			sharp_2 = DianDim(X_stream, Y_stream);	
		}
		else if (PIE == sharp_1)
		{
			if ( (-2.0 < k_x) && (2.0 > k_x))
			{
				sharp_2 = 5;
			}
			else
			{
				sharp_2 = SHU;
			}
			if ( (10.0 <= x_aver) || (10.0 <= y_aver))
			{
				sharp_2 = 5;
			}
		}
		else if (NA == sharp_1)
		{	
			if ( (-2.0 < k_y) && (2.0 > k_y) )
			{
				sharp_2 = 5;
			}
			else
			{
				sharp_2 = SHU;
			}

			if ( (10.0 <= x_aver)|| (10.0 <= y_aver) )
			{
				sharp_2 = 5;
			}
		}
		else if (SHU == sharp_1)
		{
			if ( (10.0 <= x_aver) || (10.0 <= y_aver) )
			{
				sharp_2 = 5;
			}
		}
	        
		return sharp_2;
}



/*直线拟合*/
void fit(int *array, int index, double *k, double *aver)
{
        int i = 0;
        double d_xy = 0.0;
        double d_xx = 0.0;
        double s_xy = 0.0;
        int s_x = 0;
        int s_y = 0;
        double s_xx = 0.0;
		double b = 0.0;
		double deviation = 0.0;	//偏差
		
		*aver = 0.0;

        for (i = 1; i <= index; i++)
        {
                s_xy += i*array[i-1];
                s_x += i;
                s_y += array[i-1];
                s_xx += i*i;
        }
        d_xy = index*s_xy - s_x*s_y;
        d_xx = index*s_xx - s_x*s_x;
        *k = d_xy / d_xx;
		b = (s_y/index) - (*k)*(s_x/index);


		for (i = 0; i < index; i++)
		{
			deviation = fabs(array[i] - ((*k)*(i+1)+b));
			*aver += deviation/index;
		}


}



/*分析X和Y的数据流的斜率，得出其特征*/
int slope(double k, int *stream_k)
{
        if (k >= TAN315 && k <= TAN45)
        {
			*stream_k = 1;
        }
        else if (k > TAN45)
        {
        	*stream_k = 2;
        }
        else //(k < TAN315)
        {
           *stream_k = 3;
        }


        return TRUE_;
}



/*笔画判断*/
int SharpJudge(int X_stream, int Y_stream, int index)
{
        int sharp = 0;
 
		/*返回的点坐标数小于8个则判断为点*/
        if (8 > index)
        {
            sharp =  DIAN;
			return sharp;
        }

        if ( (2 == X_stream) && ( (1 == Y_stream) || 2 == Y_stream) )
        {
                sharp = HENG;
        }
        else if ( (1 == X_stream) && (3 == Y_stream) )
        {
                sharp = SHU;
        }
        else if ( (3 == X_stream) && ((3 == Y_stream) || (1 == Y_stream) ) )
		{
                sharp = PIE;
        }
        else if ( ((2 == X_stream) && (3 == Y_stream)) || ((1 == X_stream) && (1 == Y_stream)) )
        {
                sharp = NA;
        }
        else
        {
                sharp = OTHER;
        }
        return sharp;
}


/*对于点的模糊判断*/
int DianDim(int X_stream, int Y_stream)
{
	int sharp_2 = -1;

	if ( (1 == X_stream ) && (3 == Y_stream) )
	{
		sharp_2 = SHU;
	}
	else if ( (3 == X_stream) && (3 == Y_stream) )
	{
		sharp_2 = PIE;
	}
	else if ( (2 == X_stream) && ((1 == Y_stream) || (2 == Y_stream)) )
	{
		sharp_2 = HENG;
	}
	
	return sharp_2;
}

int Seek(int Sharp_1, int Sharp_2)
{

        FILE *f;
        static int sum = 0;
        static char important[50];
        static l_other *head;
        l_other *p, *q;
        char word[10];
        int i = 0;
        int flag = 0;
        int choose_str = 0; //判断主串是否被改变
        char n[50] = {0};
        if(sum == 0){
            head = (l_other *)malloc(sizeof(l_other));
            head->next = NULL;
        }
        if(1 == m_FLAG){
            sum = 0;
            m_FLAG = 0;
            free_str(head);
        }
        Lock_other(head, Sharp_1, Sharp_2, sum, important);
        f = fopen("归总汉字", "r");
        if(f == NULL){
            printf("can not open the file!\n");
            return -1;
        }
        important[sum] = Sharp_1 + 48;
        important[sum + 1] = '\0';
        while(!feof(f)){
            fscanf(f, "%s%s", n, word);
            n[sum + 1] = '\0';
            if(strcmp(n, important) == 0){
                break;
            }
        }

        p = head->next;
        while(p != NULL){
            //printf("%s\n", p->other);
            p = p->next;
        }

        if(feof(f)){                            //主串的判断

            p = head->next;
            while(p != NULL){
                rewind(f);
                if(!feof(f)){                        //主串的转换
                    if(!str_empty(head) || ((not_str(head->next->other, sum) == 1) && (head->next->next == NULL))){
                        return -2;
                    }
                    strcpy(important, p->other);
                    head->next = p->next;
                    free(p);
                    while(!feof(f)){
                        fscanf(f, "%s%s", n, word);
                        n[sum + 1] = '\0';
                        if(strcmp(n, important) == 0){
                            choose_str = 1;
                            break;
                        }
                    }
                }
                if(feof(f)){
                    p = p->next;
                    continue;
                }
                if(choose_str == 1){
                    choose_str = 0;
                    break;
                }
            }
        }

        memset(chinese_result, 0, sizeof(chinese_result));
        for( ; i < 4 ; i++){               //输出主串结果
            if(flag == 0){
                strcpy(chinese_result[i], word);
                flag = 1;
            }else{
            fscanf(f, "%s%s", n, chinese_result[i]);
        }
        }

        p = head->next;
        q = head;
        while(p != NULL && i < 8){              //输出其他的模糊结果的结果
            rewind(f);
            while(!feof(f)){
                fscanf(f, "%s%s", n, word);
                n[sum + 1] = '\0';
                if(strcmp(n, p->other) == 0){
                    strcpy(chinese_result[i], word);
                    fscanf(f, "%s%s", n, word);
                    n[sum + 1] = '\0';
                    i++;
                    strcpy(chinese_result[i], word);
                    break;
                }
            }
            if(feof(f)){
                if(p->next == NULL){
                    break;
                }
                q->next = p->next;
                p = q->next;
                continue;
            }
            i++;
            p = p->next;
            q = q->next;
        }
        str_mohu(important, sum, i);
        bugchange();
        sum++;

        fclose(f);
        return 0;
}

int Lock_other(l_other *head, int Sharp_1, int Sharp_2, int sum, char n[50])//其他变量的测试
{
    l_other *p, *q;
    p = head;
    if(str_empty(head) == 0){
        strcpy(head->other, n);
        head->other[sum] = Sharp_1 + 48;
        if(Sharp_2 != -1){
            q = (l_other *)malloc(sizeof(l_other));
            strcpy(q->other, n);
            q->other[sum] = Sharp_2 + 48;
            q->other[sum + 1] = '\0';
            q->next = p->next;
            p->next = q;
        }
    }else{
        if(Sharp_2 == -1){
            while(p!= NULL){
                p->other[sum] = Sharp_1 + 48;
                p->other[sum + 1] = '\0';
                p = p->next;
            }
        }else{
            while(p != NULL){
                q = (l_other *)malloc(sizeof(l_other));
                strcpy(q->other, p->other);
                q->next = p->next;
                p->next = q;
                p = q->next;
            }
            p = head;
            while(p != NULL){
                p->other[sum] = Sharp_1 + 48;
                p->other[sum + 1] = '\0';
                p = p->next;
                p->other[sum] = Sharp_2 + 48;
                p->other[sum + 1] = '\0';
                p = p->next;
            }
        }
    }
    p = head;
    return 0;
}

int str_empty(l_other *head)        //结构体判空操作
{
    l_other *p;
    int leap = 0;
    p = head->next;
    while(p != NULL){
        leap++;
        p = p->next;
    }
    return leap;
}

int free_str(l_other *head)         //结构体释放函数
{
    l_other *p, *q;
    p = head->next;
    if(p == NULL){
        return -1;
    }
    q = head->next->next;
    while(q != NULL){
        free(p);
        p = q;
        q = q->next;
    }
    head->next = NULL;
    return 0;
}

//判断此字符串在文件中是否存在
int not_str(char *str, int sum)
{
    FILE *f;
    char pipei[50];
    char a[10];
    f = fopen("归总汉字", "r");
    while(!feof(f)){
        fscanf(f, "%s%s", pipei, a);
        pipei[sum + 1] = '\0';
        if(strcmp(pipei, str) == 0){
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

int str_mohu(char important[], int sum, int i)
{
    FILE *f;
    char str[10];
    char im[50];
    int num;
    int j = 0;
    int other = 0;
    important[sum + 1] = '\0';
    f = fopen("笔画排序", "r");
    while(!feof(f)){
        fscanf(f, "%d%s%s", &num, im, str);
        if((num - 1)== sum){
            break;
        }
    }
    if(feof(f)){
        printf("没有符合条件的！\n");
        return -1;
    }
    while(!feof(f)){
        j = 0;
        while(j < sum + 1){
            if(im[j] != important[j]){
                other++;
            }
            j++;
        }
        if(i == 16){
            break;
        }
        if(other == 1){
            strcpy(chinese_result[i], str);
            i++;
        }
        if(sum + 1 >= 4 && other == 2){
            strcpy(chinese_result[i], str);
            i++;
        }
        if(sum >= 7 && other == 3 ){
            strcpy(chinese_result[i], str);
            i++;
        }
        other = 0;
        fscanf(f, "%d%s%s", &num, im, str);
        if((num - 1) != sum){
            break;
        }
    }
    return 0;
}

int bugchange()
{
    int i;
    int j;
    int k;
    if(strcmp(chinese_result[0], "廵") == 0){
        for(i = 0 ; i < 12 ; i++){
            strcpy(chinese_result[i], chinese_result[i + 4]);
        }
    }
    for(i = 0 ; i < 15 ; i++){
        for(j = i + 1 ; j < 16 ; j++){
            if(strcmp(chinese_result[i], chinese_result[j]) == 0){
                for(k = j ; k < 15 ; k++){
                    strcpy(chinese_result[k], chinese_result[k + 1]);
                }
				strcpy(chinese_result[15], " ");
            }
        }
    }
    return 0;
}

