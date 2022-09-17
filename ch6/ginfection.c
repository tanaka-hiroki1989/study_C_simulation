/**********************************************/
/*�@�@ ginfection.c�v���O����                 */
/**********************************************/

/*    �h�����h�̃G�[�W�F���g�V�~�����[�V����  */
/*    2�������ʓ��œ��삷��G�[�W�F���g�Q     */
/*    2��ނ̃G�[�W�F���g�����ݍ�p���܂�     */
/*    gnuplot��1�b���Ƃɏo�͂��܂�*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define N 50       /*�G�[�W�F���g�̌�*/
#define N_OF_A 2       /*�G�[�W�F���g�̑����l�̌�*/
#define TIMELIMIT 100 /*�V�~�����[�V�����ł��؂莞��*/
#define SEED  RAND_MAX-1  /*�����̎�*/
#define R 0.1 /*�ߗׂ��K�肷�鐔�l*/

/*�J�e�S��1�̃G�[�W�F���g�̑��x*/
#define DX 0.1 
#define DY 0.1


/*�ȉ���gnuplot���p�̂��߂̒�`*/
#define ATMPFILE "atempfile.tmp" /*�ꎞ�t�@�C���̃t�@�C����*/
#define BTMPFILE "btempfile.tmp" /*�ꎞ�t�@�C���̃t�@�C����*/
#define GNUPLOT "/bin/gnuplot" /*gnuplot�̃p�X���w��*/
#define RANGE 10 /*gnuplot�̏o�͗̈�*/

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
double frand(void) ;/*��������*/
void cat0(struct agent *cat0agent,struct agent a[]) ;
                                   /*�J�e�S��0�̌v�Z���\�b�h*/
void cat1(struct agent *cat1agent) ;/*�J�e�S��1�̌v�Z���\�b�h*/

/*���ϐ�*/
double factor=1.0 ;/*�J�e�S���P�̃G�[�W�F���g�̕���*/

/*********************/
/*     main()�֐�    */
/*********************/
int main(int argc,char *argv[])
{
 struct agent a[N]={0} ; /*�G�[�W�F���g*/
 int t ;
 FILE *pipe ;/*gnuplot�Ƃ̒ʐM�p�p�C�v*/

 /*factor�̏�����*/
 if(argc>=2){/*factor�̎w�肪����*/
  factor=atof(argv[1]) ;
 }
 printf("factor : %lf\n",factor) ;
 
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
 srand(SEED) ;/*�����̏�����*/
 /*�G�[�W�F���g�̐ݒ�*/
 a[0].category=1 ;
 a[0].coord.x=-2 ;
 a[0].coord.y=-2 ;

 /*�G�[�W�F���g�V�~�����[�V����*/
 for(t=1;t<=TIMELIMIT;++t){/*�ł��؂莞�Ԃ܂Ōv�Z*/
  printf("t=%d\n",t) ;
  calcnext(a) ;/*�������̏�Ԃ��v�Z */
  fputstate(a,t) ;/*��Ԃ��t�@�C���o��*/
  /*gnuplot�ŕ`��*/
  fprintf(pipe,"plot \"" ATMPFILE "\" , \"" BTMPFILE "\"with points pt 4\n") ; 
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
 (*cat1agent).coord.x+=(frand()-0.5)*factor ;
 (*cat1agent).coord.y+=(frand()-0.5)*factor ;
}

/*************************/
/*    fputstate()�֐�    */
/*      ��Ԃ��o��       */
/*************************/
void fputstate(struct agent a[],int t)
{
 int i ;
 FILE *fpa,*fpb ;  /*�ꎞ�t�@�C���̃t�@�C���|�C���^*/

 /*�ꎞ�t�@�C�����J��*/
 if((fpa=fopen(ATMPFILE,"w"))==NULL){/*�ꎞ�t�@�C�����J���Ȃ�*/
  fprintf(stderr,"�ꎞ�t�@�C��A���J���܂���\n") ;
  exit(1) ;
 } 
 if((fpb=fopen(BTMPFILE,"w"))==NULL){/*�ꎞ�t�@�C�����J���Ȃ�*/
  fprintf(stderr,"�ꎞ�t�@�C��B���J���܂���\n") ;
  exit(1) ;
 } 

 for(i=0;i<N;++i){ /*�J�e�S���ƍ��W�̏o��*/
  if(a[i].category==0)
   fprintf(fpa,"%lf %lf\n",a[i].coord.x,a[i].coord.y) ;
  else
   fprintf(fpb,"%lf %lf\n",a[i].coord.x,a[i].coord.y) ;
 }
 fclose(fpa) ;/*�ꎞ�t�@�C�������*/
 fclose(fpb) ;/*�ꎞ�t�@�C�������*/
}

/*************************/
/*   frand()�֐�         */
/*   ��������            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

