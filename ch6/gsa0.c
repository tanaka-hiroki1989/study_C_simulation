/**********************************************/
/*�@�@�@�@       gsa0.c�v���O����             */
/**********************************************/

/*    �V���v���ȃG�[�W�F���g�V�~�����[�V����  */
/*    2�������ʓ��œ��삷��G�[�W�F���g       */
/*    gnuplot��1�b���Ƃɏo�͂��܂�            */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define N 1      /*�G�[�W�F���g�̌�*/
#define N_OF_A 2       /*�G�[�W�F���g�̑����l�̌�*/
#define TIMELIMIT 100 /*�V�~�����[�V�����ł��؂莞��*/

/*�ȉ���gnuplot���p�̂��߂̒�`*/
#define TMPFILE "tempfile.tmp" /*�ꎞ�t�@�C���̃t�@�C����*/
#define GNUPLOT "/bin/gnuplot" /*gnuplot�̃p�X���w��*/
#define RANGE 100 /*gnuplot�̏o�͗̈�*/

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
void fputstate(struct agent a[],int t) ;/*��Ԃ��o��*/
void cat0(struct agent *cat0agent) ;/*�J�e�S��0�̌v�Z���\�b�h*/
void reverse(int *i) ;/*cat0()�̉������֐�*/

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*�G�[�W�F���g*/
 int t ;
 FILE *pipe ;/*gnuplot�Ƃ̒ʐM�p�p�C�v*/
 
 /*�p�C�v���J��*/
 if((pipe=popen(GNUPLOT " -persist","w"))==NULL){
  /*pipe���J���Ȃ�*/
  fprintf(stderr,"�p�C�v���J���܂���D\n") ;
  exit(1) ;
 } 
 /*gnuplot�̏����ݒ�*/
 fprintf(pipe,"set xrange [-%d:%d]\n",RANGE,RANGE) ;
 fprintf(pipe,"set yrange [-%d:%d]\n",RANGE,RANGE) ;

 /*������*/
 a[0].iattribute[0]=1 ;

 /*�G�[�W�F���g�V�~�����[�V����*/
 for(t=0;t<=TIMELIMIT;++t){/*�ł��؂莞�Ԃ܂Ōv�Z*/
  printf("t=%d\n",t) ;
  calcnext(a) ;/*�������̏�Ԃ��v�Z */
  fputstate(a,t) ;/*��Ԃ��t�@�C���o��*/
  /*gnuplot�ŕ`��*/
  fprintf(pipe,"plot \"" TMPFILE "\" with points pt 4\n") ; 
  fflush(pipe) ;
  sleep(1) ; /*�\���̑҂����킹*/
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
/*    fputstate()�֐�    */
/*      ��Ԃ��o��       */
/*************************/
void fputstate(struct agent a[],int t)
{
 int i ;
 FILE *fp ;  /*�ꎞ�t�@�C���̃t�@�C���|�C���^*/

 /*�ꎞ�t�@�C�����J��*/
 if((fp=fopen(TMPFILE,"w"))==NULL){/*�ꎞ�t�@�C�����J���Ȃ�*/
  fprintf(stderr,"�ꎞ�t�@�C�����J���܂���\n") ;
  exit(1) ;
 } 

 for(i=0;i<N;++i) /*�J�e�S���ƍ��W�̏o��*/
  fprintf(fp,"%lf %lf\n",a[i].coord.x,a[i].coord.y) ;
 fclose(fp) ;/*�ꎞ�t�@�C�������*/
}

