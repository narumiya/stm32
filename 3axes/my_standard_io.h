//--------------------------------------------------------------------
//
//	my_standard_io.h
//
//										�쐬�E�ҏW���F2014/11/5
//										�쐬�E�ҏW�ҁF�ː�
//--------------------------------------------------------------------

//Warning:
//	���̃t�@�C���̕������M�֐��ł͈ꕶ�����M�̊֐��𒆐S�ɂ��đS�Ă̕������M���s���Ă��܂��B
//	���̂��߁A�}�C�R���A�ʐM�`���ɍ��킹���ꕶ�����M�����̂悤�Ȋ֐��ɂ��Ă��������B
//		void �֐���(char ���M���镶��)
//	�����āA���̊֐��̃A�h���X�������Ƃ��Ďg�p���Ă��������B

#ifndef my_standard_io_h
#define my_standard_io_h

#include <math.h>

//�ő啶����
#define WORD_MAX 20

//--------------------------------------------------------------
//�ʖ���`
#define END '#'				//�ʐM�f�[�^�̏I�[����

#ifndef NULL
#define NULL 0
#endif

#define READ_MODE	0
#define WRITE_MODE	1

//----------------------------------------------------------
//					��ʕ\���p�֐�
//------------------------------------------------
// title: 	�ꕶ�����M�̊֐�
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char			���M�f�[�^
// coders:	�ː�
void put_c(void (*put_char)(char c),char data);
//------------------------------------------------
// title: 	���R���̕����񑗐M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			unsigned long	���M�p�����f�[�^
// coders:	�ː�
void put_i(void (*put_char)(char c),unsigned long data);
//------------------------------------------------
// title:	�����̕����񑗐M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			signed long		���M�f�[�^
// coders:	�ː�
void put_si(void (*put_char)(char c),signed long data);
//------------------------------------------------
// title:	�����̕����񑗐M(�����_�ȉ�3��)
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			float			���M�f�[�^
// coders:	�ː�
void put_f(void (*put_char)(char c),float data);
//------------------------------------------------
// title:	�����񑗐M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^
// coders:	�ː�
void put_st(void (*put_char)(char c),char *word);
//------------------------------------------------
// title:	���s�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
// coders:	�ː�
void put_enter(void (*put_char)(char c));
//------------------------------------------------
// title:	������Ɛ���(int)�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^
//			int				���M�f�[�^
// coders:	�ː�
void i_print(void (*put_char)(char c),char *moji,int kazu);
//------------------------------------------------
// title:	������Ɛ���(float)�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^
//			float			���M�f�[�^
// coders:	�ː�
void f_print(void (*put_char)(char c),char *moji,float kazu);
//------------------------------------------------
// title:	������Ɛ���(float)x2�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^(����)
//			float			���M�f�[�^(����1)
//			float			���M�f�[�^(����2)
// coders:	�ː�
void f2_print(void (*put_char)(char c),char *moji,float kazu1,float kazu2);

//--------------------------------------------------------------------
// �i�[�f�[�^�̕ۑ�
//------------------------------------------------
// title:	�i�[�f�[�^�֐�
// return:	�ǂݍ��݃f�[�^
// argument:char 	�f�[�^�i�[��I��
//			float	�������ݎ��̃f�[�^
//			int		�ǂݏ����̃��[�h�I��
// coders:	�ː�
float value_wr_data(char character,float num,int mode);
//------------------------------------------------
// title:	�i�[�f�[�^��ύX����֐�
// return:	�Ȃ�
// argument:char 	�f�[�^�i�[��I��
//			float	�i�[�p�f�[�^
// coders:	�ː�
void write_value(char c,float num);
//------------------------------------------------
// title:	�i�[�f�[�^��ǂݎ��֐�
// return:	�Ȃ�
// argument:char 	�f�[�^�i�[��I��
//			float	�i�[�p�f�[�^
// coders:	�ː�
float read_value(char c);
//------------------------------------------------
// title:	��M�f�[�^��ۑ�����֐�
// return:	�Ȃ�
// argument:char 	��M�f�[�^
// coders:	�ː�
void receive_order_c(char character);
//��M�f�[�^����
//	1.����(a-z,A-Z)
//	2.�f�[�^(float�^)
//	3.END(�w�b�_�[�t�@�C���Œ�`)
//	���̏��̃f�[�^�����̊֐��ł͏������܂��B

#endif
