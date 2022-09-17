/******************************************/
/*�@�@�@�@       traffic.c�v���O����      */
/******************************************/

/* �Z���I�[�g�}�g���Ɋ�Â���ʗ��V�~�����[�V����        */
/* ���[���Ə�����Ԃ���C���Ԕ��W���v�Z���܂�            */
/*�@�g����   $./traffic (�������j�@< (������ԃt�@�C����)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50 /*�Z���̍ő��*/
#define R 8 /*���[���\�̑傫��*/
#define MAXT 50 /*�J��Ԃ��̉�*/
#define BUFSIZE 1024 /*���̓o�b�t�@�p�z��̒���*/
#define RULE "184" /*���[���ԍ�(184�ɌŒ�)*/
#define VEHICLE "-" /*�����Ԃ�\���L��*/

/*�֐��̃v���g�^�C�v�̐錾*/
void setrule(char *arg,int rule[]) ;/*���[���\�̏�����*/
void initca(int ca[]) ;/*�����l�̓ǂݍ���*/
int cvalue(char ch) ;/*1������0/1�ւ̕ϊ�*/
void putca(int ca[]) ;/*ca�̏�Ԃ̏o��*/
void nextt(int ca[],int rule[]) ;/*���̎����ɍX�V*/

/*********************/
/*     main()�֐�    */
/*********************/
int main(int argc,char *argv[])
{
 int t  ;/*������\���C�����񐔂̃J�E���^*/
 int ca[N]={0} ;/*�Z���̕���*/
 int rule[R] ;/*���[���\*/
 int flowrate=MAXT ;/*������*/

 /*�������̏�����*/
 if(argc<2){/*�������̎w�肪�Ȃ�*/
  fprintf(stderr,"�g�����@traffic (�������j�@< (������ԃt�@�C����)\n") ;
  exit(1) ;
 }
 flowrate=atoi(argv[1]) ;
 if(flowrate<=0){/*���������s��*/
  fprintf(stderr,"������������������܂���i%d�j\n",flowrate) ;
  exit(1) ;
 }

 /*���[���\���Z�b�g*/
 setrule(RULE,rule) ;
 
 /*ca[]�ւ̏����l�̓ǂݍ���*/
 initca(ca) ;
 printf("t=  0 ") ;
 putca(ca) ;/*ca[]�̏�Ԃ̏o��*/

 /*���Ԕ��W�̌v�Z*/
 for(t=1;t<MAXT;++t){
  nextt(ca,rule) ;/*���̎����ɍX�V*/
  if((t%flowrate)==0) ca[N-2]=1 ;/*�����Ԃ̗���*/
  printf("t=%3d ",t) ;
  putca(ca) ;/*ca[]�̏�Ԃ̏o��*/
 }

 return 0 ;
}

/*************************/
/*   nextt()�֐�         */
/*   ca�̏�Ԃ̍X�V      */
/*************************/

void nextt(int ca[],int rule[])
{
 int nextca[N]={0} ;/*�������ca[]*/
 int i ;

 /*���[���̓K�p*/
 for(i=1;i<N-1;++i)
  nextca[i]=rule[ca[i+1]*4+ca[i]*2+ca[i-1]] ;

 /*ca�̍X�V*/
 for(i=0;i<N;++i)
  ca[i]=nextca[i] ;
}


/*************************/
/*   putca()�֐�         */
/*   ca�̏�Ԃ̏o��      */
/*************************/
void putca(int ca[])
{
 int  i;
 for(i=N-1;i>=0;--i){
  if(ca[i]==1) printf(VEHICLE) ;
  else printf(" ") ;
 }
 printf("\n") ;
}

/*************************/
/*  initca()�֐�         */
/*  �����l�̓ǂݍ���     */
/*************************/
void  initca(int ca[])
{
 char linebuf[BUFSIZE] ; /*1�s���͗p�̕����z��*/
 int i=0 ;

 /*�����l��ǂݍ���*/
 if(fgets(linebuf,BUFSIZE,stdin)==NULL){/*�ǂݎ�莸�s*/
  fprintf(stderr,"�����l�̓ǂݎ��Ɏ��s���܂���\n") ;
  exit(1) ;
 }

 /*�����l�̐ݒ�*/
 for(i=0;linebuf[i]!='\0';++i)
  ca[N-1-i]=cvalue(linebuf[i]) ;/*���l�ő��*/
}


/*************************/
/*  cvalue()�֐�         */
/*  1������0/1�ւ̕ϊ�   */
/*************************/
int cvalue(char ch)
{
 if(ch=='1') return 1 ;
 else return 0 ;
}


/*************************/
/*  setrule()�֐�        */
/*  ���[���\�̏�����     */
/*************************/
void setrule(char *arg,int rule[])
{
 int ruleno ;/*���[���ԍ�*/
 int i ;

 /*���[���ԍ����擾*/
 ruleno=atoi(arg) ;
 if((ruleno<0)||(255<ruleno)){/*���[���ԍ����s��*/
  fprintf(stderr,"���[���ԍ�������������܂���i%d�j\n",ruleno) ;
  exit(1) ;
 }
 printf("���[���ԍ� %d :",ruleno) ;
 /*���[���\�̏�������*/
 for(i=0;i<R;++i){
  rule[i]=ruleno%2 ;/*2�i���ł̂P�̈ʂ̒l�����o��*/
  ruleno/=2 ;/*���V�t�g*/
 }
 /*���[���̏o��*/
 for(i=R-1;i>=0;--i)
  printf("%1d",rule[i]) ;
 printf("\n") ;
}
