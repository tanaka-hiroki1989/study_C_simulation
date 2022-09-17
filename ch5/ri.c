/**********************************************/
/*�@�@�@�@      ri.c�v���O����                */
/**********************************************/

/* �����ɂ�鐔�l�ϕ��v���O����               */
/* �[���������g���Đ��l�ϕ����s���܂�         */
/*�@�g����    $./ri (���s��n�j�@      �@    */
/*  ��Ԃ�0�`1�ɌŒ肵�Ă���܂�              */

#include <stdio.h>
#include <stdlib.h>

#define SEED  RAND_MAX-1  /*�����̎�*/
#define R 10 /*�����̌J��Ԃ���*/

/*�֐��̃v���g�^�C�v�̐錾*/
double frand(void) ;/*��������*/

/*********************/
/*     main()�֐�    */
/*********************/
int main(int argc,char *argv[])
{
 int integral ;/*�ϕ��l*/
 int n ;  /*���s��n*/
 int i,r ;  /*�J��Ԃ�����̕ϐ�*/
 double x,y ;/*�_�̍��W*/

 /*���s��n�̏�����*/
 if(argc<2){/*���s��n�̎w�肪�Ȃ�*/
  fprintf(stderr,"�g�����@ri (���s��n�j\n") ;
  exit(1) ;
 }
 if((n=atoi(argv[1]))<=0){
  fprintf(stderr,"���s��n���s���ł�(%d)\n",n) ;
  exit(1) ;
 } 

 /*�����̏�����*/
 srand(SEED) ;

 /*�ϕ������̌J��Ԃ�*/
 for(r=0;r<R;++r){
  integral=0 ;
  /*�ϕ��l�̌v�Z*/
  for(i=0;i<n;++i){
   x=frand() ; y=frand() ;
   if((x*x+y*y)<=1)/*�~�̓���*/
    ++integral ;
  }
  /*���ʂ̏o��*/
  printf("�ϕ��lI�@%.9lf    4I  %.9lf\n"
        ,(double)integral/n,(double)integral/n*4.0) ;
 }
 return 0 ;
}

/*************************/
/*   frand()�֐�         */
/*   ��������            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}
