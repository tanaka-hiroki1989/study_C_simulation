/**********************************************/
/*�@�@�@�@   bignum.c�v���O����               */
/**********************************************/

/*���{�������̗��v���O����        �@�@    �@*/
/*�R�̗ݏ���v�Z���܂�                        */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 8 /*�����i�[����z��̗v�f��*/
#define ULIMIT 99 /*�ݏ�̌J��Ԃ���*/
#define RESLIMIT 10000000UL /*7���̕����Ȃ������̍ő�l+1*/

/*�֐��̃v���g�^�C�v�̐錾*/
void printresult(unsigned long result[]) ;/*���ʂ̏o��*/
void power3(unsigned long result[]) ;/*�R���|����*/

int main()
{
 unsigned long result[N]={0} ; /*�v�Z����*/
 int i ;/*�J��Ԃ��̃J�E���^*/

 /*�����l�̐ݒ�*/
 result[0]=1 ;/*3��0��*/

 /*�ݏ�̌v�Z*/
 for(i=1;i<=ULIMIT;++i){
  power3(result) ;/*�R���|����*/
  printf("n=%3d: ",i) ;
  printresult(result) ;/*���ʂ̏o��*/
 }

 return 0 ;
}

/*************************/
/*   printresul()�֐�    */
/*    ���ʂ̏o��         */
/*************************/
void printresult(unsigned long result[])
{
 int j ;/*�J��Ԃ��̃J�E���^*/
 
 for(j=N-1;j>=0;--j){
  if(result[j]==0) printf("        ") ;/*�󔒂�8�����o��*/
  else  printf("%8lu",result[j]) ;
 }
 printf("\n") ;
}

/*************************/
/*   power3()�֐�        */
/*   �R���|����          */
/*************************/
void power3(unsigned long result[])
{
 int i ;/*�J��Ԃ��̃J�E���^*/
 unsigned long midres[N]={0} ;/*�R�{�̌v�Z����*/

 for(i=0;i<N;++i){
  midres[i]+=result[i]*3 ;
  if(midres[i]>=RESLIMIT){/*�����ӂ�*/
   if(i!=N-1){midres[i+1]+=midres[i]/RESLIMIT ;}
   else{/*���{�������������ӂ�*/
    fprintf(stderr,"���{�������������ӂꂵ�܂���\n") ;
    exit(1) ;/*�ُ�I��*/
   }
   midres[i]=midres[i]%RESLIMIT ;
  }
 }
 /*���ʂ�result[]�ւ̊i�[*/
 for(i=0;i<N;++i)
  result[i]=midres[i] ;
}


