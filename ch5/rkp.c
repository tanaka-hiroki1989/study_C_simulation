/***********************************************/
/* �@�@�@        rkp.c�v���O����               */
/***********************************************/

/*�i�b�v�T�b�N���������_���T���ŉ����v���O�����ł��D */
/*�@�g����   $./rkp (�ו��̌�) (�����d��)  (���s��)*/

#include <stdio.h>
#include <stdlib.h>


#define BUFSIZE 256/*���̓o�b�t�@�̑傫��*/
#define MAXP 256/*�ו��̌��̍ő�l*/
#define SEED  RAND_MAX-1  /*�����̎�*/
#define R 10 /*�����̌J��Ԃ���*/


/*�֐��̃v���g�^�C�v�̐錾*/
void initparcel(int parcel[][2]);/*�t�@�C������ו��̏d�ʂƉ��l��ǂݍ���*/
void prints(int p[],int n);/*���̕\��*/
void solve(int parcel[][2],int p[],int weightlimit,long nlimit,int n) ;/*�������߂�*/
void rsetp(int p[],int n) ;/*�����ɂ��ו��̋l�ߍ��킹*/
double frand(void) ;/*��������*/
int calcval(int parcel[][2],int p[],int n) ;/*�]���l�̌v�Z*/
int calcw(int parcel[][2],int p[],int n) ;/*�d�ʂ̌v�Z*/

/*****************/
/*�@main()�֐��@ */
/*****************/
int main(int argc, char **argv)
{
 int parcel[MAXP][2]={0} ;/*�ו�*/
 int p[MAXP]={0} ;/*��*/
 int weightlimit ;/*�����d��*/
 int n ;/*�ו��̌�*/
 long nlimit ;/*���s��*/
 int r ;/*�����̌J��Ԃ�����ϐ�*/

 if(argc!=4){
  fprintf(stderr,"�g�����@./rkp (�ו��̌�) (�����d��) (���s��)\n") ;
  exit(1) ;
 }

 n=atoi(argv[1]) ;
 if((n<=0)||(n>MAXP)){/*�ו��̌����s��*/
  fprintf(stderr,"�ו��̌����s���ł�(%d�j\n",n) ;
  exit(1) ;
 }
 printf("�ו��̌�:%d\n",n) ;

 if((weightlimit=atoi(argv[2]))<=0){/*�����d�ʂ�0�ȉ�*/
  fprintf(stderr,"�����d�ʂ��s���ł�(%d�j\n",weightlimit) ;
  exit(1) ;
 }
 printf("�����d�ʁ@:%d\n",weightlimit) ;

 if((nlimit=atoi(argv[3]))<=0){/*���s�񐔂�0�ȉ�*/
  fprintf(stderr,"���s�񐔂��s���ł�(%d�j\n",nlimit) ;
  exit(1) ;
 }
 printf("���s�񐔁@:%ld\n",nlimit) ;

 /*�t�@�C������ו��̏d�ʂƉ��l��ǂݍ���*/
 initparcel(parcel) ;
 /*��������*/
 srand(SEED) ;
 /*�����̌J��Ԃ�*/
 for(r=0;r<R;++r)
  solve(parcel,p,weightlimit,nlimit,n) ;

 return 0 ;
}

/***********************/
/*���������֐�solve()*/
/***********************/
void solve(int parcel[][2],int p[],int weightlimit,long nlimit,int n)
{
 int maxvalue=0 ,mweight;/*���l�̍ő�l�ƁC���̂Ƃ��̏d��*/
 int value,weight ; /*���l�Əd��*/
 long i ;
 int bestp[MAXP]={0} ;/*�ŗǉ�*/
 int j ;

 for(i=0;i<nlimit;++i){
  rsetp(p,n) ;/*�����ɂ��ו��̋l�ߍ��킹*/
  if((weight=calcw(parcel,p,n))<=weightlimit)/*�����d�ʈȓ�*/
   value=calcval(parcel,p,n) ;/*�]���l�̌v�Z*/
  else
   value=0 ;/*�d�ʃI�[�o�[*/
  if(value>maxvalue){/*�ŗǉ����X�V*/
   maxvalue=value ;
   mweight=weight ;
   for(j=0;j<n;++j)
    bestp[j]=p[j] ;
  }
 }
 printf("%d  %d ",maxvalue,mweight) ;
 prints(bestp,n) ;
}

/****************************/
/*   �@ calcw()�֐�         */
/*      �]���l�̌v�Z        */
/****************************/
int calcw(int parcel[][2],int p[],int n)
{
 int i ;
 int w=0 ;/*�d��*/

 for(i=0;i<n;++i)
  w+=parcel[i][0]*p[i]  ;

 return w ;
}

/****************************/
/*   �@ calcval()�֐�       */
/*      �]���l�̌v�Z        */
/****************************/
int calcval(int parcel[][2],int p[],int n)
{
 int i ;
 int v=0 ;/*�]���l*/

 for(i=0;i<n;++i)
  v+=parcel[i][1]*p[i]  ;

 return v ;
}

/****************************/
/*   �@ rsetp()�֐�         */
/*�����ɂ��ו��̋l�ߍ��킹*/
/****************************/
void rsetp(int p[],int n)
{
 int i ;

 for(i=0;i<n;++i)
  while((p[i]=frand()*2)>=2)  ;
}

/*************************/
/*   frand()�֐�         */
/*   ��������            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

/**************/
/*prints()�֐�*/
/*  ���̕\��  */
/**************/
void prints(int p[],int n)
{
 int i ;
 for(i=0;i<n;++i)
  printf("%1d",p[i]) ;
 printf("\n") ;
}

/****************************************/
/*�t�@�C������ו��̏d�ʂƉ��l��ǂݍ���*/
/****************************************/
void initparcel(int parcel [MAXP][2])
{
 int i=0 ;
  char linebuf[BUFSIZE] ;/*���̓o�b�t�@*/

 while((i<MAXP) && (fgets(linebuf,BUFSIZE,stdin)!=NULL)){
  sscanf(linebuf,"%d %d",&parcel[i][0],&parcel[i][1]) ;
  ++i ;
 }
}
