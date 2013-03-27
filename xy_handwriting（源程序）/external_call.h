#ifndef EXTERNAL_CALL_H
#define EXTERNAL_CALL_H

#include "judge.h"

#ifdef __cplusplus
extern "C" {
#endif
  int Judge(Coor data[], int index);	/*笔画判断*/

    int Pretreatment(Coor data[], int *index);  /*预处理*/

    int Denoising(Coor data[], int *index);   /*去噪*/

//    int StreamProcess(Coor data[], int index, int *X_stream, int *Y_stream, double *k_x, double *k_y, double *max, double *min, double *aver);  /*数据流分析*/
	
	void fit(int *array, int index, double *k, double *aver);

    int SharpJudge(int X_stream, int Y_stream, int index);  /*笔型判断*/

    int OtherJudge(Coor data[], int index);   /*对于其他笔画的判断*/

    int Dim(double k_x, double k_y, double x_aver, double y_aver, int X_stream, int Y_stream, int index, int sharp_1);   /*笔画模糊*/

    int DianDim(int X_stream, int Y_stream);  /*点模糊判断*/

    int slope(double k, int *stream_k);   /*斜率的判断*/

    int Seek(int sharp_1, int sharp_2);  /*字库查找*/

    int Lock_other(l_other *head, int Sharp_1, int Sharp_2, int sum, char n[50]); /*字库模糊*/

    int str_empty(l_other *head);/*字符串判空函数*/

    int free_str(l_other *head); /*释放空间函数*/

    int str_mohu(char important[], int sum, int i);/*按字符模糊判断*/

    int not_str(char *str, int sum);//判断此字符串在文件中是否存在

    int bugchange();/*bug处理函数*/
#ifdef __cplusplus
}
#endif

#endif // EXTERNAL_CALL_H
