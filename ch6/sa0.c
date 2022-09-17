/**********************************************/
/*�@�@�@�@    sa0.c�v���O����                 */
/**********************************************/

/*    �V���v���ȃG�[�W�F���g�V�~�����[�V����  */
/*    2�������ʓ��œ��삷��G�[�W�F���g       */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define N 1       /*�G�[�W�F���g�̌�*/
#define N_OF_A 2       /*�G�[�W�F���g�̑����l�̌�*/
#define TIMELIMIT 100 /*�V�~�����[�V�����ł��؂莞��*/


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
void cat0(struct agent *cat0agent) ;/*�J�e�S��0�̌v�Z���\�b�h*/
void reverse(int *i) ;/*cat0()�̉������֐�*/

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*�G�[�W�F���g*/
 int t ;
 
 /*������*/
 a[0].iattribute[0]=1 ;
 putstate(a,0) ;

 /*�G�[�W�F���g�V�~�����[�V����*/
 for(t=0;t<=TIMELIMIT;++t){/*�ł��؂莞�Ԃ܂Ōv�Z*/
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
  if(a[i].category==0)/*�J�e�S��0*/cat0(&a[i]) ;
  else/*���v����J�e�S�����Ȃ�*/ 
   fprintf(stderr,"ERROR �J�e�S��������܂���(%d)\n",i) ;
 }
}

/*************************/
/*      cat0()�֐�       */
/*�J�e�S��0�̌v�Z���\�b�h*/
/*************************/
void cat0(struct agent *cat0agent)
{
 /*������Ԃ̍X�V*/
 reverse(&((*cat0agent).iattribute[0])) ;
 reverse(&((*cat0agent).iattribute[1])) ;

 /*������Ԃɂ���Ď��̍��W������*/
 (*cat0agent).coord.x+=(*cat0agent).iattribute[0] ;
 (*cat0agent).coord.y+=(*cat0agent).iattribute[1] ;
}

/*************************/
/*    reverse()�֐�      */
/*cat0()�֐��̉������֐� */
/*************************/
void reverse(int *i)
{
 if(*i==0) *i=1;
 else *i=0 ;
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

