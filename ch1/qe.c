/**********************************************/
/*�@�@�@�@      qe.c�v���O����                */
/**********************************************/

/*�Öق̌^�ϊ��Ɋւ�����v���O�����@�@    �@*/
/*�Q�������������������g���ĉ����܂�          */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/

/*�֐��̃v���g�^�C�v�̐錾*/
int getdouble(double *x) ;/*�����̓ǂݍ��� */

int main()
{
 double a,b,c ; /*�Q���������̌W��*/
 double d ;/*���ʎ��̒l*/

 /*�W���̓���*/
 printf("�W��a����͂��Ă�������\n") ;
 if(getdouble(&a)==EOF) exit(1) ;
 if(a==0) exit(1) ;/*�Q���������ł͂Ȃ�*/
 printf("�W��b����͂��Ă�������\n") ;
 if(getdouble(&b)==EOF) exit(1) ;
 printf("�W��c����͂��Ă�������\n") ;
 if(getdouble(&c)==EOF) exit(1) ;

 /*���ʎ��̌v�Z*/
 d=b*b-4*a*c ;
 /*���̌����̌v�Z*/
 if(d==0)/*�d��*/
  printf("x=%lf\n",-b/2/a) ;
 else if(d<0)/*����*/
  printf("x=%lf+%lfi,%lf-%lfi\n",-b/2/a,sqrt(-d)/2/a,-b/2/a,sqrt(-d)/2/a) ;
 else /*����*/
  printf("x=%lf,%lf\n",-b/2/a+sqrt(d)/2/a,-b/2/a-sqrt(d)/2/a) ;

 return 0 ;
}

/*************************/
/*    getdouble()�֐�    */
/*    �����̓ǂݍ���     */
/*************************/
int getdouble(double *x)
{
 char linebuf[BUFSIZE] ; /*1�s���͗p�̕����z��*/
 int result=0 ;/*���͌��ʂ̃R�[�h*/

 if(fgets(linebuf,BUFSIZE,stdin)!=NULL){/*�s�̓ǂݎ�肪�\*/
  if(sscanf(linebuf,"%lf",x)<=0)/*�ϊ��ł��Ȃ����*/
    result=EOF ;/*�G���[*/
 } else {/*�s���ǂ߂Ȃ�*/
  result=EOF ;/*�t�@�C���̏I���*/
 }
 return result ;
}
