/**********************************************/
/*�@�@�@�@   randwalk.c�v���O����             */
/**********************************************/

/* �����_���E�H�[�N�V�~�����[�V����           */
/* �[���������g����2�������ʂ𐌕����܂�      */
/*�g����  $./randwalk (���s��n�j(�����̎�)  */


#include <stdio.h>
#include <stdlib.h>

/*�֐��̃v���g�^�C�v�̐錾*/
double frand(void) ;/*��������*/

/*********************/
/*     main()�֐�    */
/*********************/
int main(int argc,char *argv[])
{
 int n ;  /*���s��n*/
 int i ;  /*�J��Ԃ�����̕ϐ�*/
 int seed ;/*�����̎�*/
 double x=0,y=0 ;/*�_�̍��W*/


 /*���s��n�̏�����*/
 if(argc<3){/*�����̎w�肪�Ȃ�*/
  fprintf(stderr,"�g�����@randwalk (���s��n�j(�����̎�)\n") ;
  exit(1) ;
 }
 if((n=atoi(argv[1]))<=0){
  fprintf(stderr,"���s��n���s���ł�(%d)\n",n) ;
  exit(1) ;
 } 
 if((seed=atoi(argv[2]))<=0){
  fprintf(stderr,"�����̎킪�s���ł�(%d)\n",seed) ;
  exit(1) ;
 } 

 /*�����̏�����*/
 srand(seed) ;
 printf("%lf %lf\n",x,y) ;

 /*�����_���E�H�[�N*/
 for(i=0;i<n;++i){
   x+=(frand()-0.5)*2 ;
   y+=(frand()-0.5)*2 ;

  /*���ʂ̏o��*/
  printf("%lf %lf\n",x,y) ;
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
