/**********************************************/
/*�@�@�@coord.c�v���O����                     */
/**********************************************/

/* �s��`���̃f�[�^�����W�`���ɕϊ����܂�     */

#include <stdio.h>

#define BUFSIZE 1024 /*���̓o�b�t�@�p�z��̒���*/

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 int lineno=0 ;/*�s�ԍ�*/
 char linebuf[BUFSIZE] ; /*1�s���͗p�̕����z��*/
 int i ;

 /*�f�[�^��ǂݍ���*/
 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){/*�ǂݎ���ԌJ��Ԃ�*/
  if(linebuf[0]=='0'){/*�f�[�^�̈�*/
   for(i=0;linebuf[i]!='\0';++i)
    if(linebuf[i]=='1') printf("%d %d\n",i,-lineno) ;/*���W�̏o��*/
  ++lineno ;
  }
 }

 return 0 ;
}
