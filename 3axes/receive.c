#include  "receive.h"

float	g_atoz_value[26]	=	{	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
												0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
												0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

float	g_AtoZ_value[26]	=	{	0.00, 0.00 , 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
												0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
												0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

char g_c = '\0';

void receive_att( void )
{
    char c = '\0';

	c = receive_usart3_c();//受信データ

    receive_order_c( c );
}

char receive()
{
	return g_c;
}

//解析した命令に応じて数値をグローバル変数に格納する関数	下の関数の続きみたいな
void receive_order_depot( int target_box , char *storage_str , int minus_flag , int after_point_count , int large_size_flag )
{
    float value = 0.000;

    value = change_float(storage_str);

    if(minus_flag == 1){
        value *= ( -1.000 );
    }

    value = value * pow( 0.100, after_point_count );

    if( (target_box >= 0) && (target_box <= 25) ){
        if(large_size_flag == 0){
            g_atoz_value[target_box] = value;
        }else{
            g_AtoZ_value[target_box] = value;
        }
    }
}

void receive_order_c(char character)
{
    static int target_box = 255;										//格納命令の開始文字(ASCIIコードのa～z,A～Z)
    static char storage_str[RECEIVE_STR_COLUMN] = "";	//文字の格納用の文字列
    static int storage_num = 0;											//文字を文字列のどこに格納するか
    static int minus_flag = 0;											//マイナス値か否か
    static int point_flag = 0;							 					//小数点以下が含まれているか否か
    static int after_point_count = 0;					 				//小数点以下にどれだけ数があるか
    static int large_size_flag = 0;										//大文字なのか否か
    int reset = 0;										 						//処理のリセットをするか否か
	const char end = EN;								 				//格納命令の終了文字

    if(character == end){
            storage_str[storage_num] = '\0';
            receive_order_depot(target_box, storage_str, minus_flag, after_point_count, large_size_flag);
            reset = 1;
            target_box = 255;
            large_size_flag = 0;
    }else{
        if( (character >= '0') && (character <= '9') ){
            storage_str[storage_num] = character;
            storage_num++;
            if( point_flag == 1 ){
                after_point_count++;
            }
        }else if( (character >= 'a') && (character <= 'z') ){
            reset = 1;
            target_box = (int)(character - 'a');
            large_size_flag = 0;
        }else if( (character >= 'A') && (character <= 'Z') ){
            reset = 1;
            target_box = (int)(character - 'A');
            large_size_flag = 1;
        }else if( character == '-' ){
            minus_flag = 1;
        }else if( character == '.' ){
            point_flag = 1;
        }
    }

    if( reset == 1 ){
       strcpy(storage_str,"");
       storage_num = 0;
       minus_flag = 0;
       point_flag = 0;
       after_point_count = 0;
    }
}

//文字列をfloat型に変換	この関数はロボティクスのマイコンの授業で配られたやつですね
float change_float(char *str)
{
    float n = 0;
    int i = 0;
    while(str[i]!='\0')
    {
        if(str[i]<'0' || str[i]>'9') break;
        n=n*10+str[i]-'0';
        i++;
    }
	return(n);
}

char Receive_usart1_c(void)
{
	char i ='\0';

	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
		i = USART_ReceiveData(USART1); //受信したデータ読み込み
	}

	return i;
}

char receive_usart2_c(void)
{
	char i ='\0';

	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET){
		i = USART_ReceiveData(USART2); //受信したデータ読み込み
	}

	return i;
}

char receive_usart3_c(void)
{
	char i = '\0';

	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET){
		i = USART_ReceiveData(USART3); //受信したデータ読み込み
	}

	return i;
}

float get_atoz_value(int i)
{
	return g_atoz_value[i];
}

float get_AtoZ_value(int i)
{
	return g_AtoZ_value[i];
}
