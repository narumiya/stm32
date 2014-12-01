//--------------------------------------------------------------------
//
//	my_standard_io.c
//
//										�쐬�E�ҏW���F2014/11/5
//										�쐬�E�ҏW�ҁF�ː�
//--------------------------------------------------------------------

//Warning:
//	���̃t�@�C���̕������M�֐��ł͈ꕶ�����M�̊֐��𒆐S�ɂ��đS�Ă̕������M���s���Ă��܂��B
//	���̂��߁A�}�C�R���A�ʐM�`���ɍ��킹���ꕶ�����M�����̂悤�Ȋ֐��ɂ��Ă��������B
//		void �֐���(char ���M���镶��)
//	�����āA���̊֐��̃A�h���X�������Ƃ��Ďg�p���Ă��������B

#include "my_standard_io.h"
#include <math.h>

//----------------------------------------------------------
//					��ʕ\���p�֐�
//------------------------------------------------
// title: 	�ꕶ�����M�̊֐�
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char			���M�f�[�^
// coders:	�ː�
void put_c(void (*put_char)(char c),char data){
	put_char(data);
}

//------------------------------------------------
// title: 	���R���̕����񑗐M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			unsigned long	���M�p�����f�[�^
// coders:	�ː�
void put_i(void (*put_char)(char c),unsigned long data){
	int i=0;
	char out[WORD_MAX] = {0};

	if(data == 0){
		put_char('0');
	}else{
		for(i=0;(data>0)&(i<WORD_MAX);i++){
			out[i] = data%10;
			data *= 0.1;
		}
		for(i=i-1;i>=0;i--){
			put_char(out[i] + '0');
		}
	}
}

//------------------------------------------------
// title:	�����̕����񑗐M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			signed long		���M�f�[�^
// coders:	�ː�
void put_si(void (*put_char)(char c),signed long data){
	if(data < 0){
		put_char('-');
		put_i(put_char,(-1)*data);
	}else{
		put_i(put_char,data);
	}
}

//------------------------------------------------
// title:	�����̕����񑗐M(�����_�ȉ�3��)
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			float			���M�f�[�^
// coders:	�ː�
void put_f(void put_char(char),float data){
	const int few_below = 3;		//�ő�10��
	int
		i=0,
		i_data = 0;
	float
		i_part = 0,
		f_part = 0;

	f_part = modff(data,&i_part);
	put_si(put_char,(int)i_part);
	put_char('.');
	i_data = (int)(roundf(fabsf(f_part)*powf(10,few_below)));
	for(i=1;pow(10,few_below-i)>i_data && i<few_below;i++){
		put_char('0');
	}
	put_si(put_char,(int)(i_data));
}


//------------------------------------------------
// title:	�����񑗐M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^
// coders:	�ː�
void put_st(void (*put_char)(char c),char *word){
	int n=0;

	for(n=0;(((*(word+n))!=NULL) && (n<WORD_MAX));n++){
		put_char(*(word+n));
	}
}

//------------------------------------------------
// title:	���s�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
// coders:	�ː�
void put_enter(void (*put_char)(char c)){
	put_char(0x0d);
	put_char(0x0a);
}

//------------------------------------------------
// title:	������Ɛ���(int)�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^
//			int				���M�f�[�^
// coders:	�ː�
void i_print(void (*put_char)(char c),char *moji,int kazu){
	put_st(put_char,moji);
	put_char(',');

	put_si(put_char,kazu);
	put_char(',');
}

//------------------------------------------------
// title:	������Ɛ���(float)�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^
//			float			���M�f�[�^
// coders:	�ː�
void f_print(void (*put_char)(char c),char *moji,float kazu){
	put_st(put_char,moji);
	put_char(',');

	put_f(put_char,kazu);
	put_char(',');
}
//------------------------------------------------
// title:	������Ɛ���(float)x2�̑��M
// return:	�Ȃ�
// argument:void (*)(char)	1�������M
//			char*			���M�f�[�^(����)
//			float			���M�f�[�^(����1)
//			float			���M�f�[�^(����2)
// coders:	�ː�
void f2_print(void (*put_char)(char c),char *moji,float kazu1,float kazu2){
	put_st(put_char,moji);
	put_char(',');

	put_f(put_char,kazu1);
	put_char(',');

	put_f(put_char,kazu2);
	put_char(',');
}

//--------------------------------------------------------------------
// �i�[�f�[�^�̕ۑ�

//------------------------------------------------
// title:	�i�[�f�[�^��ύX����֐�
// return:	�Ȃ�
// argument:char 	�f�[�^�i�[��I��
//			float	�i�[�p�f�[�^
// coders:	�ː�
void write_value(char c,float num){
	value_wr_data(c,num,WRITE_MODE);
}

//------------------------------------------------
// title:	�i�[�f�[�^��ǂݎ��֐�
// return:	�Ȃ�
// argument:char 	�f�[�^�i�[��I��
//			float	�i�[�p�f�[�^
// coders:	�ː�
float read_value(char c){
	return (value_wr_data(c,0,READ_MODE));
}

//------------------------------------------------
// title:	�i�[�f�[�^�֐�
// return:	�ǂݍ��݃f�[�^
// argument:char 	�f�[�^�i�[��I��
//			float	�������ݎ��̃f�[�^
//			int		�ǂݏ����̃��[�h�I��
// coders:	�ː�
float value_wr_data(char c,float num,int mode){
	float out_data=0;
	static float atoz_value[26] = {0};
	static float AtoZ_value[26] = {0};

	if( (c >= 'a') && (c <= 'z') ){
		if(mode == WRITE_MODE)		{atoz_value[(int)(c - 'a')] = num;}
		else if(mode == READ_MODE)	{out_data = atoz_value[(int)(c - 'a')];}
	}else if( (c >= 'A') && (c <= 'Z') ){
		if(mode == WRITE_MODE)		{AtoZ_value[(int)(c - 'A')] = num;}
		else if(mode == READ_MODE)	{out_data = AtoZ_value[(int)(c - 'A')];}
    }

	return out_data;
}

//------------------------------------------------
// title:	��M�f�[�^��ۑ�����֐�
// return:	�Ȃ�
// argument:char 	��M�f�[�^
// coders:	�ː�
/*void receive_order_c(char character){
//��M�f�[�^����
//	1.����(a-z,A-Z)
//	2.�f�[�^(float�^)
//	3.END(�w�b�_�[�t�@�C���Œ�`)
//	���̏��̃f�[�^�����̊֐��ł͏������܂��B
	static char c = 0;
	static float num_data = 0;
	static int
		point_ct = 0,							 //�����𕶎���̂ǂ��Ɋi�[���邩
		flont_char_flag = 0,
		minus_flag = 0,
		point_flag = 0;							 //�����_�ȉ����܂܂�Ă��邩�ۂ�
	int reset = 0;										 //�����̃��Z�b�g�����邩�ۂ�

	if(character == END){
		if(minus_flag == 1)	num_data *= (-1);
		write_value(c,num_data);
		reset = 1;
		c=0;
	}else{
		if( (character >= '0') && (character <= '9') ){
			flont_char_flag = 0;
			if(point_flag == 0){
				num_data = num_data*10 + (character-'0');
			}else{
				point_ct++;
				num_data += (character-'0')*pow(0.1,point_ct);
            }
		}else if( ((character >= 'a') && (character <= 'z')) || ((character >= 'A') && (character <= 'Z')) ){
			reset = 1;
			c = character;
			flont_char_flag = 1;
		}else if( character == '-' && flont_char_flag == 1){
			if(minus_flag == 0)	minus_flag = 1;
			else				minus_flag = 0;
		}else if( character == '.' && flont_char_flag == 0){
			point_flag = 1;
		}
    }
	if( reset == 1 ){
		num_data = 0;
		point_ct = 0;
		point_flag = 0;
		minus_flag = 0;
	}
}
*/
