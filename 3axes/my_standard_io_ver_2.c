#include "my_standard_io_ver_2.h"
#include <math.h>

double pow_for_my_stdio(double num,int p){
	int i=0;
	double ans=1;

	if(p >= 0){
		for(i=1;i<=p;i++){
			ans *= num;
		}
	}else{
		for(i=-1;i<=p;i--){
			ans /= num;
		}
	}

	return ans;
}

//--------------------------------------------------------------------------------------------------
//��ʕ\���p�֐�


void Put_c(void (*put_c)(char c),char data){
	put_c(data);
}
//------------------------------------------------------------------------------
//	�^�C�g�� �F ����̏o��(�����̂�)
//	  �֐��� �F put_i
//	  �߂�l �F �Ȃ�
//	   ����1 �F unsigned long�^ data
//------------------------------------------------------------------------------
void Put_i(void (*put_c)(char c),unsigned long data){
	unsigned long out_data = 0;
	int i=0;
	char out[20] = {0};

	out_data = data;
	for(i=0;out_data>0;i++){
		out[i] = out_data%10;
		out_data *= 0.1;
	}

	if(data == 0){
		put_c('0');
	}else{
		for(i=i-1;i>=0;i--){
			put_c(out[i] + '0');
		}
	}
}

//------------------------------------------------------------------------------
//	�^�C�g�� �F ����̕\��(�����Ƃ��ɉ�)
//	  �֐��� �F put_si
//	  �߂�l �F �Ȃ�
//	   ����1 �F signed long�^ data
//------------------------------------------------------------------------------
void Put_si(void (*put_c)(char c),signed long data){
	if(data < 0){
		put_c('-');
		Put_i(put_c,(-1)*data);
	}else{
		Put_i(put_c,data);
	}
}

//------------------------------------------------------------------------------
//	�^�C�g�� �F �����̕\���i�����_�ȉ��O���j
//	  �֐��� �F put_f
//	  �߂�l �F �Ȃ�
//	   ����1 �F double�^ data
//------------------------------------------------------------------------------
void Put_f(void (*put_c)(char c),double data){
	const int few_below = 3;		//�ő�10��
	int
		i=0,
		i_data = 0;
	double f_data = 0;

	i_data = (int)data;
	Put_si(put_c,i_data);

	put_c('.');
	f_data = (data - i_data)*pow_for_my_stdio(10,few_below);
	i_data = (int)(fabs(f_data)+0.5);
	for(i=1;pow_for_my_stdio(10,few_below-i)>i_data && i<few_below;i++){
		put_c('0');
	}
	Put_i(put_c,i_data);
}

//------------------------------------------------------------------------------
//	�^�C�g�� �F ������̕\��
//	  �֐��� �F put_st
//	  �߂�l �F �Ȃ�
//	   ����1 �F int�^	word
//	   ����2 �F char�^	*c
//---------------------------------------------  ---------------------------------
void Put_st(void (*put_c)(char c),char *word){
	int n=0;

	for(n=0;(*(word+n)!=NULL_) && (n<20);n++){
		put_c(*(word+n));
	}
}

//------------------------------------------------------------------------------
//	�^�C�g�� �F ���s�̏o��
//	  �֐��� �F put_enter
//	  �߂�l �F �Ȃ�
//	   ����1 �F �Ȃ�
//------------------------------------------------------------------------------
void Put_enter(void (*put_c)(char c)){
	put_c(0x0d);
	put_c(0x0a);
}

void I_print(void (*put_c)(char c),char *moji,int kazu){
	Put_st(put_c,moji);
	put_c(',');

	Put_si(put_c,kazu);
	put_c(',');
}

void F_print(void (*put_c)(char c),char *moji,double kazu){
	Put_st(put_c,moji);
	put_c(',');

	Put_f(put_c,kazu);
	put_c(',');
}

//--------------------------------------------------------------------------------------------------
//�V���A���̎�M�ɂ��ϐ��ύX
void Write_value(char c,float num){
	Value_wr_data(c,num,WRITE_MODE);
}

float Read_value(char c){
	return (Value_wr_data(c,0,READ_MODE));
}

float Value_wr_data(char character,float num,int mode){
	int box=0;
	float out_data=0;
	static float atoz_value[26] = {0}; 
	static float AtoZ_value[26] = {0};

	if( (character >= 'a') && (character <= 'z') ){
		box = (int)(character - 'a');
		if(mode == WRITE_MODE)		{atoz_value[box] = num;}
		else if(mode == READ_MODE)	{out_data = atoz_value[box];}
	}else if( (character >= 'A') && (character <= 'Z') ){
		box = (int)(character - 'A');
		if(mode == WRITE_MODE)		{AtoZ_value[box] = num;}
		else if(mode == READ_MODE)	{out_data = AtoZ_value[box];}
    }
	return out_data;
}

void Receive_order_c(char character){
	const char end = END;								 //�i�[���߂̏I������

	static char c = 0;
	static float num_data = 0;
	static int
		point_ct = 0,							 //�����𕶎���̂ǂ��Ɋi�[���邩
		flont_char_flag = 0,
		minus_flag = 0,
		point_flag = 0;							 //�����_�ȉ����܂܂�Ă��邩�ۂ�
	int reset = 0;										 //�����̃��Z�b�g�����邩�ۂ�

	if(character == end){
		if(minus_flag == 1)	num_data *= (-1);
		Write_value(c,num_data);
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
