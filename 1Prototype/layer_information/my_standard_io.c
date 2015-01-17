//--------------------------------------------------------------------
//
//	my_standard_io.c
//
//										作成・編集日：2014/11/5
//										作成・編集者：桐生
//--------------------------------------------------------------------

//Warning:
//	このファイルの文字送信関数では一文字送信の関数を中心にして全ての文字送信を行っています。
//	そのため、マイコン、通信形式に合わせた一文字送信を次のような関数にしてください。
//		void 関数名(char 送信する文字)
//	そして、その関数のアドレスを引数として使用してください。

#include "my_standard_io.h"
#include <math.h>

//----------------------------------------------------------
//					画面表示用関数
//------------------------------------------------
// title: 	一文字送信の関数
// return:	なし
// argument:void (*)(char)	1文字送信
//			char			送信データ
// coders:	桐生
void put_c(void (*put_char)(char c),char data){
	put_char(data);
}

//------------------------------------------------
// title: 	自然数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			unsigned long	送信用整数データ
// coders:	桐生
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
// title:	整数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			signed long		送信データ
// coders:	桐生
void put_si(void (*put_char)(char c),signed long data){
	if(data < 0){
		put_char('-');
		put_i(put_char,(-1)*data);
	}else{
		put_i(put_char,data);
	}
}

//------------------------------------------------
// title:	実数の文字列送信(小数点以下3桁)
// return:	なし
// argument:void (*)(char)	1文字送信
//			float			送信データ
// coders:	桐生
void put_f(void put_char(char),float data){
	const int few_below = 3;		//最大10桁
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
// title:	文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
// coders:	桐生
void put_st(void (*put_char)(char c),char *word){
	int n=0;

	for(n=0;(((*(word+n))!=NULL) && (n<WORD_MAX));n++){
		put_char(*(word+n));
	}
}

//------------------------------------------------
// title:	改行の送信
// return:	なし
// argument:void (*)(char)	1文字送信
// coders:	桐生
void put_enter(void (*put_char)(char c)){
	put_char(0x0d);
	put_char(0x0a);
}

//------------------------------------------------
// title:	文字列と数字(int)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			int				送信データ
// coders:	桐生
void i_print(void (*put_char)(char c),char *moji,int kazu){
	put_st(put_char,moji);
	put_char(',');

	put_si(put_char,kazu);
	put_char(',');
}

//------------------------------------------------
// title:	文字列と数字(float)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			float			送信データ
// coders:	桐生
void f_print(void (*put_char)(char c),char *moji,float kazu){
	put_st(put_char,moji);
	put_char(',');

	put_f(put_char,kazu);
	put_char(',');
}
//------------------------------------------------
// title:	文字列と数字(float)x2の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			float			送信データ(数字1)
//			float			送信データ(数字2)
// coders:	桐生
void f2_print(void (*put_char)(char c),char *moji,float kazu1,float kazu2){
	put_st(put_char,moji);
	put_char(',');

	put_f(put_char,kazu1);
	put_char(',');

	put_f(put_char,kazu2);
	put_char(',');
}

//--------------------------------------------------------------------
// 格納データの保存

//------------------------------------------------
// title:	格納データを変更する関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
void write_value(char c,float num){
	value_wr_data(c,num,WRITE_MODE);
}

//------------------------------------------------
// title:	格納データを読み取る関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
float read_value(char c){
	return (value_wr_data(c,0,READ_MODE));
}

//------------------------------------------------
// title:	格納データ関数
// return:	読み込みデータ
// argument:char 	データ格納場選択
//			float	書き込み時のデータ
//			int		読み書きのモード選択
// coders:	桐生
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
// title:	受信データを保存する関数
// return:	なし
// argument:char 	受信データ
// coders:	桐生
/*void receive_order_c(char character){
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。
	static char c = 0;
	static float num_data = 0;
	static int
		point_ct = 0,							 //文字を文字列のどこに格納するか
		flont_char_flag = 0,
		minus_flag = 0,
		point_flag = 0;							 //小数点以下が含まれているか否か
	int reset = 0;										 //処理のリセットをするか否か

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
