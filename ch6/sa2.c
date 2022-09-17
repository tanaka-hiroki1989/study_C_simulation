/**********************************************/
/*�@�@�@�@       sa2.c�v���O����              */
/**********************************************/

/*    �V���v���ȃG�[�W�F���g�V�~�����[�V����  */
/*    2�������ʓ��œ��삷��G�[�W�F���g�Q     */
/*    2��ނ̃G�[�W�F���g�����ݍ�p���܂�     */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define N 30       /*�G�[�W�F���g�̌�*/
#define N_OF_A 2       /*�G�[�W�F���g�̑����l�̌�*/
#define TIMELIMIT 100 /*�V�~�����[�V�����ł��؂莞��*/
#define SEED  RAND_MAX-1  /*�����̎�*/
#define R 0.1 /*�ߗׂ��K�肷�鐔�l*/
/*�J�e�S��1�̃G�[�W�F���g�̑��x*/
#define DX 0.1 
#define DY 0.1

/*���W�l�i2�����x�N�g��)�̕\��*/
struct coordinate {
 double x ;/*x���W*/
 double y ;/*y���W*/
} ;

/*�G�[�W�F���g�̕\��*/
struct agent {
 int category ;/*�G�[�W�F���g�̎��*/
 struct coordinate coord ;/*���W*/
 double dattribute[N_OF_A] ;/*�����l(�����j*/
 int iattribute[N_OF_A] ;/*�����l(�����j*/
} ;



/*�֐��̃v���g�^�C�v�̐錾*/
void calcnext(struct agent a[]) ;/*�������̏�Ԃ��v�Z */
void putstate(struct agent a[],int t) ;/*��Ԃ��o��*/
double frand(void) ;/*��������*/
void cat0(struct agent *cat0agent,struct agent a[]) ;/*�J�e�S��0�̌v�Z���\�b�h*/
void cat1(struct agent *cat1agent) ;/*�J�e�S��1�̌v�Z���\�b�h*/

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*�G�[�W�F���g*/
 int t ;
 
 /*������*/
 srand(SEED) ;/*�����̏�����*/

 /*�J�e�S��1�̃G�[�W�F���g�̐ݒ�*/
 a[0].category=1 ;
 a[0].coord.x=-2 ;
 a[0].coord.y=-2 ;

 putstate(a,0) ;

 /*�G�[�W�F���g�V�~�����[�V����*/
 for(t=1;t<=TIMELIMIT;++t){/*�ł��؂莞�Ԃ܂Ōv�Z*/
  calcnext(a) ;/*�������̏�Ԃ��v�Z */
  putstate(a,t) ;/*��Ԃ��o��*/
 }

 
 return 0 ;
}

/*************************/
/*     calcnext()�֐�    */
/*   �������̏�Ԃ��v�Z  */
/*************************/
void calcnext(struct agent a[])
{
 int i ;
 for(i=0;i<N;++i){ /*�e�G�[�W�F���g�̌v�Z*/
  if(a[i].category==0)/*�J�e�S��0*/cat0(&a[i],a) ;
  else if(a[i].category==1)/*�J�e�S��1*/cat1(&a[i]) ;
  else/*���v����J�e�S�����Ȃ�*/ 
   fprintf(stderr,"ERROR �J�e�S��������܂���(%d)\n",i) ;
 }
}
/*************************/
/*      cat0()�֐�       */
/*�J�e�S��0�̌v�Z���\�b�h*/
/*************************/
void cat0(struct agent *cat0agent,struct agent a[])
{
 int i ;

 double c0x,c0y,ax,ay ; /*�����̌v�Z�Ɏg���ϐ�*/
 for(i=0;i<N;++i){
  if(a[i].category==1){
   /*�J�e�S��1�̃G�[�W�F���g�Ƃ̋����𒲂ׂ�*/
   c0x=(*cat0agent).coord.x ;
   c0y=(*cat0agent).coord.y ;
   ax=a[i].coord.x ;
   ay=a[i].coord.y ;
   if(((c0x-ax)*(c0x-ax)+(c0y-ay)*(c0y-ay))<R){
    /*�אڂ��ăJ�e�S��1�̃G�[�W�F���g������*/
    (*cat0agent).category=1 ;/*�J�e�S���P�ɕϐg*/
    return  ;
   }
  }
 }
 /*�J�e�S��1�͋ߗׂɂ͂��Ȃ�*/
 (*cat0agent).coord.x+=(frand()-0.5) ;
 (*cat0agent).coord.y+=(frand()-0.5) ;
}

/*************************/
/*      cat1()�֐�       */
/*�J�e�S��1�̌v�Z���\�b�h*/
/*************************/
void cat1(struct agent *cat1agent)
{
 (*cat1agent).coord.x+=DX ;
 (*cat1agent).coord.y+=DY ;
}

/*************************/
/*     putstate()�֐�    */
/*      ��Ԃ��o��       */
/*************************/
void putstate(struct agent a[],int t)
{
 int i ;
 printf("t=%d\n",t) ;/*�����̏o��*/
 for(i=0;i<N;++i) /*�J�e�S���ƍ��W�̏o��*/
  printf("%d\t%lf\t%lf\n",a[i].category
                       ,a[i].coord.x,a[i].coord.y) ;
}

/*************************/
/*   frand()�֐�         */
/*   ��������            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

