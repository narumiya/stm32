//--------------------------------------------------------------------
//
//	my_standard_io.h
//
//										作成・編集日：2014/11/5
//										作成・編集者：桐生
//--------------------------------------------------------------------

//Warning:
//	このファイルの文字送信関数では一文字送信の関数を中心にして全ての文字送信を行っています。
//	そのため、マイコン、通信形式に合わせた一文字送信を次のような関数にしてください。
//		void 関数名(char 送信する文字)
//	そして、その関数のアドレスを引数として使用してください。

#ifndef my_standard_io_h
#define my_standard_io_h

#include <math.h>

//最大文字数
#define WORD_MAX 20

//--------------------------------------------------------------
//別名定義
#define END '#'				//通信データの終端文字

#ifndef NULL
#define NULL 0
#endif

#define READ_MODE	0
#define WRITE_MODE	1

//----------------------------------------------------------
//					画面表示用関数
//------------------------------------------------
// title: 	一文字送信の関数
// return:	なし
// argument:void (*)(char)	1文字送信
//			char			送信データ
// coders:	桐生
void put_c(void (*put_char)(char c),char data);
//------------------------------------------------
// title: 	自然数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			unsigned long	送信用整数データ
// coders:	桐生
void put_i(void (*put_char)(char c),unsigned long data);
//------------------------------------------------
// title:	整数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			signed long		送信データ
// coders:	桐生
void put_si(void (*put_char)(char c),signed long data);
//------------------------------------------------
// title:	実数の文字列送信(小数点以下3桁)
// return:	なし
// argument:void (*)(char)	1文字送信
//			float			送信データ
// coders:	桐生
void put_f(void (*put_char)(char c),float data);
//------------------------------------------------
// title:	文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
// coders:	桐生
void put_st(void (*put_char)(char c),char *word);
//------------------------------------------------
// title:	改行の送信
// return:	なし
// argument:void (*)(char)	1文字送信
// coders:	桐生
void put_enter(void (*put_char)(char c));
//------------------------------------------------
// title:	文字列と数字(int)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			int				送信データ
// coders:	桐生
void i_print(void (*put_char)(char c),char *moji,int kazu);
//------------------------------------------------
// title:	文字列と数字(float)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			float			送信データ
// coders:	桐生
void f_print(void (*put_char)(char c),char *moji,float kazu);
//------------------------------------------------
// title:	文字列と数字(float)x2の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			float			送信データ(数字1)
//			float			送信データ(数字2)
// coders:	桐生
void f2_print(void (*put_char)(char c),char *moji,float kazu1,float kazu2);

//--------------------------------------------------------------------
// 格納データの保存
//------------------------------------------------
// title:	格納データ関数
// return:	読み込みデータ
// argument:char 	データ格納場選択
//			float	書き込み時のデータ
//			int		読み書きのモード選択
// coders:	桐生
float value_wr_data(char character,float num,int mode);
//------------------------------------------------
// title:	格納データを変更する関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
void write_value(char c,float num);
//------------------------------------------------
// title:	格納データを読み取る関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
float read_value(char c);
//------------------------------------------------
// title:	受信データを保存する関数
// return:	なし
// argument:char 	受信データ
// coders:	桐生
void receive_order_c(char character);
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。

#endif
